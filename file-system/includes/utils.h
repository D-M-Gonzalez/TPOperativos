#ifndef UTILS_H_
#define UTILS_H_

#include "../../shared/includes/tad.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>
#include <commons/collections/list.h>
#include <pthread.h>

#include "fcb_list.h"
#include "handler_file.h"

extern void* memoria_file_system;
extern int tam_memoria_file_system;
extern int tamanio_de_bloque;
extern t_log* logger;

t_log* iniciar_logger(void);
t_config* iniciar_config(char * path_config);
fcb_t* inicializar_fcb();
void inicializar_datos_memoria();
void* list_pop(t_list* list);
t_list* armar_lista_offsets(int id_fcb, int tam_a_leer, int p_seek);

#endif /* CLIENT_H_ */
