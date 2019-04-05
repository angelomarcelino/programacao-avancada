#include <cmath>
#include "vector.h"

/// Construtor por copia
Vector::Vector(const Vector &V)
{
  N = V.N;
  if (N>0)
  {
    x = new double[N];
    for (unsigned i=0; i<N; i++) x[i] = V.x[i];
  }
  else
  {
    x = NULL;
  }
}

/// Construtor especifico a partir de um inteiro (dimensao do vetor)
/// Nao pode ser utilizado como conversor de numeros inteiros para vetores
/// Por isso, declarado como explicit
Vector::Vector(int Num)
{
  if (Num<=0)
  {
    cerr << "Dimensao invalida\n";
    N = 0;
    x = NULL;
    return;
  }
  N = Num;
  x = new double[N];
}

/// Destrutor
Vector::~Vector()
{
  delete[] x;
  x = NULL;
  N = 0;
}

/// Operador de atribuicao
void Vector::operator=(const Vector &V)
{
  // Primeiro, testa se o usuario nao estah fazendo uma atribuicao redundante, tal como A=A
  if (this != &V)
  {
    // Em seguida, testa se a dimensao dos dois vetores eh a mesma
    // Se for, nao precisa desalocar e alocar de novo com outro tamnho.
    // Dah para aproveitar a mesma area, copiando soh os valores dos elementos
    if (this->N != V.N)
    {
      // Repito o codigo do destrutor
      delete[] this->x;

      // Repito o codigo do construtort por copia
      this->N = V.N;
      if (N>0)
      {
        x = new double[N];
      }
      else
      {
        x = NULL;
      }
    }
    for (unsigned i=0; i<N; i++) x[i] = V.x[i];
  }
}

/// Funcao de consulta: elemento do vetor (sem poder alterar)
double Vector::operator[](unsigned i) const
{
  if (i>=N)
  {
    cerr << "Indice invalido\n";
    return 0.0;
  }
  return x[i];
}

/// Funcao de consulta: elemento do vetor (quando precisa alterar)
double &Vector::operator[](unsigned i)
{
  static double prov=0.0;
  if (i>=N)
  {
    cerr << "Indice invalido\n";
    return prov;
  }
  return x[i];
}

/// Impressao de um vetor
ostream &operator<<(ostream &X, const Vector &V)
{
  X << '[';
  for (unsigned i=0; i<V.N; i++) X << V.x[i] << (i+1==V.N ? ']' : ';');
  return X;
}

/// Leitura de um vetor
istream &operator>>(istream &X, Vector &V)
{
  for (unsigned i=0; i<V.N; i++) X >> V.x[i];
  return X;
}

/// Norma euclidiana
double Vector::norm() const
{
  double soma(0.0);
  for (unsigned i=0; i<N; i++) soma += x[i]*x[i];
  return sqrt(soma);
}

/// Soma de vetores
Vector Vector::operator+(const Vector &V) const
{
  if (N!=V.N)
  {
    cerr << "Dimensoes incompativeis\n";
    return Vector();
  }
  if (N==0) return Vector();
  Vector prov(N);
  for (unsigned i=0; i<N; i++) prov.x[i] = x[i] + V.x[i];
  return prov;
}

/// Subtracao de vetores
Vector Vector::operator-(const Vector &V) const
{
  if (N!=V.N)
  {
    cerr << "Dimensoes incompativeis\n";
    return Vector();
  }
  if (N==0) return Vector();
  Vector prov(N);
  for (unsigned i=0; i<N; i++) prov.x[i] = x[i] - V.x[i];
  return prov;
}

/// Produto escalar (utilizando o *)
double Vector::operator*(const Vector &V) const
{
  if (N!=V.N)
  {
    cerr << "Dimensoes incompativeis\n";
    return 0.0;
  }
  if (N==0) return 0.0;
  double prov(0.0);
  for (unsigned i=0; i<N; i++) prov += x[i]*V.x[i];
  return prov;
}

/// Produto vetorial (utilizando o %)
Vector Vector::operator%(const Vector &V) const
{
  if (N!=3 || N!=V.N)
  {
    cerr << "Dimensoes incompativeis\n";
    return Vector();
  }
  Vector prov(3);
  prov.x[0] = x[1]*V.x[2] - x[2]*V.x[1];
  prov.x[1] = x[2]*V.x[0] - x[0]*V.x[2];
  prov.x[2] = x[0]*V.x[1] - x[1]*V.x[0];
  return prov;
}
