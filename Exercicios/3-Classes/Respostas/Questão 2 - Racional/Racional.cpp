#include <iostream>
#include "Racional.h"

using namespace std;

istream &operator>>(istream &X, Racional &R)
{
    X >> R.num;
    do {X >> R.den;} while (R.den<=0);
    R.simplify();
    return X;
}

ostream &operator<<(ostream &X, const Racional &R)
{
    X << R.num << '/' << R.den;
    return X;
}

void Racional::simplify(void)
{
    if (num==0)
    {
        den = 1;
        return;
    }
    if (den<0)
    {
        num = -num;
        den = -den;
    }
    int N = max(num,den);
    int D = min(num,den);
    int R;
    // Algoritmo de Euclides
    while ((R=N%D) != 0)
    {
        N = D;
        D = R;
    }
    num /= D;
    den /= D;
}

Racional Racional::operator+(const Racional &R) const
{
    //return Racional(num*R.den + R.num*den, den*R.den);
    Racional prov(num*R.den + R.num*den, den*R.den);
    prov.simplify();
    return prov;
}

Racional Racional::operator-(const Racional &R) const
{
    //return Racional(num*R.den + R.num*den, den*R.den);
    Racional prov(num*R.den - R.num*den, den*R.den);
    prov.simplify();
    return prov;
}

Racional Racional::operator*(const Racional &R) const
{
    Racional prov(num*R.num, den*R.den);
    prov.simplify();
    return prov;
}

Racional Racional::operator/(const Racional &R) const
{
    if (R.num == 0)
    {
        cerr << "Divisao por zero!\n;";
        return Racional();
    }
    Racional prov(num*R.den, den*R.num);
    prov.simplify();
    return prov;
}
