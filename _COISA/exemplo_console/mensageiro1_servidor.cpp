#include <iostream>
#include <string.h>
#include <list>
#include <algorithm>

#include "mysocket.h"
#include "mensageiro.h"

using namespace std;

struct Client
{
  string login;
  tcp_mysocket s;

  inline Client(): login(""), s() {}
  inline bool operator==(const string &L) {return login==L;}
};

typedef list<Client> list_Client;
typedef list_Client::iterator iter_Client;

#define TEMPO_MAXIMO 60
#define TEMPO_ENVIO_LOGIN 60

tcp_mysocket_server c;

list_Client LC;

bool fim = false;

MYSOCKET_STATUS envie_msg(const string &remet, const string &dest, const string &msg)
{
  iter_Client iDest;
  MYSOCKET_STATUS iResult;

  if (remet.size()<4 || remet.size()>16)
  {
    return -101;
  }
  if (dest.size()<4 || dest.size()>16)
  {
    return -102;
  }

  iDest = find(LC.begin(), LC.end(), dest);
  if (iDest != LC.end())
  {
    if (iDest->s.connected())
    {
      iResult = iDest->s.write_string(remet);
      if ( iResult == SOCKET_ERROR )
      {
        iDest->s.close();
        return -103;
      }
      iResult = iDest->s.write_string(msg);
      if ( iResult == SOCKET_ERROR )
      {
        iDest->s.close();
        return -103;
      }
    }
    else
    {
      return -104;
    }
  }
  else
  {
    return -105;
  }
  return SOCKET_OK;
}

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

  TerminateThread(th_id,0);
  // Encerra o handle da thread
  CloseHandle(th_id);

  // Enderra os sockets
  c.close();
  for (iter_Client i=LC.begin(); i!=LC.end(); i++) i->s.close();

  WSACleanup();
}
