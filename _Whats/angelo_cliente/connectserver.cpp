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
    string remetente;
    string msg;

    iter_Mensagem itr; // Perguntar sobre find

    while(sock.connected())
    {
        iResult = sock.read_int(cmd);
        switch (cmd) {
        case CMD_NEW_USER:
        case CMD_LOGIN_USER:
        case CMD_MSG_LIDA1:
        case CMD_LOGOUT_USER:
        default:
        {
            cerr << "Comando errado ou nao implementado recebido do servidor.\n";
            break;
        }
        case CMD_LOGIN_OK:
        {
            emit pt_w->interfaceConectada();
            cerr << "Conexão estabelecida corretamente "
                 << DC.getServidor() << DC.getMeuUsuario();
            break;
        }
        case CMD_LOGIN_INVALIDO:
        {
            cerr << "Conexão estabelecida corretamente "
                 << DC.getServidor() << DC.getMeuUsuario();
            emit pt_w->interfaceDesconectada();
            break;
        }
        case CMD_NOVA_MSG: //Fazer
        {
            iResult = sock.read_string(remetente);
            if (iResult < 0 ) cerr << "erro na recepcao do usr de uma msg";
            else
            {
                //itr = std::find()
            }
            break;
        }
        // Fazer o resto dos casos
        }
        //cout << "N=" << 5 << endl;
        //Sleep(2000);
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
