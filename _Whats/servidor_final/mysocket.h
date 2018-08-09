#ifndef _MYSOCKET_H_
#define _MYSOCKET_H_

#include <iostream>
#include <string>
#include "dados_whatsprog.h"


/* #############################################################
   ##  ATENCAO: VOCE DEVE DESCOMENTAR UMA DAS LINHAS ABAIXO   ##
   ##  PARA PODER COMPILAR NO WINDOWS OU NO LINUX             ##
   ############################################################# */
#define _SOP_WINDOWS_
//#define _SOP_LINUX_

// As linhas necessarias para compilar no Windows
#ifdef _SOP_WINDOWS_
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x501
#endif // _WIN32_WINNT
#include <winsock2.h>
#include <ws2tcpip.h>
#endif // _SOP_WINDOWS_

// As linhas necessarias para compilar no Linux

typedef int MYSOCKET_STATUS;

#define SOCKET_OK 0
// Valor de retorno quando o outro socket encerrou a conexao corretamente
#define SOCKET_DISCONNECTED -666
// Valor de retorno em caso de timeout
#define SOCKET_TIMEOUT -999

#define TAM_MAX_MSG_STRING 256

// Predefinicao das classes
class mysocket_queue;
class tcp_mysocket;
class tcp_mysocket_server;

/* #############################################################
   ##  A classe base dos sockets                              ##
   ############################################################# */

class mysocket {
    private:

        SOCKET id;

    public:

        /// Construtor por default
        inline mysocket(): id(INVALID_SOCKET) {}

        /// Permuta dois sockets
        /// Geralmente, deve ser utilizado ao inves do operador de atribuicao
        void swap(mysocket &S);

        /// Fecha (caso esteja aberto) um socket
        void close();

        /// Testa se um socket eh "virgem" ou foi fechado
        inline bool closed() const {
            return id==INVALID_SOCKET;
        }
        /// Testa se um socket estah aberto (aceitando conexoes)
        inline bool accepting() const {
            return !closed();
        }
        /// Testa se um socket estah conectado (pronto para ler e escrever)
        inline bool connected() const {
            return !closed();
        }

        /// Imprime um socket
        friend std::ostream& operator<<(std::ostream& os, const mysocket &);

        /// As classes amigas
        friend class tcp_mysocket;
        friend class tcp_mysocket_server;
        friend class mysocket_queue;
};

/* #############################################################
   ##  As classes dos sockets orientados a conexao (TCP)      ##
   ############################################################# */

class tcp_mysocket: public mysocket {
    public:

        /// Construtor default
        inline tcp_mysocket(): mysocket() {}

        /// Se conecta a um socket aberto
        /// Soh pode ser usado em sockets "virgens" ou explicitamente fechados
        /// Retorna SOCKET_OK, se tudo deu certo, ou outro valor, em caso de erro
        MYSOCKET_STATUS connect(const char *name, const char *port);

        /// Leh de um socket conectado
        /// Soh pode ser usado em socket para o qual tenha sido feito um "connect" antes
        /// Ou entao em um socket retornado pelo "accept" de um socket servidor
        /// O ultimo parametro eh o tempo maximo (em milisegundos) para esperar
        /// por dados; se for <0, que eh o default, espera indefinidamente.
        /// Retorna:
        /// - o numero de bytes lidos (ou seja, len, >0), em caso de sucesso;
        /// - SOCKET_TIMEOUT, se retornou por timeout;
        /// - SOCKET_DISCONNECTED, se a conexao foi fechada corretamente; ou
        /// - SOCKET_ERRO, em caso de erroiResult = read_string(login,milisec);

        MYSOCKET_STATUS read(char *dado, size_t len, long milisec=-1) const;

        /// Escreve em um socket conectado
        /// Soh pode ser usado em socket para o qual tenha sido feito um "connect" antes
        /// Ou entao em um socket retornado pelo "accept" de um socket servidor
        /// Retorna:
        /// - o numero de bytes enviados (ou seja, len), em caso de sucesso; ou
        /// - SOCKET_ERRO, em caso de erro
        MYSOCKET_STATUS write(const char* dado, size_t len) const;

        /// Leh um int32_t de um socket conectado
        /// O ultimo parametro eh o tempo maximo (em milisegundos) para esperar
        /// por dados; se for <0, que eh o default, espera indefinidamente.
        /// Retorna:
        /// - o numero de bytes lidos (ou seja, 4), em caso de sucesso;
        /// - SOCKET_TIMEOUT, se retornou por timeout;
        /// - SOCKET_DISCONNECTED, se a conexao foi fechada corretamente; ou
        /// - SOCKET_ERRO, em caso de erro
        MYSOCKET_STATUS read_int(int32_t &num, long milisec=-1) const;

        /// Escreve um int32_t em um socket conectado
        /// Retorna o numero de bytes enviados (ou seja, 4), em caso de sucesso,
        /// ou SOCKET_ERRO
        MYSOCKET_STATUS write_int(const int32_t num) const;

        /// Leh uma string de um socket conectado
        /// Primeiro leh o numero de bytes da string (int32_T), depois os caracteres
        /// O ultimo parametro eh o tempo maximo (em milisegundos) para esperar
        /// por dados; se for <0, que eh o default, espera indefinidamente.
        /// Retorna:
        /// - o numero de bytes lidos (ou seja, msg.size()), em caso de sucesso;
        /// - SOCKET_TIMEOUT, se retornou por timeout;
        /// - SOCKET_DISCONNECTED, se a conexao foi fechada corretamente; ou
        /// - SOCKET_ERRO, em caso de erro
        MYSOCKET_STATUS read_string(std::string &msg, long milisec=-1) const;


        /// Escreve uma string em um socket conectado
        /// Primeiro escreve o numero de bytes da string (int32_T), depois os caracteres
        /// Retorna o numero de bytes enviados (ou seja, msg.size()), em caso de sucesso,
        /// ou SOCKET_ERRO
        MYSOCKET_STATUS write_string(const std::string &msg) const;

};

class tcp_mysocket_server: public mysocket {
    public:

        /// Construtor default
        inline tcp_mysocket_server(): mysocket() {}

        /// Abre um novo socket para esperar conexoes
        /// Soh pode ser usado em sockets "virgens" ou explicitamente fechados
        /// Retorna SOCKET_OK ou SOCKET_ERRO
        MYSOCKET_STATUS listen(const char *port, int nconex=1);

        /// Aceita uma conexao que chegou em um socket aberto
        /// Soh pode ser usado em socket para o qual tenha sido feito um "listen" antes
        /// O socket "a" passado como parametro, em caso de sucesso, estarah conectado
        /// (nao-conectado em caso de erro)
        /// Retorna SOCKET_OK ou SOCKET_ERRO
        MYSOCKET_STATUS accept(tcp_mysocket &a) const;

};

/* #############################################################
   ##  A fila de sockets                                      ##
   ############################################################# */

class mysocket_queue {
    private:

        fd_set set;

        /// Construtor por copia
        /// NUNCA DEVE SER CHAMADO OU UTILIZADO
        mysocket_queue(const mysocket_queue &S);

        /// Operador de atribuicao
        /// NUNCA DEVE SER CHAMADO OU UTILIZADO
        void operator=(const mysocket_queue &S);

    public:
        /// Limpa a lista de sockets
        inline void clean() {
            FD_ZERO(&set);
        };

        /// Construtor e destrutor
        inline mysocket_queue() {
            clean();
        }
        inline ~mysocket_queue() {
            clean();
        }

        /// Adiciona um socket a uma fila de sockets
        /// Retorna SOCKET_OK ou SOCKET_ERRO
        MYSOCKET_STATUS include(const mysocket &a);

        /// Retira um socket de uma fila de sockets
        /// Retorna SOCKET_OK ou SOCKET_ERRO
        MYSOCKET_STATUS exclude(const mysocket &a);

        /// Bloqueia ateh haver alguma atividade de leitura em socket da fila
        /// Retorna:
        /// - o numero de sockets (>0) que tem dados a serem lidos em caso de sucesso;
        /// - SOCKET_TIMEOUT, se retornou por timeout; ou
        /// - SOCKET_ERRO, em caso de erro
        MYSOCKET_STATUS wait_read(long milisec=-1);

        /// Bloqueia ateh haver alguma atividade de conexao em socket da fila
        /// Retorna:
        /// - o numero de sockets (>0) que tem dados a serem lidos em caso de sucesso;
        /// - SOCKET_TIMEOUT, se retornou por timeout; ou
        /// - SOCKET_ERRO, em caso de erro
        inline MYSOCKET_STATUS wait_connect(long milisec=-1) {
            return wait_read(milisec);
        }

        /// Bloqueia ateh haver alguma atividade de escrita em socket da fila
        /// Retorna:
        /// - o numero de sockets (>0) que tem dados a serem lidos em caso de sucesso;
        /// - SOCKET_TIMEOUT, se retornou por timeout; ou
        /// - SOCKET_ERRO, em caso de erro
        MYSOCKET_STATUS wait_write(long milisec=-1);

        /// Testa se houve atividade em um socket especifico da fila
        bool had_activity(const mysocket &a);

};

#endif
