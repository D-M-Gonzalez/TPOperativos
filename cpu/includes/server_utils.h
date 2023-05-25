/*
 * utils.h
 *
 *  Created on: Apr 3, 2023
 *      Author: utnso
 */

#ifndef SERVER_UTILS_H_
#define SERVER_UTILS_H_

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include<commons/config.h>
#include<string.h>
#include<assert.h>
#include "../../shared/includes/tad.h"

extern t_log* logger;

int iniciar_servidor(char* puerto);
int esperar_cliente(int);
char* handshake(int);
void deserializar_header(t_paquete* paquete, int socket);
t_contexto* deserializar_contexto(t_buffer* buffer, int lineas, t_contexto* contexto);

#endif /* SERVER_UTILS_H_ */
