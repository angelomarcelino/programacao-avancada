#include "mensageiro2_cliente.h"
#include "ui_mensageiro2_cliente.h"
#include "mysocket.h"
#include <QMessageBox>

// Variaveis globais
extern tcp_mysocket sock;
extern HANDLE th_id;

Mensageiro2_Cliente::Mensageiro2_Cliente(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Mensageiro2_Cliente)
{
  ui->setupUi(this);

  // Largura das colunas da tabela de msg
  ui->msgTable->setColumnWidth(0,140);
  ui->msgTable->setColumnWidth(1,502);
  ui->msgTable->setColumnWidth(2,140);

  // Cabecalhos da tabela de msg
  ui->msgTable->setStyleSheet("QHeaderView::section { background-color:lightgray }");
  ui->msgTable->setHorizontalHeaderLabels(QStringList() << "REMETENTE" << "MENSAGEM" << "DESTINATARIO");

  // Widgets da barra de status
  statusBar()->insertWidget(0,new QLabel("Servidor: "));
  statusBar()->insertWidget(1,&ipServidor);
  statusBar()->insertWidget(2,new QLabel("   Login: "));
  statusBar()->insertWidget(3,&myLogin);

  // Coloca a interface no modo desconectado
  interface_desconectado();
}

Mensageiro2_Cliente::~Mensageiro2_Cliente()
{
  delete ui;
}

// Coloca a interface no modo conectado
void Mensageiro2_Cliente::interface_conectado(QString servidor, QString login)
{
  // Habilita o envio de msgs
  ui->userEdit->setEnabled(true);
  ui->msgEdit->setEnabled(true);
  ui->enviarButton->setEnabled(true);

  // Desabilita a acao de conectar
  ui->actionConectar->setEnabled(false);
  // Habilita a acao de desconectar
  ui->actionDesconectar->setEnabled(true);

  //Barra de status
  ipServidor.setText(servidor);
  myLogin.setText(login);

  // Usuario conectado
  connected = true;
}

// Coloca a interface no modo desconectado
void Mensageiro2_Cliente::interface_desconectado()
{
  // Usuario desconectado
  connected = false;

  // Desabilita o envio de msgs
  ui->userEdit->setEnabled(false);
  ui->msgEdit->setEnabled(false);
  ui->enviarButton->setEnabled(false);

  // Habilita a acao de conectar
  ui->actionConectar->setEnabled(true);
  // Desabilita a acao de desconectar
  ui->actionDesconectar->setEnabled(false);

  //Barra de status
  ipServidor.setText("NAO CONECTADO");
  myLogin.setText("NAO DEFINIDO");
}

void Mensageiro2_Cliente::adicionar_msg_enviada(QString dest, QString msg)
{
  // Incrementa o numero de linhas da tabela de msgs
  int nMsg = ui->msgTable->rowCount();
  nMsg++;
  ui->msgTable->setRowCount(nMsg);

  // Cria os conteudos da nova linha
  QTableWidgetItem *prov;
  // O remetente
  prov = new QTableWidgetItem(myLogin.text());
  prov->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  prov->setBackground(QBrush(QColor(200,255,200)));
  ui->msgTable->setItem(nMsg-1,0,prov);
  // A mensagem
  prov = new QTableWidgetItem(msg);
  prov->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
  prov->setBackground(QBrush(QColor(200,255,200)));
  ui->msgTable->setItem(nMsg-1,1,prov);
  // O destinatario
  prov = new QTableWidgetItem(dest);
  prov->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
  prov->setBackground(QBrush(QColor(200,255,200)));
  ui->msgTable->setItem(nMsg-1,2,prov);
}

void Mensageiro2_Cliente::adicionar_msg_recebida(QString remet, QString msg)
{
  // Incrementa o numero de linhas da tabela de msgs
  int nMsg = ui->msgTable->rowCount();
  nMsg++;
  ui->msgTable->setRowCount(nMsg);

  // Cria os conteudos da nova linha
  QTableWidgetItem *prov;
  // O remetente
  prov = new QTableWidgetItem(remet);
  prov->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  prov->setBackground(QBrush(QColor(255,255,255)));
  ui->msgTable->setItem(nMsg-1,0,prov);
  // A mensagem
  prov = new QTableWidgetItem(msg);
  prov->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  prov->setBackground(QBrush(QColor(255,255,255)));
  ui->msgTable->setItem(nMsg-1,1,prov);
  // O destinatario
  prov = new QTableWidgetItem(myLogin.text());
  prov->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
  prov->setBackground(QBrush(QColor(255,255,255)));
  ui->msgTable->setItem(nMsg-1,2,prov);
}

void Mensageiro2_Cliente::on_actionSair_triggered()
{
  QCoreApplication::quit();
}

void Mensageiro2_Cliente::on_actionConectar_triggered()
{
  if (!connected)
  {
    connectServer.show();
  }
}

void Mensageiro2_Cliente::on_actionApagar_triggered()
{
   ui->msgTable->clearContents();
   ui->msgTable->setRowCount(0);
}

void Mensageiro2_Cliente::on_actionDesconectar_triggered()
{
  if (connected)
  {
    // Encerra o socket
    sock.close();

    // Termina a thread de recepcao
    // Ao fechar o socket, a thread deve se encerrar e liberar os recursos
    // Portanto, nao deve ser necessario fazer o encerramento aqui
    /*
    if (th_id != NULL)
    {
      // Espera pelo fim da thread de recepcao (máximo de 5 segundos)
      WaitForSingleObject(th_id, 5000);
      // Encerra na forca bruta a thread de recepcao caso ela nao tenha terminado sozinha
      TerminateThread(th_id,0);
      // Encerra o handle da thread
      CloseHandle(th_id);
      th_id = NULL;
    }
    */

    // Coloca a interface no modo desconectado
    interface_desconectado();
  }
}

void Mensageiro2_Cliente::on_enviarButton_clicked()
{
  QString destinatario = ui->userEdit->text();
  QString msg = ui->msgEdit->text();
  MYSOCKET_STATUS iResult;

  if (connected)
  {
    if (msg.size()>0 && destinatario.size()>=4 && destinatario.size()<=16)
    {
      iResult = sock.write_string(destinatario.toStdString());
      if ( iResult != SOCKET_ERROR )
      {
        iResult = sock.write_string(msg.toStdString());
        if ( iResult != SOCKET_ERROR )
        {
          adicionar_msg_enviada(destinatario,msg);
        }
        else
        {
          sock.close();
          interface_desconectado();

          // Emitir msg de erro: nao foi possivel enviar texto
          QMessageBox msgBox;
          msgBox.setWindowTitle("Erro no envio");
          msgBox.setText("Nao foi possivel enviar texto "+msg);
          msgBox.exec();
        }
      }
      else
      {
        sock.close();
        interface_desconectado();

        // Emitir msg de erro: nao foi possivel enviar nome de destinatario
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erro no envio");
        msgBox.setText("Nao foi possivel enviar nome de destinatario "+destinatario);
        msgBox.exec();
      }
    }
    else
    {
      // Emitir msg de erro: dado(s) invalido(s)
      QMessageBox msgBox;
      msgBox.setWindowTitle("Erro no envio");
      msgBox.setText("Valor invalido de mensagem ("+msg+") e/ou destinatario ("+destinatario+")");
      msgBox.exec();
    }
  }
}
