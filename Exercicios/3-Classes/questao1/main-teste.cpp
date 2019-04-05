#include <iostream>
#include "ponto.h"
#include "retangulo.h"

using namespace std;

int main()
{
    ponto P1(3.0, 4.0), P2(5.0, 1.0), qqer;
    retangulo ret(P1, P2);

    cout << "Testar se um ponto esta dentro do retangulo "
         << P1 << " - " << P2 << endl;
    cin >> qqer;
    cout << "Faz parte do retangulo? ";
    cout << (ret<qqer ? "SIM" : "NOP") << endl;

    return 0;
}
