#include "../../includes/utils.h"

char* armar_lista_pids(t_list *lista)
{
	int largo = list_size(lista);
	char *pids = string_new();
	string_append(&pids, "Cola Ready %s: [");

	for (int i = 0; i < largo; i++)
	{
		pcb_t *pcb = list_get(lista, i);
		char *pid = string_from_format("%u", pcb->pid);
		string_append(&pids, " ");
		string_append(&pids, pid);

		free(pid);
	}
	string_append(&pids, " ]");

	return pids;
}

void copiar_string(char *origen, char *destino)
{
	int largo_origen = strlen(origen);

	memcpy(destino, origen, largo_origen);
}

void destroy_proceso(pcb_t *proceso) {

//	while(list_size(proceso->tabla_archivos_abiertos) != 0){
//
//		if (recurso_existe_en_lista(lista_recursos, archivo->nombre_archivo) && archivo_existe_en_tabla(tabla_global_archivos_abiertos, archivo->nombre_archivo))
//		{
//			list_remove(proceso->tabla_archivos_abiertos,0);
//
//			verif_eliminar_recurso_file(proceso,archivo);
//		}
//	}

	while(list_size(proceso->tabla_archivos_abiertos) > 0){

		archivo_abierto_t* archivo = (archivo_abierto_t*) list_get(proceso->tabla_archivos_abiertos, 0);
		if (recurso_existe_en_lista(lista_recursos, archivo->nombre_archivo) && archivo_existe_en_tabla(tabla_global_archivos_abiertos, archivo->nombre_archivo))
		{

			archivo_abierto_t* archivo_abierto_pcb = buscar_archivo_abierto_t(proceso->tabla_archivos_abiertos, archivo->nombre_archivo);
			list_remove_element(proceso->tabla_archivos_abiertos,archivo_abierto_pcb);

			if(verif_eliminar_recurso_file(proceso,archivo_abierto_pcb) == 0){
				int instancias_recurso = obtener_instancias(lista_recursos, archivo->nombre_archivo);
				sumar_instancia(lista_recursos, archivo->nombre_archivo);
				liberar_proceso_de_bloqueados_si_necesario(archivo->nombre_archivo, instancias_recurso);
			}

		}
	}

	eliminar_tabla_segmentos(proceso);

	while(list_size(proceso->tabla_segmento->segmentos) > 0){
		segmento_t* segmento = list_remove(proceso->tabla_segmento->segmentos,0);
		free(segmento);
	}
	free(proceso->tabla_segmento->segmentos);
	list_remove_element(lista_tabla_segmentos->lista, proceso->tabla_segmento);
	free(proceso->tabla_segmento);
	solicitar_tabla_segmentos();


	list_destroy_and_destroy_elements(proceso->instrucciones, (void*) instrucciones_destroy);

	list_destroy(proceso->tabla_archivos_abiertos);

	free(proceso->recurso_bloqueante);
	devolver_instancias(proceso, lista_recursos);
	free(proceso->recursos_asignados);

	free(proceso->registros_cpu);
	free(proceso);
}

char* copiar_char_puntero(const char *param)
{
	char *string1 = malloc(sizeof(char) * 2);
	memcpy(string1, "0", (sizeof(char) * 2));

	string1 = realloc(string1, strlen(param) + 1);
	memcpy(string1, param, strlen(param) + 1);

	return string1;
}

void imprimir_recursos(pcb_t* pcb){
	for(int i=0; i<list_size(pcb->recursos_asignados); i++){
		t_recurso* recurso = list_get(pcb->recursos_asignados,i);

		log_info(logger,"PID: %d - Recurso: %s",pcb->pid, recurso->nombre_recurso);
	}
}
