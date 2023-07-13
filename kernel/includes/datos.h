#ifndef DATOS_H_
#define DATOS_H_

#include<stdio.h>
#include<string.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include<commons/string.h>

#include "../../shared/includes/tad.h"

archivo_abierto_t* crear_archivo(char* nombre);
void copiar_instruccion_file(t_instruc_file* instruccion, t_contexto* contexto, uint32_t puntero);

#endif /* CLIENT_UTILS_H_ */
