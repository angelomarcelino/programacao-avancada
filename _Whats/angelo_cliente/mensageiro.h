#define PORTA_TESTE "23456"
#include <stdint.h>

enum Comandos{
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
