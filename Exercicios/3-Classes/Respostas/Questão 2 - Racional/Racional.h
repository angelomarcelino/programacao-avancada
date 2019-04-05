#include <iostream>

using namespace std;

class Racional
{
private:
    int num,den;
    void simplify(void);
public:
    //inline Racional(): num(0), den(1) {}
    //inline Racional(int I): num(I), den(1) {}
    inline Racional(int N=0, int D=1): num(N), den(D) {if (den==0) den=1;}
    inline Racional(const Racional &R): num(R.num), den(R.den) {}
    inline ~Racional() {}

    friend istream &operator>>(istream &X, Racional &R);
    friend ostream &operator<<(ostream &X, const Racional &R);

    Racional operator+(const Racional &R) const;
    Racional operator-(const Racional &R) const;
    inline Racional operator-() const {return Racional(-num,den);}
    Racional operator*(const Racional &R) const;
    Racional operator/(const Racional &R) const;
};

inline Racional operator+(int I, const Racional &R) {return Racional(I)+R;}
inline Racional operator-(int I, const Racional &R) {return Racional(I)-R;}
inline Racional operator*(int I, const Racional &R) {return Racional(I)*R;}
inline Racional operator/(int I, const Racional &R) {return Racional(I)/R;}
