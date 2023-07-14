#include "../../includes/comm_ThreadKernel.h"

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
							log_info(logger,"PID: %d - F_OPEN: %s",nueva_instruccion->pid,nueva_instruccion->param1);
							estado_file = F_OPEN_SUCCESS;
						}
						else {
							log_info(logger,"PID: %d - F_OPEN: %s - NO EXISTE",nueva_instruccion->pid,nueva_instruccion->param1);
							estado_file = FILE_DOESNT_EXISTS;
						}
						serializar_respuesta_file_kernel(kernel_connection, estado_file);
						break;
					case F_CREATE:
						if(crear_fcb(nueva_instruccion->param1) != -1){
							log_info(logger,"PID: %d - F_CREATE: %s",nueva_instruccion->pid,nueva_instruccion->param1);
							estado_file = F_CREATE_SUCCESS;
						}
						serializar_respuesta_file_kernel(kernel_connection, estado_file);
						break;
					case F_CLOSE:
						if(buscar_fcb(nueva_instruccion->param1) != -1){
							estado_file = F_CLOSE_SUCCESS;
							log_info(logger,"PID: %d - F_CLOSE: %s",nueva_instruccion->pid,nueva_instruccion->param1);
						}
						serializar_respuesta_file_kernel(kernel_connection, estado_file);
						break;
					case F_TRUNCATE:
						log_info(logger,"PID: %d - F_TRUNCATE: %s - Tamanio: %s",nueva_instruccion->pid,nueva_instruccion->param1, nueva_instruccion->param2);
						if(truncar_fcb(nueva_instruccion->param1, atoi(nueva_instruccion->param2)) != -1)
						{
							estado_file = F_TRUNCATE_SUCCESS;
						}

						serializar_respuesta_file_kernel(kernel_connection, estado_file);

						break;

					case F_WRITE:
						log_info(logger,"PID: %d - F_WRITE: %s - Puntero: %d - Memoria: %s - Tamaño: %s",nueva_instruccion->pid,nueva_instruccion->param1,nueva_instruccion->param4,nueva_instruccion->param2,nueva_instruccion->param3);
						realizar_f_write(nueva_instruccion);

						estado_file = F_WRITE_SUCCESS;
						serializar_respuesta_file_kernel(kernel_connection, estado_file);

						break;

					case F_READ:
						log_info(logger,"PID: %d - F_READ: %s - Puntero: %d - Memoria: %s - Tamaño: %s",nueva_instruccion->pid,nueva_instruccion->param1,nueva_instruccion->param4,nueva_instruccion->param2,nueva_instruccion->param3);
						realizar_f_read(nueva_instruccion);

						estado_file = F_READ_SUCCESS;
						serializar_respuesta_file_kernel(kernel_connection, estado_file);

						break;
					case F_DELETE:
						borrar_fcb(buscar_fcb(nueva_instruccion->param1));
						estado_file = F_DELETE_SUCCESS;
						log_info(logger,"PID: %d - F_DELETE: %s",nueva_instruccion->pid,nueva_instruccion->param1);
						serializar_respuesta_file_kernel(kernel_connection, estado_file);
						break;
					case PRINT_FILE_DATA:
						log_info(logger,"PID: %d Solicito impresion de datos",pid);
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
