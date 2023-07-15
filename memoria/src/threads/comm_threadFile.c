#include "../../includes/comm_threadFile.h"

void conexion_file_system(int server_connection)
{
	cpu_connection = esperar_cliente(server_connection);
	//log_info(logger, "Se conecto FILE SYSTEM");

	while (exit_status == 0)
	{
		t_paquete *paquete = malloc(sizeof(t_paquete));
		paquete->buffer = malloc(sizeof(t_buffer));
		deserializar_header(paquete, server_connection);

		switch (paquete->codigo_operacion)
		{
		case 1:
			t_instruc_mov *nueva_instruccion = inicializar_instruc_mov();
			deserializar_instruccion_mov(nueva_instruccion, paquete->buffer, paquete->lineas);

			int direccion_fisica = 0;
			int tamanio = 0;

			switch (nueva_instruccion->estado)
			{

			case F_WRITE:
				direccion_fisica = atoi(nueva_instruccion->param1);
				tamanio = atoi(nueva_instruccion->param2);

				log_info(logger, "PID: %d - Accion: LEER - Direccion Fisica: %d - Tamaño: %d - Origen: FS", nueva_instruccion->pid, direccion_fisica, tamanio);

				nueva_instruccion->param3 = realloc(nueva_instruccion->param3, tamanio);
				memcpy(nueva_instruccion->param3, memoria + direccion_fisica, tamanio);
				nueva_instruccion->param3_length = tamanio;
				break;

			case F_READ:

				log_info(logger,"PID: %d - Accion: ESCRIBIR - Direccion Fisica: %d - Tamaño: %d - Origen: FS",nueva_instruccion->pid,direccion_fisica,tamanio);

				direccion_fisica = atoi(nueva_instruccion->param1);
				tamanio = atoi(nueva_instruccion->param2);

				memcpy(memoria + direccion_fisica, nueva_instruccion->param3 , tamanio);

				break;

			default:
				break;
			}
			sleep(retardo_memoria);
			serializar_instruccion_mov(server_connection, nueva_instruccion);
			destruir_instruc_mov(nueva_instruccion);

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
