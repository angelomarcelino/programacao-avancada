#ifndef _DADOS_SERVIDOR_
#define _DADOS_SERVIDOR_

#include <string>
#include <list>
#include "dados_whatsprog.h"
#include "mysocket.h"

using namespace std;

/// Os usuarios cadastrados no servidor
class Usuario
{
private:
  /// Identificacao do usuario
  string login;
  string senha;

  /// Socket de comunicacao (idle se nao conectado)
  tcp_mysocket s;

  /// Ultima id de mensagem recebida
  int32_t last_id;
public:
  /// Construtor default
  inline Usuario(): login(""), senha(""), s(), last_id(0) {}

  /// Funcoes de consulta e de fixacao de valor
  /// As funcoes de fixacao retornam true em caso de sucesso, false se erro
  inline const string& getLogin() const {return login;}
  inline const string& getSenha() const {return senha;}
  bool setUsuario(const string &L, const string &S);

  inline tcp_mysocket& getSocket() {return s;}
  inline bool setSocket(const tcp_mysocket &S) {s=S; return true;}

  inline int32_t getLastId() const {return last_id;}
  bool setLastId(int32_t ID);

  /// Teste de igualdade com uma string (testa se a string eh igual ao login)
  inline bool operator==(const string &L) const {return login==L;}
};

/// Apelidos para uma lista de usuarios
typedef list<Usuario> list_Usuario;
typedef list_Usuario::iterator iter_Usuario;

/// Os dados dos usuarios cadastrados (conectados ou nao)
/// serao armazenados em uma variavel global (LU)
extern list_Usuario LU;

#endif //DADOS_SERVIDOR_
