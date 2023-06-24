#include "../../../includes/code_reader.h"
#include "../../../includes/mmu.h"

int ejecutar_mov_in(t_contexto *contexto, t_instruc *instruccion)
{
	int exit_status = 0;

	contexto->estado = MOV_IN;
	contexto->param1_length = instruccion->param1_length;
	contexto->param1 = realloc(contexto->param1, contexto->param1_length);
	memcpy(contexto->param1, instruccion->param1, contexto->param1_length);

	contexto->param2_length = instruccion->param2_length;
	contexto->param2 = realloc(contexto->param2, contexto->param2_length);
	memcpy(contexto->param2, instruccion->param2, contexto->param2_length);

	log_info(logger, "Ejecutando [MOV_IN]");
	exit_status = traducir_direccion(contexto->param2, contexto);

	if(exit_status != 0) return exit_status;

	t_instruc_mem *instruccion_memoria = inicializar_instruc_mem();
	copiar_instruccion_mem(instruccion_memoria, contexto);

	serializar_instruccion_memoria(memoria_connection, instruccion_memoria);

	char *valor = esperar_valor(memoria_connection);

	asignar_valor_registro(seleccionar_registro(contexto->param1), valor);

	log_info(logger, "Accion: [MOV_IN] - Valor: %s - Registro: %s", seleccionar_registro(contexto->param1), contexto->param1);

	return exit_status;
}

void asignar_valor_registro(char* registro, char* valor)
{
	int length_registro = strlen(registro);

	for (int i = 0; i < length_registro; i++)
	{
		registro[i] = valor[i];
	}
}
