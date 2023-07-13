#include "../../includes/datos.h"

archivo_abierto_t* crear_archivo(char* nombre){
	archivo_abierto_t *archivo = malloc(sizeof(archivo_abierto_t));

	archivo->pid = 0;
	archivo->posicion_puntero = 0;
	archivo->nombre_archivo = string_new();
	string_append(&archivo->nombre_archivo,nombre);

	return archivo;
}

void copiar_instruccion_file(t_instruc_file* instruccion, t_contexto* contexto, uint32_t puntero){

	instruccion->param1_length = contexto->param1_length;
	instruccion->param2_length = contexto->param2_length;
	instruccion->param3_length = contexto->param3_length;
	instruccion->estado = contexto->estado;
	instruccion->pid = contexto->pid;

	instruccion->param1 = realloc(instruccion->param1,instruccion->param1_length);
	instruccion->param2 = realloc(instruccion->param2,instruccion->param2_length);
	instruccion->param3 = realloc(instruccion->param3,instruccion->param3_length);

	memcpy(instruccion->param1,contexto->param1,instruccion->param1_length);
	memcpy(instruccion->param2,contexto->param2,instruccion->param2_length);
	memcpy(instruccion->param3,contexto->param3,instruccion->param3_length);

	instruccion->param4 = puntero;
}
