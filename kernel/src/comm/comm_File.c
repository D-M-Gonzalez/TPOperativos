#include "../../includes/comm_File.h"

void manejar_archivo(t_contexto* contexto, pcb_t* pcb){
	t_instruc_file* instruccion = inicializar_instruc_file();
	copiar_instruccion_file(instruccion,contexto,0);
	serializar_instruccion_file(file_system_connection, instruccion);

	t_resp_file respuesta = esperar_respuesta_file();

	switch(respuesta){
		case F_OPEN_SUCCESS:
			//log_info(logger,"PID: %d - F_OPEN correcto", pcb->pid);
			break;
		case F_CLOSE_SUCCESS:
			//log_info(logger,"PID: %d - F_CLOSE correcto", pcb->pid);
			break;
		case F_TRUNCATE_SUCCESS:
			//log_info(logger,"PID: %d - F_TRUNCATE correcto", pcb->pid);
			break;
		case F_SEEK_SUCCESS:
			//log_info(logger,"PID: %d - F_SEEK correcto", pcb->pid);
			break;
		case FILE_DOESNT_EXISTS:
			//log_info(logger,"PID: %d - F_CREATE requerido", pcb->pid);
			contexto->estado = F_CREATE;
			manejar_archivo(contexto,pcb);
			contexto->estado = F_OPEN;
			manejar_archivo(contexto,pcb);
			break;
		case F_DELETE_SUCCESS:
			log_info(logger,"PID: %d - Cerrar Archivo: %s", pcb->pid, contexto->param1);
			list_remove_element(tabla_global_archivos_abiertos,contexto->param1);
			//log_info(logger,"PID: %d - F_DELETE correcto", pcb->pid);
			break;
		default:
			break;
	}

	destruir_instruc_file(instruccion);
}

void editar_archivo(t_contexto* contexto, pcb_t* pcb){
	t_instruc_file* instruccion = inicializar_instruc_file();

	archivo_abierto_t* archivo_abierto_pcb = buscar_archivo_abierto_t(pcb->tabla_archivos_abiertos, contexto->param1);

	copiar_instruccion_file(instruccion,contexto,archivo_abierto_pcb->posicion_puntero);
	serializar_instruccion_file(file_system_connection, instruccion);

	t_resp_file respuesta = esperar_respuesta_file();

	switch(respuesta){
		case F_WRITE_SUCCESS:
			//log_info(logger,"PID: %d - F_WRITE correcto", pcb->pid);
			break;
		case F_READ_SUCCESS:
			//log_info(logger,"PID: %d - F_READ correcto", pcb->pid);
			break;
		default:
			break;
	}
	destruir_instruc_file(instruccion);
}

t_resp_file esperar_respuesta_file(){

		t_resp_file respuesta = F_ERROR;
		t_paquete *paquete = malloc(sizeof(t_paquete));
		paquete->buffer = malloc(sizeof(t_buffer));

		deserializar_header(paquete, file_system_connection);
		switch (paquete->codigo_operacion){
			case 1:
				t_resp_file resp = deserializar_respuesta_file(paquete->buffer) ;
				respuesta = resp;
				break;
			default:
				log_error(logger,"Fallo de serializacion de respuesta file");
				break;
		}

		free(paquete->buffer->stream);
		free(paquete->buffer);
		free(paquete);

		return respuesta;
}
