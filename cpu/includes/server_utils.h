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

extern t_log* logger;

void* recibir_buffer(int*, int);
int iniciar_servidor(char* puerto);
int esperar_cliente(int);
t_list* recibir_paquete(int);
void recibir_mensaje(int);
int recibir_operacion(int);

#endif /* SERVER_UTILS_H_ */