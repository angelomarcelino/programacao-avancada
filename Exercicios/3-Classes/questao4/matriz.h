#ifndef _MATRIZ_PONTO_H_
#define _MATRIZ_PONTO_H_

#include <iostream>
#include "vetor.h"

class Matrix
{
private:
    unsigned NL;
    vetor *x;
public:
    /// Default
    inline Matrix(): NL(0) y(NULL) {}
    /// Copia
    Matrix(Matrix &M): NL(M.NL);
    /// NL, NC
    Matrix(unsigned NL, unsigned NC);
    /// Destrutor
    ~Matrix();
    /// Atribuicao
    void operator=(const Matrix &M);

    ///Consulta
    inline unsigned Lines() const {return NL;}
    unsigned Columns() const;
    double operator[](unsigned i) const;
    double &operator[](unsigned i);

    /// Impressao de uma matriz
    friend ostream &operator<<(ostream &X, const Matrix &M);
    /// Leitura de uma matriz
    friend istream &operator>>(istream &X, Matriz &M);


};

#endif // _MATRIZ_PONTO_H_
