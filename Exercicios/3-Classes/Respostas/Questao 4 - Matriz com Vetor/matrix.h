#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "vector.h"
#include <iostream>

using namespace std;

class Matrix
{
private:
  /// Numero de linhas da matriz
  unsigned NL;
  /// Ponteiro para array de linhas (vetores) da matriz
  Vector *x;
public:
  /// Construtor default
  inline Matrix(): NL(0), x(NULL) {}
  /// Construtor por copia
  Matrix(const Matrix &M);
  /// Construtor especifico a partir de dois inteiros (dimensoes da matriz)
  Matrix(unsigned NLin, unsigned NCol);
  /// Destrutor
  ~Matrix();
  /// Operador de atribuicao
  void operator=(const Matrix &M);

  /// Funcao de consulta: numero de linhas
  inline unsigned numLines() const {return NL;}
  /// Funcao de consulta: numero de colunas
  unsigned numColumns() const;
  /// Funcao de consulta: retorna uma linha da matriz por copia
  Vector operator[](unsigned i) const;
  /// Funcao de consulta: retorna uma linha da matriz por referencia
  Vector &operator[](unsigned i);

  /// Impressao de uma matriz
  friend ostream &operator<<(ostream &X, const Matrix &M);
  /// Leitura de uma matriz
  friend istream &operator>>(istream &X, Matrix &M);

  /// Soma de matrizes
  Matrix operator+(const Matrix &M) const;
  /// Subtracao de matrizes
  Matrix operator-(const Matrix &M) const;
  /// Produto de matrizes
  Matrix operator*(const Matrix &V) const;
};

#endif
