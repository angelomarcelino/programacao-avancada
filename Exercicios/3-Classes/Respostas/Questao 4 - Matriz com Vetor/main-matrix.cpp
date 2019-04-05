#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{
  Matrix M(3,4),N(4,2), P;

  cout << "1a matriz (" << M.numLines() << ',' << M.numColumns() << "): ";
  cin >> M;

  cout << "1a matriz (" << N.numLines() << ',' << N.numColumns() << "): ";
  cin >> N;

  P = M*N;
  P[0][0] = 3.1416;

  cout << "P(" << P.numLines() << ',' << P.numColumns() << ") = " << P << endl;

  return 0;
}
