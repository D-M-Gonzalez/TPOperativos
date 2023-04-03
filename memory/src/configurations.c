#include "../include/configurations.h"


// La idea de este archivo (configurations.c) es cargar todas las configuraciones propias de del archivo de configuración para la memoria

// Tanto el path del archivo config como las propiedades incluidas en el mismo, son definadas como variables en configurations.h

t_config_properties* load_configurations(){

    t_config_properties* config_properties; 

    t_config* config;
	
	config = config_create(MEMORY_FILE_CONFIG_PATH);
    

    if (config == NULL){
		log_error(logger, "Config file does not exist");
		exit(1);
	};    

	if (config_has_property(config, PORT_PROPERTY_KEY_CONFIG)){
		(*config_properties).puerto = config_get_string_value(config, PORT_PROPERTY_KEY_CONFIG);
	}; 

    return config_properties;
}