#include <iostream>

using namespace std;

int main()
{
    char a;
    float x,y;

    a='+';

    while (a == '+' || a == '-' || a == '/' || a == '*' )
    {
        cout << "Entre sua conta: ";
        cin >> x >> a >> y;
        if (a == '+')
            cout<< "Resultado: "<< x + y;
        else if (a == '-')
            cout<< "Resultado: "<< x - y;
        else if (a == '/')
            cout<< "Resultado: "<< x / y;
        else if (a == '*')
            cout<< "Resultado: "<< x * y;
        cout << endl;
    }
    return 0;
}
