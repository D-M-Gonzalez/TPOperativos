#include "../include/sockets.h"

/*
    INICIAR SERVIDOR Y ESPERAR CLIENTE
*/


int iniciar_servidor(t_log* logger, char* ip, char* puerto)
{

	int socket_servidor;


	struct addrinfo hints, *servinfo, *p;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &servinfo);

	// Creamos el socket de escucha del servidor

	socket_servidor = socket((*servinfo).ai_family, (*servinfo).ai_socktype, (*servinfo).ai_protocol);

    if (socket_servidor == -1) {
    	log_error(logger, "Socket creation failed.");
        exit(1);
    } else {
    	log_trace(logger, "Socket successfully created.");
    }


	// Asociamos el socket a un puerto

	;

    if ((bind(socket_servidor, (*servinfo).ai_addr , (*servinfo).ai_addrlen )) != 0) {
    	log_error(logger, "Socket bind failed.");
    	exit(1);
    } else {
     	log_trace(logger, "Socket successfully binded.");
    }



	// Escuchamos las conexiones entrantes

	if ((listen(socket_servidor, SOCKET_PENDING_CONNECTIONS)) != 0) {
		log_error(logger, "Listening failed");
		exit(1);
	} else {
		log_trace(logger, "Server listening...");
	}


	freeaddrinfo(servinfo);


	return socket_servidor;
}

int esperar_cliente(t_log* logger, int socket_servidor)
{

	// Aceptamos un nuevo cliente
	int socket_cliente;

	struct sockaddr client_addr;
	socklen_t client_addrlen;

	socket_cliente = accept(socket_servidor, &client_addr, &client_addrlen);

	if(socket_cliente<0){
		log_error(logger, "Server accepting client failed.");
		exit(1);
	} else {
	 	log_info(logger, "Server accepted the client.");
	}

	return socket_cliente;
}



/*
    CREAR CLIENTE Y CONECTAR A SERVIDOR
*/

int crear_conexion(char *ip, char* puerto)
{
	t_log* logger;
	logger = log_create("tp0.log", "TP0", 1, LOG_LEVEL_INFO);

	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	// Ahora vamos a crear el socket.
	int socket_cliente = 0;

	socket_cliente = socket((*server_info).ai_family, (*server_info).ai_socktype, (*server_info).ai_protocol);

    if (socket_cliente == -1) {
    	log_error(logger, "Socket creation failed.");
        exit(1);
    } else {
    	log_info(logger, "Socket successfully created.");
    }

	// Ahora que tenemos el socket, vamos a conectarlo

	int status;
	if ((status = connect(socket_cliente, (*server_info).ai_addr , (*server_info).ai_addrlen)) < 0) {
        log_error(logger,"Connection Failed");
        exit(1);
    }

	freeaddrinfo(server_info);

	return socket_cliente;
}


/*
    CERRAR SOCKET
*/

void liberar_conexion(int socket)
{
	close(socket);
}


