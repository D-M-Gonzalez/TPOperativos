#include "../includes/mmu.h"

void traducir_direccion(char *param, int pid)
{
	int direccion_logica = atoi(param);
	int num_segmento = floor(direccion_logica / tam_max_segmento);
	int desplazamiento_segmento = direccion_logica % tam_max_segmento;

	int direccion_base_segmento = obtener_direccion_base(num_segmento, pid);

	//log_info(logger, "Direccion fisica, %d", direccion_fisica);
}

int obtener_direccion_base(int num_segmento, int pid)
{
	int direccion_base;

	tabla_segmentos_t *tabla_segmentos = obtener_tabla(pid);
	t_list *segmentos = tabla_segmentos->segmentos;

	for (int i = 0; i < list_size(segmentos); i++)
	{
		segmento_t *segmento = (segmento_t*)list_get(segmentos, i);

		if (segmento->ids == num_segmento)
		{
			direccion_base = segmento->direccion_base;
			break;
		}
	}

	return direccion_base;
}

tabla_segmentos_t* obtener_tabla(int pid)
{
	t_list *lista_de_tablas = obtener_lista_de_tablas(); //obtener lista_de_tablas de memoria

	for (int i = 0; i < list_size(lista_de_tablas); i++)
	{
		tabla_segmentos_t *tabla = (tabla_segmentos_t*) list_get(lista_de_tablas, i);
		if (tabla->pid - pid == 0)
		{
			return tabla;
		}
	}
	return NULL;
}
