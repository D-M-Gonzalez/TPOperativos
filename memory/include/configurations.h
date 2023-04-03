#ifndef MEMORY_CONFIG_H_
#define MEMORY_CONFIG_H_


#include<commons/config.h>  


#define MEMORY_FILE_CONFIG_PATH "memory.config"
#define PORT_PROPERTY_KEY_CONFIG "PUERTO_ESCUCHA"

typedef struct
{
    char* puerto;

    //Acá irian las otras propiedades del memory.config

} t_config_properties;


t_config_properties* load_configurations();

#endif MEMORY_CONFIG_H_