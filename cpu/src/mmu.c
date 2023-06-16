#include "../includes/mmu.h"

void traducir_direccion(char *param, tabla_segmentos_t *tabla_segmentos)
{
	int direccion_fisica;

	int direccion_logica = atoi(param);
	int num_segmento = floor(direccion_logica / tam_max_segmento);
	int desplazamiento_segmento = direccion_logica % tam_max_segmento;
	int direccion_base_segmento = obtener_direccion_base(num_segmento, tabla_segmentos);
	//int direccion_limite_segmento = obtener_direccion_limite(num_segmento, tabla_segmentos);

	direccion_fisica = direccion_base_segmento + desplazamiento_segmento;

	log_info(logger, "Direccion fisica: %d", direccion_fisica);

	/*if (direccion_base_segmento + desplazamiento_segmento > direccion_limite_segmento)
	{
		log_info(logger, "SEG_FAULT");
	}*/

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
	segmento_t* segmento = buscar_segmento(num_segmento, tabla_segmentos->segmentos);

	if(segmento != NULL)
	{
		return segmento->direccion_base;
	}
	else
	{
		log_info(logger, "El numero de segmento no pertenece a la tabla de segmentos del proceso");
		return -1;
	}
}

/*int obtener_direccion_limite(int num_segmento, tabla_segmentos_t *tabla_segmentos)
{
}*/
