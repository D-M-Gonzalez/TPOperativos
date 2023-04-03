#include "./include/main.h"



t_log* logger;




int main() {

    logger = log_create("memory.log", "MEMORY", true, LOG_LEVEL_TRACE);

	char* ip;
	char* puerto;

	t_config_properties* config_properties  = load_configurations();


    int server_fd = iniciar_servidor(logger, IP_MEMORIA, (*config_properties).puerto);
	int cliente_fd = esperar_cliente(logger, server_fd);
    

    return EXIT_SUCCESS;
}
