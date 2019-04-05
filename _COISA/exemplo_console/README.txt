###############################################################################

PARA COMPILAR OS SOCKETS NO WINDOWS:
###############################################################################



NAO ESQUECA DE LINKAR COM A BIBLIOTECA Ws2_32.

Para incluir essa opcao no linkador:


No CodeBlocs:
botao direito no nome do projeto,
Build options,
Linker settings,

adicionar biblioteca Ws2_32



No Qt:
adicionar no fim do arquivo <PROJETO>.pro as seguintes linhas:


LIBS   += \
    -lWs2_32



###############################################################################

Informacao sobre os sockets Windows (que são quase as mesmas do Linux):

###############################################################################


INICIO:

https://msdn.microsoft.com/en-us/library/windows/desktop/ms738545(v=vs.85).aspx

CRIANDO UMA APLICACAO WINSOCK (cliente e servidor):

https://msdn.microsoft.com/en-us/library/windows/desktop/ms737629(v=vs.85).aspx

CLIENTE:
https://msdn.microsoft.com/en-us/library/windows/desktop/bb530741(v=vs.85).aspx

SERVIDOR:

https://msdn.microsoft.com/en-us/library/windows/desktop/bb530742(v=vs.85).aspx

SELECT:

https://msdn.microsoft.com/en-us/library/windows/desktop/ms740141(v=vs.85).aspx

SEND, RECV:

https://msdn.microsoft.com/en-us/library/windows/desktop/bb530746(v=vs.85).aspx


###############################################################################

PARA COMPILAR THREADS NO LINUX:
###############################################################################



Inclua a opcao -pthread no compilador g++:

g++ -pthread -o nome_qualquer nome_qualquer.cpp
