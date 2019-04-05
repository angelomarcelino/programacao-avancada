#include <iostream>
#include <cmath>
#include "complex.h"
using namespace std;

int main(void)
{
  Complexo C1, C2, S, P;
  int fim(0);

  cout << "Digite o primeiro numero complexo (C1):\n";
  C1.ler();

  cout << "Digite o segundo numero complexo (C2):\n";
  C2.ler();

  S = C1+C2;
  P = C1*C2;

  cout << "Soma = ";
  S.imprimir();
  cout << endl;

  cout << "Produto = ";
  P.imprimir();
  cout << endl;

  while(fim!=-1)
  {
      cin >> fim;
      if(fim==-1) return 0;
  }
}


