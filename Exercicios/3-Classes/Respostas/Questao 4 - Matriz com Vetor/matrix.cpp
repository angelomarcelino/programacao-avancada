#include <cmath>
#include "matrix.h"

/// Construtor por copia
Matrix::Matrix(const Matrix &M)
{
  NL = M.NL;
  if (NL>0)
  {
    x = new Vector[NL];
    for (unsigned i=0; i<NL; i++) x[i] = M.x[i];
  }
  else
  {
    x = NULL;
  }
}

/// Construtor especifico a partir de dois inteiros (dimensoes da matriz)
Matrix::Matrix(unsigned NLin, unsigned NCol)
{
  if (NLin==0 || NCol==0)
  {
    cerr << "Dimensao invalida\n";
    NL = 0;
    x = NULL;
    return;
  }
  NL = NLin;
  x = new Vector[NL];
  for (unsigned i=0; i<NL; i++) x[i] = Vector(NCol);
}

/// Destrutor
Matrix::~Matrix()
{
  delete[] x;
  x = NULL;
  NL = 0;
}

/// Operador de atribuicao
void Matrix::operator=(const Matrix &M)
{
  // Primeiro, testa se o usuario nao estah fazendo uma atribuicao redundante, tal como A=A
  if (this != &M)
  {
    // Em seguida, testa se o numero de linhas das duas matrizes eh o mesmo
    // Se for, nao precisa desalocar e alocar de novo com outro tamanho.
    // Dah para aproveitar a mesma area, copiando soh os vetores linha
    if (this->NL != M.NL)
    {
      // Repito o codigo do destrutor
      delete[] x;

      // Repito o codigo do construtort por copia
      NL = M.NL;
      if (NL>0)
      {
        x = new Vector[NL];
      }
      else
      {
        x = NULL;
      }
    }
    // Usa o operador de atribuicao da classe Vector
    for (unsigned i=0; i<NL; i++) x[i] = M.x[i];
  }
}

/// Funcao de consulta: numero de colunas
unsigned Matrix::numColumns() const
{
  if (NL==0) return 0;
  return x[0].size();
}

/// Funcao de consulta: retorna uma linha da matriz por copia
Vector Matrix::operator[](unsigned i) const
{
  if (i>=NL)
  {
    cerr << "Indice invalido\n";
    return Vector();
  }
  return x[i];
}

/// Funcao de consulta: retorna uma linha da matriz por referencia
Vector &Matrix::operator[](unsigned i)
{
  static Vector prov;
  if (i>=NL)
  {
    cerr << "Indice invalido\n";
    return prov;
  }
  return x[i];
}

/// Impressao de uma matriz
ostream &operator<<(ostream &X, const Matrix &M)
{
  for (unsigned i=0; i<M.NL; i++) X << M.x[i] << endl;
  return X;
}

/// Leitura de uma matriz
istream &operator>>(istream &X, Matrix &M)
{
  for (unsigned i=0; i<M.NL; i++) X >> M.x[i];
  return X;
}

/// Soma de matrizes
Matrix Matrix::operator+(const Matrix &M) const
{
  if (NL!=M.NL)
  {
    cerr << "Dimensoes incompativeis\n";
    return Matrix();
  }
  if (NL==0) return Matrix();
  Matrix prov(numLines(),numColumns());
  for (unsigned i=0; i<NL; i++) prov.x[i] = x[i] + M.x[i];
  return prov;
}

/// Subtracao de matrizes
Matrix Matrix::operator-(const Matrix &M) const
{
  if (NL!=M.NL)
  {
    cerr << "Dimensoes incompativeis\n";
    return Matrix();
  }
  if (NL==0) return Matrix();
  Matrix prov(numLines(),numColumns());
  for (unsigned i=0; i<NL; i++) prov.x[i] = x[i] - M.x[i];
  return prov;
}

/// Produto de matrizes
Matrix Matrix::operator*(const Matrix &M) const
{
  if (numColumns() != M.numLines())
  {
    cerr << "Dimensoes incompativeis\n";
    return Matrix();
  }
  if (numLines()==0 || numColumns()==0 || M.numColumns()==0) return Matrix();
  Matrix prov(numLines(),M.numColumns());
  for (unsigned i=0; i<prov.numLines(); i++) for (unsigned j=0; j<prov.numColumns(); j++)
  {
    prov.x[i][j] = 0.0;
    for (unsigned k=0; k<numColumns(); k++) prov.x[i][j] += x[i][k]*M.x[k][j];
  }
  return prov;
}
