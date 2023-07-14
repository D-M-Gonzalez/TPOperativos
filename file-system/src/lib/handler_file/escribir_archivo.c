#include "../../../includes/handler_file.h"

void escribir_dato(void* dato, int offset, int size){
	memcpy(memoria_file_system + offset,dato, size);
	msync(memoria_file_system,tam_memoria_file_system,MS_SYNC);
	sleep(retardo_acceso_bloque);
}

void escribir_int(uint32_t dato,int offset){
	memcpy(memoria_file_system + offset, &dato, 4);
	msync(memoria_file_system,tam_memoria_file_system,MS_SYNC);
	sleep(retardo_acceso_bloque);
}

//no usar no tiene retardo
void _escribir_int(uint32_t dato, int offset){
	memcpy(memoria_file_system + offset, &dato, 4);
	msync(memoria_file_system,tam_memoria_file_system,MS_SYNC);
}

void escribir_bloques_indirectos(t_list* lista_bloques, int indice_inicial, int offset_indirecto){
	int size = list_size(lista_bloques);

	if(size < 2){
		log_error(logger,"No puede haber menos de 2 bloques para escribir indirectos");
		return;
	}

	for (int i = indice_inicial; i < size; i++)
	{
		offset_fcb_t *bloque = list_get(lista_bloques, i);

		int offset = ((i - 2) * sizeof(uint32_t)) + offset_indirecto;

		_escribir_int(bloque->id_bloque, offset);
	}
	sleep(retardo_acceso_bloque);
}

void escribir_datos(void* datos, t_list* lista_offsets){
	int cant_bloques = list_size(lista_offsets);
	int offset = 0;

	for(int i = 0; i<cant_bloques; i++){
		offset_fcb_t* bloque = list_get(lista_offsets,i);
		log_info(logger,"ACCESO A BLOQUE - ID Bloque: %d", bloque->id_bloque);
		escribir_dato(datos + offset, bloque->offset, bloque->tamanio);
		offset += bloque->tamanio;
	}
}
