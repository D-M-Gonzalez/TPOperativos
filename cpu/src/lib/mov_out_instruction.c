#include "../../includes/code_reader.h"

int ejecutar_mov_out(t_contexto *contexto, t_instruc *instruccion)
{
	contexto->estado = MOV_OUT;
	contexto->param1_length = instruccion->param1_length;
	contexto->param1 = realloc(contexto->param1, contexto->param1_length);
	memcpy(contexto->param1, instruccion->param1, contexto->param1_length);

	contexto->param2_length = instruccion->param2_length;
	contexto->param2 = realloc(contexto->param2, contexto->param2_length);
	memcpy(contexto->param2, instruccion->param2, contexto->param2_length);

	t_instruc_mem *instruccion_memoria = inicializar_instruc_mem();
	copiar_instruccion_mem(instruccion_memoria, contexto);

	log_info(logger, "Ejecutando [MOV_OUT] - [%s , %s]", instruccion->param1, instruccion->param2);

	serializar_instruccion_memoria(memoria_connection, instruccion_memoria);

	return 0;
}