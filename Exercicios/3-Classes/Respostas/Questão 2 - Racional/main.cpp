#include <iostream>
#include "Racional.h"

using namespace std;

int main()
{
    Racional r1(1,2), r2;
    cout << "Primeiro racional eh 1/2\n";
    cout << "Entre o segundo racional [num den]: ";
    cin >> r2;
    cout << "Soma: " << r1+r2
         << "\nProduto: " << r1*r2 << endl;
    cout << "Soma do segundo c/ 2: " << 2+r2
         << "\nSoma do segundo c/ 3: " << r2+3
         << "\nProduto do segundo p/ 2: " << 2*r2
         << "\nProduto do segundo p/ 3: " << r2*3 << endl;

    return 0;
}
