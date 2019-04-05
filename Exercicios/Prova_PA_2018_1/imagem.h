#ifndef _PIXEL_PONTO_H_
#define _PIXEL_PONTO_H_

#include <iostream>
#include <fstream>

using namespace std;

class Imagem
{
private:
    unsigned NL, NC;
    uint8_t **x;
    void criar(const unsigned &NumLi, const unsigned &NumCo);
    void copiar(const Imagem &I);
    void limpar();
public:
    inline Imagem(): NL(0), NC(0), x(NULL) {};
    inline Imagem(const Imagem &I): NL(0), NC(0), x(NULL) {copiar(I);}
    inline explicit Imagem(const unsigned &NumLi, const unsigned &NumCo) {criar(NumLi, NumCo);}
    ~Imagem() {limpar();}
    void operator=(const Imagem &I) {if(this!=&I){limpar();copiar(I);}}

    inline uint8_t getPixel(const unsigned &i, const unsigned &j) const {return x[i][j];}
    inline void setPixel(const unsigned &i, const unsigned &j, uint8_t &pixel) {if(j>=0 && j<=NC && i>=0 && i<=NL){x[i][j] = pixel;}}
    inline unsigned getNL() const {return NL;}
    inline unsigned getNC() const {return NC;}

    //friend ostream &operator<<(ostream &X, const Imagem &I);
    //friend istream &operator>>(istream &X, Imagem &I);

    void paintRectangle(unsigned &x1, unsigned &y1, unsigned &x2, unsigned &y2, uint8_t &cor);
    void salvaImagem(const char *nome) const;
};

#endif // _PIXEL_PONTO_H_
