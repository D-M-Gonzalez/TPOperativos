#include "../../includes/utils.h"

t_config* iniciar_config(char *path_config)
{
	t_config *nuevo_config;
	if ((nuevo_config = config_create(path_config)) == NULL)
	{
		printf("No pude leer la config \n");
		exit(2);
	}
	return nuevo_config;
}

t_log* iniciar_logger(void)
{
	t_log *nuevo_logger = log_create("kernel.log", "KERNEL", 1, LOG_LEVEL_DEBUG);

	return nuevo_logger;
}

t_lista_mutex* init_list_mutex()
{
	t_lista_mutex *list = malloc(sizeof(t_lista_mutex));

	list->lista = list_create();
	pthread_mutex_init(&(list->mutex), NULL);
	return list;
}
