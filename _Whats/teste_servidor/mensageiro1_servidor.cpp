#include <iostream>
#include <string.h>
#include <list>
#include <algorithm>

#include "mysocket.h"

#include "dados_servidor.h"
#include "dados_whatsprog.h"

using namespace std;

//
// Variáveis globais das 2 threads
//
// O socket de conexoes
tcp_mysocket_server c;
// O flag que indica que o software deve encerrar todas as threads
bool fim = false;
// Lista de Usuarios
list_Usuario LU;

// Thread que efetivamente desempenha as tarefas do servidor
DWORD WINAPI servidor(LPVOID lpParameter)
{
    if(lpParameter!=NULL) lpParameter = NULL;

    tcp_mysocket t;
    mysocket_queue f;
    MYSOCKET_STATUS iResult;

    int32_t cmd;

    string usuario,senha;
    iter_Usuario i;

    while (!fim)
    {
        f.clean();
        fim = !c.accepting();
        if(!fim)
        {
            f.include(c);
            for (i=LU.begin(); i!=LU.end(); i++)
            {
                if (i->getSocket().connected())
                {
                    f.include(i->getSocket());
                }
            }
        }
        /// Teste de Conexão
        iResult = f.wait_read(TIMEOUT_WHATSPROG*1000);
        if(iResult==SOCKET_ERROR)
        {
            if(!fim) cerr << "Erro na espera por atividade\n";
            fim = true;
        }
        if(!fim)
        {
            if(iResult!=SOCKET_TIMEOUT)
            {
                // Nao saiu por timeout: houve atividade em algum socket da fila
                // Testa em qual socket houve atividade.

                // Primeiro, testa os sockets dos clientes
                for (i=LU.begin(); i!=LU.end(); i++)
                {
                    if (i->getSocket().connected() && f.had_activity(i->getSocket()))
                    {
                        iResult = i->getSocket().read_int(cmd);
                        if(iResult!=SOCKET_ERROR)
                        {

                        }
                        else /// nao recebeu cmd
                        {
                            cerr << "Erro ao receber comando do cliente ";
                        }
                    }
                }
                if (f.had_activity(c)) /// Atvd no sock de conexão
                {
                    if(c.accept(t)!=SOCKET_OK)
                    {
                        cerr << "Nao foi possível estabelecer uma conexao\n";
                        fim = true;
                    }
                    if (!fim)
                    {
                        iResult = t.read_int(cmd, TIMEOUT_LOGIN_WHATSPROG*1000);
                        if (iResult < 0)
                        {
                            cerr << "Nao foi possivel ler o comando de um cliente que se conectou.\n";
                            t.close();
                        }
                        else
                        {
                            switch (cmd){
                            case CMD_NEW_USER:
                                iResult = t.read_string(usuario, TIMEOUT_LOGIN_WHATSPROG*1000);
                                if (iResult < 0)
                                {
                                    cerr << "Nao foi possivel ler o usuario de um cliente que se conectou.\n";
                                    iResult = t.write_int(CMD_LOGIN_INVALIDO);
                                    t.close();
                                }
                                else
                                {
                                    iter_Usuario itr;
                                    itr = find(LU.begin(), LU.end(), usuario);
                                    if (itr!=LU.end())
                                    {
                                        cerr << "Usuario " << usuario << "ja criado. \n";
                                        iResult = t.write_int(CMD_LOGIN_INVALIDO);
                                        t.close();
                                    }
                                    else
                                    {
                                        iResult = t.read_string(senha, TIMEOUT_LOGIN_WHATSPROG*1000);
                                        if (iResult < 0)
                                        {
                                            cerr << "Nao foi possivel ler a senha de um cliente que se conectou.\n";
                                            iResult = t.write_int(CMD_LOGIN_INVALIDO);
                                            t.close();
                                        }
                                        else
                                        {
                                            Usuario novo;
                                            novo.setUsuario(usuario,senha);
                                            if(!novo.setSocket(t))
                                            {
                                                cerr << "Erro ao setar socket.\n";
                                                iResult = t.write_int(CMD_LOGIN_INVALIDO);
                                                t.close();
                                            }
                                            else
                                            {
                                                cout << "Usuario " << novo.getLogin() << " criado e conectado.\n";
                                                iResult = t.write_int(CMD_LOGIN_OK);
                                            }
                                        }
                                    }
                                }
                                break;
                            case CMD_LOGIN_USER:
                                break;
                            }
                        }
                    }
                }
            }
            else /// Saiu por timeout
            {
                if (LU.empty())
                {
                  cout << "Servidor inativo hah " << TIMEOUT_WHATSPROG << " segundos...\n";
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

  if (c.listen(PORTA_WHATSPROG) != SOCKET_OK) {
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
    } while (msg.size()==0 || msg.size()>TAM_MAX_MSG);
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
  for (iter_Usuario i=LU.begin(); i!=LU.end(); i++)
  {
      i->getSocket().close();
  }

  /* call WSACleanup when done using the Winsock dll */
  WSACleanup();
}
