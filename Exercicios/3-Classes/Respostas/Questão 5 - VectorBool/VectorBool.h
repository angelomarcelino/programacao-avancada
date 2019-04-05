#ifndef _VECTOR_BOOL_H_
#define _VECTOR_BOOL_H_
#include <iostream>
#include <stdint.h>

using namespace std;

// Nessa classe, os booleanos serao armazenados em numeros inteiros de 16 bits
// Cada bit armazenarah um booleano
// Portanto, um objeto da classe terah um array de inteiros de tamanho igual a
// 1 + (numero de booleanos menos 1) divido por 16 (divisao inteira)

class VectorBool
{
private:
  unsigned N;    // Numero de booleanos
  unsigned Dim;  // Numero de inteiros
  uint16_t *x;   // array de inteiros

  // Funcoes privadas que lidam com alocacao de memoria
  void criar(unsigned Num);
  void copiar(const VectorBool &VB);
  void limpar();
public:
  inline VectorBool(): N(0), Dim(0), x(NULL) {}
  explicit inline VectorBool(unsigned Num) {criar(Num);}
  inline VectorBool(const VectorBool &VB) {copiar(VB);}
  inline ~VectorBool() {limpar();}

  // Funcoes de consulta
  // Para o usuario, dao a impressao que a classe realmente armazena booleanos
  // jah que a leitura e alteracao de valor dos elementos eh feita com dados bool
  inline unsigned size() const {return N;}
  inline unsigned capacity() const {return 16*Dim;}
  bool getBool(unsigned i) const;
  inline bool operator[](unsigned i) const {return getBool(i);}
  void setBool(unsigned i, bool B);

  inline void operator=(const VectorBool &VB) {if (this!=&VB) {limpar(); copiar(VB);}}
};

#endif
