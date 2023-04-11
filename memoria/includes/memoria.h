/*
 * memoria.h
 *
 *  Created on: Apr 3, 2023
 *      Author: utnso
 */

#ifndef MEMORIA_H_
#define MEMORIA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commons/log.h>
#include <pthread.h>

#include "server_utils.h"
#include "utils.h"
#include "initial_setup.h"

typedef struct
{
	int num_socket;
	int id_cliente;
} t_conexion;

void iterator(char* value);
void thread_main(t_conexion *conexion);


// ___ CONFIG VARIABLES ____

t_log* logger;

int server_connection;

int num_threads = 0;
pthread_t tid[3];

// _____________________

// ___ CONFIG VARIABLES ____

char* server_port;

t_config* config;

// _____________________





#endif /* MEMORIA_H_ */