#include "../includes/comm_ThreadKernel.h"

void comm_threadKernel(int kernel_connection){
	while(exit_status == 0){
		t_paquete *paquete = malloc(sizeof(t_paquete));
		paquete->buffer = malloc(sizeof(t_buffer));
		deserializar_header(paquete, kernel_connection);

		switch (paquete->codigo_operacion){
			case 1:
				t_instruc_file *nueva_instruccion = inicializar_instruc_file();
				deserializar_instruccion_file(nueva_instruccion, paquete->buffer, paquete->lineas);
				uint32_t pid = nueva_instruccion->pid;
				t_resp_file estado_file = F_ERROR;
				switch (nueva_instruccion->estado){
					case F_OPEN:
						if(buscar_fcb(nueva_instruccion->param1)!=-1){
							log_info(logger,"Se abrio el FCB %s correctamente",nueva_instruccion->param1);
							estado_file = F_OPEN_SUCCESS;
						}
						else {
							log_info(logger,"El archivo %s solicitado no existe", nueva_instruccion->param1);
							estado_file = FILE_DOESNT_EXISTS;
						}
						serializar_respuesta_file_kernel(kernel_connection, estado_file);
						break;
					case F_CREATE:
						if(crear_fcb(nueva_instruccion->param1) != -1){
							estado_file = F_CREATE_SUCCESS;
						}
						serializar_respuesta_file_kernel(kernel_connection, estado_file);
						break;
					case F_CLOSE:
						if(buscar_fcb(nueva_instruccion->param1) != -1){
							estado_file = F_CLOSE_SUCCESS;
							log_info(logger,"F_CLOSE para el archivo %s realizado con exito", nueva_instruccion->param1);
						}
						serializar_respuesta_file_kernel(kernel_connection, estado_file);
						break;
					case F_TRUNCATE:

						int id_fcb = buscar_fcb(nueva_instruccion->param1);
						int nuevo_tamanio = atoi(nueva_instruccion->param2);
						int tamanio_archivo = valor_fcb(id_fcb, TAMANIO_ARCHIVO);

						uint32_t puntero_indirecto = valor_fcb(id_fcb, PUNTERO_INDIRECTO);
						int offset = puntero_indirecto;

						asignar_bloques(id_fcb, 5);
						t_list* lista_bloques = list_create();
						list_add(lista_bloques, valor_fcb(id_fcb, PUNTERO_DIRECTO));

						for(int i = 0; i < 4; i++)
						{
							uint32_t id_bloque = 0;
							memcpy(&id_bloque, array_de_bloques + offset, sizeof(uint32_t));
							log_info(logger, "Valor apuntado: %d", id_bloque);
							offset += sizeof(uint32_t);
							list_add(lista_bloques, id_bloque);
						}

						/*
						if(id_fcb != -1)
						{
							if(nuevo_tamanio > tamanio_archivo)
							{
								int bloques_a_agregar = (nuevo_tamanio - tamanio_archivo) / tamanio_de_bloque; // usar ceil
								asignar_bloques(id_fcb, bloques_a_agregar);
								modificar_fcb(id_fcb, TAMANIO_ARCHIVO, nuevo_tamanio);
							}
							if(nuevo_tamanio < tamanio_archivo)
							{
								int bloques_a_sacar = (tamanio_archivo - nuevo_tamanio) / tamanio_de_bloque; // usar ceil
								//desasignar_bloques(id_fcb, bloques_a_sacar);
								modificar_fcb(id_fcb, TAMANIO_ARCHIVO, nuevo_tamanio);
							}
						}*/

						estado_file = F_TRUNCATE_SUCCESS;
						log_info(logger,"PID: %d solicito F_TRUNCATE para el archivo %s",pid, nueva_instruccion->param1);
						serializar_respuesta_file_kernel(kernel_connection, estado_file);
						break;
					case F_WRITE:
						realizar_f_write(nueva_instruccion);
						estado_file = F_WRITE_SUCCESS;
						log_info(logger,"PID: %d solicito F_WRITE para el archivo %s",pid, nueva_instruccion->param1);
						log_info(logger,"PID: %d puntero %s",pid, nueva_instruccion->param4);
						sleep(20);
						serializar_respuesta_file_kernel(kernel_connection, estado_file);
						break;
					case F_READ:
						realizar_f_read(nueva_instruccion);
						estado_file = F_READ_SUCCESS;
						log_info(logger,"PID: %d solicito F_READ para el archivo %s",pid, nueva_instruccion->param1);
						log_info(logger,"PID: %d puntero %s",pid, nueva_instruccion->param4);
						sleep(20);
						serializar_respuesta_file_kernel(kernel_connection, estado_file);
						break;
					case F_SEEK:
						estado_file = F_SEEK_SUCCESS;
						log_info(logger,"PID: %d solicito F_SEEK para el archivo %s",pid, nueva_instruccion->param1);
						serializar_respuesta_file_kernel(kernel_connection, estado_file);
						break;
					case PRINT_FILE_DATA:
						log_info(logger,"PID: %d solicito impresion de datos",pid);
						break;
					default:
						break;
				}
				free(nueva_instruccion->param1);
				free(nueva_instruccion->param2);
				free(nueva_instruccion->param3);
				free(nueva_instruccion);
				break;
			default:
				exit_status = 1;
				break;
		}
		free(paquete->buffer->stream);
		free(paquete->buffer);
		free(paquete);
	}
}
