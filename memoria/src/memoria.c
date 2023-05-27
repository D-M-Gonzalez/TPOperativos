/*
 ============================================================================
 Name        : memoria.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "../includes/memoria.h"

int main(int argc, char *argv[]) {
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

	int server_connection = iniciar_servidor(server_port);

	cpu_conectada = false;
	kernel_conectado = false;
	fileSystem_conectado = false;

	log_info(logger, "Memoria lista para recibir al CPU, Kernel o File System");
	//SO_REUSEADDR flag para reutilizar el socket

	while (1){
		if(num_threads<CANTIDAD_DE_THREADS){
			t_conexion *conexion = malloc(sizeof *conexion);
			conexion->num_socket = esperar_cliente(server_connection);
			conexion->id_cliente = num_threads;

			pthread_create(&(tid[num_threads]), NULL, (void *)thread_main, conexion);
			pthread_detach(&(tid[num_threads]));
			num_threads++;
		}
	}

	log_info(logger, "Se superaron las conexiones maximas establecidas, cerrando memoria");
	liberar_conexion(server_connection);
}

void thread_main(t_conexion *conexion){
	int estado = 1;
	log_info(logger, "Thread iniciado correctamente");
	log_info(logger,handshake(conexion->num_socket));
	t_list* lista;
}

void iterator(char* value) {
	log_info(logger,"%s", value);
}
int crear_segmento(int id_segmento,int tam_segmento)
{
	//se tendria que ver como crear el segemento

	return 0;
}
tabla_segmentos_t* borrar_segmento(id_segmento)
{

	//hacer logica para borrar el segmento
}
