#include <iostream>
#include <c.math>
#include "Complex.h"

using namespace std;

istream &operator>>(istream &X, complexo &C)
{
    cout << "Real: " << endl;
    X >> C.real;
    cout << "Imag: " << endl;
    X >> C.imag;
    return X;
}

ostream &operator<<(ostream &X, const complexo &C)
{
    X << C.real << (C.imag<0 ? '-' : '+')
         << 'j' << fabs(C.imag) <<endl;
    return X;
}

complexo complexo::getInv() const
{
    complexo prov;
    prov.real = real;
    prov.imag = imag*(-1);
    return prov;
}

complexo complexo::operator+(const complexo &C2) const
{
    complexo prov;
    prov.real = real+C2.real;
    prov.imag = imag+C2.imag;
    return prov;
}

complexo complexo::operator*(const complexo &C2) const
{
    complexo prov;
    prov.real = (real*C2.real) - (real*C2.imag);
    prov.imag = (real*C2.imag) + (imag*C2.real);
    return prov;
}

complexo complexo::operator/(const complexo &C2) const
{
    complexo prov;
    prov.real = ((real*C2.real) + (real*C2.imag)) / (pow(C2.real,2) + pow(C2.imag,2));
    prov.imag = ((real*C2.imag) - (imag*C2.real))/ (pow(C2.real,2) + pow(C2.imag,2));
    return prov;
}
