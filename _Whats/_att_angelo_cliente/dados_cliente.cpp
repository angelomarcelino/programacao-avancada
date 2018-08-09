#include "dados_cliente.h"
#include <algorithm>

bool Conversa::setCorrespondente(const string &U)
{
  if (U.size()<TAM_MIN_NOME_USUARIO || U.size()>TAM_MAX_NOME_USUARIO)
  {
    return false;
  }
  correspondente = U;
  return true;
}

Mensagem& Conversa::operator[](unsigned i)
{
  static Mensagem vazia;
  return (i<size() ? LM[i] : vazia);
}

const Mensagem& Conversa::operator[](unsigned i) const
{
  static Mensagem vazia;
  return (i<size() ? LM[i] : vazia);
}

/// Remove a i-esima msg
void Conversa::eraseMessage(unsigned i)
{
  if (i<size())
  {
    LM.erase(LM.begin()+i);
  }
}

unsigned Conversa::getNumMsgsEntregues() const
{
  return count(LM.begin(), LM.end(), testRemetStatus(correspondente, MSG_ENTREGUE));
}

void DadosCliente::clearServidorUsuario()
{
  servidor = "";
  meuUsuario = "";
  setIndexConversaAtual(-1);
  clearConversas();
}

bool DadosCliente::setServidorUsuario(const string &IP, const string &MU)
{
  // Sempre que altera a conexao, apaga todas as conversas
  setIndexConversaAtual(-1);
  clearConversas();

  if (IP=="" || MU.size()<TAM_MIN_NOME_USUARIO || MU.size()>TAM_MAX_NOME_USUARIO)
  {
    servidor = "";
    meuUsuario = "";
    return false;
  }
  servidor = IP;
  meuUsuario = MU;
  return true;
}

Conversa &DadosCliente::operator[](unsigned i)
{
  static Conversa vazia;
  return (i<size() ? LC[i] : vazia);
}

/// Retorna o indice de uma conversa cujo correspondente seja igual ao parametro
/// Retorna um numero negativo caso nao exista a conversa
int DadosCliente::getIndexConversa(const string &U) const
{
  vector<Conversa>::const_iterator i=find(LC.begin(), LC.end(), U);
  if (i==LC.end()) return -1;
  return i-LC.begin();
}

// Cria nova conversa com o nome do usuario passado como parametro
bool DadosCliente::insertConversa(const string &U)
{
  Conversa C;
  if (!C.setCorrespondente(U)) return false; // Erro na atribuicao do nome da conversa
  LC.push_back(C);
  return true;
}

bool DadosCliente::eraseConversa(unsigned i)
{
  if (i >= size())
  {
    return false;
  }
  // Apaga a conversa
  LC.erase(LC.begin()+i);
  // Faz com que nenhuma conversa esteja selecionada
  indexConversa = -1;

  return true;
}

/// Procura uma mensagem pela id, em todas as conversas
/// Recebe como parametro a id de uma mensagem e retorna dois indices:
/// o indice da conversa onde estah a mensagem que tem essa id
/// e o indice da mensagem dentro dessa conversa
/// Caso nao exista em nenhuma conversa uma msg com essa id,
/// retorna os dois indices negativos
void DadosCliente::findIndexMensagem(int32_t id, int& ind_conv, int& ind_msg) const
{
  for (ind_conv=0; ind_conv<(int)LC.size(); ind_conv++)
  {
    for (ind_msg=0; ind_msg<(int)LC[ind_conv].size(); ind_msg++)
    {
      if (LC[ind_conv][ind_msg].getId() == id) return;
    }
  }
  ind_conv = ind_msg = -1;
}

bool DadosCliente::setIndexConversaAtual(int IND)
{
  if (IND >= (int)size())
  {
    indexConversa = -1;
    return false;
  }
  indexConversa = IND;
  return true;
}

