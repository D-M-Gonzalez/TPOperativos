#include "../includes/initial_setup.h"


int initial_setup(){
	int error = 1;

	//Memoria
	
	if (config_has_property(config, "IP_MEMORIA")){
		memoria_ip = config_get_string_value(config, "IP_MEMORIA");
	} else {
		failed_initial_setup("IP_MEMORIA");
		error = 0;
	}

	if (config_has_property(config, "PUERTO_MEMORIA")){
		memoria_port = config_get_string_value(config, "PUERTO_MEMORIA");
	} else {
		failed_initial_setup("PUERTO_MEMORIA");
		error = 0;
	}


	// SERVER PORT
	if (config_has_property(config, "PUERTO_ESCUCHA")){
		server_port = config_get_string_value(config, "PUERTO_ESCUCHA");
	} else {
		failed_initial_setup("PUERTO_ESCUCHA");
		error = 0;
	}

	// PATH_SUPERBLOQUE
	if (config_has_property(config, "PATH_SUPERBLOQUE")){
		path_superbloque = config_get_string_value(config, "PATH_SUPERBLOQUE");
	} else {
		failed_initial_setup("PATH_SUPERBLOQUE");
		error = 0;
	}

	// PATH_BITMAP
	if (config_has_property(config, "PATH_BITMAP")){
		path_bitmap = config_get_string_value(config, "PATH_BITMAP");
	} else {
		failed_initial_setup("PATH_BITMAP");
		error = 0;
	}

	// PATH_BLOQUES
	if (config_has_property(config, "PATH_BLOQUES")){
		path_bloques = config_get_string_value(config, "PATH_BLOQUES");
	} else {
		failed_initial_setup("PATH_BLOQUES");
		error = 0;
	}

	// PATH_FCB
	if (config_has_property(config, "PATH_FCB")){
		path_fcb_folder = config_get_string_value(config, "PATH_FCB");
	} else {
		failed_initial_setup("PATH_FCB");
		error = 0;
	}


	// RETARDO_ACCESO_BLOQUE
	if (config_has_property(config, "RETARDO_ACCESO_BLOQUE")){
		retardo_acceso_bloque = config_get_int_value(config, "RETARDO_ACCESO_BLOQUE");
		} else {
			failed_initial_setup("RETARDO_ACCESO_BLOQUE");
			error = 0;
		}

	if(error == 1){
		log_info(logger, "Valores de configuracion leidos correctamente");
		return EXIT_SUCCESS;
	} else {
		return EXIT_FAILURE;
	}


}

void failed_initial_setup(char* key){
	char *info_error = string_new();
	string_append(&info_error, "No se pudo obtener del archivo config el valor de ");
	string_append(&info_error, key);
	log_error(logger, "%s",info_error);
}
