#include "../../../includes/code_reader.h"

int ejecutar_create_segment(t_contexto *contexto, t_instruc *instruccion)
{
	if (validar_tam_segmento(atoi(instruccion->param2)))
	{
		return ejecutar_syscall(contexto, instruccion, CREATE_SEGMENT, 2);
	}
	else
	{
		log_error(logger, "PID: %d - Error SEG_FAULT - Segmento: %s - Tamanio invalido: %s",
				contexto->pid, instruccion->param1, instruccion->param2);
		contexto_estado = ERROR_SEG_FAULT;
		return -1;
	}
}
