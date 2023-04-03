#ifndef SOCKETS_H_
#define SOCKETS_H_

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<commons/log.h>

#define SOCKET_PENDING_CONNECTIONS 4

int iniciar_servidor(t_log* logger, char* ip, char* puerto);
int esperar_cliente(t_log* logger, int socket_servidor);

int crear_conexion(char* ip, char* puerto);

void liberar_conexion(int socket_cliente);

#endif /* SOCKETS_H_ */