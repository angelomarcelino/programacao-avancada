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
        cout << "Entre um númerio: ";
        cin >> a;
        cout << endl;
        if (a>=0)
        {
            media = media + a;
            cont++;
        }
    }
    cout << "Média: " << media/cont << endl;
    return 0;
}
