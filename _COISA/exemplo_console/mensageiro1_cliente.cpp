#include <iostream>
#include <string.h>

#include "mysocket.h"
#include "mensageiro.h"

using namespace std;

/* ==================================================================

Este aplicativo cliente-servidor permite o envio de mensagens entre
os softwares clientes e o software servidor.
As mensagens trocadas sao formadas pelos seguintes campos:
1) Usuario - uma string formada por dois campos:
   1.1) Tamanho da string: um inteiro [ 4 bytes ]
   1.2) Caracteres da string: varios chars [ tamanho do texto ]
   Significa o destinatario, nas msgs do cliente para o servidor,
   ou o remetente, nas msgs do servidor para o cliente
2) Texto - uma string formada por dois campos:
   2.1) Tamanho do texto: um inteiro [ sizeof(int) bytes ]
   2.2) Caracteres do texto: varios chars [ tamanho do texto ]
   Contem a msg efetivamente enviada

A primeira msg a ser enviada pelo cliente para o servidor eh
diferente das demais. Deve conter apenas o nome do usuario. Esse
nome identificarah o cliente daih em diante: todas as msgs enviadas
para esse nome do usuario serao direcionadas pelo servidor para esse
cliente.

================================================================== */

/* ==================================================================

Este programa tem uma thread principal que espera que o usuário
digite alguma coisa e envia esta msg para um servidor via
socket. Uma outra thread imprime todas as msgs recebidas pelo
socket.

================================================================== */

// Aqui vao as variaveis globais das duas threads

tcp_mysocket s;
bool fim = false;

// Esta eh a thread que escreve em tela as mensagens recebidas

DWORD WINAPI le_msg(LPVOID lpParameter)
{
  string remetente,msg;
  MYSOCKET_STATUS iResult;

  while (!fim) {
    iResult = s.read_string(remetente);
    if (iResult<0)
    {
      if (iResult==SOCKET_ERROR)
      {
        cerr << "Problema na leitura do remetente via socket. Desconectando\n";
      }
      if (iResult==SOCKET_DISCONNECTED)
      {
        cout << "Servidor desconectou\n";
      }
      if (iResult==SOCKET_TIMEOUT)
      {
        // Nunca deve acontecer, jah que a read_int nao tem timeout
        cerr << "MISTERIO! A leitura do remetente deu um timeout nao previsto\n";
      }
      fim = true;
    }
    if (!fim)
    {
      iResult = s.read_string(msg);
      if (iResult<0)
      {
        if (iResult==SOCKET_ERROR)
        {
          cerr << "Problema na leitura da msg via socket. Desconectando\n";
        }
        if (iResult==SOCKET_DISCONNECTED)
        {
          cout << "Servidor desconectou\n";
        }
        if (iResult==SOCKET_TIMEOUT)
        {
          // Nunca deve acontecer, jah que a read_string nao tem timeout
          cerr << "MISTERIO! A leitura da msg deu um timeout nao previsto\n";
        }
        fim = true;
      }
    }
    if (!fim)
    {
      cout << endl
           << "=========================================================\n"
           << "Mensagem recebida de " << remetente <<":\n"
           << msg << endl
    	     << "=========================================================\n";
    }
  }
  return 0;
}

// O programa principal contém o ciclo que envia as mensagens digitadas

int main(int argc, char **argv)
{
  WSADATA wsaData;
  HANDLE tHandle;
  string usuario;
  string msg;
  MYSOCKET_STATUS iResult;

  // All processes that call Winsock functions must first initialize the use of the Windows Sockets DLL (WSAStartup)
  // before making other Winsock functions calls
  // The MAKEWORD(2,2) parameter of WSAStartup makes a request for version 2.2 of Winsock on the system
  iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (iResult != 0) {
    cerr << "WSAStartup failed: " << iResult << endl;
    exit(1);
  }

  // Determina o numero IP do servidor (digitado ou lido do argumento de chamada)
  if( argc<2 )
  {
    cout << "Maquina onde estah rodando o servidor (IP): ";
    cin >> ws;
    getline(cin, msg);
  }
  else
  {
    msg = argv[1];
  }

  // Conecta com o servidor
  if (s.connect(msg.c_str(), PORTA_TESTE) == SOCKET_OK)
  {
    cout << "Conectado ao servidor " << msg << " na porta " << PORTA_TESTE << endl;
  }
  else
  {
    cerr << "Problema na conexao ao servidor " << msg << " na porta " << PORTA_TESTE << endl;
    exit(1);
  }

  // Cria a thread que escreve as mensagens recebidas
  tHandle = CreateThread(NULL, 0, le_msg, NULL , 0, NULL);
  if (tHandle == NULL)
  {
    cerr << "Problema na criacao da thread: " << GetLastError() << endl;
    exit(1);
  }

  // Envia para o servidor o nome de usuario que identificarah esse cliente
  do
  {
    s.write_int(CMD_NEW_USER);
    cout << "Login deste cliente [4 a 16 caracteres]: ";
    cin >> ws;
    getline(cin, usuario);
  } while (usuario.size()<4 || usuario.size()>16);
  iResult = s.write_string(usuario);
  if ( iResult == SOCKET_ERROR )
  {
    cerr << "Problema na escrita do login no socket...\n";
    exit(1);
  }

  // Este é o ciclo que envia as mensagens digitadas
  while (!fim)
  {
    if (!fim)
    {
      do
      {
        cout << "Usuario a enviar msg [4 a 16 caracteres, FIM para terminar]: ";
        cin >> ws;
        getline(cin, usuario);
      } while (usuario!="FIM" && (usuario.size()<4 || usuario.size()>16));
      if (!fim) fim = (usuario=="FIM");
    }

    if (!fim)
    {
      do
      {
        cout << "Mensagem a enviar [max " << TAM_MAX_MSG_STRING << " caracteres, FIM para terminar]: ";
        cin >> ws;
        getline(cin, msg);
      } while (msg.size()==0 || msg.size()>TAM_MAX_MSG_STRING);
      if (!fim) fim = (msg=="FIM");
    }

    if (!fim)
    {
      iResult = s.write_string(usuario);
      if ( iResult == SOCKET_ERROR )
      {
        cout << "Problema na escrita do usuario no socket...\n";
        fim = true;
      }
    }
    if (!fim)
    {
      iResult = s.write_string(msg);
      if ( iResult == SOCKET_ERROR )
      {
        cout << "Problema na escrita do texto no socket...\n";
        fim = true;
      }
    }
    Sleep(1000); // Espera 1 seg para as mensagens nao se sobreporem no terminal
  }

  // Espera pelo fim da thread de recepcao (máximo de 5 segundos)
  cout << "Aguardando o encerramento da outra thread...\n";
  WaitForSingleObject(tHandle, 5000);
  // Encerra na forca bruta a thread de recepcao caso ela nao tenha terminado sozinha
  // (ou seja, a funcao WaitForSingleObject tenha saído por timeout)
  TerminateThread(tHandle,0);
  // Encerra o handle da thread
  CloseHandle(tHandle);

  // Encerra o socket
  s.close();

  /* call WSACleanup when done using the Winsock dll */
  WSACleanup();
}
