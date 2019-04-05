#include <iostream>
#include <string.h>

#include "mysocket.h"

using namespace std;

#define PORTA_TESTE "23456"

int main(int argc, char **argv)
{
  WSADATA wsaData;
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

  if( argc<2 ) {
    cout << "Maquina onde esta rodando o servidor (IP): ";
    cin >> ws;
    getline(cin, msg);
  }
  else {
    msg = argv[1];
  }

  if (s.connect(msg.c_str(), PORTA_TESTE) == SOCKET_OK)
  {
    cout << "Conectado ao servidor " << msg << " na porta " << PORTA_TESTE
         << "pelo socket " << s << endl;
  }
  else
  {
    cerr << "Problema na conexao ao servidor " << msg << " na porta " << PORTA_TESTE << endl;
    fim = true;
  }

  while (!fim)
  {
    do
    {
      cout << "Mensagem a enviar (max " << TAM_MAX_MSG_STRING << " caracteres, FIM para terminar): ";
      cin >> ws;
      getline(cin, msg);
    } while (msg.size()==0 || msg.size()>TAM_MAX_MSG_STRING);
    if (!fim) fim = (msg=="FIM");

    iResult = s.write_string(msg);
    if ( iResult == SOCKET_ERROR )
    {
      cerr << "Problema ao enviar mensagem para o servidor\n";
      s.shutdown();
      fim = true;
    }

    cout << "Aguardando msg do servidor...\n";
    iResult = s.read_string(msg);
    if (iResult == SOCKET_ERROR)
    {
       cout << "Erro na recepcao de msg do servidor. Desconectando\n";
       s.shutdown();
       fim = true;
    }
    else
    {
      cout << "Mensagem recebida do servidor: " << msg << endl;
      if (msg == "FIM")
      {
        cout << "Servidor se desconectou\n";
        s.shutdown();
        fim = true;
      }
    }
  }

  // Desliga o socket
  cout << "Encerrando o socket de comunicacao\n";
  s.close();

  /* call WSACleanup when done using the Winsock dll */
  WSACleanup();
}
