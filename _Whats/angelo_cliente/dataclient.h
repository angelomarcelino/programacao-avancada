#ifndef DATACLIENT_H
#define DATACLIENT_H

#define PORTA_TESTE "23456"
#include <stdint.h>
#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

enum Comandos
{
    CMD_NEW_USER = 1001,
    CMD_LOGIN_USER,
    CMD_LOGIN_OK,
    CMD_LOGIN_INVALIDO,
    CMD_NOVA_MSG,
    CMD_MSG_RECEBIDA,
    CMD_MSG_ENTREGUE,
    CMD_MSG_LIDA1,
    CMD_MSG_LIDA2,
    CMD_ID_INVALIDA,
    CMD_USER_INVALIDO,
    CMD_MSG_INVALIDA,
    CMD_LOGOUT_USER
};

enum StatusMensagem {zero_st = 0, MSG_ENVIADA, MSG_RECEBIDA, MSG_ENTREGUE, MSG_LIDA};

class Mensagem
{
private:
    string dest;
    string txt;
    int id;
    StatusMensagem st;
public:
    //Construtor por Default
    inline Mensagem(): dest(""), txt(""), id(), st(zero_st) {}
    inline Mensagem(string dest="",string txt="", int id=-1, StatusMensagem st=zero_st) {}
    inline ~Mensagem() {}

    //Metodos de Consulta
    inline string getDest() const {return dest;}
    inline string getTxt() const {return txt;}
    inline int getId() const {return id;}
    inline StatusMensagem getStatus() const {return st;}

    //Metodos de Setar
    void setDest(string &Dest);
    void setTxt(string &Txt);
    void setId(unsigned Id);
    void setStatus(StatusMensagem St);
};

class Conversa
{
private:
    string corsp;
    vector<Mensagem> ListMsg;

    void alocar(unsigned NM); //usar limpar
    void copiar(const Conversa &C); //usar limpar
public:
    //Construtor por Default
    inline Conversa(): corsp(""), ListMsg() {}
    inline Conversa(const Conversa &C) {copiar(C);}
    void limpar();
    inline ~Conversa() {limpar();}
    inline void operator=(const Conversa &C) {if(this!=&C){limpar();copiar(C);}}

    inline bool operator==(Conversa &C){return corsp==C.corsp;}

    //Metodos de consulta
    inline string getCorresp() const {return corsp;}
    inline unsigned getNumMsg() const {return ListMsg.size();}
    Mensagem getMsg(unsigned Id) const;
    StatusMensagem getStMsg(unsigned Id) const;

    //Metodos de Mod
    void setCorresp(string &Corresp);
    void insertMsg(Mensagem &M) {ListMsg.push_back(M);}
    void deleteMsg(unsigned Id);
};

class DataClient
{
private:
    list<Conversa> LC;
    string login;
    string ipservidor;
    string senha;

    void alocar(unsigned NC); //usar limpar
    void copiar(const DataClient &DC); //usar limpar
public:
    inline DataClient(): LC(), login(""), ipservidor(""), senha("") {}
    inline DataClient(const DataClient &DC) {copiar(DC);}
    void limpar();
    inline ~DataClient() {limpar();}
    inline void operator=(const DataClient &DC) {if(this!=&DC){limpar();copiar(DC);}}

    //Metodos de Consulta
    inline string getLogin() const {return login;}
    inline string getIpServ() const {return ipservidor;}
    inline string getSenha() const {return senha;}
    inline unsigned getNumConv() const {return LC.size();}
    string getCorresp(unsigned i) const;
    unsigned getConversa(string Corresp) const;
    unsigned getMsgsConv(unsigned i) const;
    string getMsgConv(unsigned IdC, unsigned IdM) const;
    StatusMensagem getStMsgConv(unsigned IdC, unsigned IdM) const;

    //Metodos de Mod
    inline void setLogin(string Login) {login = Login;}
    inline void setIp(string IpServ) {ipservidor = IpServ;}
    inline void setSenha(string Senha) {senha = Senha;}
    void insertConversa();
    void deleteConversa(unsigned id);

};

#endif // DATACLIENT_H
