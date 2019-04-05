#include <iostream>
/// Tipo Complexo

class Complexo
{
private:
  double real, imag;
public:
  /// Construtores
  inline Complexo(): real(0.0), imag(0.0) {}
  inline Complexo(double R): real(R), imag(0.0) {}
  inline Complexo(double R, double I): real(R), imag(I) {}

  inline double getReal() const {return real;}
  inline double getImag() const {return imag;}

  void ler();
  void imprimir() const;
  Complexo operator+(const Complexo &C2) const;
  Complexo operator*(const Complexo &C2) const;
};
