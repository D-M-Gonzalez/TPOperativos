#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

#include "../../shared/includes/tad.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "utils.h"

extern t_lista_mutex* lista_recursos;
extern t_list * tabla_global_archivos_abiertos;
extern sem_t sem_tabla_archivos;

//extern  pcb_t* pcb;
extern t_log* logger;

int verif_crear_recurso_file(archivo_abierto_t* archivo);
int verif_eliminar_recurso_file(pcb_t* proceso, archivo_abierto_t* archivo);
void crear_recurso_file(archivo_abierto_t* archivo);
void eliminar_recurso_file(archivo_abierto_t* archivo, t_recurso* recurso_a_eliminar);

#endif /* FILE_UTILS_H_ */
