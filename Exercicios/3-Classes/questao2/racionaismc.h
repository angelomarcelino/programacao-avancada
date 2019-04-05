#ifndef _RACIONAL_PONTO_H
#define _RACIONAL_PONTO_H

#include <iostream>
using namespace std;

class racional
{
private:
    int x,y;
public:
    void smfy();

    ///Construtores
    inline racional (int a=0, int b=1): x(a), y(b) {smfy();}
    inline racional (const racional &R): x(R.x), y(R.y) {smfy();}

    ///Metodos
    friend ostream &operator<<(ostream &X, const racional &R);
    friend istream &operator>>(istream &X, racional &R);


    racional operator+(const racional &R2) const;
    racional operator+(const int &i) const;
    racional operator*(const racional &R2) const;
    racional operator*(const int &i) const;
};

#endif //_RACIONAL_PONTO_H
