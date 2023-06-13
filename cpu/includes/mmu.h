#ifndef MMU_H_
#define MMU_H_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

extern int tam_max_segmento;

void traducir_direccion(char* param);
obtener_direccion_base(int num_segmento);

#endif /* MMU_H_ */
