#ifndef SERVER_H
#define SERVER_H
#include "dados_whatsprog.h"
#include "dados_servidor.h"


class Server {
    public:
        Server();
        virtual ~Server();
        bool read();
        bool save() const;
    protected:
    private:

}
};

#endif // SERVER_H
