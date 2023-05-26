#include "../includes/file-system.h"

int main(int argc, char *argv[]) {
	//Iniciamos tanto el log como el config
	logger = iniciar_logger();

	 if (argc < 2) {
		 log_error(logger, "Falta parametro del path del archivo de configuracion");
		 return EXIT_FAILURE;
	 }

	config = iniciar_config(argv[1]);

	//Inicializamos las variables globales desde el config, que loggee errores o success si todo esta bien
	int exit_status = initial_setup();
	if (exit_status==EXIT_FAILURE){
		return EXIT_FAILURE;
	}

	if((memoria_connection = crear_conexion(memoria_ip,memoria_port)) == 0 || handshake_cliente(memoria_connection,3,4) == -1) {
		terminar_programa();
		return EXIT_FAILURE;
	}

	int server_connection = iniciar_servidor(server_port);

	log_info(logger, "File System listo para recibir al Kernel");
	int connection_fd = esperar_cliente(server_connection);
	log_info(logger,handshake(connection_fd));
	t_list* lista;


	return EXIT_SUCCESS;
}
void iterator(char* value) {
	log_info(logger,"%s", value);
}

void terminar_programa()
{
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(memoria_connection);
}
void existe_archivo(archivo_abierto_t* archivo){

	int encontrado=0;
	int num_archivos=sizeof(tabla_file_system);

	for(int i=0;i<num_archivos;i++){
		 if (archivo->id_archivo == tabla_file_system->archivos_abiertos[i].id_archivo) { // Comparar el nombre del archivo con cada elemento de la lista
		            encontrado = 1;
		            break;
		        }
	}
	if(encontrado){
      log_info(logger,"existe el archivo en la tabla de archivos del file system");
	}
	else
	{
		 log_info(logger,"No existe el archivo en la tabla  de archivos del file system");
	}
}
archivo_abierto_t* crear_archivo(){
	archivo_abierto_t* archivo;

	archivo=fopen("nombre_archivo.txt", "w");
	//faltaria ver el tam del archivo
	return archivo;
}

