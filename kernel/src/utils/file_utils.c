#include "../../includes/file_utils.h"

int verif_crear_recurso_file(archivo_abierto_t* archivo){
	sem_wait(&sem_tabla_archivos);
	int result = 0;

	if(!archivo_existe_en_tabla(tabla_global_archivos_abiertos, archivo->nombre_archivo)){

		crear_recurso_file(archivo);
		result = 1;
	}
	sem_post(&sem_tabla_archivos);

	return result;
}

void crear_recurso_file(archivo_abierto_t* archivo){
	list_add(tabla_global_archivos_abiertos, archivo->nombre_archivo);

	int recurso_length = strlen(archivo->nombre_archivo) + 1;
	t_recurso *recurso = malloc(sizeof(t_recurso));
	recurso->id = list_size(lista_recursos->lista);
	recurso->nombre_recurso = malloc(recurso_length);
	memcpy(recurso->nombre_recurso,archivo->nombre_archivo,recurso_length);
	recurso->instancias = 1;
	pthread_mutex_init(&(recurso->mutex_instancias), NULL);
	recurso->cola_bloqueados = init_list_mutex();
	list_add(lista_recursos->lista, recurso);
}

int verif_eliminar_recurso_file(pcb_t *proceso, archivo_abierto_t* archivo){
	sem_wait(&sem_tabla_archivos);
	int result = 0;

	int instancias_recurso = obtener_instancias(lista_recursos, archivo->nombre_archivo);
	t_recurso *recurso_a_eliminar = buscar_recurso(lista_recursos, archivo->nombre_archivo);
	if(instancias_recurso == 1 && list_size(recurso_a_eliminar->cola_bloqueados->lista) == 0){
		for(int i = 0; i<list_size(proceso->recursos_asignados) ; i++){
			t_recurso* recurso = list_get(proceso->recursos_asignados,i);
			if(strcmp(recurso->nombre_recurso,archivo->nombre_archivo) == 0) list_remove(proceso->recursos_asignados,i);
		}
		eliminar_recurso_file(archivo,recurso_a_eliminar);
		result = 1;
	}

	sem_post(&sem_tabla_archivos);

	return result;
}

void eliminar_recurso_file(archivo_abierto_t* archivo, t_recurso* recurso_a_eliminar){
	eliminar_archivo_abierto_t(tabla_global_archivos_abiertos, archivo->nombre_archivo);
	list_mutex_destroy(recurso_a_eliminar->cola_bloqueados);
	pthread_mutex_destroy(&(recurso_a_eliminar->mutex_instancias));
	list_remove_element(lista_recursos->lista, recurso_a_eliminar);
	free(archivo->nombre_archivo);
	free(archivo);
	free(recurso_a_eliminar->nombre_recurso);
	free(recurso_a_eliminar);
}
