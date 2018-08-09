#ifndef DADOS_CLIENTE_H
#define DADOS_CLIENTE_H

#include <string>
#include <vector>
#include <stdint.h>
#include "dados_whatsprog.h"
#include "mysocket.h"
#include "whatsclient.h"

using namespace std;

typedef vector<Mensagem>::const_iterator itr_Msg;

// Classe utilizada para armazenar as conversas no cliente
class Conversa
{
private:
  /// Correspondente (outro participante da conversa). O "meuUsuario" (ver classe DadosCliente a seguir)
  /// e o "correspondente" devem ser o remetente ou o destinatario de todas as mensagens da conversa.
  string correspondente;

  /// Todas as mensagens da conversa
  vector<Mensagem> LM;
public:
  /// Construtor default
  inline Conversa(): correspondente(""), LM() {}

  /// Retorna o numero de mensagens da conversa
  inline unsigned size() const {return LM.size();}

  /// Retorna a i-esima mensagem da conversa (const e nao const)
  const Mensagem &operator[](unsigned i) const;
  Mensagem &operator[](unsigned i);

  /// Apaga todas as msgs da conversa
  inline void clearMessages() {LM.clear();}

  /// Insere nova msg no final da conversa
  inline void pushMessage(const Mensagem &M) {LM.push_back(M);}

  /// Remove ultima msg (do final da conversa)
  inline void popMessage() {LM.pop_back();}

  /// Remove a i-esima msg
  void eraseMessage(unsigned i);

  /// Retorna o numero de msgs entregues mas ainda nao lidas de uma conversa
  unsigned getNumMsgsEntregues() const;

  /// Funcoes de consulta/alteracao dos demais parametros
  /// As funcoes de alteracao retornam false em caso de erro, true se OK
  inline const string &getCorrespondente() const {return correspondente;}
  bool setCorrespondente(const string &U);

  inline vector<Mensagem>::const_iterator begin() const {return LM.begin();}
  inline vector<Mensagem>::const_iterator end() const {return LM.end();}

  /// Teste de igualdade entre uma consulta e uma string
  /// Utilizado pelos algoritmos STL: find, count, etc
  inline bool operator==(const string &C) const {return correspondente==C;}
};

class DadosCliente
{
private:
  /// O computador (IP) onde roda o programa servidor
  string servidor;

  /// O nome do usuario do cliente
  string meuUsuario;

  /// O indice da conversa atualmente sendo visualizada
  /// De 0 acima; se negativo, nenhuma conversa estah selecionada
  int indexConversa;

  /// A ultima ID utilizada em msg enviada por mim
  /// Maior que zero; se igual a 0, nenhuma msg foi enviada ainda
  uint32_t idMensagem;

  /// Todas as conversas
  vector<Conversa> LC;
public:
  ///  Construtor default
  inline DadosCliente():
      servidor(""),meuUsuario(""),indexConversa(-1),idMensagem(0),LC() {}

  /// Funcoes de consulta dos dados principais (servidor, login do usuario)
  inline const string &getServidor() const {return servidor;}
  inline const string &getMeuUsuario() const {return meuUsuario;}

  /// Limpa o servidor e o nome do usuario (deslogar)
  void clearServidorUsuario();

  /// Define os parametros principais da conexao: servidor e usuario (login)
  /// Retorna false em caso de erro, true se OK
  bool setServidorUsuario(const string &IP, const string &MU);

  /// Retorna o numero de conversas
  inline unsigned size() const {return LC.size();}

  /// Retorna a i-esima conversa
  Conversa &operator[](unsigned i);

  /// Retorna o indice de uma conversa cujo correspondente seja igual ao parametro
  /// Retorna um numero negativo caso nao exista a conversa
  int getIndexConversa(const string &U) const;

  /// Inclui (cria) uma nova conversa com o correspondente passado como parametro
  /// Retorna false em caso de erro, true se OK
  bool insertConversa(const string &U);

  /// Exclui a i-esima conversas
  /// Retorna false em caso de erro, true se OK
  bool eraseConversa(unsigned i);

  /// Apaga todas as conversas
  inline void clearConversas() {LC.clear();}

  /// Gera (incrementa) uma id valida para a proxima msg
  inline uint32_t getNovaIdMensagem() {return ++idMensagem;}

  /// Procura uma mensagem pela id, em todas as conversas
  /// Recebe como parametro a id de uma mensagem e retorna dois indices:
  /// o indice da conversa onde estah a mensagem que tem essa id
  /// e o indice da mensagem dentro dessa conversa
  /// Caso nao exista em nenhuma conversa uma msg com essa id,
  /// retorna os dois indices negativos
  void findIndexMensagem(int32_t id, int& ind_conv, int& ind_msg) const;

  /// Funcoes de consulta/alteracao dos demais parametros
  /// As funcoes de alteracao retornam false em caso de erro, true se OK
  inline int getIndexConversaAtual() const {return indexConversa;}
  bool setIndexConversaAtual(int IND);
};

/// Os dados das conversas do cliente serao armazenados em uma variavel global
extern DadosCliente DCliente;

/// O socket do cliente serah armazenado em uma variavel global
extern tcp_mysocket sock;

/// O identificador da thread de leitura de dados do socket
extern HANDLE th_id;

/// Ponteiro para a janela Qt principal
/// Permite utilizar a interface em outros programas
extern WhatsClient* pt_w;

/// Funcao da thread que recebe as informacoes do socket e
/// armazena na variavel DCliente.
/// Estah definida junto com a funcao main
DWORD WINAPI le_msg(LPVOID lpParameter);


#endif // DADOS_CLIENTE_H
