#include "../../../includes/short_term_planification.h"

void iniciar_planificador_corto_plazo()
{

	pthread_t hilo_ready;
	pthread_t hilo_block;
	pthread_t hilo_exec;
	pthread_create(&hilo_ready, NULL, (void*) estado_ready, NULL);
	pthread_create(&hilo_block, NULL, (void*) estado_block, NULL);
	pthread_create(&hilo_exec, NULL, (void*) estado_exec, NULL);
	pthread_detach(hilo_ready);
	pthread_detach(hilo_block);
	pthread_detach(hilo_exec);
}

long double calcular_ratio(pcb_t *pcb_actual)
{
	long double ratio = (((long double) temporal_gettime(pcb_actual->tiempo_espera_en_ready) + (long double) pcb_actual->estimado_proxima_rafaga) / (long double) pcb_actual->estimado_proxima_rafaga);

	return ratio;
}

bool mayor_ratio(void *proceso_1, void *proceso_2)
{
	long double ratio_1 = calcular_ratio((pcb_t*) proceso_1);
	long double ratio_2 = calcular_ratio((pcb_t*) proceso_2);

	return ratio_1 > ratio_2;
}
