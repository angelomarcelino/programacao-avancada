#include <iostream>     /* cerr */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sstream>      /* stringstream */
#include "dados_servidor.h"

// Fixa login e senha do usuario
// Retorna true se OK; false em caso de erro
bool Usuario::setUsuario(const string &L, const string &S)
{
  if (L.size()<TAM_MIN_NOME_USUARIO || L.size()>TAM_MAX_NOME_USUARIO ||
      S.size()<TAM_MIN_SENHA || S.size()>TAM_MAX_SENHA)
  {
    return false;
  }
  login=L;
  senha=S;
  return true;
}

bool Usuario::setLastId(int32_t ID)
{
  if (ID<=0 || ID<=last_id)
  {
    return false;
  }
  last_id = ID;
  return true;
}
