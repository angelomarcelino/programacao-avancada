#include <iostream>
#include <cmath>
#include "ponto.h"
#include "retangulo.h"
#include <cmath>

using namespace std;

double retangulo::area() const
{
    double area;
    area = fabs((D.getX()-A.getX())*((D.getY()-A.getY())));
    return area;
}

bool retangulo::operator<(const ponto &p) const
{
    if (p.getX()<A.getX()) return false;
    if (p.getX()>D.getX()) return false;
    if (p.getY()<D.getY()) return false;
    if (p.getY()>A.getY()) return false;
    return true;
}
