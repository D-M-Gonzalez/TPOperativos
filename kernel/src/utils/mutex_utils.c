#include "../../includes/utils.h"

void list_push(t_lista_mutex *list, void *info)
{
	pthread_mutex_lock(&(list->mutex));
	list_add(list->lista, info);
	pthread_mutex_unlock(&(list->mutex));
}

void* list_pop(t_lista_mutex *list)
{
	pthread_mutex_lock(&(list->mutex));
	void *info = list_remove(list->lista, 0);
	pthread_mutex_unlock(&(list->mutex));
	return info;
}

void list_mutex_destroy(t_lista_mutex *list)
{
	list_destroy(list->lista);
	pthread_mutex_destroy(&(list->mutex));
	free(list);
}

bool list_mutex_is_empty(t_lista_mutex *list)
{
	pthread_mutex_lock(&(list->mutex));
	bool is_empty = list_is_empty(list->lista);
	pthread_mutex_unlock(&(list->mutex));
	return is_empty;
}

int list_mutex_size(t_lista_mutex *list)
{
	pthread_mutex_lock(&(list->mutex));
	int size = list_size(list->lista);
	pthread_mutex_unlock(&(list->mutex));
	return size;
}

void* list_mutex_get(t_lista_mutex *list, int index)
{
	pthread_mutex_lock(&(list->mutex));
	void *element = list_get(list->lista, index);
	pthread_mutex_unlock(&(list->mutex));
	return element;
}
