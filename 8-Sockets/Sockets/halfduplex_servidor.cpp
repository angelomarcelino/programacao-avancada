#include <iostream>
#include <string.h>

#include "mysocket.h"

using namespace std;

#define PORTA_TESTE "23456"

int main(void)
{
  WSADATA wsaData;
  tcp_mysocket_server c;
  tcp_mysocket s;

  bool fim = false;
  string msg;

  // All processes that call Winsock functions must first initialize the use of the Windows Sockets DLL (WSAStartup)
  // before making other Winsock functions calls
  // The MAKEWORD(2,2) parameter of WSAStartup makes a request for version 2.2 of Winsock on the system
  MYSOCKET_STATUS iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (iResult != 0) {
    cerr << "WSAStartup failed: " << iResult << endl;
    exit(1);
  }

  // Coloca o socket de controle em modo de espera
  if (c.listen(PORTA_TESTE,1) != SOCKET_OK) {
    cerr << "Não foi possível abrir o socket de controle\n";
    fim = true;
  }
  else
  {
    // Aguarda uma conexao
    cout << "Aguardando conexao do cliente...\n";
    if (c.accept(s) == SOCKET_OK)
    {
      cout << "Cliente conectado no socket " << s << endl;
    }
    else
    {
      cerr << "Não foi possível estabelecer uma conexão\n";
      fim = true;
    }
  }

  while (!fim)
  {
    cout << "Aguardando msg do cliente...\n";
    iResult = s.read_string(msg);
    if (iResult == SOCKET_ERROR)
    {
       cout << "Erro na recepcao de msg do cliente. Desconectando\n";
       s.shutdown();
       fim = true;
    }
    else
    {
      cout << "Mensagem recebida do cliente: " << msg << endl;
      if (msg == "FIM")
      {
        cout << "Cliente se desconectou\n";
        s.shutdown();
        fim = true;
      }
    }

    if (!fim) do
    {
      cout << "Mensagem para o cliente [max " << TAM_MAX_MSG_STRING << " caracteres, FIM para terminar]: ";
      cin >> ws;
      getline(cin,msg);
    } while (msg.size()==0 || msg.size()>TAM_MAX_MSG_STRING);
    if (!fim) fim = (msg=="FIM");

    iResult = s.write_string(msg);
    if ( iResult == SOCKET_ERROR )
    {
      cerr << "Problema ao enviar mensagem para o cliente\n";
      s.shutdown();
      fim = true;
    }
  }

  // Desliga os sockets
  cout << "Encerrando o socket de conexoes\n";
  c.close();
  cout << "Encerrando o socket de comunicacao\n";
  s.close();

  /* call WSACleanup when done using the Winsock dll */
  WSACleanup();
}
