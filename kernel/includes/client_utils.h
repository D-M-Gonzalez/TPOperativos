#ifndef CLIENT_UTILS_H_
#define CLIENT_UTILS_H_

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<commons/log.h>


#include "calculos.h"
#include "datos.h"
#include "../../shared/includes/tad.h"

extern t_log* logger;

int crear_conexion(char* ip, char* puerto);
void liberar_conexion(int socket_cliente);
int handshake(int socket_cliente, uint8_t tipo_cliente, uint8_t tipo_servidor);
void serializar_contexto(int socket, t_contexto* contexto);
void serializar_instruccion_memoria(int socket,t_instruc_mem* instruccion);
void serializar_solicitud_tabla(int socket);
void serializar_solicitud_compactacion(int socket);
void serializar_instruccion_file(int socket,t_instruc_file* instruccion);

#endif /* CLIENT_UTILS_H_ */
