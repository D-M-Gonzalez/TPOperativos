#include "../../includes/comm_Mem.h"

void realizar_f_write(t_instruc_file* instruccion_file){

	int direccion_fisica = atoi(instruccion_file->param2);
	int tamanio = atoi(instruccion_file->param3);
	int puntero_archivo = instruccion_file->param4;
	char* placeholder = "0";

	t_instruc_mov *instruccion_mem = inicializar_instruc_mov();
	instruccion_mem->pid = instruccion_file->pid;
	generar_instruccion_mov(instruccion_mem, F_WRITE, direccion_fisica, tamanio, placeholder);
	serializar_instruccion_mov(memoria_connection, instruccion_mem);

	void* datos = esperar_valor(memoria_connection);

	int id_fcb = buscar_fcb(instruccion_file->param1);

	t_list* lista_de_bloques = armar_lista_offsets(id_fcb,tamanio,puntero_archivo);

	escribir_datos(datos, lista_de_bloques);

	list_destroy_and_destroy_elements(lista_de_bloques,free);
	free(datos);
	destroy_instruc_mov(instruccion_mem);
}

void realizar_f_read(t_instruc_file* instruccion_file){

	int direccion_fisica = atoi(instruccion_file->param2);
	int tamanio = atoi(instruccion_file->param3);
	int puntero_archivo = instruccion_file->param4;

	int id_fcb = buscar_fcb(instruccion_file->param1);

	t_list* lista_de_bloques = armar_lista_offsets(id_fcb,tamanio,puntero_archivo);
	void* datos = leer_datos(lista_de_bloques);

	t_instruc_mov *instruccion_mem = inicializar_instruc_mov();
	instruccion_mem->pid = instruccion_file->pid;
	generar_instruccion_mov(instruccion_mem, F_READ, direccion_fisica, tamanio, datos);
	serializar_instruccion_mov(memoria_connection, instruccion_mem);

	list_destroy_and_destroy_elements(lista_de_bloques,free);
	char* valor = esperar_valor(memoria_connection);

	free(valor);
	free(datos);
	destroy_instruc_mov(instruccion_mem);
}
