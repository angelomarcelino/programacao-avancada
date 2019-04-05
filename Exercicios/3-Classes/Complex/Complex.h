#include <iostream>

using namespace std;

/// Tipo complexo

class complexo
{
private:
    double real, imag;
public:
    ///construtores
    inline complexo(double R=0.0, double I=0.0): real(R), imag(I) {}
    inline complexo(const complexo &C): real(C.real), imag(C.imag) {}

//  inline explicit complexo(double R=0.0, double I=0.0): real(R), imag(I) {}
//  serve somente como construtor, nao como conversor.

    //funcoes de consulta
    inline double getReal() const {return real;}
    inline double getImag() const {return imag;}

    friend ostream &operator<<(ostream &X, const complexo &C);
    friend istream &operator>>(istream &X, complexo &C);

    //metodos da classe
    complexo getInv() const;
    complexo operator+(const complexo &C2) const;
    complexo operator*(const complexo &C2) const;
    complexo operator/(const complexo &C2) const;
    //lembrar de sempre passar por referencia, caso nao altere, usar const
};
