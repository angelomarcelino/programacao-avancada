#include <iostream>
#include "racionaismc.h"

using namespace std;

int main()
{
    racional R, R2;
    int i;
    cout << "Entre seu numero rcmcs: ";
    cin >> R;
    cout << R;
    cout << "\nEntre seu numero rcmcs: ";
    cin >> R2;
    cout << R2;
    cout << "\nEntre seu numero int: ";
    cin >> i;
    cout << R << '+' << R2 << '=' << R+R2 << endl;
    cout << R << '+' << i << '=' << R+i << endl;
    cout << R << '*' << R2 << '=' << R*R2 << endl;
    cout << R << '*' << i << '=' << R*i << endl;

    return 0;
}
