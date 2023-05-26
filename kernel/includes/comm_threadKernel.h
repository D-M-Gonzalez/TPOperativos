#ifndef COMM_THREADKERNEL_H_
#define COMM_THREADKERNEL_H_

#include "../../shared/includes/tad.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "client_utils.h"
#include "server_utils.h"
#include "general_planification_utils.h";
#include "long_term_planification.h";
//#include "../includes/kernel.h"
//extern  pcb_t* pcb;
extern int cpu_connection;
extern t_log* logger;
extern tabla_archivos_abiertos_t archivos_abiertos;

t_contexto* obtener_contexto_pcb(pcb_t* pcb);
void enviar_contexto(pcb_t* pcb);



#endif /* COMM_THREADKERNEL_H_ */
