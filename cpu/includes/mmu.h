#ifndef MMU_H_
#define MMU_H_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"../../shared/includes/tad.h"

extern int tam_max_segmento;

void traducir_direccion(char* param, tabla_segmentos_t *tabla_segmentos);
int obtener_direccion_base(int num_segmento, tabla_segmentos_t *tabla_segmentos);

#endif /* MMU_H_ */
