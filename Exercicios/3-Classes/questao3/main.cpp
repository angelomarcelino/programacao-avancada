#include <iostream>
#include <cstdlib> /* srand, rand */
#include <ctime>   /* time */
#include "vetor.h"

using namespace std;

int main()
{
  vetor V1, V2(3);

  /// Inicializa a geracao de numeros aleatorios
  srand (time(NULL));

  cout << "1o vetor :";
  cin >> V1;

  /// Gera numeros entre -50 e +50
  for (unsigned i=0; i<V2.size(); i++)
  {
    V2[i] = rand()%101 - 50.0;
  }

  cout << "V1 = " << V1 << " (norma " << V1.norma() << ')' << endl;
  cout << "V2 = " << V2 << " (norma " << V2.norma() << ')' << endl;
  cout << "Produto escalar = " << V1*V2 << endl;
  cout << "Produto vetorial = " << V1%V2 << endl;

  return 0;
}
