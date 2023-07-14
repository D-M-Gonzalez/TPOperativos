#ifndef DATOS_H_
#define DATOS_H_

#include<stdio.h>
#include<string.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include<commons/string.h>

#include "../../shared/includes/tad.h"

void crear_header(void* a_enviar, t_buffer* buffer, int lineas, uint32_t codigo);
void copiar_contexto(void* stream, t_contexto* contexto);
void copiar_instruccion_memoria(void* stream, t_instruc_mem* instruccion);
void copiar_instruc_file(void* stream, t_instruc_file* instruccion);
archivo_abierto_t* crear_archivo(char* nombre);
void copiar_instruccion_file(t_instruc_file* instruccion, t_contexto* contexto, uint32_t puntero);

#endif /* CLIENT_UTILS_H_ */
