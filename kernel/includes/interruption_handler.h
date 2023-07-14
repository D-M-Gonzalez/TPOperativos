#ifndef INTERRUPTION_HANDLER_H_
#define INTERRUPTION_HANDLER_H_

#include "../../shared/includes/tad.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "client_utils.h"
#include "server_utils.h"
#include "utils.h"
#include "long_term_planification.h"
#include "short_term_planification.h"
#include "comm_Mem.h"
#include "comm_File.h"
#include "comm_threadKernel.h"

extern t_lista_mutex* lista_recursos;
extern t_list * tabla_global_archivos_abiertos;

//extern  pcb_t* pcb;
extern t_log* logger;

contexto_estado_t resumir_ejecucion(pcb_t* pcb);

#endif /* INTERRUPTION_HANDLER_H_ */
