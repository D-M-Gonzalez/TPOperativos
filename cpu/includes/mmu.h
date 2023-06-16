#ifndef MMU_H_
#define MMU_H_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<commons/log.h>
#include"../../shared/includes/tad.h"

extern int tam_max_segmento;

extern t_log *logger;

void traducir_direccion(char *param, tabla_segmentos_t *tabla_segmentos);
segmento_t* buscar_segmento(int num_segmento, t_list *segmentos);
int obtener_direccion_base(int num_segmento, tabla_segmentos_t *tabla_segmentos);

#endif /* MMU_H_ */
