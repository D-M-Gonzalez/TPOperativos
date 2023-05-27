#ifndef UTILS_H_
#define UTILS_H_

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>
#include <commons/collections/list.h>
#include <pthread.h>
#include "../../shared/includes/tad.h"

typedef struct {
	t_list * lista;
    pthread_mutex_t mutex;
} t_lista_mutex;

t_log* iniciar_logger(void);
t_config* iniciar_config(char * path_config);
t_lista_mutex* init_list_mutex();
void list_push(t_lista_mutex * list , void* info);
void * list_pop(t_lista_mutex * list);
void list_mutex_destroy(t_lista_mutex * list);
bool list_mutex_is_empty(t_lista_mutex * list);
int list_mutex_size(t_lista_mutex * list);
bool estaEnTabla_archivos_abiertos(char* nombre_archivo,tabla_archivos_abiertos_t* tabla_archivos_abiertos);
#endif /* CLIENT_H_ */
