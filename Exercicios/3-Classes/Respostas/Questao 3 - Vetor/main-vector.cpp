#include <iostream>
#include <cstdlib> /* srand, rand */
#include <ctime>   /* time */
#include "vector.h"

using namespace std;

int main()
{
  Vector V1(3), V2(3);

  /// Inicializa a geracao de numeros aleatorios
  srand (time(NULL));

  cout << "1o vetor (" << V1.size() << "): ";
  cin >> V1;

  /// Gera numeros entre -50 e +50
  for (unsigned i=0; i<V2.size(); i++)
  {
    V2[i] = rand()%101 - 50.0;
  }

  cout << "V1 = " << V1 << " (norma " << V1.norm() << ')' << endl;
  cout << "V2 = " << V2 << " (norma " << V2.norm() << ')' << endl;
  cout << "Produto escalar = " << V1*V2 << endl;
  cout << "Produto vetorial = " << V1%V2 << endl;

  return 0;
}
