#include "../../includes/comm_threadCpu.h"

void conexion_cpu(int server_connection)
{
	cpu_connection = esperar_cliente(server_connection);
	log_info(logger,"Se conecto CPU");

	while (exit_status == 0)
	{
		t_paquete *paquete = malloc(sizeof(t_paquete));
		paquete->buffer = malloc(sizeof(t_buffer));
		deserializar_header(paquete, server_connection);

		switch (paquete->codigo_operacion)
		{
		case 1:
			t_instruc_mem *nueva_instruccion = inicializar_instruc_mem();
			deserializar_instruccion_memoria(nueva_instruccion, paquete->buffer, paquete->lineas);

			int direccion_fisica;
			char valor[17];

			switch (nueva_instruccion->estado)
			{
				case MOV_IN:
					direccion_fisica = atoi(nueva_instruccion->param2);
					memcpy(valor, (char*)(memoria + direccion_fisica), sizeof(valor));
					nueva_instruccion->param2_length = sizeof(valor);
					snprintf(nueva_instruccion->param2, nueva_instruccion->param2_length, "%s", valor);
					serializar_instruccion_memoria(server_connection, nueva_instruccion);
					log_info(logger,"PID: %d - Accion: MOV_IN - Direccion Fisica: %d - Tamanio: %d - Origen: CPU",nueva_instruccion->pid,direccion_fisica,sizeof(valor));
					break;
				case MOV_OUT:
					direccion_fisica = atoi(nueva_instruccion->param1);
					memcpy((char *)(memoria + direccion_fisica), nueva_instruccion->param2, nueva_instruccion->param2_length);
					log_info(logger,"PID: %d - Accion: MOV_OUT - Direccion Fisica: %d - Tamanio: %d - Origen: CPU",nueva_instruccion->pid,direccion_fisica,sizeof(valor));
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