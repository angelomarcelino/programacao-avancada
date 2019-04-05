//Both
enum STATUS_MSG {zero_st = 0, MSG_ENVIADA, MSG_RECEBIDA, MSG_ENTREGUE, MSG_LIDA} 

class Mensagem 
{
private:
    string remt;
    string dest;
    string txt;
    unsigned id;
    STATUS_MSG st(zero_st);
}

//Client
class Conversa 
{
private:
    string correspondente;
    vector<Mensagem> ListMsg;
public:
    operator==(string corrsp);
}

//No "main" do cliente
vector<Conversa> ListConv;
itr = find(... , destinatario)
itr->ListMsg.push_back(mensagem)

//Server
list<Mensagem> Buffer;
find msgs recebidas e enviar
find msgs lidas e enviar cmds

class Client 
{
    string login, senha;
    MY_SOCKET sockt_client;
}

vector<Client> VecClient;
