#include <iostream>

using namespace std;

int main()
{
    float a, media, cont;
    a = 0;
    media = 0;
    cont = 0;
    while (a>=0)
    {
        cout << "Entre um n�merio: ";
        cin >> a;
        cout << endl;
        if (a>=0)
        {
            media = media + a;
            cont++;
        }
    }
    cout << "M�dia: " << media/cont << endl;
    return 0;
}
