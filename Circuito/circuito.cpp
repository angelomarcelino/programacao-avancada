#include <iostream>
#include <string>
#include <vector>
#include "bool3S.h"
#include "circuito.h"
#include <limits>
#include <bits/stdc++.h>

using namespace std;

///***********PORTA************///
Porta::Porta(unsigned NI): Nin(NI), saida(UNDEF_3S)
{
    if(NI<1) Nin = 1;
    if(NI>NUM_MAX_INPUTS_PORTA) Nin = 0;
    for(unsigned i=0; i<NUM_MAX_INPUTS_PORTA; i++) id_in[i] = 0;
}

Porta::Porta(const Porta &P): Nin(P.Nin), saida(P.saida)
{
    for(unsigned i=0; i<P.Nin; i++) id_in[i] = P.id_in[i];
}

int Porta::getId_in(unsigned i) const
{
    if(i>Nin) return 0;
    else return id_in[i];
}

void Porta::setNumInputs(unsigned N)
{
    if(N<NUM_MAX_INPUTS_PORTA) Nin=N;
}

void Porta::setSaida(bool3S s)
{
    if(saida!=s) saida = s;
}

void Porta::setId_in(unsigned i, int Id)
{
    if(i<Nin) id_in[i] = Id;
}

bool Porta::ler(istream &I)
{
    bool prv(false);
    I >> Nin;
    I.ignore(numeric_limits<streamsize>::max(),':');
    if (Nin>1 && Nin<=NUM_MAX_INPUTS_PORTA)
    {
        prv=true;
        for(unsigned i=0; i<Nin; i++)
        {
            I >> id_in[i];
        }
    }
    return prv;
}

///***********NOT************///
void Porta_NOT::setNumInputs(unsigned N)
{
    if (N==1) Nin=N;
}

bool Porta_NOT::ler(istream &I)
{
    bool prov(false);
    I >> Nin;
    if(Nin==1)
    {
        I.ignore(numeric_limits<streamsize>::max(),':');
        I >> id_in[0];
        prov = true;
    }
    return prov;
}

///**********SIMULACOES***********///
bool3S Porta_NOT::simular(const bool3S in[])
{
    saida = ~in[0];
    return ~in[0];
}

bool3S Porta_AND::simular(const bool3S in[])
{
    bool3S prov(TRUE_3S);
    for(unsigned i=0; i<Nin; i++)
    {
        prov = prov & in[i];
    }
    saida = prov;
    return prov;
}

bool3S Porta_NAND::simular(const bool3S in[])
{
    bool3S prov(TRUE_3S);
    for(unsigned i=0; i<Nin; i++)
    {
        prov = prov & in[i];
    }
    saida = ~prov;
    return ~prov;
}

bool3S Porta_OR::simular(const bool3S in[])
{
    bool3S prov(FALSE_3S);
    for(unsigned i=0; i<Nin; i++)
    {
        prov = prov | in[i];
    }
    saida = prov;
    return prov;
}

bool3S Porta_NOR::simular(const bool3S in[])
{
    bool3S prov(FALSE_3S);
    for(unsigned i=0; i<Nin; i++)
    {
        prov = prov | in[i];
    }
    saida = ~prov;
    return ~prov;
}

bool3S Porta_XOR::simular(const bool3S in[])
{
    bool3S prov(FALSE_3S);
    for(unsigned i=0; i<Nin; i++)
    {
        prov = prov ^ in[i];
    }
    saida = prov;
    return prov;
}

bool3S Porta_NXOR::simular(const bool3S in[])
{
    bool3S prov(FALSE_3S);
    for(unsigned i=0; i<Nin; i++)
    {
        prov = prov ^ in[i];
    }
    saida = ~prov;
    return ~prov;
}

///**********CIRCUITO*************///
void Circuito::alocar(unsigned NI, unsigned NO, unsigned NP)
{
    inputs.resize(NI,UNDEF_3S);
    id_out.resize(NO, 0);
    portas.resize(NP, NULL);
}

void Circuito::copiar(const Circuito &C)
{
    for(unsigned i=0; i<C.inputs.size(); i++) inputs[i] = C.inputs[i];
    for(unsigned i=0; i<C.id_out.size(); i++) id_out[i] = C.id_out[i];
    for(unsigned i=0; i<C.portas.size(); i++) portas.push_back(C.portas[i]->clone());
}

void Circuito::limpar()
{
    inputs.clear();
    id_out.clear();
    for(unsigned i=0; i<portas.size(); i++) {if (portas[i]!=NULL) {delete portas[i];}}
    portas.clear();
}

string Circuito::getNomePorta(unsigned IdPorta) const
{
    if (IdPorta>portas.size()) return "??";
    if (portas[IdPorta]==NULL) return "??";
    return portas[IdPorta]->getNome();
}

unsigned Circuito::getNumInputsPorta(unsigned IdPorta) const
{
    if (IdPorta>portas.size()) return 0;
    if (portas[IdPorta]==NULL) return 0;
    return portas[IdPorta]->getNumInputs();
}

int Circuito::getId_inPorta(unsigned IdPorta, unsigned i) const
{
    if (IdPorta>portas.size()) return -666;
    if (portas[IdPorta-1]==NULL) return 0;
    return portas[IdPorta-1]->getId_in(i);
}

bool3S Circuito::getSaida(unsigned IdOut) const
{
    if (id_out[IdOut-1]>0) return portas[(id_out[IdOut-1])-1]->getSaida();
    else return inputs[(-1*id_out[IdOut-1])-1];
}

int Circuito::getIdOutput(unsigned IdOut) const
{
    if (IdOut>id_out.size()) return -666;
    return id_out[IdOut-1];
}

bool Circuito::valido() const
{
    if(inputs.empty()||id_out.empty()||portas.empty()) return false;
    for(unsigned i=0; i<portas.size(); i++)
    {
        if(getNumInputsPorta(i)==0) return false;
        for(unsigned j=0; j<getNumInputsPorta(i); j++)
        {
            if(getId_inPorta(i+1,j)==0) return false;
        }
    }
    for(unsigned i=0; i<id_out.size(); i++)
    {
        if(id_out[i]==0) return false;
    }
    return true;
}

void Circuito::setPorta(unsigned IdPorta, const string &T, unsigned NIn) ///incluir funcao erro
{
    Porta_AND AN;
    Porta_NAND NA;
    Porta_NOR NO;
    Porta_NOT NT;
    Porta_NXOR NX;
    Porta_OR OR;
    Porta_XOR XO;

    if (IdPorta>portas.size()) return;

    if (portas[IdPorta]!=NULL) delete portas[IdPorta];

    if(T == "NT"){
        (&NT)->setNumInputs(NIn);
        portas[IdPorta]=(&NT)->clone();
    }
    else if(T == "AN"){
        (&AN)->setNumInputs(NIn);
        portas[IdPorta]=(&AN)->clone();
    }
    else if(T == "NA"){
        (&NA)->setNumInputs(NIn);
        portas[IdPorta]=(&NA)->clone();
    }
    else if(T == "OR"){
        (&OR)->setNumInputs(NIn);
        portas[IdPorta]=(&OR)->clone();
    }
    else if(T == "NO"){
        (&NO)->setNumInputs(NIn);
        portas[IdPorta]=(&NO)->clone();
    }
    else if(T == "XO"){
        (&XO)->setNumInputs(NIn);
        portas[IdPorta]=(&XO)->clone();
    }
    else if(T == "NX"){
        (&NX)->setNumInputs(NIn);
        portas[IdPorta]=(&NX)->clone();
    }
    else return; ///incluir funcao erro
}

void Circuito::setId_inPorta(unsigned IdPorta, unsigned I, int Id) const
{
    if (IdPorta>portas.size() || I>NUM_MAX_INPUTS_PORTA) return;
    portas[IdPorta]->setId_in(I, Id);
}

void Circuito::setIdOutput(unsigned IdOut, int Id)
{
    if(IdOut > id_out.size()) return;
    if(Id>0 && Id>portas.size()) return;
    if(Id<0 && (Id*-1)>inputs.size()) return;
    id_out[IdOut] = Id;
}

bool Circuito::salvar(const string &arq) const ///lembrar de tirar os cerr
{
    if(!valido()) return false;
    const char *arq_arr = arq.c_str();
    ofstream myfile(arq_arr);

    if (myfile.is_open())
    {
      /// Salva o cabecalho em uma linha
      myfile << "CIRCUITO: " << inputs.size() << ' ' << id_out.size() << ' ' << portas.size() << endl;
      myfile << "PORTAS:" << endl;
      /// Salva cada um das portas em uma linha
      for (unsigned i=0; i<portas.size(); i++)
      {
          myfile << i+1 << ") "<< *portas[i] << endl;
      }
      myfile << "SAIDAS:" << endl;
      for (unsigned i=0; i<id_out.size(); i++)
      {
          myfile << i+1 << ") " << id_out[i] << endl;
      }
      myfile.close();
    }
    else
    {
      /*cerr << "Erro na abertura do arquivo " << arq << " para escrita\n";*/
      return false;
    }
    return true;
}

bool Circuito::ler(const string &arq) ///lembrar de tirar os cerr
{
  /// Cria a stream associada ao arquivo
  const char *arq_arr = arq.c_str();
  ifstream myfile(arq_arr);

  if (myfile.is_open())
  {
    string pS;
    unsigned Nin;
    unsigned Nout;
    unsigned Nportas;
    string tipo;
    Porta_AND AN;
    Porta_NAND NA;
    Porta_NOR NO;
    Porta_NOT NT;
    Porta_NXOR NX;
    Porta_OR OR;
    Porta_XOR XO;

    myfile >> pS >> Nin >> Nout >> Nportas;
    if (pS!="CIRCUITO:" || Nin==0 || Nout==0 || Nportas==0)
    {
      /*cerr << "Arquivo " << arq << " invalido para leitura (cabecalho)\n";*/
      return false;
    }

    myfile.ignore(numeric_limits<streamsize>::max(),'\n');
    myfile >> pS;
    if (pS!="PORTAS:")
    {
        /*cerr << "Arquivo " << arq << " parcialmente invalido para leitura (segundo cabecalho)\n";*/
        return false;
    }
    /// Antes de ler os dados de um arquivo, zera o conteudo atual do Circuito
    limpar();
    alocar(Nin, Nout, Nportas);

    unsigned teste;
    for (unsigned i=0; i<portas.size(); i++)
    {
      myfile >> teste; /// teste de ordem
      if(teste != i+1){
          /*cerr<<"Portas fora de ordem, ou faltando\n";*/
          return false;
      }
      myfile.ignore(numeric_limits<streamsize>::max(),')');
      /// Le o tipo da porta
      myfile >> tipo;
      if(tipo == "NT") {portas[i]=((&NT)->clone());}
      else if(tipo == "AN") {portas[i]=((&AN)->clone());}
      else if(tipo == "NA") {portas[i]=((&NA)->clone());}
      else if(tipo == "OR") {portas[i]=((&OR)->clone());}
      else if(tipo == "NO") {portas[i]=((&NO)->clone());}
      else if(tipo == "XO") {portas[i]=((&XO)->clone());}
      else if(tipo == "NX") {portas[i]=((&NX)->clone());}
      else{ /// Tipo de porta nao era valida
          /*cerr << "Arquivo " << arq << " parcialmente invalido para leitura (portas)\n";*/
          return false;
      }
      portas[i]->ler(myfile);
    }

    myfile.ignore(numeric_limits<streamsize>::max(),'\n');
    myfile >> pS;
    if (pS!="SAIDAS:")
    {
        /*cerr << "Arquivo " << arq << " parcialmente invalido para leitura (terceiro cabecalho)\n";*/
        return false;
    }

    for(unsigned i=0; i<Nout; i++)
    {
        myfile >> teste; /// teste de ordem
        if(teste != i+1){
            /*cerr<<"Portas fora de ordem, ou faltando\n";*/
            return false;
        }
        myfile.ignore(numeric_limits<streamsize>::max(),')');
        myfile >> id_out[i];
    }
    myfile.close();
  }
  else
  {
    /*cerr << "Erro na abertura do arquivo " << arq << " para leitura\n";*/
    return false;
  }
  return true;
}

void Circuito::simular() ///testar no codeblocks
{
  if(!valido()) return; ///add func erro
  for(unsigned i=0; i<portas.size(); i++) portas[i]->setSaida(UNDEF_3S);

  bool tudo_def, alguma_def;
  bool3S in_porta[NUM_MAX_INPUTS_PORTA];

  do{
    tudo_def = true;
    alguma_def = false;
    for(unsigned i=0 ; i<portas.size(); i++)
    {
      if(portas[i]->getSaida()==UNDEF_3S)
      {
         for (unsigned j=0; j<(portas[i]->getNumInputs()); j++)
         {
            if(portas[i]->getId_in(j) < 0)
            {
                in_porta[j] = inputs[-1*(portas[i]->getId_in(j))-1];
            }
            if(portas[i]->getId_in(j) > 0)
            {
                in_porta[j] = portas[(portas[i]->getId_in(j))-1]->getSaida();
            }
         }
         portas[i]->simular(in_porta);
         /*
         cout << "\nteste: " << portas[i]->getNome() << ' '
              << portas[i]->getSaida();
         for (unsigned g=0; g<(portas[i]->getNumInputs()); g++)
         {
             cout << ' ' << portas[i]->getId_in(g) << ' ' << in_porta[g];
         }
         cout << endl;
         */
         if(portas[i]->getSaida() == UNDEF_3S) tudo_def = false;
         else {alguma_def = true;}
      }
    }
  }while(!tudo_def && alguma_def);
}

bool Circuito::simular(vector<bool3S> Inputs)
{
    if(Inputs.size() != getNumInputs()) return false;
    for(unsigned i=0; i < Inputs.size(); i++)
    {
        inputs[i] = Inputs[i];
    }
    simular();
    return true;
}

void Circuito::gerarTabela(void)
{
    if(!valido()) return; ///add func erro
    for(unsigned i=0; i<inputs.size(); i++) {inputs[i]=UNDEF_3S;}

    int i(0);
    int cont(0);
    do{
        imprimirEntradas(cont);
        simular(inputs);
        imprimirSaidas(cont);
        cont++;
        i=inputs.size()-1;
        while(i>=0 && inputs[i]==TRUE_3S) {inputs[i] = UNDEF_3S; i--;}
        if(i>=0)
        {
            if(inputs[i] == UNDEF_3S) {inputs[i] = FALSE_3S;}
            else {inputs[i] = TRUE_3S;}
        }
    }while(i>=0);
}


//***************NAO VAI SER USADO EM QT***********************///
//***********PORTA************//
void Porta::digitar()
{
    do{
        cout << "Numero de entradas: ";
        cin >> Nin;
    }while (Nin<2 || Nin>NUM_MAX_INPUTS_PORTA);
    for(unsigned i=0; i<Nin; i++)
    {
        cout <<"ID da Entrada "<<i<<": ";
        cin >> id_in[i];
    }
    saida = UNDEF_3S;
}

ostream &Porta::imprimir(ostream &O) const
{
    O << this->getNome() << ' ' << Nin
      << ':';
    for(unsigned i=0; i<Nin; i++)
    {
        O << ' ' << id_in[i];
    }
    return O;
}

//************NOT*************//
void Porta_NOT::digitar()
{
    cout << "ID da Entrada " << 0 << ": ";
    cin >> id_in[0];
    saida = UNDEF_3S;
}

//**********CIRCUITO**********//
void Circuito::digitar() // e se id_in da porta for invalido?
{
    unsigned Nin, Nout, Nport;

    cout << "Numero de entradas: ";
    cin >> Nin;
    cout << "Numero de saidas: ";
    cin >> Nout;
    cout << "Numero de portas: ";
    cin >> Nport;

    limpar();
    alocar(Nin, Nout, Nport);
    ///Entrada das portas
    Porta_AND AN;
    Porta_NAND NA;
    Porta_NOR NO;
    Porta_NOT NT;
    Porta_NXOR NX;
    Porta_OR OR;
    Porta_XOR XO;
    string tipo;
    unsigned cont1(0);
    do{
        bool porta_valida(true);
        cout << "Tipo da porta " << cont1+1 << ") : ";
        cin >> tipo;
        if(tipo == "NT") portas[cont1]=((&NT)->clone());
        else if(tipo == "AN") portas[cont1]=((&AN)->clone());
        else if(tipo == "NA") portas[cont1]=((&NA)->clone());
        else if(tipo == "OR") portas[cont1]=((&OR)->clone());
        else if(tipo == "NO") portas[cont1]=((&NO)->clone());
        else if(tipo == "XO") portas[cont1]=((&XO)->clone());
        else if(tipo == "NX") portas[cont1]=((&NX)->clone());
        else{
            cerr << "Tipo de porta invalida." << endl;
            porta_valida = false;
        }
        if(porta_valida) {portas[cont1]->digitar(); cont1++;} /// e se id_in da porta for invalido?
    }while(cont1<Nport);

    /// Entrada das saidas
    int cont(0);
    do{
        int teste;
        bool passou(false);
        cout << "Saida " << cont+1 << " recebe de: ";
        cin >> teste;

        if(teste>0 && teste<=portas.size()){id_out[cont] = teste; cont++; passou=true;}
        else if(teste<0)
        {
            if((teste*(-1))<=inputs.size()) {id_out[cont] = teste; cont++; passou=true;}
        }
        if(teste==0) {id_out[cont]=0; passou=true;}
        if(!passou) cerr<<"erro\n";

    }while (cont<Nout);
}

void Circuito::digitarEntradas()
{
    cout << "Digite as " << inputs.size() << " entradas.\n";
    for (unsigned i=0; i<inputs.size(); i++)
    {
        cout << (i+1) << "): ";
        cin >> inputs[i];
    }
}

/*void Circuito::imprimirEntradas(void) const
{
    cout << "ENTRADAS:";
    for (unsigned i=0; i<inputs.size(); i++)
    {
        cout << inputs[i] << ' ';
    }
    cout << "\t";
}

void Circuito::imprimirSaidas(void) const
{
    cout << "SAIDAS:";
    for (unsigned i=0; i<id_out.size(); i++)
    {
        cout << getSaida(i+1) << ' ';
    }
    cout << endl;
}*/

ostream &Circuito::imprimir(ostream &O) const // nao vai ser usada no qt
{
    O << "CIRCUITO: " << getNumInputs() << ' '
      << getNumOutputs() << ' ' << getNumPortas() << '\n'
      << "PORTAS: \n";
    for (unsigned i=0; i<getNumPortas(); i++)
    {
        O << i+1 << ')' << ' ' << *portas[i] << '\n';
    }
    O << "SAIDAS: \n";
    for (unsigned i=0; i<getNumOutputs(); i++)
    {
        O << i+1 << ')' << ' ' << id_out[i] << '\n';
    }
    return O;
}
