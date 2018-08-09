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
        QTableWidgetItem *prov;
        prov = new QTableWidgetItem;
        prov->setText(QString::number(DC[i].getNumMsgsEntregues())+"/"+QString::number(DC[i].size()));
        prov->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        if (DC[i].getNumMsgsEntregues()>0) prov->setBackground(QBrush(QColor(200, 255, 200)));
        if ((int)i == DC.getIndexConversaAtual()) prov->setBackground(QBrush(QColor(0, 161, 241)));
        else prov->setBackground(QBrush(QColor(255,255,255)));
        ui->conversasTable->setItem(i,0,prov);

        //Correspondente
        prov = new QTableWidgetItem;
        prov->setText(QString::fromStdString(DC[i].getCorrespondente()));
        prov->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        if (DC[i].getNumMsgsEntregues()>0) prov->setBackground(QBrush(QColor(200, 255, 200)));
        if ((int)i == DC.getIndexConversaAtual()) prov->setBackground(QBrush(QColor(0, 161, 241)));
        else prov->setBackground(QBrush(QColor(255,255,255)));
        ui->conversasTable->setItem(i,1,prov);
    }

}

void WhatsClient::slotRedesenhaMsgs() // Fazer status
{
    ui->msgsTable->clearContents();
    ui->msgsTable->setRowCount(DC[DC.getIndexConversaAtual()].size());

    int atual = DC.getIndexConversaAtual();
    for(unsigned i=0; i<DC[atual].size(); i++)
    {
        // Mensagem
        QTableWidgetItem *prov;
        prov = new QTableWidgetItem;
        prov->setText(QString::fromStdString(DC[atual][i].getTexto()));
        if (DC[atual][i].getRemetente()==DC.getMeuUsuario())
        {
            prov->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            prov->setBackground(QBrush(QColor(200,255,200)));
        }
        if (DC[atual][i].getRemetente()==DC[atual].getCorrespondente())
        {
            prov->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            prov->setBackground(QBrush(QColor(255,255,255)));
        }
        ui->msgsTable->setItem(i,0,prov);

        //Status
    }
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
    M.setId(DC[atual].size()+1);
    M.setStatus(MSG_ENVIADA);

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
                        DC[atual].pushMessage(M);
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

void WhatsClient::on_conversasTable_cellClicked(int row, int column)// Altera o staus de visualizacao
{
    DC.setIndexConversaAtual(row);
    if (column > ui->conversasTable->columnCount()) return;
    Corresp->setText(QString::fromStdString(DC[DC.getIndexConversaAtual()].getCorrespondente()));

    testDestStatus coisa(DC[row].getCorrespondente(), MSG_ENTREGUE);

    itr_Msg itr;
    MYSOCKET_STATUS iResult;
    for (itr=DC[row].begin(); itr!=DC[row].end(); itr++)
    {
        itr = std::find(itr, DC[row].end(), coisa);
        if (itr != DC[row].end())
        {
            DC[row][itr->getId()].setStatus(MSG_LIDA); // GAMBIARRA
            if (connected)
            {
                iResult = sock.write_int(CMD_MSG_LIDA1);
                if (iResult != SOCKET_ERROR)
                {
                    iResult = sock.write_int(itr->getId());
                    if (iResult != SOCKET_ERROR)
                    {
                        iResult = sock.write_string(itr->getRemetente());
                        if (iResult != SOCKET_ERROR)
                        {
                            std::cout << "Mensagem '" << itr->getTexto()
                            << "' informada ao servidor que foi visualida.\n";
                        }
                        else // erro no envio do remetente
                        {
                            QMessageBox msgBox;
                            msgBox.setWindowTitle("Erro no envio");
                            msgBox.setText("Nao foi possivel enviar remetente"
                                           + QString::fromStdString(itr->getRemetente()));
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
        }
    }

    emit RedesenhaMsgs();
    emit RedesenhaConversas();

}

