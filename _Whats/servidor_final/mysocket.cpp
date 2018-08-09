#include <iostream>

#include "mysocket.h"
#include "dados_whatsprog.h"



// As linhas necessarias para compilar no Linux
#ifdef _SOP_LINUX_
#define SD_SEND SHUT_WR
#define closesocket(x) close(x)
#include <sys/types.h>
#include <netdb.h>
#endif // _SOP_LINUX_


using namespace std;

/*********************************************
 A classe base mysocket
 *********************************************/

/// Permuta dois sockets
/// Geralmente, deve ser utilizado ao inves do operador de atribuicao
void mysocket::swap(mysocket &S) {
    SOCKET id_prov(id);
    id = S.id;
    S.id = id_prov;
}

/// Fecha (destroi) o socket
void mysocket::close() {
    if (id != INVALID_SOCKET) {
        ::closesocket(id);
    }
    id = INVALID_SOCKET;
}

/// Impressao
std::ostream& operator<<(std::ostream& os, const mysocket &s) {
    os << s.id;
    return os;
}

/*********************************************
 Sockets orientados a conexao (STREAM SOCKET)
 *********************************************/

// Sockets clientes

/// Se conecta a um socket aberto
/// Soh pode ser usado em sockets "virgens" ou explicitamente fechados
/// Retorna SOCKET_OK, se tudo deu certo, ou outro valor, em caso de erro
MYSOCKET_STATUS tcp_mysocket::connect(const char *name, const char *port) {
    if (id!=INVALID_SOCKET) {
        return(SOCKET_ERROR);
    }

    // The getaddrinfo function is used to determine the values in the sockaddr structure:
    // The getaddrinfo function provides protocol-independent translation from an ANSI host name to an address.
    // Parameters:
    // pNodeName: A pointer to a NULL-terminated ANSI string that contains a host name or a numeric host address as string
    //   NULL = any
    // pServiceName: A pointer to a NULL-terminated ANSI string that contains either a service name or port number as string
    //   DEFAULT_PORT ("27015") is the port number associated with the server that the client will connect to.
    // pHints: A pointer to an addrinfo structure that provides hints about the type of socket the caller supports.
    //   AF_INET is used to specify the IPv4 address family.
    //   SOCK_STREAM is used to specify a stream socket.
    //   IPPROTO_TCP is used to specify the TCP protocol .
    //   AI_PASSIVE flag indicates the caller intends to use the returned socket address structure in a call to the bind function.
    //     When the AI_PASSIVE flag is set and pNodeName parameter to the getaddrinfo function is a NULL pointer,
    //     the IP address portion of the socket address structure is set to INADDR_ANY for IPv4 addresses or
    //     IN6ADDR_ANY_INIT for IPv6 addresses.
    // ppResult: A pointer to a linked list of one or more addrinfo structures that contains response information about the host.

    struct addrinfo hints, *result = NULL;  // para getaddrinfo, bind
    MYSOCKET_STATUS iResult;

    memset(&hints, 0, sizeof (hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Call the getaddrinfo function requesting the IP address for the server.
    iResult = getaddrinfo(name, port, &hints, &result);
    if (iResult != 0) {
        return iResult;
    }

    // Create a SOCKET for the client to communicate with the server
    // Use the first IP address returned by the call to getaddrinfo that matched the address family, socket type, and protocol
    // specified in the hints parameter. In this example, a TCP stream socket was specified with a socket type of SOCK_STREAM
    // and a protocol of IPPROTO_TCP. The address family was left unspecified (AF_UNSPEC), so the returned IP address could be
    // either an IPv6 or IPv4 address for the server.
    id = ::socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (id == INVALID_SOCKET) {
        freeaddrinfo(result);
        return SOCKET_ERROR;
    }

    // Connect to server.
    iResult = ::connect( id, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        // Should really try the next address returned by getaddrinfo if the connect call failed
        // But for this simple example we just free the resources
        // returned by getaddrinfo and print an error message
        freeaddrinfo(result);
        close();
        return iResult;
    }

    // Once the connect function is called, the address information returned by the getaddrinfo function is no longer needed.
    // The freeaddrinfo function is called to free the memory allocated by the getaddrinfo function for this address information.
    freeaddrinfo(result);

    return(SOCKET_OK);
}

/// Leh de um socket conectado
/// Soh pode ser usado em socket para o qual tenha sido feito um "connect" antes
/// Ou entao em um socket retornado pelo "accept" de um socket servidor
/// O ultimo parametro eh o tempo maximo (em milisegundos) para esperar
/// por dados; se for <0, que eh o default, espera indefinidamente.
/// Retorna:
/// - o numero de bytes lidos (ou seja, len, >0), em caso de sucesso;
/// - SOCKET_TIMEOUT, se retornou por timeout;
/// - SOCKET_DISCONNECTED, se a conexao foi fechada corretamente; ou
/// - SOCKET_ERRO, em caso de erro
MYSOCKET_STATUS tcp_mysocket::read(char *dado, size_t len, long milisec) const {
    if (!connected() || len<=0) {
        return(SOCKET_ERROR);
    }
    if (milisec>=0) {
        // Com timeout
        mysocket_queue f;
        f.include(*this);
        MYSOCKET_STATUS iResult=f.wait_read(milisec);
        if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT) {
            return iResult;
        }
    }

    int ultima_leitura,recebidos=0,falta_receber=len;
    do {
        // recv: receives data from a connected socket
        // Parameters:
        // s: The descriptor that identifies a connected socket.
        // buf: A pointer to the buffer to receive the incoming data.
        // len: The length, in bytes, of the buffer pointed to by the buf parameter.
        // flags: A set of flags that influences the behavior of this function.
        ultima_leitura = ::recv(id,dado,falta_receber,0);

        if ( ultima_leitura == 0 ) {
            // Servidor desconectou
            return SOCKET_DISCONNECTED;
        }
        if ( ultima_leitura == SOCKET_ERROR ) {
            // Deu erro
            return SOCKET_ERROR;
        }
        recebidos += ultima_leitura;
        falta_receber -= ultima_leitura;
        if (falta_receber > 0) {
            dado += ultima_leitura;
        }
    } while (falta_receber>0);
    return(recebidos);
}

/// Escreve em um socket conectado
/// Soh pode ser usado em socket para o qual tenha sido feito um "connect" antes
/// Ou entao em um socket retornado pelo "accept" de um socket servidor
/// Retorna:
/// - o numero de bytes enviados (ou seja, len), em caso de sucesso; ou
/// - SOCKET_ERRO, em caso de erro
MYSOCKET_STATUS tcp_mysocket::write(const char *dado, size_t len) const {
    if (!connected()) {
        return(SOCKET_ERROR);
    }
    if (len==0) {
        return(SOCKET_ERROR);
    }

    int ultimo_envio,enviados=0,falta_enviar=len;
    do {
        // send: sends data on a connected socket
        // Parameters:
        // s: The descriptor that identifies a connected socket.
        // buf: A pointer to a buffer containing the data to be transmitted.
        // len: length, in bytes, of the data in buffer pointed to by the buf parameter.
        // flags: A set of flags that specify the way in which the call is made.
        ultimo_envio = ::send(id, dado, falta_enviar, 0);

        if ( ultimo_envio == SOCKET_ERROR ) {
            return ultimo_envio;
        }
        enviados += ultimo_envio;
        falta_enviar -= ultimo_envio;
        if (falta_enviar > 0) {
            dado += ultimo_envio;
        }
    } while (falta_enviar>0);
    return(enviados);
}

/// Leh um int32_t de um socket conectado
/// O ultimo parametro eh o tempo maximo (em milisegundos) para esperar
/// por dados; se for <0, que eh o default, espera indefinidamente.
/// Retorna:
/// - o numero de bytes lidos (ou seja, 4), em caso de sucesso;
/// - SOCKET_TIMEOUT, se retornou por timeout;
/// - SOCKET_DISCONNECTED, se a conexao foi fechada corretamente; ou
/// - SOCKET_ERRO, em caso de erro
MYSOCKET_STATUS tcp_mysocket::read_int(int32_t &num, long milisec) const {
    MYSOCKET_STATUS iResult;

    iResult = read((char*)&num,sizeof(num),milisec); // sizeof(num) == 4
    return iResult;
}

/// Escreve um int32_t em um socket conectado
/// Retorna o numero de bytes enviados (ou seja, 4), em caso de sucesso,
/// ou SOCKET_ERRO
MYSOCKET_STATUS tcp_mysocket::write_int(const int32_t num) const {
    MYSOCKET_STATUS iResult;

    iResult = write((char*)&num,sizeof(num)); // sizeof(num) == 4
    return iResult;
}

/// Leh uma string de um socket conectado
/// Primeiro leh o numero de bytes da string (int32_T), depois os caracteres
/// O ultimo parametro eh o tempo maximo (em milisegundos) para esperar
/// por dados; se for <0, que eh o default, espera indefinidamente.
/// Retorna:
/// - o numero de bytes lidos (ou seja, msg.size()), em caso de sucesso;
/// - SOCKET_TIMEOUT, se retornou por timeout;
/// - SOCKET_DISCONNECTED, se a conexao foi fechada corretamente; ou
/// - SOCKET_ERRO, em caso de erro
MYSOCKET_STATUS tcp_mysocket::read_string(string &msg, long milisec) const {
    static char buffer[TAM_MAX_MSG_STRING+1];
    int32_t len;
    MYSOCKET_STATUS iResult;

    // Le o numero de caracteres da string
    iResult = read_int(len,milisec);
    if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT || iResult==SOCKET_DISCONNECTED) {
        // Erro ou timeout ou desconexao
        msg = "";
        return iResult;
    }
    if (len > TAM_MAX_MSG_STRING) {
        // Msg muito grande
        msg = "";
        return SOCKET_ERROR;
    }
    // Le os caracteres da string
    iResult = read(buffer,len,milisec);
    if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT || iResult==SOCKET_DISCONNECTED) {
        // Erro ou timeout ou desconexao
        msg = "";
        return iResult;
    }
    if ( iResult != len ) {
        // Erro de tamanho da msg
        msg = "";
        return SOCKET_ERROR;
    }
    // Retorna uma string C++ a partir de buffer, que eh um array de char ("string" C)
    buffer[len] = 0;
    msg = buffer;  // Faz a conversao de char* para string ao atribuir
    return iResult;
}





/// Escreve uma string em um socket conectado
/// Primeiro escreve o numero de bytes da string (int32_T), depois os caracteres
/// Retorna o numero de bytes enviados (ou seja, msg.size()), em caso de sucesso,
/// ou SOCKET_ERRO
MYSOCKET_STATUS tcp_mysocket::write_string(const string &msg) const {
    int32_t len;
    MYSOCKET_STATUS iResult;

    len = msg.size();
    iResult = write_int(len);
    if (iResult == SOCKET_ERROR) {
        return SOCKET_ERROR;
    }
    iResult = write(msg.c_str(),len);
    if ( iResult != len ) {
        return SOCKET_ERROR;
    }
    return iResult;
}

// Sockets servidores

/// Abre um novo socket para esperar conexoes
/// Soh pode ser usado em sockets "virgens" ou explicitamente fechados
/// Retorna SOCKET_OK ou SOCKET_ERRO
MYSOCKET_STATUS tcp_mysocket_server::listen(const char *port, int nconex) {
    if (id!=INVALID_SOCKET) {
        return(SOCKET_ERROR);
    }
    // Cria o socket

    // The getaddrinfo function is used to determine the values in the sockaddr structure:
    // The getaddrinfo function provides protocol-independent translation from an ANSI host name to an address.
    // Parameters:
    // pNodeName: A pointer to a NULL-terminated ANSI string that contains a host name or a numeric host address as string
    //   NULL = any
    // pServiceName: A pointer to a NULL-terminated ANSI string that contains either a service name or port number as string
    //   DEFAULT_PORT ("27015") is the port number associated with the server that the client will connect to.
    // pHints: A pointer to an addrinfo structure that provides hints about the type of socket the caller supports.
    //   AF_INET is used to specify the IPv4 address family.
    //   SOCK_STREAM is used to specify a stream socket.
    //   IPPROTO_TCP is used to specify the TCP protocol .
    //   AI_PASSIVE flag indicates the caller intends to use the returned socket address structure in a call to the bind function.
    //     When the AI_PASSIVE flag is set and pNodeName parameter to the getaddrinfo function is a NULL pointer,
    //     the IP address portion of the socket address structure is set to INADDR_ANY for IPv4 addresses or
    //     IN6ADDR_ANY_INIT for IPv6 addresses.
    // ppResult: A pointer to a linked list of one or more addrinfo structures that contains response information about the host.

    struct addrinfo hints, *result = NULL;  // para getaddrinfo, bind
    MYSOCKET_STATUS iResult;

    memset(&hints, 0, sizeof (hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the local address and port to be used by the server
    iResult = getaddrinfo(NULL, port, &hints, &result);
    if (iResult != 0) {
        cerr << "mysocket listen - getaddrinfo failed\n";
        return SOCKET_ERROR;
    }

    // Create a SOCKET for the server to listen for client connections
    // Use the first IP address returned by the call to getaddrinfo that matched the address family, socket type, and protocol
    // specified in the hints parameter
    id = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (id == INVALID_SOCKET) {
        cerr << "mysocket listen - error at socket()\n";
        freeaddrinfo(result);
        return SOCKET_ERROR;
    }

    // Atribuicao do nome do socket

    // For a server to accept client connections, it must be bound to a network address within the system.
    // Call the bind function, passing the created socket and sockaddr structure returned from the getaddrinfo function as parameters.
    // Setup the TCP listening socket
    iResult = bind( id, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        cerr << "mysocket listen - bind failed\n";
        freeaddrinfo(result);
        close();
        return SOCKET_ERROR;
    }

    // Once the bind function is called, the address information returned by the getaddrinfo function is no longer needed.
    // The freeaddrinfo function is called to free the memory allocated by the getaddrinfo function for this address information.
    freeaddrinfo(result);

    // After the socket is bound to an IP address and port on the system,
    // the server must then listen on that IP address and port for incoming connection requests
    // Parameters:
    // s: A descriptor identifying a bound, unconnected socket.
    // backlog: The maximum length of the queue of pending connections.
    //   If set to SOMAXCONN, will set the backlog to a maximum reasonable value.
    // the created socket and a value for the maximum length of the queue of pending connections to accept
    iResult = ::listen( id, nconex );
    if ( iResult == SOCKET_ERROR ) {
        close();
        return SOCKET_ERROR;
    }

    return SOCKET_OK;
}

/// Aceita uma conexao que chegou em um socket aberto
/// Soh pode ser usado em socket para o qual tenha sido feito um "listen" antes
/// O socket "a" passado como parametro, em caso de sucesso, estarah conectado
/// (nao-conectado em caso de erro)
/// Retorna SOCKET_OK ou SOCKET_ERRO
MYSOCKET_STATUS tcp_mysocket_server::accept(tcp_mysocket &a) const {
    if (!accepting()) {
        return SOCKET_ERROR;
    }
    a.id = ::accept(id,NULL,NULL);
    if (a.id == INVALID_SOCKET) {
        return SOCKET_ERROR;
    }
    return SOCKET_OK;
}

/*********************************************
A CLASSE mysocket_queue (FILA DE SOCKETS)
*********************************************/

/// Adiciona um socket a uma fila de sockets
/// Retorna SOCKET_OK ou SOCKET_ERRO
MYSOCKET_STATUS mysocket_queue::include(const mysocket &a) {
    FD_SET(a.id,&set);
    return(SOCKET_OK);
}

/// Retira um socket de uma fila de sockets
/// Retorna SOCKET_OK ou SOCKET_ERRO
MYSOCKET_STATUS mysocket_queue::exclude(const mysocket &a) {
    if (FD_ISSET(a.id,&set)) {
        FD_CLR(a.id,&set);
        return(SOCKET_OK);
    }
    return(SOCKET_ERROR);
}

/// Bloqueia ateh haver alguma atividade de leitura em socket da fila
/// Retorna:
/// - o numero de sockets (>0) que tem dados a serem lidos em caso de sucesso;
/// - SOCKET_TIMEOUT, se retornou por timeout; ou
/// - SOCKET_ERRO, em caso de erro
MYSOCKET_STATUS mysocket_queue::wait_read(long milisec) {
    int iResult;
    if (milisec >= 0) {
        struct timeval t;
        t.tv_sec = milisec/1000;
        t.tv_usec = 1000*(milisec - 1000*t.tv_sec);
        iResult = ::select(0, &set, NULL, NULL, &t);
    } else {
        iResult = ::select(0, &set, NULL, NULL, NULL);
    }
    if (iResult<0) return SOCKET_ERROR;
    if (iResult==0) return SOCKET_TIMEOUT;
    return iResult;
}

/// Bloqueia ateh haver alguma atividade de escrita em socket da fila
/// Retorna:
/// - o numero de sockets (>0) que tem dados a serem lidos em caso de sucesso;
/// - SOCKET_TIMEOUT, se retornou por timeout; ou
/// - SOCKET_ERRO, em caso de erro
MYSOCKET_STATUS mysocket_queue::wait_write(long milisec) {
    int iResult;
    if (milisec >= 0) {
        struct timeval t;
        t.tv_sec = milisec/1000;
        t.tv_usec = 1000*(milisec - 1000*t.tv_sec);
        iResult = ::select(0, NULL, &set, NULL, &t);
    } else {
        iResult = ::select(0, NULL, &set, NULL, NULL);
    }
    if (iResult<0) return SOCKET_ERROR;
    if (iResult==0) return SOCKET_TIMEOUT;
    return iResult;
}

// Testa se houve atividade em um socket especifico da fila
bool mysocket_queue::had_activity(const mysocket &a) {
    return(FD_ISSET(a.id,&set));
}





