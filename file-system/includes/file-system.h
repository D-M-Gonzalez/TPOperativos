#ifndef FILE_SYSTEM_H_
#define FILE_SYSTEM_H_

#include "../../shared/includes/tad.h"
#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "client_utils.h"
#include "server_utils.h"
#include "utils.h"
#include "initial_setup.h"

void iterator(char* value);
void terminar_programa();

// ___ CONFIG VARIABLES ____



t_log* logger;

int server_connection;

int memoria_connection;

// _____________________

// ___ CONFIG VARIABLES ____
char* memoria_ip;
char* memoria_port;

char* server_port;

t_config* config;

tabla_archivos_abiertos_t* tabla_file_system;

// _____________________

#endif
