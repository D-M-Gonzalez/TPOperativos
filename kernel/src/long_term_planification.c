/*
 * long_term_planification.c
 *
 *  Created on: May 4, 2023
 *      Author: utnso
 */
#include "../includes/long_term_planification.h"

void estado_new(){
	while(1)
	{
		sem_wait(&sem_grado_multi);
		sem_wait(&sem_estado_new);
		pcb_t* pcb_para_listo = list_pop(pcb_new_list);
		list_push(pcb_ready_list,pcb_para_listo);
		pcb_para_listo->tiempo_espera_en_ready = temporal_create();
		pcb_para_listo->estado = PCB_READY;
		log_info(logger, "PID: %d - Estado Anterior: PCB_NEW - Estado Actual: PCB_READY", pcb_para_listo->pid);
		sem_post(&sem_estado_ready);
	}
}

void estado_exit(){
	while(1){
		uint8_t resultado = 1;
		sem_wait(&sem_estado_exit);
		pcb_t* proceso = list_pop(pcb_exit_list);
		proceso->estado=PCB_EXIT;
		send(proceso->consola, &resultado, sizeof(uint8_t), NULL);
		destroy_proceso(proceso);
		sem_post(&sem_grado_multi);
	}
}



