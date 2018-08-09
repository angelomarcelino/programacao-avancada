#include <iostream>
#include <string.h>
#include <list>
#include <algorithm>
#include <windows.h>


#include "mysocket.h"
#include "dados_whatsprog.h"
#include "dados_servidor.h"

using namespace std;
typedef int MYSOCKET_STATUS;


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
struct Client {
    string login;
    tcp_mysocket s;

    inline Client(): login(""), s() {}
    inline bool operator==(const string &L) {
        return login==L;
    }
};

// Apelidos para uma lista de clientes e para o iterator correspondente
typedef list<Client> list_Client;
typedef list_Client::iterator iter_Client;

//#define TEMPO_MAXIMO 60      // Tempo maximo de espera por alguma atividade (em segundos)
//#define TEMPO_ENVIO_LOGIN 60 // Tempo maximo para o cliente enviar o nome de login apos conexao (em s)

//
// Variáveis globais das 2 threadsd
//
// O socket de conexoes
tcp_mysocket_server c;
// A lista de clientes
list_Client LC;
// O flag que indica que o software deve encerrar todas as threads
bool fim = false;


list_Mensagem msgList;
list_Usuario LU;

/// Luiz IMPLEMENTATIONS


MYSOCKET_STATUS envie_comando(tcp_mysocket &s, const int &msg) {
    MYSOCKET_STATUS iResult;
    cout<<"\nEnviandmo comando "<<msg<<" pelo socket\n";
    // Testa se o destinatario estah conectado
    if (s.connected()) {

        // Escreve a int do comando
        iResult = s.write_int(msg);
        if ( iResult == SOCKET_ERROR ) {
            cout<<"\nErro ao enviar comando, fechando socket\n";
            s.close();
            return -103;
        }

        return SOCKET_OK;
    }
    cout<<"\nsocket nao conectado, fechando socket\n";
    s.close();
    return -103;
}


MYSOCKET_STATUS read_usuario(tcp_mysocket t,Usuario &u, long milisec=-1) {
    string login,senha;
    MYSOCKET_STATUS iResult;
    iResult = t.read_string(login,milisec);
    if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT || iResult==SOCKET_DISCONNECTED) {
        // Erro ou timeout ou desconexao
        u.setUsuario("","");
        return iResult;
    }

    iResult = t.read_string(senha,milisec);
    if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT || iResult==SOCKET_DISCONNECTED) {
        // Erro ou timeout ou desconexao
        u.setUsuario("","");
        return iResult;
    }
    if(login.size() > TAM_MAX_NOME_USUARIO || login.size() < TAM_MIN_NOME_USUARIO ||
            senha.size() > TAM_MAX_SENHA || senha.size() < TAM_MIN_SENHA) {
        u.setUsuario("","");
        return SOCKET_ERROR;
    }
    u.setUsuario(login,senha);
    return iResult;

}


MYSOCKET_STATUS read_msg(tcp_mysocket t,Mensagem &m,int32_t LI, long milisec) {
//string login,senha;
    int32_t id;
    string destinatario, texto;
    MYSOCKET_STATUS iResult;
    iResult = t.read_int(id,TIMEOUT_WHATSPROG*1000);
    if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT || iResult==SOCKET_DISCONNECTED) {
        // Erro ou timeout ou desconexao
        return iResult;
    }
    iResult = t.read_string(destinatario,milisec);
    if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT || iResult==SOCKET_DISCONNECTED) {
        // Erro ou timeout ou desconexao
        return iResult;
    }

    iResult = t.read_string(texto,milisec);
    if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT || iResult==SOCKET_DISCONNECTED) {
        // Erro ou timeout ou desconexao

        return iResult;
    }
    if(!(LI<id)) {
        return CMD_ID_INVALIDA;
    } else if(destinatario.size() > TAM_MAX_NOME_USUARIO || destinatario.size() < TAM_MIN_NOME_USUARIO) {
        return CMD_USER_INVALIDO;
    } else if(texto.size()>TAM_MAX_MSG) {
        return CMD_MSG_INVALIDA;
    }
    m.setId(id);
    m.setDestinatario(destinatario);
    m.setTexto(texto);
    m.setStatus(MSG_RECEBIDA);
    return CMD_MSG_RECEBIDA;

}


MYSOCKET_STATUS send_msg(tcp_mysocket t,Mensagem &m,int32_t LI, long milisec) {
//string login,senha;
    int32_t id;
    string destinatario, texto;
    MYSOCKET_STATUS iResult;

    iResult = envie_comando(t,CMD_NOVA_MSG);
    if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT || iResult==SOCKET_DISCONNECTED) {
        // Erro ou timeout ou desconexao
        return iResult;
    }

    iResult = t.write_int(m.getId());
    if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT || iResult==SOCKET_DISCONNECTED) {
        // Erro ou timeout ou desconexao
        return iResult;
    }
    iResult = t.write_string(m.getDestinatario());
    if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT || iResult==SOCKET_DISCONNECTED) {
        // Erro ou timeout ou desconexao
        return iResult;
    }

    iResult = t.write_string(m.getTexto());
    if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT || iResult==SOCKET_DISCONNECTED) {
        // Erro ou timeout ou desconexao

        return iResult;
    }

    return iResult;

}


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
//   -105: Destinatario nao existeCMD_LOGIN_INVALIDO
MYSOCKET_STATUS envie_msg(const string &remet, const string &dest, const string &msg) {
    iter_Client iDest;
    MYSOCKET_STATUS iResult;

    // Testa os nomes do remetente e do destinatario
    if (remet.size()<4 || remet.size()>16) {
        return -101;
    }
    if (dest.size()<4 || dest.size()>16) {
        return -102;
    }
    // Testa se o destinatario existe, ou seja,
    // procura o destinatario dentro da lista de clientes
    iDest = find(LC.begin(), LC.end(), dest);
    if (iDest != LC.end()) {
        // Testa se o destinatario estah conectado
        if (iDest->s.connected()) {
            // Escreve o login do remetente no socket do destinatario
            iResult = iDest->s.write_string(remet);
            if ( iResult == SOCKET_ERROR ) {
                iDest->s.close();
                return -103;
            }
            // Escreve o texto da msg
            iResult = iDest->s.write_string(msg);
            if ( iResult == SOCKET_ERROR ) {
                iDest->s.close();
                return -103;
            }
        } else {
            // O destinatario existe mas nao estah conectado
            return -104;
        }
    } else {
        // O destinatario nao existe na lista de clientes
        return -105;
    }
    return SOCKET_OK;
}

// Funcoo auxiliar para enviar comando para um cliente especifico
// Testa se os nomes do remetente e do destinatario sao validos (4 a 16 caracteres)
// Depois, testa se o destinatario existe
// Finalmente, testa se o destinatario estah conectado
// Valores de retorno:
//   SOCKET_OK: tudo certo
//   -101: login do remetente invalido
//   -102: login do destinatario invalido
//   -103: erro na escrita no socket do destinatario
//   -104: Destinatario nao conectado
//   -105: Destinatario nao existeCMD_LOGIN_INVALIDO
//MYSOCKET_STATUS envie_comando(const string &remet, const string &dest, const int &msg) {
//    iter_Usuario iDest;
//    MYSOCKET_STATUS iResult;
//
//    // Testa os nomes do remetente e do destinatario
//    if (remet.size()<TAM_MIN_NOME_USUARIO || remet.size()>TAM_MAX_NOME_USUARIO) {
//        return -101;
//    }
//    if (dest.size()<TAM_MIN_NOME_USUARIO || dest.size()>TAM_MAX_NOME_USUARIO) {
//        return -102;
//    }
//    // Testa se o destinatario existe, ou seja,
//    // procura o destinatario dentro da lista de clientes
//    iDest = find(LU.begin(), LU.end(), dest);
//    if (iDest != LU.end()) {
//        // Testa se o destinatario estah conectado
//        if (iDest->getSocket().connected()) {
//
//            // Escreve a int do comando
//            iResult = iDest->getSocket().write_int(msg);
//            if ( iResult == SOCKET_ERROR ) {
//                iDest->getSocket().close();
//                return -103;
//            }
//        } else {
//            // O destinatario existe mas nao estah conectado
//            return -104;
//        }
//    } else {
//        // O destinatario nao existe na lista de clientes
//        return -105;
//    }
//    return SOCKET_OK;
//}

///////////////////////////////////////////
//Funçao de luiz para enviar o comando////





// Thread que efetivamente desempenha as tarefas do servidor

DWORD WINAPI servidor(LPVOID lpParameter) {
    tcp_mysocket t;
    mysocket_queue f;
    MYSOCKET_STATUS iResult;

    string usuario,msg;
    int command;
    iter_Client i;
    iter_Usuario j;
    iter_Mensagem im;

    while (!fim) {
        // Inclui na fila de sockets para o select todos os sockets que eu
        // quero monitorar para ver se houve chegada de dados
        f.clean();
        fim = !c.accepting();
        if (!fim) {
            // Monitora o socket de conexoes
            f.include(c);
            for (j=LU.begin(); j!=LU.end(); j++) {
                if (j->getSocket().connected()) {
                    // Monitora todos os sockets de clientes conectados
                    f.include(j->getSocket());
                }
            }
        }
        cerr<<"\nEsperando por atividade...\n";
        // Espera que chegue algum dado em qualquer dos sockets da fila
        iResult = f.wait_read(TIMEOUT_WHATSPROG*1000);
        if (iResult==SOCKET_ERROR) {
            if (!fim) cerr << "\nErro na espera por alguma atividade\n";
            fim = true;
        }
        if (!fim) {
            if (iResult!=SOCKET_TIMEOUT) {
                // Nao saiu por timeout: houve atividade em algum socket da fila
                // Testa em qual socket houve atividade.
                cout<<"\nNao saiu por TIMEOUT\n";
                // Primeiro, testa os sockets dos clientes
                for (j=LU.begin(); j!=LU.end(); j++) {

                    if (j->getSocket().connected() && f.had_activity(j->getSocket())) {
                        iResult = j->getSocket().read_int(command,TIMEOUT_WHATSPROG*1000);
                        if (iResult<0) {
                            if (iResult==SOCKET_ERROR) {
                                cerr << "Erro ao receber destinatario do cliente " << j->getLogin() << ". Desconectando\n";
                            }
                            if (iResult==SOCKET_DISCONNECTED) {
                                cout << "Cliente " << j->getLogin() << " desconectou\n";
                            }
                            if (iResult==SOCKET_TIMEOUT) {
                                // Nunca deve acontecer, jah que a read_string nao tem timeout
                                cerr << "MISTERIO! A leitura do destinatario do cliente " << j->getLogin() << " deu um timeout nao previsto\n";
                            }
                            j->getSocket().close();

                        } else {
                            Mensagem m;
                            iter_Usuario dest;
                            int32_t id;
                            string rem;

                            switch(command) {

                            case CMD_NOVA_MSG:
                                cout<<"\nNOVA_MSG\n";
                                m.setRemetente(j->getLogin());
                                iResult = read_msg(j->getSocket(),m,j->getLastId(),TIMEOUT_WHATSPROG*1000);
                                if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT || iResult==SOCKET_DISCONNECTED) {
                                    j->getSocket().close();
                                } else {
                                    if(j->getSocket().connected())
                                        envie_comando(j->getSocket(),iResult);
                                }

                                //TODO: Enviar para o remetente
                                dest = find(LU.begin(), LU.end(), m.getDestinatario());
                                if (dest != LU.end()) {
                                    cout<<"\nUsuário "<< m.getDestinatario()<<" existente, tudo nos conformes\n";
                                    cout<<"\nVerificando Conexão\n";
                                    if(dest->getSocket().connected()) {
                                        cout<<"\nUsuário conectado, enviando mensagem\n";
                                        iResult = send_msg(dest->getSocket(),m,dest->getLastId(),TIMEOUT_WHATSPROG*1000);
                                        if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT || iResult==SOCKET_DISCONNECTED) {
                                            dest->getSocket().close();
                                        } else {
                                            cout<<"\n------------------------------------------------------\n";
                                            cout<<"\nMensagem: "<<m.getTexto()<<" \n "<<j->getLogin()<<" --> "<< m.getDestinatario()<< " deu: "<<iResult<<endl;
                                            cout<<"\n------------------------------------------------------\n";
                                            cout<<"\nEnviando confirmação de ENTREGUE\n";
                                            iResult = envie_comando(j->getSocket(),CMD_MSG_ENTREGUE);
                                            if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT || iResult==SOCKET_DISCONNECTED) {

                                            } else {
                                                m.setStatus(MSG_ENTREGUE);
                                            }


                                        }


                                    } else {
                                        cout<<"\nUsuário não conectado, salvando no buffer\n";
                                        msgList.push_back(m);

                                    }
                                } else {
                                    cout<<"\nUsuário "<< m.getDestinatario()<<" nao existente ERRO\n";
                                    envie_comando(j->getSocket(),CMD_USER_INVALIDO);

                                }


                                break;

                            case CMD_MSG_LIDA1:
                                cout<<"\nCMD_MSG_LIDA1\n";


                                MYSOCKET_STATUS iResult;
                                iResult = j->getSocket().read_int(id,TIMEOUT_WHATSPROG*1000);
                                if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT || iResult==SOCKET_DISCONNECTED) {
                                    // Erro ou timeout ou desconexao
                                    cout<<"\nDEu erro, fechando socket\n";
                                    j->getSocket().close();
                                    //return iResult;
                                } else {
                                    iResult = j->getSocket().read_string(rem,TIMEOUT_WHATSPROG*1000);
                                    if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT || iResult==SOCKET_DISCONNECTED) {
                                        cout<<"\nDEu erro, fechando socket\n";
                                        j->getSocket().close();
                                    } else {
                                        cout<<"\nMensagem de Id: "<<id<<" de remetente: "<<rem<<endl;
                                        cout<<"\nProcurando no BUFFER\n";
                                        testRemetId t(rem,id);
                                        im = find(msgList.begin(),msgList.end(),t);
                                        if(im != msgList.end()) {
                                            cout<<"\nMensagem Econtrada! Alterando status...\n";
                                            im->setStatus(MSG_LIDA);
                                            dest = find(LU.begin(), LU.end(), im->getRemetente());
                                            if(dest!= LU.end()) {
                                                cout<<"\nRemetente econtrado, verificando conexão..\n";
                                                if(dest->getSocket().connected()) {
                                                    cout<<"\nRemetente conectado..\n";
                                                    envie_comando(dest->getSocket(),CMD_MSG_LIDA2);
                                                }
                                            }
                                        } else {
                                            cout<<"\nMensagem não encontrada no buffer, fechando socket()\n";
                                            j->getSocket().close();
                                        }
                                    }

                                }

                                break;
                            case CMD_LOGOUT_USER:
                                cout<<"\nCMD_LOGOUT_USER\n";
                                j->getSocket().close();


                                break;
                            default:
                                cout<<"\nCOMANDO INVALIDO OU ERRO DESCONHECIDO FECHANDO SOCKET\n";
                                j->getSocket().close();

                                break;
                            }
                        }



//                        if (i->s.connected()) {
//                            iResult = envie_msg(i->login,usuario,msg);
//                            if (iResult == SOCKET_OK) {
//                                cout << i->login << "->" << usuario << ": " << msg << endl;
//                            } else {
//                                string msg_erro;
//                                switch(iResult) {
//                                case -101:
//                                    msg_erro = "REMETENTE "+i->login+" INVALIDO";
//                                    break;
//                                case -102:
//                                    msg_erro = "DESTINATARIO "+usuario+" INVALIDO";
//                                    break;
//                                case -103:
//                                    msg_erro = "PROBLEMA NO ENVIO PARA O DESTINATARIO "+usuario;
//                                    break;
//                                case -104:
//                                    msg_erro = "DESTINATARIO "+usuario+" NAO CONECTADO";
//                                    break;
//                                case -105:
//                                    msg_erro = "DESTINATARIO "+usuario+" NAO EXISTE";
//                                    break;
//                                default:
//                                    msg_erro = "ERRO DESCONHECIDO (CONTATE O ADMNISTRADOR)";
//                                    break;
//                                }
//                                iResult = envie_msg("SERVIDOR", i->login, msg_erro);
//                                if (iResult != SOCKET_OK) {
//                                    i->s.close();
//                                }
//                            }
//                        }
                    }
                }

                // Depois, testa se houve atividade no socket de conexao
                if (f.had_activity(c)) {
                    if (c.accept(t) != SOCKET_OK) {
                        cerr << "Nao foi possível estabelecer uma conexao\n";
                        fim = true;
                    }
                    if (!fim) {
                        //Verifica o comando enviado
                        iResult = t.read_int(command,TIMEOUT_WHATSPROG*1000);
                        if (iResult < 0) {
                            cerr << "Nao foi possivel ler o login de um cliente que se conectou.\n";
                            t.close();
                        } else {

                            if(command == CMD_NEW_USER) {
                                cout<<" NOVO USUÀRIO \n";
                                Usuario u;
                                iResult = u.read_usuario(t,TIMEOUT_LOGIN_WHATSPROG*1000);
                                if (iResult < 0) {
                                    cout<<"\nErro no Socket, fechando socket\n";
                                    t.close();
                                } else if(u.getSenha() =="" && u.getLogin() == "") {
                                    cerr << "\n Credenciais invalidas, CMD_LOGIN_INVALIDO\n";
                                    iResult = envie_comando(t,CMD_LOGIN_INVALIDO);
                                    if (iResult != SOCKET_OK) {
                                        cout<<"\nErro fechando socket\n";
                                    }
                                    t.close();
                                } else {
                                    cout<<"\nUsuario - "<<u.getLogin()<<"  "<<u.getSenha()<<endl;
                                    // Procura se jah existe um cliente conectado com o mesmo login
                                    j = find(LU.begin(), LU.end(), u.getLogin());
                                    if (j != LU.end()) {
                                        cout<<"\nUsuário já existente, verificando conexao\n";
                                        //cout<<"\nLuiz -> "<<j->getSocket().connected();
                                        if (j->getSocket().connected()) {
                                            cout<<"\nUsuário já conectado,fechando socket\n";
                                            iResult = envie_comando(t,CMD_LOGIN_INVALIDO);
                                            if (iResult != SOCKET_OK) {
                                                cout<<"\nErro, fechando socket()\n";
                                                t.close();
                                            }
                                            t.close();
                                        } else {
                                            cout<<"\nUsuário nao conectado,verificando senha\n";
                                            if(j->getSenha() == u.getSenha()) {
                                                cout<<"\nSenha Correta\n";
                                                //t.swap(j->getSocket());
                                                u.setSocket(t);
                                                cout << "Cliente " << u.getLogin() << " reconectado...\n";
                                                iResult = envie_comando(u.getSocket(),CMD_LOGIN_OK);
                                                if (iResult != SOCKET_OK) {
                                                    u.getSocket().close();
                                                } else
                                                    cout<<"\nComando enviado\n";
                                            } else {
                                                cout<<"\nSenha Incorreta\n";
                                                iResult = envie_comando(t,CMD_LOGIN_INVALIDO);
                                                if (iResult != SOCKET_OK) {
                                                    t.close();
                                                } else
                                                    cout<<"\nComando enviado\n";
                                                t.close();
                                            }
                                        }
                                    } else {
                                        cout<<"\nUsuario Novo, Cadastrando...\n";
                                        //t.swap(u.getSocket());
                                        u.setSocket(t);
                                        LU.push_back(u);
                                        cout << "Cliente " << u.getLogin() << " criado e conectado, enviando comando.\n";
                                        iResult = envie_comando(u.getSocket(),CMD_LOGIN_OK);
                                        if (iResult != SOCKET_OK) {
                                            u.getSocket().close();
                                        } else
                                            cout<<"\nComando enviado\n"<<u.getSocket();
                                    }

                                }

                            } else if(command == CMD_LOGIN_USER) {
                                cout<<" LOGIN USUÀRIO \n";
                                Usuario u;
                                iResult = u.read_usuario(t,TIMEOUT_LOGIN_WHATSPROG*1000);
                                if (iResult < 0) {
                                    cerr << "\n Erro no socket, fechando...\n";
                                    t.close();
                                } else if(u.getSenha() == "" && u.getLogin() == "") {
                                    cout<<"\nCMD_LOGIN_INVALIDO\n";
                                    iResult = envie_comando(t,CMD_LOGIN_INVALIDO);
                                    if (iResult != SOCKET_OK) {
                                        t.close();
                                    }
                                    t.close();
                                } else {
                                    cout<<"\nUsuario - "<<u.getLogin()<<"  "<<u.getSenha()<<endl;
                                    // Procura se jah existe um cliente conectado com o mesmo login
                                    j = find(LU.begin(), LU.end(), u.getLogin());
                                    if (j != LU.end()) {
                                        cout<<"\nUsuario cadastrado,\n";
                                        if(j->getSenha() == u.getSenha()) {
                                            cout<<"\nSenha Correta\n";
                                            if (j->getSocket().connected()) {
                                                cout<<"\nUsuário já conectado, fechando Socket....\n";
                                                iResult = envie_comando(t,CMD_LOGIN_INVALIDO);
                                                if (iResult != SOCKET_OK) {
                                                    t.close();
                                                }
                                                t.close();
                                            } else {
                                                cout<<"\nUsuario nao conectado, conectando....\n";
                                                j->setSocket(t);
                                                iResult = envie_comando(j->getSocket(),CMD_LOGIN_OK);
                                                if (iResult != SOCKET_OK) {
                                                    j->getSocket().close();
                                                } else
                                                    cout<<"\nComando enviado\n"<<u.getSocket();

                                            }
                                        } else {
                                            cout<<"\nSenha incorreta,fechando socket\n";
                                            iResult = envie_comando(t,CMD_LOGIN_INVALIDO);
                                            if (iResult != SOCKET_OK) {
                                                t.close();
                                            }
                                            t.close();

                                        }
                                    } else {
                                        cout<<"Usuário nao econtrado, fechando socket\n";
                                        iResult = envie_comando(t,CMD_LOGIN_INVALIDO);
                                        if (iResult != SOCKET_OK) {
                                            t.close();
                                        }
                                        t.close();
                                    }
                                }

                            } else {
                                cout<<" Comando invalido agora, fechando socket\n";
                                t.close();
                            }
                        }

                    }
                }
            } else {
                // Saiu por timeout: nao houve atividade em nenhum socket da fila
                if (LC.empty()) {
                    cout << "Servidor inativo hah " << TIMEOUT_WHATSPROG << " segundos...\n";
                }
            }
        }
    }
    return 0;
}

int main(void) {
    WSADATA wsaData;
    MYSOCKET_STATUS iResult;
    string msg;
    string luiz = "luiz";
    string felipe = "luiz ";


    // All processes that call Winsock functions must first initialize the use of the Windows Sockets DLL (WSAStartup)
    // before making other Winsock functions calls
    // The MAKEWORD(2,2) parameter of WSAStartup makes a request for version 2.2 of Winsock on the system
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
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
    if (th_id == NULL) {
        cerr << "Problema na criacao da thread\n";
        exit(1);
    }


    while (!fim) {
        do {
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
    //WSACleanup();
}






