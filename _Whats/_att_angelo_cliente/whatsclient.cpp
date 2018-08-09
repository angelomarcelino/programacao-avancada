#include "whatsclient.h"
#include "ui_whatsclient.h"
#include "mysocket.h"
#include "dados_cliente.h"
#include "dados_whatsprog.h"
#include <QMessageBox>
#include <QObject>
#include <algorithm>

extern tcp_mysocket sock;
extern HANDLE th_id;
extern WhatsClient* pt_w;
extern DadosCliente DC;


WhatsClient::WhatsClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WhatsClient)
{
    ui->setupUi(this);

    // Largura das colunas da tabela de msg e conversas
    ui->msgsTable->setColumnWidth(0,480);
    ui->conversasTable->setColumnWidth(0,50);

    // Cabecalhos da tabela de msg e conversas
    ui->msgsTable->setStyleSheet("QHeaderView::section { background-color:lightgray }");
    ui->msgsTable->setHorizontalHeaderLabels(QStringList() << "Mensagem" << "status");
    ui->conversasTable->setStyleSheet("QHeaderView::section { background-color:lightgray }");
    ui->conversasTable->setHorizontalHeaderLabels(QStringList() << "Lidas" << "Conversas");

    // Status
    ipServidor = new QLabel;
    Login = new QLabel;
    Corresp = new QLabel;
    statusBar()->insertWidget(0,new QLabel("Servidor: "));
    statusBar()->insertWidget(1,ipServidor);
    statusBar()->insertWidget(2,new QLabel("   Login: "));
    statusBar()->insertWidget(3,Login);
    statusBar()->insertWidget(4,new QLabel("   Correspondente: "));
    statusBar()->insertWidget(5,Corresp);

    // Conexões
    connect(this, SIGNAL(interfaceConectada(void)), this, SLOT(slotinterfaceConectada(void)));
    connect(this, SIGNAL(interfaceDesconectada()), this, SLOT(slotinterfaceDesconectada()));
    connect(this, SIGNAL(RedesenhaConversas()), this, SLOT(slotRedesenhaConversas()));
    connect(this, SIGNAL(RedesenhaMsgs()), this, SLOT(slotRedesenhaMsgs()));
    connect(this, SIGNAL(MsgErro(QString)), this, SLOT(slotMsgErro(QString)));

    // Coloca a interface no modo desconectado
    slotinterfaceDesconectada();
}

WhatsClient::~WhatsClient()
{
    delete ui;
}

void WhatsClient::slotinterfaceDesconectada()
{
    connected = false;
    ui->msgEdit->setEnabled(false);
    ui->enviarButton->setEnabled(false);
    ui->actionApagar->setEnabled(false);
    ui->actionDesconectar->setEnabled(false);
    ui->actionNovaConv->setEnabled(false);

    ui->actionConectar->setEnabled(true);
    ui->conversasTable->clearContents();
    ui->msgsTable->clearContents();
    ipServidor->setText("--");
    Login->setText("--");
    Corresp->setText("--");
    DC.clearConversas();
    DC.clearServidorUsuario();
}

void WhatsClient::slotinterfaceConectada()
{
    connected = true;
    ui->msgEdit->setEnabled(true);
    ui->enviarButton->setEnabled(true);
    ui->actionApagar->setEnabled(true);
    ui->actionDesconectar->setEnabled(true);
    ui->actionNovaConv->setEnabled(true);

    ui->actionConectar->setEnabled(false);

    emit RedesenhaConversas();
    emit RedesenhaMsgs();

    ipServidor->setText(QString::fromStdString(DC.getServidor()));
    Login->setText(QString::fromStdString(DC.getMeuUsuario()));
    Corresp->setText(QString::fromStdString(DC[DC.getIndexConversaAtual()].getCorrespondente()));
}

void WhatsClient::slotRedesenhaConversas()
{
    ui->conversasTable->clearContents();
    ui->conversasTable->setRowCount(DC.size());

    for(unsigned i=0; i<DC.size(); i++)
    {
        //Lidas
        QLabel *prov;
        prov = new QLabel;
        prov->setText(QString::number(DC[i].getNumMsgsEntregues())+"/"+QString::number(DC[i].size()));

        cout << DC[i].getNumMsgsEntregues() << "/" << DC[i].size() << endl;

        prov->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        if (DC[i].getNumMsgsEntregues()!=0) prov->setStyleSheet("background: rgb(200, 255, 200)");
        if ((int)i == DC.getIndexConversaAtual()) prov->setStyleSheet("background: rgb(0, 161, 241)");
        if((int)i != DC.getIndexConversaAtual() && DC[i].getNumMsgsEntregues()==0) prov->setStyleSheet("background: rgb(255,255,255)");
        ui->conversasTable->setCellWidget(i,0,prov);

        //Correspondente
        prov = new QLabel;
        prov->setText(QString::fromStdString(DC[i].getCorrespondente()));
        prov->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        if (DC[i].getNumMsgsEntregues()!=0) prov->setStyleSheet("background: rgb(200, 255, 200)");
        if ((int)i == DC.getIndexConversaAtual()) prov->setStyleSheet("background: rgb(0, 161, 241)");
        if((int)i != DC.getIndexConversaAtual() && DC[i].getNumMsgsEntregues()==0) prov->setStyleSheet("background: rgb(255,255,255)");
        ui->conversasTable->setCellWidget(i,1,prov);
    }

}

void WhatsClient::slotRedesenhaMsgs()
{
    ui->msgsTable->clearContents();
    ui->msgsTable->setRowCount(DC[DC.getIndexConversaAtual()].size());

    int atual = DC.getIndexConversaAtual();
    for(unsigned i=0; i<DC[atual].size(); i++)
    {
        // Mensagem
        QLabel *prov;
        prov = new QLabel;
        prov->setText(QString::fromStdString(DC[atual][i].getTexto()));
        if (DC[atual][i].getRemetente()==DC.getMeuUsuario())
        {
            prov->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            prov->setStyleSheet("background: rgb(200,255,200)");
        }
        if (DC[atual][i].getRemetente()==DC[atual].getCorrespondente())
        {
            prov->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            prov->setStyleSheet("background: rgb(255,255,255)");
        }
        ui->msgsTable->setCellWidget(i,0,prov);

        //Status
        if (DC[atual][i].getRemetente() == DC.getMeuUsuario())
        {
            prov = new QLabel;
            prov->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            if (DC[atual][i].getStatus() == MSG_ENVIADA)
            {
                prov->setText("?");
                prov->setStyleSheet("background: rgb(255,255,255)");
            }
            if (DC[atual][i].getStatus() == MSG_RECEBIDA)
            {
                prov->setText("V");
                prov->setStyleSheet("background: rgb(215, 210, 235)");
            }
            if (DC[atual][i].getStatus() == MSG_ENTREGUE)
            {
                prov->setText("Vv");
                prov->setStyleSheet("background: rgb(215, 210, 235)");
            }
            if (DC[atual][i].getStatus() == MSG_LIDA)
            {
                prov->setText("Vv");
                prov->setStyleSheet("background: rgb(50, 150, 255)");
            }
            ui->msgsTable->setCellWidget(i,1,prov);
        }
    }
}

void WhatsClient::slotMsgErro(QString S)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Erro");
    msgBox.setText(S);
    msgBox.exec();
}

void WhatsClient::on_actionConectar_triggered()
{
    telaConnect.exec();
}

void WhatsClient::on_actionNovaConv_triggered()
{
    telaConversa.exec();
}

void WhatsClient::on_actionApagar_triggered() // Apagar Msgs
{
    int atual = DC.getIndexConversaAtual();
    if (DC[atual].getCorrespondente()=="" || DC.size()==0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erro");
        msgBox.setText("Nenhuma conversa selecionada");
        msgBox.exec();
        return;
    }
    else
    {
        DC[atual].clearMessages();
        emit RedesenhaMsgs();
        emit RedesenhaConversas();
    }
}

void WhatsClient::on_actionDesconectar_triggered()
{
    if (connected)
    {
        // Encerra o socket
        MYSOCKET_STATUS iResult;
        iResult = sock.write_int(CMD_LOGOUT_USER);
        if (iResult != SOCKET_ERROR)
        {
            sock.close();

            // Termina a thread de recepcao
            // Ao fechar o socket, a thread deve se encerrar e liberar os recursos
            // Portanto, nao deve ser necessario fazer o encerramento aqui
            // Coloca a interface no modo desconectado
            emit interfaceDesconectada();
        }
        else // Erro no envio do comando
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Erro no envio");
            msgBox.setText("Nao foi possivel enviar o comando de lougout");
            msgBox.exec();
        }
    }
    emit interfaceDesconectada();
}

void WhatsClient::on_actionSair_triggered()
{
    on_actionDesconectar_triggered();
    QCoreApplication::quit();
}

void WhatsClient::on_enviarButton_clicked() // Envio de mensagem
{
    int atual = DC.getIndexConversaAtual();
    if (DC.size()==0 || DC[atual].getCorrespondente()=="")
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erro");
        msgBox.setText("Antes de enviar alguma mensagem, \n"
                       "adicione uma conversa");
        msgBox.exec();
        if(DC.size()==0) telaConversa.exec();
        return;
    }
    QString remet = QString::fromStdString(DC.getMeuUsuario());
    QString dest = QString::fromStdString(DC[atual].getCorrespondente());
    QString texto = ui->msgEdit->text();
    if (texto.size()>TAM_MAX_MSG || texto.size()==0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erro");
        msgBox.setText("Mensagem muito grande ou vazia");
        msgBox.exec();
        return;
    }

    Mensagem M;
    M.setRemetente(remet.toStdString());
    M.setDestinatario(dest.toStdString());
    M.setTexto(texto.toStdString());
    M.setId(DC.getNovaIdMensagem());

    MYSOCKET_STATUS iResult;
    // Envio ao servidor
    if (connected)
    {
        iResult = sock.write_int(CMD_NOVA_MSG);
        if (iResult != SOCKET_ERROR)
        {
            iResult = sock.write_int(M.getId());
            if(iResult != SOCKET_ERROR)
            {
                iResult = sock.write_string(M.getDestinatario());
                if (iResult != SOCKET_ERROR)
                {
                    iResult = sock.write_string(M.getTexto());
                    if (iResult != SOCKET_ERROR) // tudo deu certo
                    {
                        M.setStatus(MSG_ENVIADA);
                        DC[atual].pushMessage(M);
                        /*cout << CMD_NOVA_MSG << " Enter clicado "
                             << DC[id_conv][DC[id_conv].size()-1].getTexto() << " "
                             << DC[id_conv][DC[id_conv].size()-1].getRemetente() << " "
                             << DC[id_conv][DC[id_conv].size()-1].getDestinatario() << " "
                             << DC[id_conv][DC[id_conv].size()-1].getId() << " "
                             << DC[id_conv][DC[id_conv].size()-1].getStatus() << endl;*/
                        emit RedesenhaMsgs();
                    }
                    else // erro de msg
                    {
                        sock.close();
                        emit interfaceDesconectada();

                        QMessageBox msgBox;
                        msgBox.setWindowTitle("Erro no envio");
                        msgBox.setText("Nao foi possivel enviar texto "+texto);
                        msgBox.exec();
                    }
                }
                else // erro de dest
                {
                    sock.close();
                    emit interfaceDesconectada();

                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Erro no envio");
                    msgBox.setText("Nao foi possivel enviar destinatario"+dest);
                    msgBox.exec();
                }
            }
            else // erro de id
            {
                sock.close();
                emit interfaceDesconectada();

                QMessageBox msgBox;
                msgBox.setWindowTitle("Erro no envio");
                msgBox.setText("Nao foi possivel enviar id "+
                               QString::number(M.getId())+" da msg");
                msgBox.exec();
            }
        }
        else // CMD erro
        {
            sock.close();
            emit interfaceDesconectada();

            QMessageBox msgBox;
            msgBox.setWindowTitle("Erro");
            msgBox.setText("Erro ao enviar o comando");
            msgBox.exec();
        }
    }
    else // O Cliente n ta conectado
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erro");
        msgBox.setText("O cliente não está conectado a um servidor");
        msgBox.exec();
    }

    emit RedesenhaConversas();
    ui->msgEdit->clear();
}

void WhatsClient::on_msgEdit_returnPressed() // Envio com enter
{
    QString text = ui->msgEdit->text();
    if (text.size()>0)
    {
        on_enviarButton_clicked();
    }
}

void WhatsClient::on_conversasTable_cellClicked(int row, int column)// Le as msgs
{
    if (column > ui->conversasTable->columnCount()) return;
    DC.setIndexConversaAtual(row);
    Corresp->setText(QString::fromStdString(DC[DC.getIndexConversaAtual()].getCorrespondente()));

    unsigned teste;
    testRemetStatus parametro(DC[row].getCorrespondente(), MSG_ENTREGUE);
    teste = std::count(DC[row].begin(), DC[row].end(), parametro);

    if (DC[row].getNumMsgsEntregues() != teste) cerr << "ERRO N SEI OQ TA CONTECENO\n";

    MYSOCKET_STATUS iResult;
    Citr_Msg itrM = DC[row].begin();

    for (unsigned i = 0; i < DC[row].getNumMsgsEntregues(); i++)
    {
        itrM = std::find(itrM, DC[row].end(), parametro);
        if (itrM != DC[row].end())
        {
            i++;
            if (connected)
            {
                DC[row][itrM - DC[row].begin()].setStatus(MSG_LIDA); // GAMBIARRA
                iResult = sock.write_int(CMD_MSG_LIDA1);
                if (iResult != SOCKET_ERROR)
                {
                    iResult = sock.write_int(itrM->getId());
                    if (iResult != SOCKET_ERROR)
                    {
                        iResult = sock.write_string(itrM->getRemetente());
                        if (iResult != SOCKET_ERROR)
                        {
                            std::cout << "Mensagem '" << itrM->getTexto() << "' "
                            << itrM->getId() << " " << itrM->getDestinatario() << " "
                            << itrM->getRemetente() << " " << itrM->getStatus() << " "
                            << " informada ao servidor que foi visualizada.\n";
                        }
                        else // erro no envio do remetente
                        {
                            QMessageBox msgBox;
                            msgBox.setWindowTitle("Erro no envio");
                            msgBox.setText("Nao foi possivel enviar remetente"
                                           + QString::fromStdString(itrM->getRemetente()));
                            msgBox.exec();
                        }
                    }
                    else //erro no envio do id
                    {
                        QMessageBox msgBox;
                        msgBox.setWindowTitle("Erro no envio");
                        msgBox.setText("Nao foi possivel enviar id");
                        msgBox.exec();
                    }
                }
                else // erro no envio do cmd
                {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Erro no envio");
                    msgBox.setText("Nao foi possivel enviar cmd");
                    msgBox.exec();
                }
            }
            else // Nao conectado
            {
                QMessageBox msgBox;
                msgBox.setWindowTitle("Erro");
                msgBox.setText("Cliente nao conectado!");
                msgBox.exec();
            }
            itrM++;
        }
    }

    emit RedesenhaMsgs();
    emit RedesenhaConversas();

}

