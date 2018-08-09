#ifndef DADOS_WHATSPROG_H
#define DADOS_WHATSPROG_H

#include <string>
#include <stdint.h>


#include <list>

using namespace std;

// A porta de comunicacao cliente-servidor
#define PORTA_WHATSPROG "23456"

// Timeout (em segundos) para esperar o envio de um dado obrigatorio pelo socket
#define TIMEOUT_WHATSPROG 30
// Timeout (em segundos)  para o cliente enviar o nome de login apos conexao
#define TIMEOUT_LOGIN_WHATSPROG 60

// Numero de bytes das informacoes a serem enviadas/recebidas
#define TAM_MIN_NOME_USUARIO 6
#define TAM_MAX_NOME_USUARIO 12
#define TAM_MIN_SENHA 6
#define TAM_MAX_SENHA 12
#define TAM_MAX_MSG 255

/// Os possiveis estados de uma mensagem
enum MsgStatus {
    MSG_ENVIADA=1,
    MSG_RECEBIDA=2,
    MSG_ENTREGUE=3,
    MSG_LIDA=4,
    MSG_INVALIDA=-1
};

enum ComandoWhatsProg {
    CMD_NEW_USER=1001,
    CMD_LOGIN_USER=1002,
    CMD_LOGIN_OK=1003,
    CMD_LOGIN_INVALIDO=1004,
    CMD_NOVA_MSG=1005,
    CMD_MSG_RECEBIDA=1006,
    CMD_MSG_ENTREGUE=1007,
    CMD_MSG_LIDA1=1008,
    CMD_MSG_LIDA2=1009,
    CMD_ID_INVALIDA=1010,
    CMD_USER_INVALIDO=1011,
    CMD_MSG_INVALIDA=1012,
    CMD_LOGOUT_USER=1013
};

typedef int MYSOCKET_STATUS;


/// Alguns tipos auxiliares que sao utilizados pelos algoritmos STL:
/// find, count, etc
/// Sao definidos diferentes tipos para que se possa fazer diferentes
/// buscas em uma lista de mensagens, sobrecarregando de formas diferentes
/// o operador == para cada um desses tipos

/// Testar mensagens com um dado remetente e status
class testRemetStatus {
    private:
        string remetente;
        MsgStatus status;
    public:
        inline testRemetStatus(string R, MsgStatus S): remetente(R), status(S) {}
        friend class Mensagem;
};

/// Testar mensagens com um dado destinatario e status
class testDestStatus {
    private:
        string destinatario;
        MsgStatus status;
    public:
        inline testDestStatus(string D, MsgStatus S): destinatario(D), status(S) {}
        friend class Mensagem;
};

/// Testar mensagens com um dado remetente e id
class testRemetId {
    private:
        string remetente;
        int32_t id;
    public:
        inline testRemetId(string R, int32_t I): remetente(R), id(I) {}
        friend class Mensagem;
};

/// As mensagens armazenadas no cliente e no servidor
class Mensagem {
    private:

        /// Identificador da mensagem
        int32_t id;

        /// Nomes do remetente e do destinatario
        string remetente;
        string destinatario;

        /// Texto da mensagem
        string texto;

        /// Estado (status) da mensagem
        MsgStatus status;

    public:

        /// Construtor especifico
        inline Mensagem(): id(0), remetente(""), destinatario(""),
            texto(""), status(MSG_INVALIDA) {}

        /// Funcoes de consulta/alteracao de parametros
        /// As funcoes de alteracao retornam false em caso de erro, true se OK

        inline int32_t getId() const {
            return id;
        }
        bool setId(int32_t I);

        inline const string &getRemetente() const {
            return remetente;
        }
        bool setRemetente(const string &R);

        inline const string &getDestinatario() const {
            return destinatario;
        }
        bool setDestinatario(const string &D);

        inline const string &getTexto() const {
            return texto;
        }
        bool setTexto(const string &T);

        inline MsgStatus getStatus() const {
            return status;
        }
        bool setStatus(MsgStatus S);

        /// Os testes de igualdade entre uma msg e os tipos auxiliares
        /// que sao utilizados pelos algoritmos STL: find, count, etc
        inline bool operator==(const testRemetStatus &T) const {
            return remetente==T.remetente && status==T.status;
        }
        inline bool operator==(const testDestStatus &T) const {
            return destinatario==T.destinatario && status==T.status;
        }
        inline bool operator==(const testRemetId &T) const {
            return remetente==T.remetente && id==T.id;
        }


};

/// Apelidos para uma lista de mensagens
typedef list<Mensagem> list_Mensagem;
typedef list_Mensagem::iterator iter_Mensagem;

#endif // DADOS_WHATSPROG_H
