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
/*
void imprimir_datos(void* memoria, int tam_memoria){
	int offset = tam_memoria;
	int lineas = tam_memoria / tam_linea;
	int espacios = (ceil((double)tam_linea / tam_columna) - 1) * lineas;
	int b = 0;
	int c = 0;
	int linea = 0;
	int columna = 0;

	char string[tam_memoria + lineas * 4 + espacios + 1];
	char nueva_linea = '\n';
	char fin_linea = ':';
	char espacio = ' ';
	char final = '\0';

	int init = 0;
	char* numero_linea = string_itoa(linea);
	memcpy(string + init,&nueva_linea, sizeof(char));
	init++;
	memcpy(string + init,numero_linea, sizeof(char));
	init++;
	memcpy(string + init,&fin_linea, sizeof(char));
	init++;
	memcpy(string + init,&espacio, sizeof(char));
	init++;
	linea++;
	free(numero_linea);

	for(int i = init; i<(offset + lineas * 4 + espacios); i++){
		if((c % tam_linea) == 0 && c != 0){
			char* numero_linea = string_itoa(linea);
			memcpy(string + i,&nueva_linea, sizeof(char));
			i++;
			memcpy(string + i,numero_linea, sizeof(char));
			i++;
			memcpy(string + i,&fin_linea, sizeof(char));
			i++;
			memcpy(string + i,&espacio, sizeof(char));
			c=0;
			columna=0;
			linea++;
			free(numero_linea);
			continue;
		}
		if((columna % tam_columna) == 0 && columna != 0){
			memcpy(string + i,&espacio, sizeof(char));
			i++;
		}
		uint16_t byte_new;
		memcpy(&byte_new, memoria + b, 1);
		char character;
		if(byte_new < 32){
			character = byte_new + '0';
		} else {
			character = byte_new;
		}
		memcpy(string + i,&character, sizeof(char));
		if(string[i] == '\0') string[i] = '0';
		b++;
		columna++;
		c++;
	}
	memcpy(string + (offset + lineas * 4 + espacios),&final, sizeof(char));
	printf("\e[1;1H\e[2J");
	printf("%s",string);
}
*/

void imprimir_datos(void* memoria, int tam_memoria){
	int offset = tam_memoria * 2;
	int lineas = ceil((double)tam_memoria / tam_linea);
	int espacios = (ceil((double)tam_linea / tam_columna) - 1) * lineas;
	int b = 0;
	int c = 0;
	int linea = 0;
	int columna = 0;

	char string[tam_memoria * 2 + lineas * 4 + espacios + 1];
	char nueva_linea = '\n';
	char fin_linea = ':';
	char espacio = ' ';
	char final = '\0';

	int init = 0;
	char* numero_linea = string_itoa(linea);
	memcpy(string + init,&nueva_linea, sizeof(char));
	init++;
	memcpy(string + init,numero_linea, sizeof(char));
	init++;
	memcpy(string + init,&fin_linea, sizeof(char));
	init++;
	memcpy(string + init,&espacio, sizeof(char));
	init++;
	linea++;
	free(numero_linea);

	for(int i = init; i<(offset + lineas * 4 + espacios); i++){
		if((c % tam_linea) == 0 && c != 0){
			char* numero_linea = string_itoa(linea);
			memcpy(string + i,&nueva_linea, sizeof(char));
			i++;
			memcpy(string + i,numero_linea, sizeof(char));
			i++;
			memcpy(string + i,&fin_linea, sizeof(char));
			i++;
			memcpy(string + i,&espacio, sizeof(char));
			c=0;
			columna=0;
			linea++;
			free(numero_linea);
			continue;
		}
		if((columna % tam_columna) == 0 && columna != 0){
			memcpy(string + i,&espacio, sizeof(char));
			i++;
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
		columna++;
		c++;
	}
	memcpy(string + (offset + lineas * 4 + espacios),&final, sizeof(char));
	printf("\e[1;1H\e[2J");
	printf("%s",string);
}

