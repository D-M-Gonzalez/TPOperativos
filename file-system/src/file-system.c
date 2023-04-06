#include "file-system.h"

int main(void)
{
	int conexion_cliente;
	int conexion_servidor;
	char* ip;
	char* puerto_cliente;
	char* puerto_server;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();
	config = iniciar_config();

	ip = config_get_string_value(config,"IP_MEMORIA");
	puerto_cliente = config_get_string_value(config,"PUERTO_MEMORIA");
	puerto_server = config_get_string_value(config, "PUERTO_ESCUCHA");

	// Creamos una conexión hacia el servidor (memoria)

	conexion_cliente = crear_conexion(ip, puerto_cliente);

	if(conexion_cliente != 0) log_info(logger, "Conexion con la memoria establecida correctamente");

	conexion_servidor = iniciar_servidor(puerto_server);

	log_info(logger, "File system listo para recibir al Kernel");
	int cliente_fd = esperar_cliente(conexion_servidor);

	t_list* lista;
	while (1) {
		int cod_op = recibir_operacion(cliente_fd);
		switch (cod_op) {
		case MENSAJE:
			recibir_mensaje(cliente_fd);
			break;
		case PAQUETE:
			lista = recibir_paquete(cliente_fd);
			log_info(logger, "Me llegaron los siguientes valores:\n");
			list_iterate(lista, (void*) iterator);
			break;
		case -1:
			log_error(logger, "el cliente se desconecto. Terminando servidor");
			return EXIT_FAILURE;
		default:
			log_warning(logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}

	return EXIT_SUCCESS;

}

void iterator(char* value) {
	log_info(logger,"%s", value);
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("./file-system.log","File system",true,LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create("./file-system.config");

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	while(1){
		leido = readline("> ");

		if(strcmp(leido,"")==0)break;

		log_info(logger,leido);
		free(leido);
	}

}

void paquete(int conexion)
{

	char* leido;
	t_paquete* paquete = crear_paquete();

	while(1){
		leido = readline("> ");

		if(strcmp(leido,"")==0){
			break;
		}
		agregar_a_paquete(paquete,leido,(strlen(leido)+1));
		free(leido);
	}

	enviar_paquete(paquete,conexion);
	eliminar_paquete(paquete);

}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}
