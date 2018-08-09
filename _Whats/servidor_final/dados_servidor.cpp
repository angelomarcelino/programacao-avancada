#include <iostream>     /* cerr */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sstream>      /* stringstream */
#include "dados_servidor.h"

// Fixa login e senha do usuario
// Retorna true se OK; false em caso de erro
bool Usuario::setUsuario(const string &L, const string &S) {
    if (L.size()<TAM_MIN_NOME_USUARIO || L.size()>TAM_MAX_NOME_USUARIO ||
            S.size()<TAM_MIN_SENHA || S.size()>TAM_MAX_SENHA) {
        return false;
    }
    login=L;
    senha=S;
    return true;
}

bool Usuario::setLastId(int32_t ID) {
    if (ID<=0 || ID<=last_id) {
        return false;
    }
    last_id = ID;
    return true;
}

MYSOCKET_STATUS Usuario::read_usuario(tcp_mysocket t, long milisec) {
    //string login,senha;
    MYSOCKET_STATUS iResult;
    iResult = t.read_string(login,milisec);
    if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT || iResult==SOCKET_DISCONNECTED) {
        // Erro ou timeout ou desconexao
        login = "";
        return iResult;
    }

    iResult = t.read_string(senha,milisec);
    if (iResult==SOCKET_ERROR || iResult==SOCKET_TIMEOUT || iResult==SOCKET_DISCONNECTED) {
        // Erro ou timeout ou desconexao
        login = "";
        senha = "";
        return iResult;
    }
    if(login.size() > TAM_MAX_NOME_USUARIO || login.size() < TAM_MIN_NOME_USUARIO ||
            senha.size() > TAM_MAX_SENHA || senha.size() < TAM_MIN_SENHA) {
        login = "";
        senha = "";
        return iResult;
    }
    return iResult;

}


