#include <iostream>
#include <string.h>
#include <list>
#include <algorithm>

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

// Classe que armazena os dados que definem um cliente: login e socket
struct Client
{
  string login;
  tcp_mysocket s;

  inline Client(): login(""), s() {}
  inline bool operator==(const string &L) {return login==L;}
};

// Apelidos para uma lista de clientes e para o iterator correspondente
typedef list<Client> list_Client;
typedef list_Client::iterator iter_Client;

#define TEMPO_MAXIMO 60      // Tempo maximo de espera por alguma atividade (em segundos)
#define TEMPO_ENVIO_LOGIN 60 // Tempo maximo para o cliente enviar o nome de login apos conexao (em s)

//
// Variáveis globais das 2 threads
//
// O socket de conexoes
tcp_mysocket_server c;
// A lista de clientes
list_Client LC;
// O flag que indica que o software deve encerrar todas as threads
bool fim = false;

// Funcoo auxiliar para enviar mensagem para um cliente especifico
// Testa se os nomes do remetente e do destinatario sao validos (4 a 16 caracteres)
// Depois, testa se o destinatario existe
// Finalmente, testa se o destinatario estah conectado
// Valores de retorno:
//   SOCKET_OK: tudo certo
//   -101: login do remetente invalido
//   -102: login do destinatario invalido
//   -103: erro na escrita no socket do destinatario
//   -104: Destinatario nao conectado
//   -105: Destinatario nao existe
MYSOCKET_STATUS envie_msg(const string &remet, const string &dest, const string &msg)
{
  iter_Client iDest;
  MYSOCKET_STATUS iResult;

  // Testa os nomes do remetente e do destinatario
  if (remet.size()<4 || remet.size()>16)
  {
    return -101;
  }
  if (dest.size()<4 || dest.size()>16)
  {
    return -102;
  }
  // Testa se o destinatario existe, ou seja,
  // procura o destinatario dentro da lista de clientes
  iDest = find(LC.begin(), LC.end(), dest);
  if (iDest != LC.end())
  {
    // Testa se o destinatario estah conectado
    if (iDest->s.connected())
    {
      // Escreve o login do remetente no socket do destinatario
      iResult = iDest->s.write_string(remet);
      if ( iResult == SOCKET_ERROR )
      {
        iDest->s.close();
        return -103;
      }
      // Escreve o texto da msg
      iResult = iDest->s.write_string(msg);
      if ( iResult == SOCKET_ERROR )
      {
        iDest->s.close();
        return -103;
      }
    }
    else
    {
      // O destinatario existe mas nao estah conectado
      return -104;
    }
  }
  else
  {
    // O destinatario nao existe na lista de clientes
    return -105;
  }
  return SOCKET_OK;
}

// Thread que efetivamente desempenha as tarefas do servidor
DWORD WINAPI servidor(LPVOID lpParameter)
{
  tcp_mysocket t;
  mysocket_queue f;
  MYSOCKET_STATUS iResult;

  string usuario,msg;
  iter_Client i;

  while (!fim)
  {
    // Inclui na fila de sockets para o select todos os sockets que eu
    // quero monitorar para ver se houve chegada de dados
    f.clean();
    fim = !c.accepting();
    if (!fim)
    {
      // Monitora o socket de conexoes
      f.include(c);
      for (i=LC.begin(); i!=LC.end(); i++)
      {
    	  if (i->s.connected())
    	  {
    	    // Monitora todos os sockets de clientes conectados
	        f.include(i->s);
    	  }
      }
    }

    // Espera que chegue algum dado em qualquer dos sockets da fila
    iResult = f.wait_read(TEMPO_MAXIMO*1000);
    if (iResult==SOCKET_ERROR)
    {
      if (!fim) cerr << "Erro na espera por alguma atividade\n";
      fim = true;
    }
    if (!fim)
    {
      if (iResult!=SOCKET_TIMEOUT)
      {
        // Nao saiu por timeout: houve atividade em algum socket da fila
        // Testa em qual socket houve atividade.

        // Primeiro, testa os sockets dos clientes
        for (i=LC.begin(); i!=LC.end(); i++)
        {
          if (i->s.connected() && f.had_activity(i->s))
          {
            iResult = i->s.read_string(usuario);
            if (iResult<0)
            {
              if (iResult==SOCKET_ERROR)
              {
                cerr << "Erro ao receber destinatario do cliente " << i->login << ". Desconectando\n";
              }
              if (iResult==SOCKET_DISCONNECTED)
              {
                cout << "Cliente " << i->login << " desconectou\n";
              }
              if (iResult==SOCKET_TIMEOUT)
              {
                // Nunca deve acontecer, jah que a read_string nao tem timeout
                cerr << "MISTERIO! A leitura do destinatario do cliente " << i->login << " deu um timeout nao previsto\n";
              }
              i->s.close();
            }
            if (i->s.connected())
            {
              iResult = i->s.read_string(msg);
              if (iResult<0)
              {
                if (iResult==SOCKET_ERROR)
                {
                  cerr << "Erro ao receber mensagem do cliente " << i->login << ". Desconectando\n";
                }
                if (iResult==SOCKET_DISCONNECTED)
                {
                  cout << "Cliente " << i->login << " desconectou\n";
                }
                if (iResult==SOCKET_TIMEOUT)
                {
                  // Nunca deve acontecer, jah que a read_string nao tem timeout
                  cerr << "MISTERIO! A leitura da msg do cliente " << i->login << " deu um timeout nao previsto\n";
                }
                i->s.close();
              }
            }
            if (i->s.connected())
            {
              iResult = envie_msg(i->login,usuario,msg);
              if (iResult == SOCKET_OK)
              {
                cout << i->login << "->" << usuario << ": " << msg << endl;
              }
              else
              {
                string msg_erro;
                switch(iResult)
                {
                case -101:
                  msg_erro = "REMETENTE "+i->login+" INVALIDO";
                  break;
                case -102:
                  msg_erro = "DESTINATARIO "+usuario+" INVALIDO";
                  break;
                case -103:
                  msg_erro = "PROBLEMA NO ENVIO PARA O DESTINATARIO "+usuario;
                  break;
                case -104:
                  msg_erro = "DESTINATARIO "+usuario+" NAO CONECTADO";
                  break;
                case -105:
                  msg_erro = "DESTINATARIO "+usuario+" NAO EXISTE";
                  break;
                default:
                  msg_erro = "ERRO DESCONHECIDO (CONTATE O ADMNISTRADOR)";
                  break;
                }
                iResult = envie_msg("SERVIDOR", i->login, msg_erro);
                if (iResult != SOCKET_OK)
                {
                  i->s.close();
                }
              }
            }
          }
        }

        // Depois, testa se houve atividade no socket de conexao
        if (f.had_activity(c))
        {
          if (c.accept(t) != SOCKET_OK)
          {
            cerr << "Nao foi possível estabelecer uma conexao\n";
            fim = true;
          }
          if (!fim)
          {
            // Leh o nome de usuario do cliente
            iResult = t.read_string(usuario,TEMPO_ENVIO_LOGIN*1000);
            if (iResult < 0)
            {
              cerr << "Nao foi possivel ler o login de um cliente que se conectou.\n";
              t.close();
            }
            else
            {
              if (usuario.size()<4 || usuario.size()>16)
              {
                t.write_string("SERVIDOR");
                t.write_string("LOGIN "+usuario+" INVALIDO");
                t.close();
              }
              else
              {
                // Procura se jah existe um cliente conectado com o mesmo login
                i = find(LC.begin(), LC.end(), usuario);
                if (i != LC.end())
                {
                  if (i->s.connected())
                  {
                    t.write_string("SERVIDOR");
                    t.write_string("USUARIO "+usuario+" JA CONECTADO");
                    t.close();
                  }
                  else
                  {
                    t.swap(i->s);
                    cout << "Cliente " << usuario << " reconectado.\n";
                  }
                }
                else
                {
                  Client novo;
                  novo.login = usuario;
                  t.swap(novo.s);
                  LC.push_back(novo);
                  cout << "Cliente " << usuario << " criado e conectado.\n";
                }
              }
            }
          }
        }
      }
      else
      {
        // Saiu por timeout: nao houve atividade em nenhum socket da fila
        if (LC.empty())
        {
          cout << "Servidor inativo hah " << TEMPO_MAXIMO << " segundos...\n";
        }
      }
    }
  }
  return 0;
}

int main(void)
{
  WSADATA wsaData;
  string msg;

  // All processes that call Winsock functions must first initialize the use of the Windows Sockets DLL (WSAStartup)
  // before making other Winsock functions calls
  // The MAKEWORD(2,2) parameter of WSAStartup makes a request for version 2.2 of Winsock on the system
  MYSOCKET_STATUS iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (iResult != 0) {
    cerr << "WSAStartup failed: " << iResult << endl;
    exit(1);
  }

  if (c.listen(PORTA_TESTE) != SOCKET_OK) {
    cerr << "Nao foi possível abrir o socket de controle\n";
    exit(1);
  }

  // Cria a thread que recebe e reenvia as mensagens
  HANDLE th_id = CreateThread(NULL, 0, servidor, NULL , 0, NULL);
  if (th_id == NULL)
  {
    cerr << "Problema na criacao da thread\n";
    exit(1);
  }


  while (!fim)
  {
    do
    {
      cout << "Digite FIM para terminar: ";
      cin >> ws;
      getline(cin,msg);
    } while (msg.size()==0 || msg.size()>TAM_MAX_MSG_STRING);
    if (!fim) fim = (msg=="FIM");
  }

  // Espera pelo fim da thread do servidor (máximo de 5 segundos)
  cout << "Aguardando o encerramento da outra thread...\n";
  WaitForSingleObject(th_id, 5000);
  // Encerra na "forca bruta" a thread do servidor caso ela nao tenha terminado sozinha
  // (ou seja, a funcao WaitForSingleObject tenha saído por timeout)
  TerminateThread(th_id,0);
  // Encerra o handle da thread
  CloseHandle(th_id);

  // Enderra os sockets
  c.close();
  for (iter_Client i=LC.begin(); i!=LC.end(); i++) i->s.close();

  /* call WSACleanup when done using the Winsock dll */
  WSACleanup();
}
