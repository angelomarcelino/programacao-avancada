#ifndef _ARMAZENADOR_CLASSE_H_
/// If not defined __________
#define _ARMAZENADOR_CLASSE_H_
/// Define __________

#include<iostream>
using namespace std;

typedef double valor;
/// se eu quiser mudar pra int, so mudo aqui

class lista_valor
{
private:
  unsigned N;
  valor *x;
public:

  ///Construtores e Destrutor
  inline lista_valor(): N(0), x(NULL) {} ///Construtor por Default (TEM QUE TER p/ ponteiros)
  explicit lista_valor(unsigned int Num); ///Explicit para nao servir como conversor
  lista_valor(const lista_valor &L);  ///Construtor por cópia (TEM QUE TER p/ ponteiros)
  ~lista_valor(); ///Destrutor (TEM QUE TER p/ ponteiros)

  ///Funcoes
  void operator=(const lista_valor &L); ///Metodo de atribuicao

  ///Imprimir
  friend ostream &operator<<(ostream &X, const lista_valor &L);
  inline void imprimir() const {cout << *this << endl;}

  ///Consulta
  inline unsigned tamanho() const {return N;}
  valor operator[](unsigned i) const;
  inline valor primeiro(void) const {return operator[](0);}

  ///Inclusao e exclusao de valores
  void inserir(valor V);
  void remover(void);

};
#endif /// _ARMAZENADOR_CLASSE_H_
