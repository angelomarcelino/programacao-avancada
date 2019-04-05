#include <iostream>
#include <cmath>

using namespace std;

inline double pow2(double x) {return x*x;}

class Retangulo;

class Ponto
{
private:
    double x,y;
public:
    inline Ponto(double X=0.0, double Y=0.0): x(X), y(Y) {}
    void imprimir(ostream &O=cout) const;
    void ler(istream &I=cin);
    double distancia(const Ponto &P) const;
    bool operator<(Retangulo R) const;
    friend class Retangulo;
};

class Retangulo
{
private:
    Ponto mini,maxi;
public:
    Retangulo(double minX, double minY, double maxX, double maxY);
    double area() const;
    bool pontoInterno(const Ponto &P) const;
};

void Ponto::imprimir(ostream &O) const
{
    O << '(' << x << ',' << y << ')';
}

void Ponto::ler(istream &I)
{
    I >> x >> y;
}

ostream &operator<<(ostream &O, const Ponto &P)
{
    P.imprimir(O);
    return O;
}

istream &operator>>(istream &I, Ponto &P)
{
    P.ler(I);
    return I;
}

double Ponto::distancia(const Ponto &P) const
{
    return sqrt(pow2(x-P.x)+pow2(y-P.y));
}

bool Ponto::operator<(Retangulo R) const
{
    return R.pontoInterno(*this);
}

Retangulo::Retangulo(double minX, double minY, double maxX, double maxY)
{
    if (minX > maxX)
    {
        double prov = minX;
        minX = maxX;
        maxX = minX;
    }
    if (minY > maxY)
    {
        double prov = minY;
        minY = maxY;
        maxY = minY;
    }
    mini.x = minX;
    mini.y = minY;
    maxi.x = maxX;
    maxi.y = maxY;
}

double Retangulo::area() const
{
    return (maxi.x-mini.x)*(maxi.y-mini.y);
}

bool Retangulo::pontoInterno(const Ponto &P) const
{
    if (P.x < mini.x) return false;
    if (P.y < mini.y) return false;
    if (P.x > maxi.x) return false;
    if (P.y > maxi.y) return false;
    return true;
}

int main(void)
{
    Ponto P;
    Retangulo R(1,1, 10,15);

    cout << "Testa se um ponto dado estah dentro do retangulo [1,1] - [10,15]\n";
    cout << "Qual o ponto [x,y]? ";
    cin >> P;
    cout << "Ponto eh interno? " << (P<R ? "SIM" : "NAO") << endl;
}
