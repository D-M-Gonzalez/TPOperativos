#include "../../includes/datos.h"

void crear_header(void* a_enviar, t_buffer* buffer, int lineas, uint32_t codigo){
	//Reservo el stream para el header del paquete
	int offset = 0;

	//Añado los datos del header al stream
	memcpy(a_enviar + offset, &(codigo), sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(a_enviar + offset, &(lineas), sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(a_enviar + offset, &(buffer->size), sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(a_enviar + offset, buffer->stream, buffer->size);
}

void copiar_contexto(void* stream, t_contexto* contexto){
	int lineas = list_size(contexto->instrucciones);
	int offset = 0;

	for(int i = 0; i < lineas; i++){
			t_instruc* instrucciones = list_get(contexto->instrucciones, i);

			memcpy(stream + offset, &instrucciones->nro, sizeof(uint32_t));
			offset += sizeof(uint32_t);
			memcpy(stream + offset, &instrucciones->instruct_length, sizeof(uint32_t));
			offset += sizeof(uint32_t);
			memcpy(stream + offset, instrucciones->instruct, instrucciones->instruct_length);
			offset += instrucciones->instruct_length;
			memcpy(stream + offset, &instrucciones->param1_length, sizeof(uint32_t));
			offset += sizeof(uint32_t);
			memcpy(stream + offset, instrucciones->param1, instrucciones->param1_length);
			offset += instrucciones->param1_length;
			memcpy(stream + offset, &instrucciones->param2_length, sizeof(uint32_t));
			offset += sizeof(uint32_t);
			memcpy(stream + offset, instrucciones->param2, instrucciones->param2_length);
			offset += instrucciones->param2_length;
			memcpy(stream + offset, &instrucciones->param3_length, sizeof(uint32_t));
			offset += sizeof(uint32_t);
			memcpy(stream + offset, instrucciones->param3, instrucciones->param3_length);
			offset += instrucciones->param3_length;
		}

	memcpy(stream + offset, &contexto->registros->ip, sizeof(uint16_t));
	offset += sizeof(uint16_t);
	memcpy(stream + offset, contexto->registros->ax, sizeof(char) * 5);
	offset += sizeof(char) * 5;
	memcpy(stream + offset, contexto->registros->bx, sizeof(char) * 5);
	offset += sizeof(char) * 5;
	memcpy(stream + offset, contexto->registros->cx, sizeof(char) * 5);
	offset += sizeof(char) * 5;
	memcpy(stream + offset, contexto->registros->dx, sizeof(char) * 5);
	offset += sizeof(char) * 5;
	memcpy(stream + offset, contexto->registros->eax, sizeof(char) * 9);
	offset += sizeof(char) * 9;
	memcpy(stream + offset, contexto->registros->ebx, sizeof(char) * 9);
	offset += sizeof(char) * 9;
	memcpy(stream + offset, contexto->registros->ecx, sizeof(char) * 9);
	offset += sizeof(char) * 9;
	memcpy(stream + offset, contexto->registros->edx, sizeof(char) * 9);
	offset += sizeof(char) * 9;
	memcpy(stream + offset, contexto->registros->rax, sizeof(char) * 17);
	offset += sizeof(char) * 17;
	memcpy(stream + offset, contexto->registros->rbx, sizeof(char) * 17);
	offset += sizeof(char) * 17;
	memcpy(stream + offset, contexto->registros->rcx, sizeof(char) * 17);
	offset += sizeof(char) * 17;
	memcpy(stream + offset, contexto->registros->rdx, sizeof(char) * 17);
	offset += sizeof(char) * 17;
	memcpy(stream + offset, &contexto->pid, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, &contexto->estado, sizeof(contexto_estado_t));
	offset += sizeof(contexto_estado_t);

	memcpy(stream + offset, &contexto->param1_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, contexto->param1, contexto->param1_length);
	offset += contexto->param1_length;

	memcpy(stream + offset, &contexto->param2_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, contexto->param2, contexto->param2_length);
	offset += contexto->param2_length;

	memcpy(stream + offset, &contexto->param3_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, contexto->param3, contexto->param3_length);
	offset += contexto->param3_length;

	//copiar tabla de segmentos
	memcpy(stream + offset, &contexto->tabla_segmento->pid, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	uint32_t size_lista = list_size(contexto->tabla_segmento->segmentos);
	memcpy(stream + offset, &size_lista, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	for (int i = 0; i < size_lista; i++)
	{
		segmento_t *segmento = list_get(contexto->tabla_segmento->segmentos, i);
		memcpy(stream + offset, &segmento->ids, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		memcpy(stream + offset, &segmento->direccion_base, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		memcpy(stream + offset, &segmento->tamanio, sizeof(uint32_t));
		offset += sizeof(uint32_t);
	}
}

void copiar_instruccion_memoria(void* stream, t_instruc_mem* instruccion){
	int offset = 0;

	memcpy(stream + offset, &instruccion->estado, sizeof(contexto_estado_t));
	offset += sizeof(contexto_estado_t);

	memcpy(stream + offset, &instruccion->pid, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, &instruccion->param1_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, instruccion->param1, instruccion->param1_length);
	offset += instruccion->param1_length;

	memcpy(stream + offset, &instruccion->param2_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, instruccion->param2, instruccion->param2_length);
	offset += instruccion->param2_length;

	memcpy(stream + offset, &instruccion->param3_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, instruccion->param3, instruccion->param3_length);
}

void copiar_instruc_file(void* stream, t_instruc_file* instruccion){
	int offset = 0;

	memcpy(stream + offset, &instruccion->estado, sizeof(contexto_estado_t));
	offset += sizeof(contexto_estado_t);

	memcpy(stream + offset, &instruccion->pid, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(stream + offset, &instruccion->param1_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, instruccion->param1, instruccion->param1_length);
	offset += instruccion->param1_length;

	memcpy(stream + offset, &instruccion->param2_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, instruccion->param2, instruccion->param2_length);
	offset += instruccion->param2_length;

	memcpy(stream + offset, &instruccion->param3_length, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	memcpy(stream + offset, instruccion->param3, instruccion->param3_length);
	offset += instruccion->param3_length;

	memcpy(stream + offset, &instruccion->param4, sizeof(uint32_t));
}

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
