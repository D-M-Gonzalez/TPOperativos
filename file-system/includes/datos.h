#ifndef DATOS_H_
#define DATOS_H_

#include<stdio.h>
#include<string.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include<commons/string.h>

#include "../../shared/includes/tad.h"

void copiar_tabla_segmentos(void *stream, t_list *lista_tablas);
void copiar_instruccion_memoria(void* stream, t_instruc_mem* instruccion);
void copiar_instruccion_mov(void* stream, t_instruc_mov* instruccion);
void copiar_instruccion_mem(t_instruc_mem* instruccion, t_instruc_file* contexto);
t_instruc_mem* inicializar_instruc_mem();
t_instruc_file* inicializar_instruc_file();
fcb_t* iniciar_fcb(char* path_fcb);
void copiar_instruccion_memoria(void* stream, t_instruc_mem* instruccion);
t_instruc_mov* inicializar_instruc_mov();
void generar_instruccion_mov(t_instruc_mov* instruccion_nueva,contexto_estado_t instruccion, uint32_t dir_fisica, uint32_t tamanio, char* valor);

#endif /* CLIENT_UTILS_H_ */
