#include <iostream>
#include <fstream>
#include "imagem.h"

using namespace std;

void Imagem::criar(const unsigned &NumLi, const unsigned &NumCo)
{
    NL = NumLi;
    NC = NumCo;
    x = new uint8_t*[NL];
    for(unsigned i=0;i<NL;i++) x[i] = new uint8_t[NC];
}

void Imagem::copiar(const Imagem &I)
{
    if(NC==0 && NL==0 && x==NULL)
    {
        NL = I.NL;
        NC = I.NC;
        x = new uint8_t*[NL];
        for(unsigned i=0;i<NL;i++) x[i] = new uint8_t[NC];
        for(unsigned i=0;i<NL;i++)
        {
            for(unsigned j=0;j<NC;j++) x[i][j] = I.x[i][j];
        }
    }
    else cerr << "Erro inesperado";
}

void Imagem::limpar()
{
    if(x!=NULL)
    {
        for (unsigned i=0; i<NL; i++) delete[] x[i];
        delete[] x;
    }
    x = NULL;
    NC = NL = 0;
}

void Imagem::paintRectangle(unsigned &x1, unsigned &y1, unsigned &x2, unsigned &y2, uint8_t &cor)
{
    if(x1>=0 && x2 <=NC && y1>=0 && y2<=NL)
    {
        for(unsigned i=x1; i<=x2; i++)
        {
            for(unsigned j=y1; j<=y2; j++) x[i][j] = cor;
        }
    }
}

void Imagem::salvaImagem(const char *nome) const
{
    ofstream f(nome);

    f << "P2\n";
    f << NC << ' ' << NL << endl;
    f << (unsigned)255 << endl;
    for (unsigned i=0; i<NL; i++)
    {
        for (unsigned j=0; j<NC; j++)
        {
            f << (unsigned)x[i][j] << ' ';
        }
        f << endl;
    }
    f.close();
    cout << "Arquivo "<<nome<<" salvo!\n";
}
