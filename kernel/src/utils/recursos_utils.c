#include "../../includes/utils.h"

char* crear_recurso(const char *param)
{
	char *string1 = malloc(sizeof(char) * 2);
	memcpy(string1, "0", (sizeof(char) * 2));

	string1 = realloc(string1, strlen(param) + 1);
	memcpy(string1, param, strlen(param) + 1);

	return string1;
}

// void borrar_recurso(const char* param)

t_recurso* buscar_recurso(t_lista_mutex *lista_recursos, const char *nombre_recurso)
{
	for (int i = 0; i < list_mutex_size(lista_recursos); i++)
	{
		t_recurso *recurso = (t_recurso*) list_mutex_get(lista_recursos, i);
		if (strcmp(recurso->nombre_recurso, nombre_recurso) == 0)
		{
			return recurso;
		}
	}
	return NULL;
}

bool recurso_existe_en_lista(t_lista_mutex *lista_recursos, const char *nombre_recurso)
{
	t_recurso *recurso = buscar_recurso(lista_recursos, nombre_recurso);
	return (recurso != NULL);
}

void restar_instancia(t_lista_mutex *lista_recursos, const char *nombre_recurso)
{
	t_recurso *recurso = buscar_recurso(lista_recursos, nombre_recurso);
	pthread_mutex_lock(&(recurso->mutex_instancias));
	recurso->instancias--;
	pthread_mutex_unlock(&(recurso->mutex_instancias));
}

void sumar_instancia(t_lista_mutex *lista_recursos, const char *nombre_recurso)
{
	t_recurso *recurso = buscar_recurso(lista_recursos, nombre_recurso);
	pthread_mutex_lock(&(recurso->mutex_instancias));
	recurso->instancias++;
	pthread_mutex_unlock(&(recurso->mutex_instancias));
}

int obtener_instancias(t_lista_mutex *lista_recursos, const char *nombre_recurso)
{
	t_recurso *recurso = buscar_recurso(lista_recursos, nombre_recurso);
	return recurso->instancias;
}

void asignar_recurso(pcb_t *pcb, const char *nombre_recurso)
{
	t_recurso *recurso_asignado = buscar_recurso(lista_recursos, nombre_recurso);
	list_add(pcb->recursos_asignados, recurso_asignado);
}

void desasignar_recurso_si_lo_tiene_asignado(pcb_t *pcb, const char *nombre_recurso)
{
	for(int i = 0; i<list_size(pcb->recursos_asignados); i++){
		t_recurso* recurso = list_get(pcb->recursos_asignados,i);

		if(strcmp(recurso->nombre_recurso, nombre_recurso) == 0){
			list_remove(pcb->recursos_asignados,i);
			i--;
		}
	}
}

void devolver_instancias(pcb_t *pcb, t_lista_mutex *lista_recursos)
{
	if (!list_is_empty(pcb->recursos_asignados))
	{
		while(list_size(pcb->recursos_asignados)>0)
		{
			t_recurso *recurso_asignado = list_remove(pcb->recursos_asignados, 0);
			log_info(logger,"Liberacion PID: %d - Recurso: %s", pcb->pid, recurso_asignado->nombre_recurso);
			int instancias_recurso = obtener_instancias(lista_recursos, recurso_asignado->nombre_recurso);
			sumar_instancia(lista_recursos, recurso_asignado->nombre_recurso);

			liberar_proceso_de_bloqueados_si_necesario(recurso_asignado->nombre_recurso, instancias_recurso);

			log_info(logger, "PID: %d - Libera recurso: %s - Instancias: %d", pcb->pid, recurso_asignado->nombre_recurso, recurso_asignado->instancias);
		}
	}
}

void liberar_proceso_de_bloqueados_si_necesario(const char *recurso, int instancias_recurso)
{
	if (instancias_recurso < 0)
	{
		t_recurso *recurso_bloqueante = buscar_recurso(lista_recursos, recurso);
		pcb_t *pcb_desbloqueado = list_pop(recurso_bloqueante->cola_bloqueados);
		desasignar_recurso_si_lo_tiene_asignado(pcb_desbloqueado, recurso_bloqueante->nombre_recurso);
		list_push(pcb_ready_list, pcb_desbloqueado);
		pcb_desbloqueado->tiempo_espera_en_ready = temporal_create();
		log_info(logger, "PID: %d - Estado Anterior: PCB_BLOCK - Estado Actual: PCB_READY", pcb_desbloqueado->pid);
		sem_post(&sem_estado_ready);
	}

}
