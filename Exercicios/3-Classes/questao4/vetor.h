#ifndef _VETOR_PONTO_H_
#define _VETOR_PONTO_H_

#include <iostream>
using namespace std;

class vetor
{
private:
    unsigned N;
    double *x;

public:
    /// Default
    inline vetor(): N(0), x(NULL) {}
    /// Cópia
    vetor(const vetor &V);
    /// Explicito
    explicit vetor(int i);
    /// Destrutor
    ~vetor();

    /// Atribuicao
    void operator=(const vetor &V);
    /// Consulta
    double operator[](unsigned i) const;
    double &operator[](unsigned i);
    inline unsigned size() const {return N;}

    /// Impressao de um vetor
    friend ostream &operator<<(ostream &X, const vetor &V);
    /// Leitura de um vetor
    friend istream &operator>>(istream &X, vetor &V);

    ///Operacoes
    double norma() const;
    vetor operator+(const vetor &V) const;
    vetor operator-(const vetor &V) const;
    double operator*(const vetor &V) const; /// prod escalar
    vetor operator%(const vetor &V) const; /// prod vetorial
};


#endif // _VETOR_PONTO_H_
