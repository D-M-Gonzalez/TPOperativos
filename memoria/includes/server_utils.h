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
#include<stdbool.h>
#include<string.h>
#include<assert.h>
#include "../../shared/includes/tad.h"

/*typedef enum
{
	MENSAJE,
	PAQUETE
}op_code;
*/
extern t_log* logger;
extern bool cpu_conectada;
extern bool kernel_conectado;
extern bool fileSystem_conectado;

int iniciar_servidor(char* puerto);
int esperar_cliente(int);
char* handshake(int);
void deserializar_header(t_paquete* paquete, int socket_cliente);
void deserializar_contexto(t_contexto* contexto, t_buffer* buffer, int lineas);
void liberar_conexion(int socket_servidor);

#endif /* SERVER_UTILS_H_ */
