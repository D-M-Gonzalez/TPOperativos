#include "../includes/mmu.h"

void traducir_direccion(char *param, tabla_segmentos_t *tabla_segmentos)
{
	int direccion_fisica;

	int direccion_logica = atoi(param);
	int num_segmento = floor(direccion_logica / tam_max_segmento);
	int desplazamiento_segmento = direccion_logica % tam_max_segmento;
	int direccion_base_segmento = obtener_direccion_base(num_segmento, tabla_segmentos);

	direccion_fisica = direccion_base_segmento + desplazamiento_segmento;

	log_info(logger, "Direccion fisica: %d", direccion_fisica);

	//if(desplazamiento_segmento + tamanio_direccion > tamanio_segmento) segmentation fault

}

int obtener_direccion_base(int num_segmento, tabla_segmentos_t *tabla_segmentos)
{
	int direccion_base = -1;
	t_list *segmentos = tabla_segmentos->segmentos;

	for (int i = 0; i < list_size(segmentos); i++)
	{
		segmento_t *segmento = (segmento_t*) list_get(segmentos, i);

		if (segmento->ids == num_segmento)
		{
			direccion_base = segmento->direccion_base;
			break;
		}
	}

	if(direccion_base == -1)
	{
		log_info(logger, "El numero de segmento no pertenece a la tabla de segmentos del proceso");
	}

	return direccion_base;
}
