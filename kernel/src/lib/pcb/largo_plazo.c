#include "../../../includes/long_term_planification.h"

void iniciar_planificador_largo_plazo(){
	pthread_t hilo_new;
	pthread_t hilo_exit;
	pthread_create(&hilo_new, NULL, (void *)estado_new, NULL);
	pthread_create(&hilo_exit,NULL, (void *)estado_exit,NULL);
	pthread_detach(hilo_new);
	pthread_detach(hilo_exit);
}

pcb_t *crear_proceso(t_list* instrucciones, uint32_t socket){
	pcb_t *proceso = malloc(sizeof(pcb_t));
	sem_wait(&sem_pid_aumento);
	proceso->pid = ++pid;
	sem_post(&sem_pid_aumento);
	proceso->consola = socket;
	proceso->estimado_proxima_rafaga = estimacion_inicial;
	proceso->instrucciones = list_create();
	copiar_lista_instrucciones(proceso->instrucciones,instrucciones);
	proceso->registros_cpu = inicializar_registros();
	proceso->estado = PCB_NEW;
	proceso->recurso_bloqueante = malloc(sizeof(char)*2);
	proceso->recursos_asignados = list_create();
	proceso->tabla_segmento = solicitar_segmento_0(proceso->pid);
	memcpy(proceso->recurso_bloqueante,"0",(sizeof(char)*2));
	proceso->tabla_archivos_abiertos = list_create();
	return proceso;
}

void agregar_pcb_a_new(t_list* instrucciones, uint32_t socket){
	pcb_t *proceso = crear_proceso(instrucciones, socket);
	list_push(pcb_new_list,proceso);
	log_info(logger, "Se crea el proceso: %d en NEW", proceso->pid);
	sem_post(&sem_estado_new);
}
