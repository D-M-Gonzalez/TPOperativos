#include "./include/consola.h"

#include <readline/readline.h>
//aca va estar el codigo
int main(void){

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_conig* config;

	logger=iniciar_logger();
	config=iniciar_config();

	//guardo los valores pedidos
	ip=config_get_string_value(config,"IP_KERNEL");
	puerto=config_get_string_value(config,"PUERTO_KERNEL");

	//leo los valores del config
	log_info(logger,"ip del kernel: %s \n",ip);
	log_info(logger,"puerto del kernel: %s \n",puerto);

	//creo una conexion hacia el servidor(Kernel)
	conexion=crear_conexion(ip,puerto);

   //armamos y enviamos el paquete
	paquete(conexion);
	terminar_programa(conexion,logger,config);

}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	nuevo_logger=log_create("./consola.log","Consola",1,LOG_LEVEL_INFO);

}
t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	nuevo_config=config_create("./consola.config");
}
void leer_consola(t_log* logger){

	char *leido;

	while(1){
		leido=readline(">");
		if(strcmp(leido,"")==0)
		{
			break;
		}
		log_info(logger,leido);
		free(leido);
	}
}

vod paquete(int conexion)
{
	char* leido;

	t_paquete* paquete=crear_paquete();
	//leemos y agregamos las lineas al paquete

	while(1){
		leido=readline("> ");
		if(strcmp(leido,"")==0){
			break;
		}
		agregar_a_paquete(paquete,leido,strlen(leido)+1);
		free(leido);

	}

 enviar_paquete(paquete,conexion);
 puts("Mensaje llego al servidor Kernel,con exito!");
 eliminar_paquete(paquete);

}
 void terminar_programa(int conexion,t_log* logger,t_config* config)
 {
	 log_destroy(logger);
	 config_destroy(config);
	 liberar_conexion(conexion);
 }
