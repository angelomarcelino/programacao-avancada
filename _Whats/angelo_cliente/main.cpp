#include "whatsclient.h"
#include <QApplication>
#include "mysocket.h"
#include "dados_cliente.h"
#include "dados_whatsprog.h"

//Variaveis globais
DadosCliente DC;
tcp_mysocket sock;
HANDLE th_id;
WhatsClient* pt_w;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WhatsClient w;
    pt_w = &w;

    WSADATA wsaData;
    MYSOCKET_STATUS iResult;

    // All processes that call Winsock functions must first initialize the use of the Windows Sockets DLL (WSAStartup)
    // before making other Winsock functions calls
    // The MAKEWORD(2,2) parameter of WSAStartup makes a request for version 2.2 of Winsock on the system
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0)
    {
      cerr << "WSAStartup failed: " << iResult << endl;
      exit(1);
    }
    th_id = NULL;

    w.show();

    int prov = a.exec();

    /* call WSACleanup when done using the Winsock dll */
    WSACleanup();

    return prov;
}
