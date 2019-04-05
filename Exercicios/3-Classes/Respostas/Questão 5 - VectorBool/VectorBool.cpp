#include "VectorBool.h"

void VectorBool::criar(unsigned Num)
{
  N = Num;
  // Um objeto da classe terah um array de inteiros de tamanho igual a
  // 1 + (N-1)/16 (divisao inteira)
  Dim = (N==0 ? 0 : 1+(N-1)/16);
  x = (Dim==0 ? NULL : new uint16_t[Dim]);
}

void VectorBool::copiar(const VectorBool &VB)
{
  criar(VB.N);
  for (unsigned i=0; i<Dim; i++) x[i] = VB.x[i];
}

void VectorBool::limpar()
{
  if (x!=NULL) delete[] x;
  Dim = 0;
  N = 0;
}

bool VectorBool::getBool(unsigned i) const
{
  if (i>=N)
  {
    cerr << "Index out of range\n";
    return false;
  }
  unsigned i_int = i/16; // Em qual inteiro o bool estah armazenado
  unsigned i_bit = i%16; // Em qual bit do inteiro o bool estah armazenado
  // 0x8000, em hexadecimal, corresponde, em binario, a 1000 0000 0000 0000
  // Deslocando-se essa constante i_bits bits para a direita, com o operador >>,
  // obtem-se um numero binario com quase todos os bits 0, exceto por um 1
  // na posicao correspondente ao bit que armazena o booleano que se deseja
  unsigned mascara = (0x8000 >> i_bit);

  // Faz um AND binario (operador &) entre o inteiro e a mascara
  // Dah zero se o bit for 0; um valor diferente de zero se for 1
  return ( (x[i_int] & mascara) ? true : false);
}

void VectorBool::setBool(unsigned i, bool B)
{
  if (i>=N)
  {
    cerr << "Index out of range\n";
    return;
  }
  unsigned i_int = i/16; // Em qual inteiro o bool estah armazenado
  unsigned i_bit = i%16; // Em qual bit do inteiro o bool estah armazenado
  // 0x8000, em hexadecimal, corresponde, em binario, a 1000 0000 0000 0000
  // Deslocando-se essa constante i_bits bits para a direita, com o operador >>,
  // obtem-se um numero binario com quase todos os bits 0, exceto por um 1
  // na posicao correspondente ao bit que armazena o booleano que se deseja
  unsigned mascara = (0x8000 >> i_bit);

  if (B)
  {
    // Faz um OR binario (operador |) entre o inteiro e a mascara
    // Coloca 1 no bit correponde ao 1 da mascara; deixa inalterados os demais
    x[i_int] |= mascara;
  }
  else
  {
    // Nega todos os bits da mascara: 1->0 e 0->1
    mascara = ~mascara;

    // Faz um AND binario (operador &) entre o inteiro e a mascara
    // Coloca 0 no bit correponde ao 0 da mascara; deixa inalterados os demais
    x[i_int] &= mascara;
  }
}


