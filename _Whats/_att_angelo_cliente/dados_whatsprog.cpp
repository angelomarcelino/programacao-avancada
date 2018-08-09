#include "dados_whatsprog.h"

bool Mensagem::setId(int32_t I)
{
  if (I<=0)
  {
    return false;
  }
  id=I;
  return true;
}

bool Mensagem::setRemetente(const string &R)
{
  if (R.size()<TAM_MIN_NOME_USUARIO || R.size()>TAM_MAX_NOME_USUARIO)
  {
    return false;
  }
  remetente=R;
  return true;
}

bool Mensagem::setDestinatario(const string &D)
{
  if (D.size()<TAM_MIN_NOME_USUARIO || D.size()>TAM_MAX_NOME_USUARIO)
  {
    return false;
  }
  destinatario=D;
  return true;
}

bool Mensagem::setTexto(const string &T)
{
  if (T.size()==0 || T.size()>TAM_MAX_MSG)
  {
    return false;
  }
  texto=T;
  return true;
}


bool Mensagem::setStatus(MsgStatus S)
{
  if (S!=MSG_ENVIADA && S!=MSG_RECEBIDA && S!=MSG_ENTREGUE && S!=MSG_LIDA)
  {
    return false;
  }
  status=S;
  return true;
}
