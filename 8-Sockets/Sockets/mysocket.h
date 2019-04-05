#ifndef _MYSOCKET_H_
#define _MYSOCKET_H_

#include <iostream>
#include <cstdlib>

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x501
#endif // _WIN32_WINNT

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

using namespace std;

/*
###############################################################################

NAO ESQUECA DE LINKAR COM A BIBLIOTECA Ws2_32. Incluir essa opcao no linkador

No CodeBlocs: botao direito no nome do projeto, Build options, Linker settings,
adicionar biblioteca Ws2_32

No Qt: adicionar no fim do arquivo <PROJETO>.pro as seguintes linhas:

LIBS   += \
    -lWs2_32

###############################################################################

Infomacao sobre os sockets Windows:

INICIO:
https://msdn.microsoft.com/en-us/library/windows/desktop/ms738545(v=vs.85).aspx
CRIANDO UMA APLICACAO WINSOCK (cliente e servidor):
https://msdn.microsoft.com/en-us/library/windows/desktop/ms737629(v=vs.85).aspx
CLIENTE:
https://msdn.microsoft.com/en-us/library/windows/desktop/bb530741(v=vs.85).aspx
SERVIDOR:
https://msdn.microsoft.com/en-us/library/windows/desktop/bb530742(v=vs.85).aspx
SELECT:
https://msdn.microsoft.com/en-us/library/windows/desktop/ms740141(v=vs.85).aspx
SEND, RECV:
https://msdn.microsoft.com/en-us/library/windows/desktop/bb530746(v=vs.85).aspx
*/

typedef int MYSOCKET_STATUS;
#define SOCKET_OK 0
#define TAM_MAX_MSG_STRING 256

typedef enum
{
  MYSOCKET_IDLE=0,
  MYSOCKET_ACCEPTING=1,
  MYSOCKET_CONNECTED=2
} MYSOCKET_STATE;

// Predefinicao das classes
class mysocket_queue;
class tcp_mysocket;
class tcp_mysocket_server;

/* #############################################################
   ##  A classe base dos sockets                              ##
   ############################################################# */

class mysocket
{
private:

  SOCKET id;
  MYSOCKET_STATE state;

public:

  // Construtor por default
  inline mysocket(): id(INVALID_SOCKET), state(MYSOCKET_IDLE) {}

  // Permuta dois sockets
  // Geralmente, deve ser utilizado ao inves do operador de atribuicao
  void swap(mysocket &S);

  // Proibe novos envios de dados via socket
  // Retorna SOCKET_OK ou SOCKET_ERRO
  MYSOCKET_STATUS shutdown();

  // Fecha (caso esteja aberto) um socket
  void close();

  // Testa se um socket eh "virgem" ou foi fechado
  inline bool closed() const {return (id==INVALID_SOCKET && state==MYSOCKET_IDLE);}
  // Testa se um socket estah aberto (aceitando conexoes)
  inline bool accepting() const {return (id!=INVALID_SOCKET && state==MYSOCKET_ACCEPTING);}
  // Testa se um socket estah conectado (pronto para ler e escrever)
  inline bool connected() const {return (id!=INVALID_SOCKET && state==MYSOCKET_CONNECTED);}

  // Imprime um socket
  friend std::ostream& operator<<(std::ostream& os, const mysocket &);

  // As classes amigas
  friend class tcp_mysocket;
  friend class tcp_mysocket_server;
  friend class mysocket_queue;
};

/* #############################################################
   ##  As classes dos sockets orientados a conexao (TCP)      ##
   ############################################################# */

class tcp_mysocket: public mysocket
{
public:

  // Construtor default
  inline tcp_mysocket(): mysocket() {}

  // Se conecta a um socket aberto
  // Soh pode ser usado em sockets "virgens" ou explicitamente fechados
  // Retorna SOCKET_OK, se tudo deu certo, ou outro valor, em caso de erro
  MYSOCKET_STATUS connect(const char *name, const char *port);

  // Escreve em um socket conectado
  // Soh pode ser usado em socket para o qual tenha sido feito um "connect" antes
  // Ou entao em um socket retornado pelo "accept" de um socket servidor
  // Retorna o numero de bytes enviados (ou seja, len), em caso de sucesso,
  // ou SOCKET_ERRO
  MYSOCKET_STATUS write(const char* dado, size_t len) const;

  // Leh de um socket conectado
  // Soh pode ser usado em socket para o qual tenha sido feito um "connect" antes
  // Ou entao em um socket retornado pelo "accept" de um socket servidor
  // O ultimo parametro eh o tempo maximo (em milisegundos) para esperar
  // por dados; se for <0, que eh o default, espera indefinidamente.
  // Retorna o numero de bytes lidos (ou seja, len), em caso de sucesso,
  // zero, se retornou por timeout, ou SOCKET_ERRO, em caso de erro
  MYSOCKET_STATUS read(char *dado, size_t len, long milisec=-1) const;

  // Escreve um int32_t em um socket conectado
  // Retorna o numero de bytes enviados (ou seja, 4), em caso de sucesso,
  // ou SOCKET_ERRO
  MYSOCKET_STATUS write_int(const int32_t num) const;

  // Leh um int32_t de um socket conectado
  // O ultimo parametro eh o tempo maximo (em milisegundos) para esperar
  // por dados; se for <0, que eh o default, espera indefinidamente.
  // Retorna o numero de bytes lidos (ou seja, 4), em caso de sucesso,
  // zero, se retornou por timeout, ou SOCKET_ERRO, em caso de erro
  MYSOCKET_STATUS read_int(int32_t &num, long milisec=-1) const;

  // Escreve uma string em um socket conectado
  // Primeiro escreve o numero de bytes da string (int32_T), depois os caracteres
  // Retorna o numero de bytes enviados (ou seja, msg.size()), em caso de sucesso,
  // ou SOCKET_ERRO
  MYSOCKET_STATUS write_string(const string &msg) const;

  // Leh uma string de um socket conectado
  // Primeiro leh o numero de bytes da string (int32_T), depois os caracteres
  // O ultimo parametro eh o tempo maximo (em milisegundos) para esperar
  // por dados; se for <0, que eh o default, espera indefinidamente.
  // Retorna o numero de bytes lidos (ou seja, msg.size()), em caso de sucesso,
  // zero, se retornou por timeout, ou SOCKET_ERRO, em caso de erro
  MYSOCKET_STATUS read_string(string &msg, long milisec=-1) const;

};

class tcp_mysocket_server: public mysocket
{
public:

  // Construtor default
  inline tcp_mysocket_server(): mysocket() {}

  // Abre um novo socket para esperar conexoes
  // Soh pode ser usado em sockets "virgens" ou explicitamente fechados
  // Retorna SOCKET_OK ou SOCKET_ERRO
  MYSOCKET_STATUS listen(const char *port, int nconex=1);

  // Aceita uma conexao que chegou em um socket aberto
  // Soh pode ser usado em socket para o qual tenha sido feito um "listen" antes
  // O socket "a" passado como parametro, em caso de sucesso, estarah conectado
  // (nao-conectado em caso de erro)
  // Retorna SOCKET_OK ou SOCKET_ERRO
  MYSOCKET_STATUS accept(tcp_mysocket &a) const;

};

/* #############################################################
   ##  A fila de sockets                                      ##
   ############################################################# */

class mysocket_queue
{
 private:

  fd_set set;

  // Construtor por copia
  // NUNCA DEVE SER CHAMADO OU UTILIZADO
  mysocket_queue(const mysocket_queue &S);

  // Operador de atribuicao
  // NUNCA DEVE SER CHAMADO OU UTILIZADO
  void operator=(const mysocket_queue &S);

 public:
  // Limpa a lista de sockets
  inline void clean() {FD_ZERO(&set);};

  // Construtor e destrutor
  inline mysocket_queue() {clean();}
  inline ~mysocket_queue() {clean();}

  // Adiciona um socket a uma fila de sockets
  // Retorna SOCKET_OK ou SOCKET_ERRO
  MYSOCKET_STATUS include(const mysocket &a);

  // Retira um socket de uma fila de sockets
  // Retorna SOCKET_OK ou SOCKET_ERRO
  MYSOCKET_STATUS exclude(const mysocket &a);

  // Bloqueia ateh haver alguma atividade de leitura em socket da fila
  // Retorna o numero de sockets (>0) que tem dados a serem lidos,
  // em caso de sucesso; zero, se retornou por timeout, ou SOCKET_ERRO, em caso de erro
  MYSOCKET_STATUS wait_read(long milisec=-1);

  // Bloqueia ateh haver alguma atividade de conexao em socket da fila
  // Retorna o numero de sockets (>0) que tem conexoes a serem lidos,
  // em caso de sucesso; zero, se retornou por timeout, ou SOCKET_ERRO, em caso de erro
  inline MYSOCKET_STATUS wait_connect(long milisec=-1) {return wait_read(milisec);}

  // Bloqueia ateh haver alguma atividade de escrita em socket da fila
  // Retorna o numero de sockets (>0) que tiveram dados escritos,
  // em caso de sucesso; zero, se retornou por timeout, ou SOCKET_ERRO, em caso de erro
  MYSOCKET_STATUS wait_write(long milisec=-1);

  // Testa se houve atividade em um socket especifico da fila
  bool had_activity(const mysocket &a);

  // Impressao
  friend std::ostream& operator<<(std::ostream& os, const mysocket_queue &);

};

#endif
