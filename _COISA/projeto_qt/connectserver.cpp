#include <string>
#include "connectserver.h"
#include "ui_connectserver.h"
#include "mensageiro2_cliente.h"
#include "mysocket.h"
#include "mensageiro.h"
#include <QMessageBox>

// Variaveis globais
extern tcp_mysocket sock;
extern HANDLE th_id;
extern Mensageiro2_Cliente* pt_w;

using namespace std;

DWORD WINAPI le_msg(LPVOID lpParameter)
{
  string remetente,msg;
  MYSOCKET_STATUS iResult;
  bool erro(false);

  // A linha a seguir nao serve de nada
  // Estah aih soh para que o compilador pare de emitir a advertencia de que
  // o parametro lpParameter nao eh utilizado para nada!!!
  if (lpParameter!=NULL) lpParameter = NULL;

  while (sock.connected())
  {
    iResult = sock.read_string(remetente);
    if (iResult > 0)
    {
      iResult = sock.read_string(msg);
      if (iResult > 0)
      {
        pt_w->adicionar_msg_recebida(QString(remetente.c_str()), QString(msg.c_str()));
      }
      else
      {
        // A leitura da string retornou
        // SOCKET_ERROR, SOCKET_DISCONNECTED ou SOCKET_TIMEOUT
        // Se for SOCKET_TIMEOUT, nao precisa fazer nada. Na realidade,
        // SOCKET_TIMEOUT nunca deve acontecer, pois nao foi definido um timeout.
        // Nos outros dois casos, a conexao encerrou, de forma correta ou com erro.
        if (iResult != SOCKET_TIMEOUT)
        {
          sock.close();
          if (iResult == SOCKET_ERROR) erro=true;
        }
      }
    }
    else
    {
      // A leitura da string retornou
      // SOCKET_ERROR, SOCKET_DISCONNECTED ou SOCKET_TIMEOUT
      // Se for SOCKET_TIMEOUT, nao precisa fazer nada. Na realidade,
      // SOCKET_TIMEOUT nunca deve acontecer, pois nao foi definido um timeout.
      // Nos outros dois casos, a conexao encerrou, de forma correta ou com erro.
      if (iResult != SOCKET_TIMEOUT)
      {
        sock.close();
        if (iResult == SOCKET_ERROR) erro=true;
      }
    }
  }
  if (erro)
  {
    // Emitir msg de erro: conexao interrompida abruptamente
    QMessageBox msgBox;
    msgBox.setWindowTitle("Erro na recepcao");
    msgBox.setText("Erro na leitura do servidor");
    msgBox.exec();
  }
  // Fecha o socket se jah nao estiver fechado
  sock.close();
  // Coloca a interface em modo desconectado
  pt_w->interface_desconectado();
  // Libera o handle da thread
  CloseHandle(th_id);
  th_id = NULL;

  return 0;
}

ConnectServer::ConnectServer(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ConnectServer)
{
  ui->setupUi(this);
}

ConnectServer::~ConnectServer()
{
  delete ui;
}

void ConnectServer::on_buttonBox_accepted()
{
  QString server = ui->editServidor->text();
  QString usuario = ui->editLogin->text();
  MYSOCKET_STATUS iResult;

  // O numero IP de um servidor deve ter no minimo 7 caracteres
  // O nome de login deve ter entre 4 e 16 caracteres
  if (server.size()>7 && usuario.size()>=4 && usuario.size()<=16)
  {
    if (sock.connect(server.toLatin1(), PORTA_TESTE) == SOCKET_OK)
    {
      // Socket estah conectado
      th_id = CreateThread(NULL, 0, le_msg, NULL , 0, NULL);
      if (th_id != NULL)
      {
        // Thread estah funcionando
        iResult = sock.write_string(usuario.toStdString());
        if ( iResult != SOCKET_ERROR )
        {
          // Coloca a interface no modo conectado
          pt_w->interface_conectado(server,usuario);
        }
        else
        {
          TerminateThread(th_id,0);
          // Encerra o handle da thread
          CloseHandle(th_id);
          th_id = NULL;
          sock.close();

          // Emitir msg de erro: nao foi possivel enviar nome de login
          QMessageBox msgBox;
          msgBox.setWindowTitle("Erro na conexao");
          msgBox.setText("Nao foi possivel enviar nome de login "+usuario);
          msgBox.exec();
        }
      }
      else
      {
        sock.close();

        // Emitir msg de erro: nao foi possivel criar thread
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erro na conexao");
        msgBox.setText("Nao foi possivel criar thread de leitura");
        msgBox.exec();
      }
    }
    else
    {
      // Emitir msg de erro: nao foi possivel conectar
      QMessageBox msgBox;
      msgBox.setWindowTitle("Erro na conexao");
      msgBox.setText("Nao foi possivel conectar com o servidor "+server);
      msgBox.exec();
    }
  }
  else
  {
    // Emitir msg de erro: dado(s) invalido(s)
    QMessageBox msgBox;
    msgBox.setWindowTitle("Erro na conexao");
    msgBox.setText("Valor invalido de servidor ("+server+") e/ou login ("+usuario+")");
    msgBox.exec();

  }
}
