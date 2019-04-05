#include <iostream>
#include <cmath>
#include "complex.h"

using namespace std;

/// Os metodos da classe

void Complexo::ler()
{
  cout << "R? ";
  cin >> real;
  cout << "I? ";
  cin >> imag;
}

void Complexo::imprimir() const
{
  cout << real << (imag<0.0 ? '-' : '+') << 'j' << fabs(imag);
}

Complexo Complexo::operator+(const Complexo &C2) const
{
  Complexo prov;
  prov.real = real+C2.real;
  prov.imag = imag+C2.imag;
  return prov;
}

Complexo Complexo::operator*(const Complexo &C2) const
{
  Complexo prov;
  prov.real = real*C2.real - imag*C2.imag;
  prov.imag = real*C2.imag + C2.real*imag;
  return prov;
}

