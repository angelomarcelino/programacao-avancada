#include <iostream>
#include <cstdlib>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
using namespace std;

int main()
{
    int rdm, gss, cont;

    srand (time(NULL));

    cont = 0;
    rdm = rand() % 101;
    gss = -1;

    while (rdm != gss)
    {
        cout << "Chute: ";
        cin >> gss;
        cout << endl;
        if (gss > rdm)
            cout << "Seu chute esta acima" << endl;
        else if (gss < rdm)
            cout << "Seu chute esta abaixo" << endl;
        cont++;
    }
    cout << "Acertou mizeravi, depois de " << cont << " vezes."<< endl;
    return 0;
}
