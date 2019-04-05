#ifndef _CLASSE_PONTO_H_
#define _CLASSE_PONTO_H_

#include <iostream>

using namespace std;

class ponto
{
private:
    double x;
    double y;
public:
    /// Construtores
    inline ponto (double A=0, double B=0): x(A), y(B) {}

    ///funcoes
    friend ostream &operator<<(ostream &X, const ponto &P);
    friend istream &operator>>(istream &X, ponto &P);
    inline double getX() const {return x;}
    inline double getY() const {return y;}

    ///metodos
    double distancia (const ponto &P2) const;
};
#endif // _CLASSE_PONTO_H_
