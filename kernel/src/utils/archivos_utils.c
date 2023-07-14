#include "../../includes/utils.h"

void imprimir_tabla_archivos(){
	void imprimir_tabla(archivo_abierto_t* tabla){
		log_info(logger, "PID: %d - Nombre Archivo: %s - Puntero: %d", tabla->pid, tabla->nombre_archivo, tabla->posicion_puntero);
	}
	list_iterate(tabla_global_archivos_abiertos,(void*) imprimir_tabla);
}

// ___ Funciones de archivos ____

char* buscar_archivo(t_list *tabla_archivos_abiertos, const char *nombre_archivo)
{
	for (int i = 0; i < list_size(tabla_archivos_abiertos); i++)
	{
		char* archivo = (char*) list_get(tabla_archivos_abiertos, i);
		if (strcmp(archivo, nombre_archivo) == 0)
		{
			return archivo;
		}
	}
	return NULL;
}


bool archivo_existe_en_tabla(t_list *tabla_archivos_abiertos, const char *nombre_archivo)
{
	char *archivo = buscar_archivo(tabla_archivos_abiertos, nombre_archivo);
	return (archivo != NULL);
}


archivo_abierto_t* buscar_archivo_abierto_t (t_list *tabla_archivos_abiertos, const char *nombre_archivo)
{
	for (int i = 0; i < list_size(tabla_archivos_abiertos); i++)
	{
		archivo_abierto_t* archivo = (archivo_abierto_t*) list_get(tabla_archivos_abiertos, i);
		if (strcmp(archivo->nombre_archivo, nombre_archivo) == 0)
		{
			return archivo;
		}
	}
	return NULL;
}

void eliminar_archivo_abierto_t(t_list *tabla_archivos_abiertos, const char *nombre_archivo)
{
	bool buscar_archivo(void *archivo){
		char *archivo_actual = (char *) archivo;
		return strcmp(archivo_actual, nombre_archivo) == 0;
	}

	list_remove_by_condition(tabla_archivos_abiertos, buscar_archivo);
}
