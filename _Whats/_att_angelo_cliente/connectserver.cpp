#include "connectserver.h"
#include "ui_connectserver.h"
#include <string>
#include "whatsclient.h"
#include "mysocket.h"
#include "dados_cliente.h"
#include "dados_whatsprog.h"
#include <QMessageBox>

extern tcp_mysocket sock;
extern HANDLE th_id;
extern WhatsClient* pt_w;
extern DadosCliente DC;

using namespace std;

DWORD WINAPI le_msg(LPVOID lpParameter)
{
    if(lpParameter!=NULL) lpParameter = NULL;

    MYSOCKET_STATUS iResult;
    int32_t cmd;

    int32_t id_msg;
    int ind_conv, ind_msg;
    string remetente;
    string msg;

    while(sock.connected())
    {
        iResult = sock.read_int(cmd);
        if (iResult != SOCKET_ERROR)
        {
            switch (cmd) {
            case CMD_NEW_USER:
            case CMD_LOGIN_USER:
            case CMD_MSG_LIDA1:
            case CMD_LOGOUT_USER:
            default:
            {
                emit pt_w->MsgErro("Comando errado ou nao implementado recebido do servidor.\n");
                break;
            }
            case CMD_LOGIN_OK:
            {
                emit pt_w->interfaceConectada();
                if(sock.connected())
                {
                    emit pt_w->MsgErro("Conexão estabelecida corretamente "
                                                        + QString::fromStdString(DC.getServidor()+" "+DC.getMeuUsuario()));
                    cout << "Conexao estabelecida corretamente \n";
                }
                break;
            }
            case CMD_LOGIN_INVALIDO:
            {
                emit pt_w->MsgErro("Erro do login recebido pelo servidor\n"
                                   + QString::fromStdString(DC.getServidor()+" "+DC.getMeuUsuario()));
                emit pt_w->interfaceDesconectada();
                sock.close();
                break;
            }
            case CMD_NOVA_MSG:
            {
                iResult = sock.read_int(id_msg);
                if (iResult != SOCKET_ERROR)
                {
                    Mensagem M;
                    M.setId(id_msg);
                    iResult = sock.read_string(remetente);
                    if (iResult != SOCKET_ERROR )
                    {
                        M.setRemetente(remetente);
                        M.setDestinatario(DC.getMeuUsuario());
                        int id_conv = DC.getIndexConversa(remetente);
                        if(id_conv < 0 ) // Nova conversa
                        {
                            if(DC.insertConversa(remetente))
                            {
                                id_conv = DC.getIndexConversa(remetente);
                                iResult = sock.read_string(msg);
                                if (iResult < 0 ) emit pt_w->MsgErro("Erro ao receber txt de uma msg");
                                else
                                {
                                    M.setTexto(msg);
                                    M.setStatus(MSG_ENTREGUE);
                                    DC[id_conv].pushMessage(M);
                                    cout << CMD_NOVA_MSG << " "
                                         << DC[id_conv][DC[id_conv].size()-1].getTexto() << " "
                                         << DC[id_conv][DC[id_conv].size()-1].getRemetente() << " "
                                         << DC[id_conv][DC[id_conv].size()-1].getDestinatario() << " "
                                         << DC[id_conv][DC[id_conv].size()-1].getId() << " "
                                         << DC[id_conv][DC[id_conv].size()-1].getStatus() << endl;
                                    emit pt_w->RedesenhaConversas();
                                }
                            }
                            else // Nao inseriu nv conversa
                            {
                                emit pt_w->MsgErro("Erro ao criar conversa");
                            }
                        }
                        else // Conversa ja existente
                        {
                            iResult = sock.read_string(msg);
                            if (iResult < 0 ) emit pt_w->MsgErro("Erro ao receber txt de uma msg");
                            else
                            {
                                M.setTexto(msg);
                                M.setStatus(MSG_RECEBIDA);
                                DC[id_conv].pushMessage(M);
                                emit pt_w->RedesenhaConversas();
                                if(id_conv == DC.getIndexConversaAtual())
                                {
                                    id_msg = DC[id_conv].size()-1;
                                    DC[id_conv][id_msg].setStatus(MSG_LIDA);
                                    iResult = sock.write_int(CMD_MSG_LIDA1);
                                    if(iResult != SOCKET_ERROR)
                                    {
                                        cout << "1005 Enviou MSG_LIDA_1\n";
                                        iResult = sock.write_int(DC[id_conv][id_msg].getId());
                                        if(iResult != SOCKET_ERROR)
                                        {
                                            cout << "1005 Enviou ID\n";
                                            iResult = sock.write_string(DC[id_conv][id_msg].getRemetente());
                                            if (iResult != SOCKET_ERROR) cout << "1005 Enviou Remet\n";
                                            else cerr << "1005 Erro no envio de remet\n";
                                        }
                                        else cerr << "1005 Erro no envio Id\n";
                                    }
                                    else cerr << "1005 Erro no envio MSG_LIDA_1\n";
                                    emit pt_w->RedesenhaMsgs();
                                }
                            }
                        }
                    }
                    else cerr << "1005 Erro ao receber usuário de uma msg\n";
                }
                else // Erro ao receber Id
                {
                    emit pt_w->MsgErro("Erro ao receber Id de msg");
                }
                break;
            }
            case CMD_MSG_RECEBIDA:
            {
                iResult = sock.read_int(id_msg);
                if (iResult != SOCKET_ERROR)
                {
                    /*DC.findIndexMensagem(id_msg, ind_conv, ind_msg);

                    if(ind_conv >= 0 && ind_msg >=0 )
                    {
                        if(DC[ind_conv][ind_msg].getRemetente() == DC.getMeuUsuario())
                        {
                           if(DC[ind_conv][ind_msg].getStatus() == MSG_ENVIADA)
                           {
                               DC[ind_conv][ind_msg].setStatus(MSG_RECEBIDA);
                               if (ind_conv == DC.getIndexConversaAtual())
                               {
                                   emit pt_w->RedesenhaMsgs();
                               }
                               cout << CMD_MSG_RECEBIDA << " "
                                    << DC[ind_conv][DC[ind_conv].size()-1].getTexto() << " "
                                    << DC[ind_conv][DC[ind_conv].size()-1].getRemetente() << " "
                                    << DC[ind_conv][DC[ind_conv].size()-1].getDestinatario() << " "
                                    << DC[ind_conv][DC[ind_conv].size()-1].getId() << " "
                                    << DC[ind_conv][DC[ind_conv].size()-1].getStatus() << endl;
                           }
                           else cerr << "1006 Status de msg diferente de MSG_enviada ou recebida ou entregue\n";
                        }
                        else cerr << "1006 Remetente de msg diferente de myUser\n";
                    }
                    else cerr << "1006 Misterio: MSG Nao encontrada\n"; */
                    bool achou(false);
                    Citr_Msg itr = DC[0].end();
                    for(unsigned idC=0; (idC<DC.size())&&(itr==DC[idC].end()); idC++)
                    {
                        itr = std::find(DC[idC].begin(), DC[idC].end(), testRemetId(DC.getMeuUsuario(),id_msg));
                        if(itr!=DC[idC].end())
                        {
                            if(itr->getStatus()==MSG_ENVIADA)
                            {
                                achou = true;
                                DC[idC][itr - DC[idC].begin()].setStatus(MSG_RECEBIDA);
                                if ((int)idC==DC.getIndexConversaAtual())
                                {
                                    emit pt_w->RedesenhaMsgs();
                                }
                                cout << CMD_MSG_RECEBIDA << " " << "DEU CERTO "
                                     << DC[idC][itr - DC[idC].begin()].getTexto() << " "
                                     << DC[idC][itr - DC[idC].begin()].getRemetente() << " "
                                     << DC[idC][itr - DC[idC].begin()].getDestinatario() << " "
                                     << DC[idC][itr - DC[idC].begin()].getId() << " "
                                     << DC[idC][itr - DC[idC].begin()].getStatus() << endl;
                            }
                            else cerr << "1006 msg com status errado\n";
                        }
                        else cerr << "1006 nao ta na conversa" << idC << endl;
                    }
                    if (!achou) cerr << "1006 nao achou\n";
                }
                else // Erro ao receber ID
                {
                    cerr << "1006 Erro ao receber id\n";
                }
                break;
            }
            case CMD_MSG_ENTREGUE:
            {
                iResult = sock.read_int(id_msg);
                if (iResult != SOCKET_ERROR)
                {
                    /*DC.findIndexMensagem(id_msg, ind_conv, ind_msg);
                    if(ind_conv >= 0 && ind_msg >=0 )
                    {
                        if(DC[ind_conv][ind_msg].getRemetente() == DC.getMeuUsuario())
                        {
                           if(DC[ind_conv][ind_msg].getStatus() == MSG_ENVIADA
                             || DC[ind_conv][ind_msg].getStatus() == MSG_RECEBIDA)
                           {
                               DC[ind_conv][ind_msg].setStatus(MSG_ENTREGUE);
                               if (ind_conv == DC.getIndexConversaAtual())
                               {
                                   emit pt_w->RedesenhaMsgs();
                               }
                               cout << CMD_MSG_ENTREGUE << " "
                                    << DC[ind_conv][DC[ind_conv].size()-1].getTexto() << " "
                                    << DC[ind_conv][DC[ind_conv].size()-1].getRemetente() << " "
                                    << DC[ind_conv][DC[ind_conv].size()-1].getDestinatario() << " "
                                    << DC[ind_conv][DC[ind_conv].size()-1].getId() << " "
                                    << DC[ind_conv][DC[ind_conv].size()-1].getStatus() << endl;
                           }
                           else cerr << "1007 Status de msg diferente de MSG_enviada ou recebida ou entregue\n";
                        }
                        else cerr << "1007 Remetente de msg diferente de myUser\n";
                    }
                    else cerr << "1007 Misterio: MSG Nao encontrada\n"; */
                    bool achou(false);
                    Citr_Msg itr = DC[0].end();
                    for(unsigned idC=0; (idC<DC.size())&&(itr==DC[idC].end()); idC++)
                    {
                        itr = std::find(DC[idC].begin(), DC[idC].end(), testRemetId(DC.getMeuUsuario(),id_msg));
                        if(itr!=DC[idC].end())
                        {
                            if(itr->getStatus()==MSG_ENVIADA
                               ||itr->getStatus()==MSG_RECEBIDA)
                            {
                                achou = true;
                                DC[idC][itr - DC[idC].begin()].setStatus(MSG_ENTREGUE);
                                if ((int)idC==DC.getIndexConversaAtual())
                                {
                                    emit pt_w->RedesenhaMsgs();
                                }
                                cout << CMD_MSG_ENTREGUE << " " << "DEU CERTO "
                                     << DC[idC][itr - DC[idC].begin()].getTexto() << " "
                                     << DC[idC][itr - DC[idC].begin()].getRemetente() << " "
                                     << DC[idC][itr - DC[idC].begin()].getDestinatario() << " "
                                     << DC[idC][itr - DC[idC].begin()].getId() << " "
                                     << DC[idC][itr - DC[idC].begin()].getStatus() << endl;
                            }
                            else cerr << "1007 msg com status errado\n";
                        }
                        else cerr << "1007 nao ta na conversa" << idC << endl;
                    }
                    if (!achou) cerr << "1007 nao achou\n";
                }
                else // Erro ao receber ID
                {
                    cerr << "1007 Erro ao receber id\n";
                }
                break;
            }
            case CMD_MSG_LIDA2:
            {
                iResult = sock.read_int(id_msg);
                if (iResult != SOCKET_ERROR)
                {
                    /*DC.findIndexMensagem(id_msg, ind_conv, ind_msg);
                    if(ind_conv >= 0 && ind_msg >=0 )
                    {
                        if(DC[ind_conv][ind_msg].getRemetente() == DC.getMeuUsuario())
                        {
                           if(DC[ind_conv][ind_msg].getStatus() == MSG_ENVIADA
                             || DC[ind_conv][ind_msg].getStatus() == MSG_RECEBIDA
                             || DC[ind_conv][ind_msg].getStatus() == MSG_ENTREGUE)
                           {
                               DC[ind_conv][ind_msg].setStatus(MSG_LIDA);
                               if (ind_conv == DC.getIndexConversaAtual())
                               {
                                   emit pt_w->RedesenhaMsgs();
                               }
                               cout << CMD_MSG_LIDA2 << " "
                                    << DC[ind_conv][DC[ind_conv].size()-1].getTexto() << " "
                                    << DC[ind_conv][DC[ind_conv].size()-1].getRemetente() << " "
                                    << DC[ind_conv][DC[ind_conv].size()-1].getDestinatario() << " "
                                    << DC[ind_conv][DC[ind_conv].size()-1].getId() << " "
                                    << DC[ind_conv][DC[ind_conv].size()-1].getStatus() << endl;
                           }
                           else cerr << "1009 Status de msg diferente de MSG_enviada ou recebida ou entregue\n";
                        }
                        else cerr << "1009 Remetente de msg diferente de myUser\n";
                    }
                    else cerr << "1009 Misterio: MSG Nao encontrada\n";*/
                    bool achou(false);
                    Citr_Msg itr = DC[0].end();
                    for(unsigned idC=0; (idC<DC.size())&&(itr==DC[idC].end()); idC++)
                    {
                        itr = std::find(DC[idC].begin(), DC[idC].end(), testRemetId(DC.getMeuUsuario(),id_msg));
                        if(itr!=DC[idC].end())
                        {
                            if(itr->getStatus()==MSG_ENVIADA
                               ||itr->getStatus()==MSG_RECEBIDA
                               ||itr->getStatus()==MSG_ENTREGUE)
                            {
                                achou = true;
                                DC[idC][itr - DC[idC].begin()].setStatus(MSG_LIDA);
                                if ((int)idC==DC.getIndexConversaAtual())
                                {
                                    emit pt_w->RedesenhaMsgs();
                                }
                                cout << CMD_MSG_LIDA2 << " " << "DEU CERTO "
                                     << DC[idC][itr - DC[idC].begin()].getTexto() << " "
                                     << DC[idC][itr - DC[idC].begin()].getRemetente() << " "
                                     << DC[idC][itr - DC[idC].begin()].getDestinatario() << " "
                                     << DC[idC][itr - DC[idC].begin()].getId() << " "
                                     << DC[idC][itr - DC[idC].begin()].getStatus() << endl;
                            }
                            else cerr << "1009 msg com status errado\n";
                        }
                        else cerr << "1009 nao ta na conversa" << idC << endl;
                    }
                    if (!achou) cerr << "1009 nao achou\n";
                }
                else // Erro ao receber ID
                {
                    cerr << "1009 Erro ao receber id\n";
                }
                break;
            }
            case CMD_MSG_INVALIDA:
            case CMD_USER_INVALIDO:
            case CMD_ID_INVALIDA:
            {
                iResult = sock.read_int(id_msg);
                if (iResult != SOCKET_ERROR)
                {
                    DC.findIndexMensagem(id_msg, ind_conv, ind_msg);
                    if(ind_conv >= 0 && ind_msg >=0 )
                    {
                        if(DC[ind_conv][ind_msg].getRemetente() == DC.getMeuUsuario())
                        {
                            if(DC[ind_conv][ind_msg].getStatus() == MSG_ENVIADA)
                            {
                                DC[ind_conv].eraseMessage(ind_msg);
                                if (ind_conv == DC.getIndexConversaAtual())
                                {
                                    emit pt_w->RedesenhaMsgs();
                                }
                                if(cmd == CMD_ID_INVALIDA) emit pt_w->MsgErro("Id enviado ao servidor errado!");
                                if(cmd == CMD_MSG_INVALIDA) emit pt_w->MsgErro("Mensagem enviada ao servidor errada!");
                                if(cmd == CMD_USER_INVALIDO)
                                {
                                    emit pt_w->MsgErro("Destinatario enviado ao servidor errado!");
                                    DC.eraseConversa(ind_conv);
                                    emit pt_w->RedesenhaConversas();
                                    if (ind_conv == DC.getIndexConversaAtual())
                                    {
                                        emit pt_w->RedesenhaMsgs();
                                    }
                                }
                            }
                            else emit pt_w->MsgErro("Status de msg diferente de MSG_enviada ou recebida ou entregue");
                        }
                        else emit pt_w->MsgErro("Remetente de msg diferente de myUser");
                    }
                    else emit pt_w->MsgErro("Misterio: MSG Nao encontrada");
                }
                else // Erro ao receber ID
                {
                    emit pt_w->MsgErro("Erro ao receber id");
                }
                break;
            }
            }
        }
        else // Erro ao receber comando
        {
            if(sock.connected()) emit pt_w->MsgErro("Erro ao receber comando");
            sock.close();
        }
    }

    return 0;
}

connectServer::connectServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connectServer)
{
    ui->setupUi(this);
}

connectServer::~connectServer()
{
    delete ui;
}

void connectServer::on_buttonBox_accepted() //Login existente
{

    QString servidor = ui->servEdit->text();
    QString login = ui->logEdit->text();
    QString senha = ui->passEdit->text();

    MYSOCKET_STATUS iResult;
    // O numero IP de um servidor deve ter no minimo 7 caracteres
    // O nome de login deve ter entre 6 e 12 caracteres
    // A senha do user de ter entre 6 e 2 caracteres
    if (servidor.size()>=7 && login.size()>=TAM_MIN_NOME_USUARIO && login.size()<=TAM_MAX_NOME_USUARIO &&
        senha.size()>=TAM_MIN_SENHA && senha.size()<=TAM_MAX_SENHA)
    {
        if (sock.connect(servidor.toLatin1(), PORTA_WHATSPROG) == SOCKET_OK)
        {
            //Socket funfou
            th_id = CreateThread(NULL, 0, le_msg, NULL, 0, NULL);
            if (th_id != NULL)
            {
                //Thread workando
                iResult = sock.write_int(CMD_LOGIN_USER);
                if(iResult != SOCKET_ERROR)
                {
                    //Enviar e setar o Dado no cliente
                    DC.setServidorUsuario(servidor.toStdString(), login.toStdString());
                    iResult = sock.write_string(DC.getMeuUsuario());
                    if (iResult!=SOCKET_ERROR)
                    {
                        iResult = sock.write_string(senha.toStdString());
                        if(iResult!=SOCKET_ERROR) // Workou
                        {
                            emit pt_w->interfaceConectada();
                        }
                        else //erro no envio de senha
                        {
                            TerminateThread(th_id,0);
                            // Encerra o handle da thread
                            CloseHandle(th_id);
                            th_id = NULL;
                            sock.close();

                            // Emitir msg de erro: nao foi possivel enviar senha
                            QMessageBox msgBox;
                            msgBox.setWindowTitle("Erro na conexao");
                            msgBox.setText("Nao foi possivel enviar a senha");
                            msgBox.exec();
                        }
                    }
                    else //erro no envio do usuario
                    {
                        TerminateThread(th_id,0);
                        // Encerra o handle da thread
                        CloseHandle(th_id);
                        th_id = NULL;
                        sock.close();

                        // Emitir msg de erro: nao foi possivel enviar nome de login
                        QMessageBox msgBox;
                        msgBox.setWindowTitle("Erro na conexao");
                        msgBox.setText("Nao foi possivel enviar nome de login "+login);
                        msgBox.exec();
                    }
                }
                else //CMD nao workou
                {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Erro no servidor");
                    msgBox.setText("Erro ao enviar comando de login");
                    msgBox.exec();
                }
            }
            else //Thread n workou
            {
                sock.close();
                QMessageBox msgBox;
                msgBox.setWindowTitle("Erro na thread");
                msgBox.setText("Erro ao criar a thread de leitura");
                msgBox.exec();
            }
        }
        else //Socket nao funfou
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Erro na conexao");
            msgBox.setText("Erro ao conectar com o servidor "+servidor);
            msgBox.exec();
        }
    }
    else //Erro nos parametros
    {
        QString erro;
        if(servidor.size()<7) erro = "SERVIDOR";
        else if(login.size()<TAM_MIN_NOME_USUARIO || login.size()>TAM_MAX_NOME_USUARIO) erro = "LOGIN";
        else if(senha.size()<TAM_MIN_SENHA || senha.size()>TAM_MAX_SENHA) erro = "SENHA";
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erro na conexao");
        msgBox.setText("Erro no campo '"+erro+"'");
        msgBox.exec();
    }
}

void connectServer::on_cadastrarButton_clicked()
{

    QString servidor = ui->servEdit->text();
    QString login = ui->logEdit->text();
    QString senha = ui->passEdit->text();

    MYSOCKET_STATUS iResult;
    // O numero IP de um servidor deve ter no minimo 7 caracteres
    // O nome de login deve ter entre 6 e 12 caracteres
    // A senha do user de ter entre 6 e 2 caracteres
    if (servidor.size()>=7 && login.size()>=TAM_MIN_NOME_USUARIO && login.size()<=TAM_MAX_NOME_USUARIO &&
        senha.size()>=TAM_MIN_SENHA && senha.size()<=TAM_MAX_SENHA)
    {
        if (sock.connect(servidor.toLatin1(), PORTA_WHATSPROG) == SOCKET_OK)
        {
            //Socket funfou
            th_id = CreateThread(NULL, 0, le_msg, NULL, 0, NULL);
            if (th_id != NULL)
            {
                //Thread workando
                iResult = sock.write_int(CMD_NEW_USER);
                if(iResult != SOCKET_ERROR)
                {
                    //Enviar e setar o Dado no cliente
                    DC.setServidorUsuario(servidor.toStdString(), login.toStdString());
                    iResult = sock.write_string(DC.getMeuUsuario());
                    if (iResult!=SOCKET_ERROR)
                    {
                        iResult = sock.write_string(senha.toStdString());
                        if(iResult!=SOCKET_ERROR) // Deu certo
                        {
                            emit pt_w->interfaceConectada();
                        }
                        else //erro no envio de senha
                        {
                            TerminateThread(th_id,0);
                            // Encerra o handle da thread
                            CloseHandle(th_id);
                            th_id = NULL;
                            sock.close();

                            // Emitir msg de erro: nao foi possivel enviar senha
                            QMessageBox msgBox;
                            msgBox.setWindowTitle("Erro na conexao");
                            msgBox.setText("Nao foi possivel enviar a senha");
                            msgBox.exec();
                        }
                    }
                    else //erro no envio do usuario
                    {
                        TerminateThread(th_id,0);
                        // Encerra o handle da thread
                        CloseHandle(th_id);
                        th_id = NULL;
                        sock.close();

                        // Emitir msg de erro: nao foi possivel enviar nome de login
                        QMessageBox msgBox;
                        msgBox.setWindowTitle("Erro na conexao");
                        msgBox.setText("Nao foi possivel enviar nome de login "+login);
                        msgBox.exec();
                    }
                }
                else //CMD nao workou
                {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Erro no servidor");
                    msgBox.setText("Erro ao enviar comando de login");
                    msgBox.exec();
                }
            }
            else //Thread n workou
            {
                sock.close();
                QMessageBox msgBox;
                msgBox.setWindowTitle("Erro na thread");
                msgBox.setText("Erro ao criar a thread de leitura");
                msgBox.exec();
            }
        }
        else //Socket nao funfou
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Erro na conexao");
            msgBox.setText("Erro ao conectar com o servidor "+servidor);
            msgBox.exec();
        }
    }
    else //Erro nos parametros
    {
        QString erro;
        if(servidor.size()<7) erro = "SERVIDOR";
        else if(login.size()<TAM_MIN_NOME_USUARIO || login.size()>TAM_MAX_NOME_USUARIO) erro = "LOGIN";
        else if(senha.size()<TAM_MIN_SENHA || senha.size()>TAM_MAX_SENHA) erro = "SENHA";
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erro na conexao");
        msgBox.setText("Erro no campo '"+erro+"'");
        msgBox.exec();
    }
    this->close();
}
