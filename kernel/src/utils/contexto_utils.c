#include "../../includes/utils.h"

t_contexto* inicializar_contexto()
{
	t_contexto *contexto = malloc(sizeof(t_contexto));
	contexto->instrucciones = list_create();
	contexto->registros = inicializar_registros();
	contexto->param1 = malloc(sizeof(char) * 2);
	memcpy(contexto->param1, "0", (sizeof(char) * 2));
	contexto->param1_length = sizeof(char) * 2;
	contexto->param2 = malloc(sizeof(char) * 2);
	memcpy(contexto->param2, "0", (sizeof(char) * 2));
	contexto->param2_length = sizeof(char) * 2;
	contexto->param3 = malloc(sizeof(char) * 2);
	memcpy(contexto->param3, "0", (sizeof(char) * 2));
	contexto->param3_length = sizeof(char) * 2;
	contexto->estado = EXIT;
	contexto->pid = 0;

	contexto->tabla_segmento = malloc(sizeof(tabla_segmentos_t));
	contexto->tabla_segmento->pid = 0;
	contexto->tabla_segmento->segmentos = list_create();

	return contexto;
}

void destruir_contexto(t_contexto* contexto){
	list_destroy_and_destroy_elements(contexto->instrucciones, (void*) instrucciones_destroy);
	list_destroy_and_destroy_elements(contexto->tabla_segmento->segmentos, free);
	free(contexto->tabla_segmento);
	free(contexto->param1);
	free(contexto->param2);
	free(contexto->param3);
	free(contexto->registros);
	free(contexto);
}

void duplicar_contexto(t_contexto* contexto_destino, t_contexto* contexto_origen){
	contexto_destino->param1_length = contexto_origen->param1_length;
	contexto_destino->param2_length = contexto_origen->param2_length;
	contexto_destino->param3_length = contexto_origen->param3_length;
	contexto_destino->estado = contexto_origen->estado;
	contexto_destino->pid = contexto_origen->pid;

	contexto_destino->param1 = realloc(contexto_destino->param1,contexto_origen->param1_length);
	contexto_destino->param2 = realloc(contexto_destino->param2,contexto_origen->param2_length);
	contexto_destino->param3 = realloc(contexto_destino->param3,contexto_origen->param3_length);

	memcpy(contexto_destino->param1,contexto_origen->param1,contexto_destino->param1_length);
	memcpy(contexto_destino->param2,contexto_origen->param2,contexto_destino->param2_length);
	memcpy(contexto_destino->param3,contexto_origen->param3,contexto_destino->param3_length);

	copiar_registros(contexto_destino->registros, contexto_origen->registros);
	copiar_lista_instrucciones(contexto_destino->instrucciones,contexto_origen->instrucciones);

	duplicar_tabla_segmentos(contexto_origen->tabla_segmento,contexto_destino->tabla_segmento);
}
