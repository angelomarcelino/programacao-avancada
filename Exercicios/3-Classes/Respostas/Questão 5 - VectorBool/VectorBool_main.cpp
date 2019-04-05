#include <iostream>
#include "VectorBool.h"

using namespace std;

int main()
{
    VectorBool X(50);

    cout << "O vetor contem " << X.size() << " booleanos\n";
    cout << "Pode armazenar ateh " << X.capacity() << " booleanos sem precisar realocar\n";
    for (unsigned i=0; i<50; i++)
    {
      X.setBool(i,i%2);
    }
    for (unsigned i=0; i<50; i++)
    {
      cout << X[i];
    }
    cout << endl;


    return 0;
}
