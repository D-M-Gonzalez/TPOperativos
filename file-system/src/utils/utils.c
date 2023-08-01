#include "../../includes/utils.h"

t_config* iniciar_config(char * path_config)
{
	t_config* nuevo_config;
	if((nuevo_config = config_create(path_config))==NULL){
		printf("No pude leer la config \n");
		exit(2);
	}
	return nuevo_config;
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("file-system.log", "FILE-SYSTEM", 1, LOG_LEVEL_DEBUG);

	return nuevo_logger;
}

void inicializar_datos_memoria(){
	int offset = tam_memoria_file_system;
	char caracter = '\0';

	for(int i = 0; i<offset; i++){
		memcpy(memoria_file_system + i,&caracter, sizeof(char));
	}

}

t_list* armar_lista_offsets(int id_fcb, int tam_a_leer, int p_seek){
	t_list* lista_offsets = list_create();

	int bloque_apuntado = ceil((double)(p_seek + 1) / tamanio_de_bloque);
	int nro_bloque = 0;
	t_list* lista_bloques = obtener_lista_de_bloques(id_fcb,p_seek,tam_a_leer);
	int cant_bloques = list_size(lista_bloques);

	while(nro_bloque < cant_bloques){
		offset_fcb_t* nuevo_offset = malloc(sizeof(offset_fcb_t));
		offset_fcb_t* bloque = list_get(lista_bloques, nro_bloque);

		nuevo_offset->offset = bloque->id_bloque * tamanio_de_bloque;
		nuevo_offset->id_bloque = bloque->id_bloque;
		nuevo_offset->tamanio = tamanio_de_bloque;

		if(tam_a_leer < tamanio_de_bloque){
			nuevo_offset->offset = nuevo_offset->offset + (p_seek - ((bloque_apuntado - 1) * tamanio_de_bloque));
			nuevo_offset->tamanio = tam_a_leer;
		} else if (nro_bloque + 1 == cant_bloques){
			nuevo_offset->tamanio = (p_seek + tam_a_leer) - ((bloque_apuntado - 1) * tamanio_de_bloque);
		} else if(nro_bloque == 0){
			nuevo_offset->offset = nuevo_offset->offset + (p_seek - ((bloque_apuntado - 1) * tamanio_de_bloque));
			nuevo_offset->tamanio = (bloque_apuntado * tamanio_de_bloque) - p_seek;
		}

		nro_bloque++;
		bloque_apuntado = ceil(((double)(p_seek + 1) + (tamanio_de_bloque * nro_bloque)) / tamanio_de_bloque);

		list_add(lista_offsets,nuevo_offset);
	}

	list_destroy_and_destroy_elements(lista_bloques,free);

	return lista_offsets;
}

void* list_pop(t_list* list)
{
	int last_element_index = (list->elements_count - 1);
	return list_remove(list, last_element_index);
}
