#include "../../../includes/code_reader.h"
#include "../../../includes/mmu.h"

int ejecutar_mov_in(t_contexto *contexto, t_instruc *instruccion)
{
	t_instruc_mov *instruccion_movimiento = inicializar_instruc_mov();
	instruccion_movimiento->pid = contexto->pid;
	char *registro = seleccionar_registro(instruccion->param1);
	char* placeholder = "0";
	uint32_t tamanio = strlen(registro);

	int dir_fisica = traducir_direccion(instruccion->param2, contexto, tamanio);

	if(dir_fisica < 0) return 1;

	generar_instruccion_mov(instruccion_movimiento,MOV_IN,dir_fisica,tamanio,placeholder);

	serializar_instruccion_mov(memoria_connection, instruccion_movimiento);

	void* valor = esperar_valor(memoria_connection);

	asignar_valor_registro(seleccionar_registro(instruccion->param1), valor, tamanio);

	int direccion_logica = atoi(instruccion->param2);

	int num_segmento = floor(direccion_logica / tam_max_segmento);

	log_info(logger,"PID: %d - Accion: ESCRIBIR - Segmento: %d - Dirección Física: %d - Valor: %s ", contexto->pid, num_segmento, dir_fisica, seleccionar_registro(instruccion->param1));

	int largo1 = strlen(instruccion->param1);
	int largo2 = strlen(instruccion->param2);
	char* params = malloc(largo1 + largo2 + 2);
	memcpy(params,instruccion->param1,largo1);
	memcpy(params + largo1, " ", 1);
	memcpy(params + largo1 + 1, instruccion->param2, largo2);
	memcpy(params + largo1 + largo2 + 1, "", 1);

	free(valor);
	free(params);

	destroy_instruc_mov(instruccion_movimiento);

	ip++;

	return 0;
}
