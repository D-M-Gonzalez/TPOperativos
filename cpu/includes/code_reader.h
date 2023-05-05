#ifndef CODE_READER_H_
#define CODE_READER_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<commons/log.h>

#include "../../shared/includes/tad.h"

int leer_instruccion(t_instruc* instruccion);
int ejecutar_set(char* param1, char* param2);
int ejecutar_yield();
int ejecutar_exit();
void cambiar_registro(char* registro, char* valor);
char* seleccionar_registro(char* param);

extern t_log* logger;
extern char ax[5];
extern char bx[5];
extern char cx[5];
extern char dx[5];
extern char eax[9];
extern char ebx[9];
extern char ecx[9];
extern char edx[9];
extern char rax[17];
extern char rbx[17];
extern char rcx[17];
extern char rdx[17];
extern uint32_t delay;

#endif /* CODE_READER_H_ */
