#include "../../includes/utils.h"

t_config* iniciar_config(char * path_config)
{
	t_config* nuevo_config;
	if((nuevo_config = config_create(path_config))==NULL){
		printf("No pude leer la config \n");
		exit(2);
	}
	return nuevo_config;
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("memoria.log", "MEMORIA", 1, LOG_LEVEL_DEBUG);

	return nuevo_logger;
}

void imprimir_datos(void* memoria, int tam_memoria){
	int offset = tam_memoria * 2;
	int lineas = floor((double)tam_memoria / tam_linea);
	int b = 0;
	int c = 0;

	char string[tam_memoria * 2 + lineas + 1];
	char nueva_linea = '\n';
	char final = '\0';

	for(int i = 0; i<(offset + lineas); i++){
		if((c % tam_linea) == 0 && c != 0){
			memcpy(string + i,&nueva_linea, sizeof(char));
			c=0;
			continue;
		}
		char byte_new;
		memcpy(&byte_new, memoria + b, 1);
		char* character = malloc(2);
		sprintf(character,"%02hhX",byte_new);
		memcpy(string + i,character, sizeof(char));
		i++;
		memcpy(string + i,character + 1, sizeof(char));
		free(character);
		b++;
		c++;
	}
	memcpy(string + (offset + lineas),&final, sizeof(char));
	printf("\e[1;1H\e[2J");
	printf("%s",string);
}
