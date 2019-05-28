#ifndef _CIRCUITO_H_
#define _CIRCUITO_H_

#include <iostream>
#include <string>
#include <vector>
#include "bool3S.h"

using namespace std;

///
/// A CLASSE PORTA
///

#define NUM_MAX_INPUTS_PORTA 4

class Porta;
typedef Porta *ptr_Porta;

class Porta {
protected:
  unsigned Nin;
  int id_in[NUM_MAX_INPUTS_PORTA];
  bool3S saida;
public:
  Porta(unsigned NI=2);
  Porta(const Porta &);
  inline virtual ~Porta() {}

  virtual ptr_Porta clone() const = 0;

  virtual string getNome() const = 0;

  /// Funcoes de consulta
  inline unsigned getNumInputs() const {return Nin;}
  inline bool3S getSaida() const {return saida;}
  int getId_in(unsigned i) const;

  /// Funcoes de modificacao
  virtual void setNumInputs(unsigned N);
  void setSaida(bool3S s);
  void setId_in(unsigned i, int Id);

  virtual void digitar(); //nao serve em qt

  virtual bool ler(istream &I);

  ostream &imprimir(ostream &O) const; //nao serve em qt

  virtual bool3S simular(const bool3S in[]) = 0;
};

inline ostream &operator<<(ostream &O, const Porta &X) {return (&X)->imprimir(O);}; //nao usa em qt

/// As outras PORTAS
class Porta_NOT: public Porta {
public:
  inline Porta_NOT(): Porta(1) {}
  inline ~Porta_NOT() {}
  inline ptr_Porta clone() const {return new Porta_NOT(*this);}
  inline string getNome() const {return "NT";};

  void setNumInputs(unsigned N);

  void digitar();
  bool ler(istream &I);

  bool3S simular(const bool3S in[]);
};

class Porta_AND: public Porta {
public:
  inline Porta_AND(): Porta() {}
  inline ~Porta_AND() {}
  inline ptr_Porta clone() const {return new Porta_AND(*this);}
  inline string getNome() const {return "AN";};

  bool3S simular(const bool3S in[]);
};

class Porta_NAND: public Porta {
public:
  inline Porta_NAND(): Porta() {}
  inline ~Porta_NAND() {}
  inline ptr_Porta clone() const {return new Porta_NAND(*this);}
  inline string getNome() const {return "NA";};

  bool3S simular(const bool3S in[]);
};

class Porta_OR: public Porta {
public:
  inline Porta_OR(): Porta() {}
  inline ~Porta_OR() {}
  inline ptr_Porta clone() const {return new Porta_OR(*this);}
  inline string getNome() const {return "OR";};

  bool3S simular(const bool3S in[]);
};

class Porta_NOR: public Porta {
public:
  inline Porta_NOR(): Porta() {}
  inline ~Porta_NOR() {}
  inline ptr_Porta clone() const {return new Porta_NOR(*this);}
  inline string getNome() const {return "NO";};

  bool3S simular(const bool3S in[]);
};

class Porta_XOR: public Porta {
public:
  inline Porta_XOR(): Porta() {}
  inline ~Porta_XOR() {}
  inline ptr_Porta clone() const {return new Porta_XOR(*this);}
  inline string getNome() const {return "XO";};

  bool3S simular(const bool3S in[]);
};

class Porta_NXOR: public Porta {
public:
  inline Porta_NXOR(): Porta() {}
  inline ~Porta_NXOR() {}
  inline ptr_Porta clone() const {return new Porta_NXOR(*this);}
  inline string getNome() const {return "NX";};

  bool3S simular(const bool3S in[]);
};

/// A CLASSE CIRCUITO
class Circuito {
private:
  vector<bool3S> inputs;   /// vetor que deve ser alocado com dimensao "Nin"
  vector<int> id_out;       /// vetor que deve ser alocado com dimensao "Nout"
  vector<ptr_Porta> portas; /// vetor que deve ser alocado com dimensao "Nportas"

  void alocar(unsigned NI, unsigned NO, unsigned NP); ///usar limpar()
  void copiar(const Circuito &C);///usar limpar()
public:
  /// Construtores
  inline Circuito():inputs(),id_out(),portas() {}
  inline Circuito(const Circuito &C) {copiar(C);}
  void limpar();
  inline ~Circuito() {limpar();}
  inline void operator=(const Circuito &C) {if (this!=&C) {limpar(); copiar(C);}}

  /// Funcoes de consulta
  inline unsigned getNumInputs() const {return inputs.size();}
  inline unsigned getNumOutputs() const {return id_out.size();}
  inline unsigned getNumPortas() const {return portas.size();}

  /// Caracteristicas das portas
  string getNomePorta(unsigned IdPorta) const;
  unsigned getNumInputsPorta(unsigned IdPorta) const;
  int getId_inPorta(unsigned IdPorta, unsigned i) const;

  /// Caracteristicas das saidas
  bool3S getSaida(unsigned IdOut) const;
  bool3S getEntrada(unsigned IdIn) const {return inputs[IdIn];}
  int getIdOutput(unsigned IdOut) const;
  bool valido() const;

  /// Funcoes de modificacao de valores
  inline void redimensionar(unsigned NI, unsigned NO, unsigned NP) {limpar(); alocar(NI,NO,NP);}
  void setPorta(unsigned IdPorta, const string &T, unsigned NIn);
  void setId_inPorta(unsigned IdPorta, unsigned I, int Id) const;
  void setIdOutput(unsigned IdOut, int Id);

  /// Entrada dos dados de um circuito via teclado
  void digitar(); //nao serve em qt
  bool ler(const string &arq);
  ostream &imprimir(ostream &O=cout) const; //nao serve em qt
  bool salvar(const string &arq) const;
  void digitarEntradas();
  void imprimirEntradas(int i) const;
  void imprimirSaidas(int i) const;

  /// Simulacao
  void simular();
  bool simular(vector<bool3S> Inputs);
  void gerarTabela(void);
};

inline ostream &operator<<(ostream &O, const Circuito &C) {return C.imprimir(O);}

#endif /// _CIRCUITO_H_
