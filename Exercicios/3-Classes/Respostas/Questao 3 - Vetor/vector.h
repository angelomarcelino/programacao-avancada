#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>

using namespace std;

class Vector
{
private:
  /// Dimensao do vetor
  unsigned N;
  /// Ponteiro para array de elementos do vetor
  double *x;
public:
  /// Construtor default
  inline Vector(): N(0), x(NULL) {}
  /// Construtor por copia
  Vector(const Vector &V);
  /// Construtor especifico a partir de um inteiro (dimensao do vetor)
  /// Nao pode ser utilizado como conversor de numeros inteiros para vetores
  /// Por isso, declarado como explicit
  explicit Vector(int Num);
  /// Destrutor
  ~Vector();
  /// Operador de atribuicao
  void operator=(const Vector &V);

  /// Funcao de consulta: dimensao do vetor
  inline unsigned size() const {return N;}
  /// Funcao de consulta: elemento do vetor (sem poder alterar)
  double operator[](unsigned i) const;
  /// Funcao de consulta: elemento do vetor (quando precisa alterar)
  double &operator[](unsigned i);

  /// Impressao de um vetor
  friend ostream &operator<<(ostream &X, const Vector &V);
  /// Leitura de um vetor
  friend istream &operator>>(istream &X, Vector &V);

  /// Norma euclidiana
  double norm() const;

  /// Soma de vetores
  Vector operator+(const Vector &V) const;
  /// Subtracao de vetores
  Vector operator-(const Vector &V) const;
  /// Produto escalar (utilizando o *)
  double operator*(const Vector &V) const;
  /// Produto vetorial (utilizando o %)
  Vector operator%(const Vector &V) const;
};

#endif
