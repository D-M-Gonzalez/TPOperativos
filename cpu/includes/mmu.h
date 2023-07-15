#ifndef MMU_H_
#define MMU_H_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<commons/log.h>
#include"client_utils.h"
#include"../../shared/includes/tad.h"

extern int tam_max_segmento;
extern t_log *logger;
extern int server_connection;
extern uint32_t contexto_estado;

int traducir_direccion(char* direccion, t_contexto *contexto, uint32_t largo);
bool validar_tam_segmento(int tam_segmento);
segmento_t* buscar_segmento(int num_segmento, t_list *segmentos);
int obtener_direccion_base(int num_segmento, tabla_segmentos_t *tabla_segmentos);
int obtener_tamanio_segmento(int num_segmento, tabla_segmentos_t *tabla_segmentos);

#endif /* MMU_H_ */
