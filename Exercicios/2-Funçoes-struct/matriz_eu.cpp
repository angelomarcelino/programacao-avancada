#include <iostream>

using namespace std;

struct Matriz{
    unsigned int NL, NC;
    float **x;
};

Matriz novaMatriz(unsigned int NLin, unsigned int NCol)
{
    Matriz prov;

    if(NLin==0 || NCol==0)
    {
        cerr << "Dimensao invalida!\n";
        prov.NC = 0;
        prov.NL = 0;
        prov.x = NULL;
        return (prov);
    }
    prov.NL = NLin;
    prov.NC = NCol;
    prov.x = new float *[NLin];
    for (unsigned i=0; i<NLin; i++)
    {
        prov.x[i] = new float[NCol];
        for(unsigned j=0; j<NCol; j++) prov.x[i][j] = 0.0;
    }

    return prov;
}

void imprimeMatriz(Matriz &X)
{
    if(X.NC==0 || X.NL==0 || X.x==NULL)
    {
        cerr << "Matriz invalida" << endl;
        return;
    }

    for(int i=0; i<X.NL; i++)
    {
        for(int j=0; j<X.NC; j++) cout << X.x[i][j] << ' ';
        cout << endl;
    }
}

void liberaMatriz(Matriz &P)
{
    if(P.x!=NULL)
    {
        for(int i=0; i<P.NL; i++) delete[] P.x[i];
        delete[] P.x;
    }
    P.NC = P.NL = 0;
    P.x = NULL;
}

Matriz produtoMatrizes(Matriz M, Matriz N)
{
    Matriz prov;
    if (M.NC!=N.NL || M.NC==0 || M.NL==0 || N.NL==0)
    {
        cerr << "Dimensoes invalidas.";
        prov.NC = 0;
        prov.NL = 0;
        prov.x = NULL;
        return prov;
    }
    prov = novaMatriz(M.NL,N.NC);
    for(int i=0; i<prov.NL; i++)
    {
        for(int j=0; j<prov.NC; j++)
        {
            prov.x[i][j] = 0;
            for (int k=0; k<N.NC; k++)
            {
                prov.x[i][j] += (M.x[i][k]*N.x[k][j]);
            }
        }
    }
    return prov;
}

void leMatriz(Matriz &M)
{
    cout << "Entre com os dados da matriz: \n";
    for (int i=0; i<M.NL; i++)
    {
        for(int j=0; j<M.NC; j++)
        {
            cout << '(' << i+1 << ',' << j+1 << ')' <<':';
            cin >> M.x[i][j];
        }
    }
}

int main(void)
{
    /// Declaracao das matrizes
    Matriz A, B, C;

    unsigned NLa, NCa, NLb, NCb;
    do {
        cout << "Linhas de A: ";
        cin >> NLa;
    } while (NLa <= 0);
    do {
        cout << "Colunas de A: ";
        cin >> NCa;
    } while (NCa <= 0);
    /// Obs: NLb = NCa
    NLb = NCa;
    do {
        cout << "Colunas de B: ";
        cin >> NCb;
    } while (NCb <= 0);

    /// Alocacao das matrizes
    A = novaMatriz(NLa,NCa);
    B = novaMatriz(NLb,NCb);

    /// Leitura das matrizes A e B
    cout << "Matriz A: \n";
    leMatriz(A);
    imprimeMatriz(A);
    cout << "Matriz B: \n";
    leMatriz(B);
    imprimeMatriz(B);

    /// produto das matrizes
    C = produtoMatrizes(A,B);

    /// Impressao das matrizes
    cout << "Produto AxB: \n";
    imprimeMatriz(C);

    /// Liberacao das memorias
    liberaMatriz(A);
    liberaMatriz(B);
    liberaMatriz(C);

    return  0;
}
