#include "../../includes/utils.h"

t_instruc_file* inicializar_instruc_file()
{
	t_instruc_file* instruccion = malloc(sizeof(t_instruc_file));
	instruccion->pid=0;
	instruccion->param1 = malloc(sizeof(char) * 2);
	memcpy(instruccion->param1, "0", (sizeof(char) * 2));
	instruccion->param1_length = sizeof(char) * 2;
	instruccion->param2 = malloc(sizeof(char) * 2);
	memcpy(instruccion->param2, "0", (sizeof(char) * 2));
	instruccion->param2_length = sizeof(char) * 2;
	instruccion->param3 = malloc(sizeof(char) * 2);
	memcpy(instruccion->param3, "0", (sizeof(char) * 2));
	instruccion->param3_length = sizeof(char) * 2;
	instruccion->param4 = 0;
	instruccion->estado = F_OPEN;

	return instruccion;
}

t_instruc_mem* inicializar_instruc_mem()
{
	t_instruc_mem* instruccion = malloc(sizeof(t_instruc_mem));
	instruccion->pid=0;
	instruccion->param1 = malloc(sizeof(char) * 2);
	memcpy(instruccion->param1, "0", (sizeof(char) * 2));
	instruccion->param1_length = sizeof(char) * 2;
	instruccion->param2 = malloc(sizeof(char) * 2);
	memcpy(instruccion->param2, "0", (sizeof(char) * 2));
	instruccion->param2_length = sizeof(char) * 2;
	instruccion->param3 = malloc(sizeof(char) * 2);
	memcpy(instruccion->param3, "0", (sizeof(char) * 2));
	instruccion->param3_length = sizeof(char) * 2;
	instruccion->estado = CREATE_SEGMENT;

	return instruccion;
}

t_list* copiar_lista_instrucciones(t_list *nueva_lista, t_list *lista_instrucciones)
{
	int lineas = list_size(lista_instrucciones);

	for (int i = 0; i < lineas; i++)
	{
		t_instruc *instrucciones = list_get(lista_instrucciones, i);
		t_instruc *nueva_instruccion = malloc(sizeof(t_instruc));

		memcpy(&nueva_instruccion->nro, &instrucciones->nro, sizeof(uint32_t));

		memcpy(&nueva_instruccion->instruct_length, &instrucciones->instruct_length, sizeof(uint32_t));

		nueva_instruccion->instruct = malloc(instrucciones->instruct_length);
		memcpy(nueva_instruccion->instruct, instrucciones->instruct, instrucciones->instruct_length);

		memcpy(&nueva_instruccion->param1_length, &instrucciones->param1_length, sizeof(uint32_t));

		nueva_instruccion->param1 = malloc(instrucciones->param1_length);
		memcpy(nueva_instruccion->param1, instrucciones->param1, instrucciones->param1_length);

		memcpy(&nueva_instruccion->param2_length, &instrucciones->param2_length, sizeof(uint32_t));

		nueva_instruccion->param2 = malloc(instrucciones->param2_length);
		memcpy(nueva_instruccion->param2, instrucciones->param2, instrucciones->param2_length);

		memcpy(&nueva_instruccion->param3_length, &instrucciones->param3_length, sizeof(uint32_t));

		nueva_instruccion->param3 = malloc(instrucciones->param3_length);
		memcpy(nueva_instruccion->param3, instrucciones->param3, instrucciones->param3_length);

		list_add(nueva_lista, nueva_instruccion);
	}

	return nueva_lista;
}

void copiar_instruccion_mem(t_instruc_mem* instruccion, t_contexto* contexto){

	instruccion->param1_length = contexto->param1_length;
	instruccion->param2_length = contexto->param2_length;
	instruccion->param3_length = contexto->param3_length;
	instruccion->estado = contexto->estado;
	instruccion->pid = contexto->pid;

	instruccion->param1 = realloc(instruccion->param1,instruccion->param1_length);
	instruccion->param2 = realloc(instruccion->param2,instruccion->param2_length);
	instruccion->param3 = realloc(instruccion->param3,instruccion->param3_length);

	memcpy(instruccion->param1,contexto->param1,instruccion->param1_length);
	memcpy(instruccion->param2,contexto->param2,instruccion->param2_length);
	memcpy(instruccion->param3,contexto->param3,instruccion->param3_length);

}

void instrucciones_destroy(t_instruc *instruccion)
{
	free(instruccion->instruct);
	free(instruccion->param1);
	free(instruccion->param2);
	free(instruccion->param3);
	free(instruccion);
}



void destruir_instruc_mem(t_instruc_mem* instruccion){
	free(instruccion->param1);
	free(instruccion->param2);
	free(instruccion->param3);
	free(instruccion);
}

void destruir_instruc_file(t_instruc_file* instruccion){
	free(instruccion->param1);
	free(instruccion->param2);
	free(instruccion->param3);
	free(instruccion);
}
