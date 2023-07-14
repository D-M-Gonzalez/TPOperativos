#include "../../includes/utils.h"

void copiar_tabla_segmentos(tabla_segmentos_t* tabla_contexto,tabla_segmentos_t* tabla_pcb){
	uint32_t size = list_size(tabla_pcb->segmentos);
	tabla_contexto->pid = tabla_pcb->pid;

	for(int i = 0; i<size; i++){
		segmento_t* segmento = list_get(tabla_pcb->segmentos,i);
		segmento_t* nuevo_segmento = malloc(sizeof(segmento_t));

		nuevo_segmento->direccion_base = segmento->direccion_base;
		nuevo_segmento->ids = segmento->ids;
		nuevo_segmento->tamanio = segmento->tamanio;

		list_add(tabla_contexto->segmentos,nuevo_segmento);
	}
}

void imprimir_segmentos(segmento_t* segmento){
	log_info(logger,"Segmento %d, base %d, tamanio %d",segmento->ids,segmento->direccion_base,segmento->tamanio);
}


void duplicar_tabla_segmentos(tabla_segmentos_t* tabla_origen, tabla_segmentos_t* tabla_destino){
	void duplicar(segmento_t* segmento){
		segmento_t* nuevo_segmento = malloc(sizeof(segmento_t));

		nuevo_segmento->direccion_base = segmento->direccion_base;
		nuevo_segmento->ids = segmento->ids;
		nuevo_segmento->tamanio = segmento->tamanio;

		list_add(tabla_destino->segmentos,nuevo_segmento);
	}
	list_iterate(tabla_origen->segmentos, (void*) duplicar);
	tabla_destino->pid = tabla_origen->pid;
}

bool existe_tabla_segmentos(t_list* lista_tablas, int pid){
	bool encontrado = false;
	int size = list_size(lista_tablas);

	for(int i=0; i<size; i++){
		tabla_segmentos_t* tabla = list_get(lista_tablas,i);

		if((encontrado = tabla->pid == pid)) break;
	}

	return encontrado;
}

tabla_segmentos_t* solicitar_segmento_0(int pid){
	t_instruc_mem* instruccion = inicializar_instruc_mem();
	instruccion->estado = ALLOCATE_SEGMENT;
	instruccion->pid = pid;

	serializar_instruccion_memoria(memoria_connection, instruccion);

	solicitar_tabla_segmentos();

	tabla_segmentos_t* tabla = buscar_tabla_segmentos(lista_tabla_segmentos->lista,pid);

	destruir_instruc_mem(instruccion);

	return tabla;
}

void imprimir_tabla_segmentos(){
	void imprimir_tabla(tabla_segmentos_t* tabla){
		void imprimir_segmentos(segmento_t* segmento){
			log_info(logger,"PID: %d - Segmento: %d - Base: %d - Tamanio: %d",tabla->pid,segmento->ids,segmento->direccion_base,segmento->tamanio);
		}
		list_iterate(tabla->segmentos, (void*) imprimir_segmentos);
	}
	list_iterate(lista_tabla_segmentos->lista,(void*) imprimir_tabla);
}

tabla_segmentos_t* buscar_tabla_segmentos(t_list* lista_tablas, int pid){
	bool buscar_tabla(tabla_segmentos_t* tabla){
		return tabla->pid == pid;
	}

	tabla_segmentos_t* tabla_encontrada = list_find(lista_tablas,(void*)buscar_tabla);

	return tabla_encontrada;
}

void eliminar_tabla_segmentos(pcb_t* proceso){
	t_contexto* contexto_eliminar = inicializar_contexto();

	contexto_eliminar->estado = DELETE_TABLE;
	contexto_eliminar->pid = proceso->pid;
	//La peticion de eliminacion se hace directamente a memoria
	delete_segment(contexto_eliminar,proceso);

	destruir_contexto(contexto_eliminar);
}
