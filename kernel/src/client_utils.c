#include "../includes/client_utils.h"

int crear_conexion(char *ip, char* puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	// Ahora vamos a crear el socket.
	int socket_cliente = socket(server_info->ai_family,server_info->ai_socktype,server_info->ai_protocol);

	// Ahora que tenemos el socket, vamos a conectarlo
	connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen);

	freeaddrinfo(server_info);

	return socket_cliente;
}

int handshake(int socket_cliente, uint8_t tipo_cliente, uint8_t tipo_servidor){

	char* message = "";
	uint8_t handshake = tipo_cliente;
	uint8_t result = 0;

	switch(tipo_servidor){
				case 1:
					message = "Cpu";
					break;
				case 2:
					message = "Kernel";
					break;
				case 3:
					message = "File system";
					break;
				case 4:
					message = "Memoria";
					break;
				default:
					break;
			}

	send(socket_cliente, &handshake, sizeof(uint8_t), NULL);
	//log_info(logger, message);
	recv(socket_cliente, &result, sizeof(uint8_t), MSG_WAITALL);

	if(result == 1){
		//log_info(logger, "Se establecio correctamente la conexion");
	} else {
		log_error(logger, "Fallo al realizar el handshake, cerrando conexion");
		result = -1;
	}

	return result;
}

void serializar_contexto(int socket, t_contexto* contexto){
	//Creo el buffer a utilizar para las instrucciones
	t_buffer* buffer = malloc(sizeof(t_buffer));

	//Leo la lista de instrucciones para sumar el tamaño de toda la lista
	buffer->size = calcular_tam_registros(contexto->registros);
	buffer->size = buffer->size + calcular_tam_contexto(contexto);
	buffer->size = buffer->size + calcular_tam_instrucciones(contexto->instrucciones);
	buffer->size = buffer->size + calcular_tam_tabla_segmentos(contexto->tabla_segmento);

	//Asigno memoria para el stream del tamaño de mi lista
	void* stream = malloc(buffer->size);

	//Leo toda la lista para copiar los valores en memoria
	copiar_contexto(stream,contexto);

	//Añado el stream a mi buffers
	buffer->stream = stream;

	void* a_enviar = malloc(buffer->size + sizeof(uint32_t) * 3);

	crear_header(a_enviar,buffer,list_size(contexto->instrucciones),1);

	//Envio todo el stream al servidor
	send(socket, a_enviar, buffer->size + sizeof(uint32_t) + sizeof(uint32_t) + sizeof(uint32_t), 0);

	//Libero memoria que ya no voy a utilizar
	free(buffer->stream);
	free(buffer);
	free(a_enviar);
}

void serializar_instruccion_memoria(int socket,t_instruc_mem* instruccion)
{
	//Creo el buffer a utilizar para las instrucciones
		t_buffer* buffer = malloc(sizeof(t_buffer));

		buffer->size = calcular_tam_instruc_mem(instruccion);

		//Asigno memoria para el stream del tamaño de mi lista
		void* stream = malloc(buffer->size);

		//Leo toda la lista para copiar los valores en memoria
		copiar_instruccion_memoria(stream,instruccion);

		//Añado el stream a mi buffers
		buffer->stream = stream;

		void* a_enviar = malloc(buffer->size + sizeof(uint32_t) * 3);

		crear_header(a_enviar,buffer,0,1);

		//Envio todo el stream al servidor
		send(socket, a_enviar, buffer->size + sizeof(uint32_t) + sizeof(uint32_t) + sizeof(uint32_t), 0);

		//Libero memoria que ya no voy a utilizar
		free(buffer->stream);
		free(buffer);
		free(a_enviar);
}

void serializar_solicitud_tabla(int socket){
	t_buffer* buffer = malloc(sizeof(t_buffer));

	buffer->size = sizeof(char);

	void* stream = malloc(buffer->size);

	memcpy(stream,"",sizeof(char));

	buffer->stream = stream;

	void* a_enviar = malloc(buffer->size + sizeof(uint32_t) * 3);

	crear_header(a_enviar,buffer,0,2);

	send(socket, a_enviar, buffer->size + sizeof(uint32_t) + sizeof(uint32_t) + sizeof(uint32_t), 0);

	free(buffer->stream);
	free(buffer);
	free(a_enviar);
}
void serializar_solicitud_compactacion(int socket){
	t_buffer* buffer = malloc(sizeof(t_buffer));

	buffer->size = sizeof(char);

	void* stream = malloc(buffer->size);

	memcpy(stream,"",sizeof(char));

	buffer->stream = stream;

	void* a_enviar = malloc(buffer->size + sizeof(uint32_t) * 3);

	crear_header(a_enviar,buffer,0,3);

	send(socket, a_enviar, buffer->size + sizeof(uint32_t) + sizeof(uint32_t) + sizeof(uint32_t), 0);

	free(buffer->stream);
	free(buffer);
	free(a_enviar);
}

void serializar_instruccion_file(int socket,t_instruc_file* instruccion)
{
	//Creo el buffer a utilizar para las instrucciones
		t_buffer* buffer = malloc(sizeof(t_buffer));

		buffer->size = calcular_tam_instruc_file(instruccion);

		//Asigno memoria para el stream del tamaño de mi lista
		void* stream = malloc(buffer->size);

		//Leo toda la lista para copiar los valores en memoria
		copiar_instruc_file(stream,instruccion);

		//Añado el stream a mi buffers
		buffer->stream = stream;

		void* a_enviar = malloc(buffer->size + sizeof(uint32_t) * 3);

		crear_header(a_enviar,buffer,0,1);

		//Envio todo el stream al servidor
		send(socket, a_enviar, buffer->size + sizeof(uint32_t) + sizeof(uint32_t) + sizeof(uint32_t), 0);

		//Libero memoria que ya no voy a utilizar
		free(buffer->stream);
		free(buffer);
		free(a_enviar);
}

void liberar_conexion(int socket_cliente)
{
	close(socket_cliente);
}
