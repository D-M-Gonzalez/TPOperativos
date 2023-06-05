#include "../includes/comm_threadMem.h"

void conexion_kernel(int server_connection){

	log_info(logger, "Memoria lista para recibir mensajes del Kernel");
		int connection_fd = esperar_cliente(server_connection);
		log_info(logger, handshake(connection_fd));

		while (1)
		{
			t_paquete *paquete = malloc(sizeof(t_paquete));
			paquete->buffer = malloc(sizeof(t_buffer));
			deserializar_header(paquete, server_connection);

			switch (paquete->codigo_operacion)
			{
			case 1:
				t_contexto *contexto_actualizado = inicializar_contexto();
				deserializar_contexto(contexto_actualizado, paquete->buffer, paquete->lineas);


				switch (contexto_actualizado->estado)
				{
				case CREATE_SEGMENT:
					log_info(logger, "Llego create_segmente a memoria");
					//responder a kernel
				}


				free(contexto_actualizado->param1);
				free(contexto_actualizado->param2);
				free(contexto_actualizado->param3);
				//free(contexto_actualizado->registros);
				free(contexto_actualizado);
				break;

			default:
				log_info(logger, "falle");
				break;
			}
		}
}



