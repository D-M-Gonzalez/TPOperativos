#include "../../../includes/code_reader.h"

int ejecutar_mov_out(t_contexto *contexto, t_instruc *instruccion)
{
	int exit_status = 0;

	t_instruc_mov *instruccion_movimiento = inicializar_instruc_mov();
	instruccion_movimiento->pid = contexto->pid;
	char *registro = seleccionar_registro(instruccion->param2);
	uint32_t tamanio = strlen(registro);

	int dir_fisica = traducir_direccion(instruccion->param1, contexto, tamanio);

	if(dir_fisica < 0) return 1;

	generar_instruccion_mov(instruccion_movimiento,MOV_OUT,dir_fisica,tamanio,registro);

	serializar_instruccion_mov(memoria_connection, instruccion_movimiento);

	char* valor = esperar_valor(memoria_connection);

	destroy_instruc_mov(instruccion_movimiento);

	int direccion_logica = atoi(instruccion->param2);

	int num_segmento = floor(direccion_logica / tam_max_segmento);

	log_info(logger,"PID: %d - Accion: LEER - Segmento: %d - Dirección Física: %d - Valor: %s ", contexto->pid, num_segmento, dir_fisica, valor);

	int largo1 = strlen(instruccion->param1);
	int largo2 = strlen(instruccion->param2);
	char* params = malloc(largo1 + largo2 + 1);
	memcpy(params,instruccion->param1,largo1);
	memcpy(params + largo1, instruccion->param2, largo2);
	memcpy(params + largo1 + largo2, "", 1);
	log_instruccion(contexto->pid,"MOV OUT",params);

	ip++;
	free(params);
	free(valor);

	return exit_status;
}
