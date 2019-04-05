#include <iostream>
#include <cmath>
#include "ponto.h"

using namespace std;

///funcoes
ostream &operator<<(ostream &X, const ponto &P)
{
    X <<'('<<P.x<<','<<P.y<<')';
    return X;
}

istream &operator>>(istream &X, ponto &P)
{
    cout << "Entre com o ponto (x,y): ";
    X >> P.x >> P.y;
    return X;
}

///metodos
double ponto::distancia (const ponto &P2) const
{
    double D;
    D = sqrt(pow((P2.x - x),2) + pow((P2.y - y),2));
    return D;
}
