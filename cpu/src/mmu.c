#include "../includes/mmu.h"

int traducir_direccion(char* direccion, t_contexto *contexto, uint32_t largo)
{
	int direccion_fisica;
	int direccion_logica = atoi(direccion);

	int num_segmento = floor(direccion_logica / tam_max_segmento);
	int desplazamiento_segmento = direccion_logica % tam_max_segmento;
	int direccion_base_segmento = obtener_direccion_base(num_segmento, contexto->tabla_segmento);
	int tamanio_segmento = obtener_tamanio_segmento(num_segmento, contexto->tabla_segmento);

	if (direccion_base_segmento == -1 || tamanio_segmento == -1 || desplazamiento_segmento + largo > tamanio_segmento){
		log_error(logger, "PID: %d - Error SEG_FAULT - Segmento: %d - Offset: %d - Tamaño: %d",
				contexto->pid, num_segmento, desplazamiento_segmento, tamanio_segmento);
		contexto_estado = ERROR_SEG_FAULT;
		return -1;
	}

	direccion_fisica = direccion_base_segmento + desplazamiento_segmento;

	return direccion_fisica;
}

bool validar_tam_segmento(int tam_segmento)
{
	return tam_segmento <= tam_max_segmento;
}

segmento_t* buscar_segmento(int num_segmento, t_list *segmentos)
{
	for (int i = 0; i < list_size(segmentos); i++)
	{
		segmento_t *segmento = (segmento_t*) list_get(segmentos, i);

		if (segmento->ids == num_segmento)
		{
			return segmento;
		}
	}

	return NULL;
}

int obtener_direccion_base(int num_segmento, tabla_segmentos_t *tabla_segmentos)
{
	segmento_t *segmento = buscar_segmento(num_segmento, tabla_segmentos->segmentos);

	if (segmento != NULL)
	{
		return segmento->direccion_base;
	}
	else
	{
		return -1;
	}
}

int obtener_tamanio_segmento(int num_segmento, tabla_segmentos_t *tabla_segmentos)
{
	segmento_t *segmento = buscar_segmento(num_segmento, tabla_segmentos->segmentos);

	if (segmento != NULL)
	{
		return segmento->tamanio;
	}
	else
	{
		return -1;
	}
}
