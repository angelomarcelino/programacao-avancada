#include <iostream>
#include <cmath>
#include "racionaismc.h"

using namespace std;


ostream &operator<<(ostream &X, const racional &R)
{
    X << '(' << R.x << '/' << R.y << ')';
    return X;
}

istream &operator>>(istream &X, racional &R)
{
    cout << "\nEntre com X/Y: ";
    X >> R.x >> R.y;
    R.smfy();
    return X;
}

void racional::smfy()
{
    int maior;
    if (x>y) maior = x;
    else maior = y;
    for (int i=1; i<maior; i++)
    {
        if (x%i==0 && y%i==0)
        {
            x = x/i;
            y = y/i;
            maior = maior/i;
        }
    }
}

racional racional::operator+(const racional &R2) const
{
    racional R3;
    R3.x = (x*R2.y) + (R2.x*y);
    R3.y = (y*R2.y);
    R3.smfy();
    return R3;
}

racional racional::operator+(const int &i) const
{
    racional R(0,y);
    R.x = x + (i*y);
    R.smfy();
    return R;
}

racional racional::operator*(const racional &R2) const
{
    racional R;
    R.x = x*R2.x;
    R.y = y*R2.y;
    R.smfy();
    return R;
}

racional racional::operator*(const int &i) const
{
    racional R(0,y);
    R.x = x*i;
    R.smfy();
    return R;
}
