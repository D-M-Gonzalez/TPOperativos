#include "../../includes/comm_threadKernel.h"

t_contexto* obtener_contexto_pcb(pcb_t *pcb)
{
	t_contexto *contexto = inicializar_contexto();
	copiar_registros(contexto->registros, pcb->registros_cpu);
	copiar_lista_instrucciones(contexto->instrucciones, pcb->instrucciones);
	copiar_tabla_segmentos(contexto->tabla_segmento, pcb->tabla_segmento);
	contexto->pid = pcb->pid;
	return contexto;
}

contexto_estado_t enviar_contexto(pcb_t *pcb)
{
	t_contexto *contexto = obtener_contexto_pcb(pcb);
	t_paquete *paquete = malloc(sizeof(t_paquete));
	paquete->buffer = malloc(sizeof(t_buffer));

	serializar_contexto(cpu_connection, contexto);
	deserializar_header(paquete, cpu_connection);
	switch (paquete->codigo_operacion)
	{
	case 1:
		t_contexto *contexto_actualizado = inicializar_contexto();
		deserializar_contexto(contexto_actualizado, paquete->buffer, paquete->lineas);
		copiar_registros(pcb->registros_cpu, contexto_actualizado->registros);
		pcb->estado_exec = contexto_actualizado->estado;
		pcb->estado = EXEC;

		switch (contexto_actualizado->estado)
		{
		case ERROR_SEG_FAULT:
			log_info(logger, "PID: %d - Estado Anterior: PCB_EXEC - Estado Actual: PCB_EXIT", pcb->pid);
			log_info(logger, "Finaliza el proceso %d - Motivo: SEG_FAULT", pcb->pid);
			list_push(pcb_exit_list, pcb);
			sem_post(&sem_estado_exit);
			break;

		case EXIT:
			log_info(logger, "PID: %d - Estado Anterior: PCB_EXEC - Estado Actual: PCB_EXIT", pcb->pid);
			log_info(logger, "Finaliza el proceso %d - Motivo: SUCCESS", pcb->pid);
			list_push(pcb_exit_list, pcb);
			sem_post(&sem_estado_exit);
			break;

		case YIELD:
			list_push(pcb_ready_list, pcb);
			pcb->tiempo_espera_en_ready = temporal_create();
			//log_info(logger, "El proceso %d llego a yield. Se envio al final de ready", pcb->pid);
			sem_post(&sem_estado_ready);
			break;

		case IO:
			t_io_block_args *args = malloc(sizeof(t_io_block_args));
			args->pcb = pcb;
			int time = atoi(contexto_actualizado->param1);
			args->block_time = time;
			pthread_t thread_io_block;
			pthread_create(&thread_io_block, NULL, (void*) io_block, (t_io_block_args*) args);
			pthread_detach(thread_io_block);
			break;

		case WAIT:
			char *recurso_wait = crear_recurso(contexto_actualizado->param1);

			if (recurso_existe_en_lista(lista_recursos, recurso_wait))
			{
				asignar_recurso(pcb, recurso_wait);
				restar_instancia(lista_recursos, recurso_wait);
				int instancias_recurso = obtener_instancias(lista_recursos, recurso_wait);
				log_info(logger, "PID: %d - Wait: %s - Instancias: %d", pcb->pid, recurso_wait, instancias_recurso);
				if (instancias_recurso < 0)
				{
					log_info(logger,"PID: %d - Bloqueado por: %s",pcb->pid,recurso_wait);
					int recurso_length = strlen(recurso_wait) + 1;
					pcb->recurso_bloqueante = realloc(pcb->recurso_bloqueante, recurso_length);
					memcpy(pcb->recurso_bloqueante, recurso_wait, recurso_length);
					list_push(pcb_block_list, pcb);
					sem_post(&sem_estado_block);
				}
				else
				{
					enviar_contexto(pcb);
				}
			}
			else
			{
				log_error(logger, "No existe el recurso %s - terminando proceso PID: %d", recurso_wait, pcb->pid);
				log_info(logger, "PID: %d - Estado Anterior: PCB_EXEC - Estado Actual: PCB_EXIT", pcb->pid);
				log_info(logger, "Finaliza el proceso %d - Motivo: INVALID_RESOURCE", pcb->pid);
				list_push(pcb_exit_list, pcb);
				sem_post(&sem_estado_exit);
			}

			free(recurso_wait);
			break;

		case SIGNAL:
			char *recurso_signal = crear_recurso(contexto_actualizado->param1);

			if (recurso_existe_en_lista(lista_recursos, recurso_signal))
			{
				int instancias_recurso = obtener_instancias(lista_recursos, recurso_signal);
				sumar_instancia(lista_recursos, recurso_signal);
				int instancias_actualizadas = obtener_instancias(lista_recursos, recurso_signal);
				log_info(logger, "PID: %d - Signal: %s - Instancias: %d", pcb->pid, recurso_signal, instancias_actualizadas);
				liberar_proceso_de_bloqueados_si_necesario(recurso_signal, instancias_recurso);
				enviar_contexto(pcb);
			}
			else
			{
				list_push(pcb_exit_list, pcb);
				log_info(logger, "Finaliza el proceso %d - Motivo: INVALID_RESOURCE", pcb->pid);
				log_error(logger, "No existe el recurso %s - terminando proceso PID: %d", recurso_signal, pcb->pid);
				sem_post(&sem_estado_exit);
			}
			free(recurso_signal);
			break;

		case F_OPEN:
			log_info(logger, "PID: %d - Abrir Archivo: %s", pcb->pid, contexto_actualizado->param1);

			archivo_abierto_t *archivo = crear_archivo(contexto_actualizado->param1);

			list_add(pcb->tabla_archivos_abiertos, archivo);

			verif_crear_recurso_file(archivo);

			asignar_recurso(pcb, archivo->nombre_archivo);
			restar_instancia(lista_recursos, archivo->nombre_archivo);

			int instancias_recurso = obtener_instancias(lista_recursos, archivo->nombre_archivo);
			if (instancias_recurso < 0)
			{
				int recurso_length = strlen(archivo->nombre_archivo) + 1;
				pcb->recurso_bloqueante = realloc(pcb->recurso_bloqueante, recurso_length);
				memcpy(pcb->recurso_bloqueante, archivo->nombre_archivo, recurso_length);
				list_push(pcb_block_list, pcb);
				sem_post(&sem_estado_block);
			}
			else
			{
				manejar_archivo(contexto_actualizado,pcb);
				enviar_contexto(pcb);
			}


			break;

		case F_DELETE:
			manejar_archivo(contexto_actualizado,pcb);
			//log_info(logger, "El proceso %d se comunico con FileSystem. Se continua su ejecucion", pcb->pid);
			enviar_contexto(pcb);
			break;

		case F_CLOSE:
			imprimir_recursos(pcb);
			log_info(logger, "PID: %d - Cerrar Archivo: %s", pcb->pid, contexto_actualizado->param1);

			char *archivo_abierto = contexto_actualizado->param1;

			if (recurso_existe_en_lista(lista_recursos, archivo_abierto) && archivo_existe_en_tabla(tabla_global_archivos_abiertos, archivo_abierto))
			{
				manejar_archivo(contexto_actualizado,pcb);
				archivo_abierto_t* archivo_abierto_pcb = buscar_archivo_abierto_t(pcb->tabla_archivos_abiertos, archivo_abierto);
				list_remove_element(pcb->tabla_archivos_abiertos,archivo_abierto_pcb);

				if(verif_eliminar_recurso_file(pcb,archivo_abierto_pcb) == 0){
					int instancias_recurso = obtener_instancias(lista_recursos, archivo_abierto);
					sumar_instancia(lista_recursos, archivo_abierto);
					liberar_proceso_de_bloqueados_si_necesario(archivo_abierto, instancias_recurso);
				}

				enviar_contexto(pcb);
			}
			else
			{
				list_push(pcb_exit_list, pcb);
				log_info(logger, "Finaliza el proceso %d - Motivo: INVALID_RESOURCE", pcb->pid);
				//log_error(logger, "No existe el archivo %s - terminando proceso PID: %d", archivo_abierto, pcb->pid);
				sem_post(&sem_estado_exit);
			}
			break;

		case F_TRUNCATE:
			log_info(logger,"PID: %d - Archivo: %s - Tamaño: %s",pcb->pid,contexto_actualizado->param1, contexto_actualizado->param2);
			t_read_write_block_args *args_truncate = malloc(sizeof(t_read_write_block_args));
			args_truncate->pcb = pcb;
			args_truncate->contexto = inicializar_contexto();

			duplicar_contexto(args_truncate->contexto,contexto_actualizado);

			pthread_t thread_truncate_block;
			pthread_create(&thread_truncate_block, NULL, (void*) file_system_truncate_block, args_truncate);
			pthread_detach(thread_truncate_block);
			break;

		case F_SEEK:
			log_info(logger, "PID: %d - Actualizar puntero Archivo: %s - Puntero %s", pcb->pid, contexto_actualizado->param1, contexto_actualizado->param2);

			int archivo_abierto_seek = atoi(contexto_actualizado->param2);

			archivo_abierto_t* archivo_abierto_seek_pcb = buscar_archivo_abierto_t(pcb->tabla_archivos_abiertos, contexto_actualizado->param1);

			archivo_abierto_seek_pcb->posicion_puntero = archivo_abierto_seek;

			enviar_contexto(pcb);
			break;


		case F_READ:

			t_read_write_block_args *args_read = malloc(sizeof(t_read_write_block_args));
			args_read->pcb = pcb;
			args_read->contexto = inicializar_contexto();

			duplicar_contexto(args_read->contexto,contexto_actualizado);

			archivo_abierto_t* archivo_abierto_pcb_read = buscar_archivo_abierto_t(pcb->tabla_archivos_abiertos, contexto_actualizado->param1);

			log_info(logger, "PID: %d - Leer Archivo: %s - Puntero %d - Dirección Memoria %s - Tamaño %s", pcb->pid, contexto_actualizado->param1, archivo_abierto_pcb_read->posicion_puntero, contexto_actualizado->param2, contexto_actualizado->param3);
			log_info(logger,"PID: %d - Bloqueado por: %s",pcb->pid, contexto_actualizado->param1);
			//log_info(logger,"PID: %d - Estado Anterior: PCB_EXEC - Estado Actual: PCB_BLOCK - Razon: F_READ",pcb->pid);
			pthread_t thread_read_block;
			pthread_create(&thread_read_block, NULL, (void*) file_system_read_write_block, args_read);
			pthread_detach(thread_read_block);

			break;

		case F_WRITE:
			t_read_write_block_args *args_write = malloc(sizeof(t_read_write_block_args));
			args_write->pcb = pcb;
			args_write->contexto = inicializar_contexto();

			duplicar_contexto(args_write->contexto,contexto_actualizado);

			archivo_abierto_t* archivo_abierto_pcb_write = buscar_archivo_abierto_t(pcb->tabla_archivos_abiertos, contexto_actualizado->param1);

			log_info(logger, "PID: %d - Escribir  Archivo: %s - Puntero %d - Dirección Memoria %s - Tamaño %s", pcb->pid, contexto_actualizado->param1, archivo_abierto_pcb_write->posicion_puntero, contexto_actualizado->param2, contexto_actualizado->param3);
			log_info(logger,"PID: %d - Bloqueado por: %s",pcb->pid, contexto_actualizado->param1);
			//log_info(logger,"PID: %d - Estado Anterior: PCB_EXEC - Estado Actual: PCB_BLOCK - Razon: F_WRITE",pcb->pid);
			pthread_t thread_write_block;
			pthread_create(&thread_write_block, NULL, (void*) file_system_read_write_block, args_write);
			pthread_detach(thread_write_block);

			break;

		case PRINT_FILE_DATA:
			{
				t_instruc_file* instruccion = inicializar_instruc_file();
				char* puntero = string_new();
				string_append(&puntero,"");
				copiar_instruccion_file(instruccion,contexto_actualizado,puntero);
				serializar_instruccion_file(file_system_connection, instruccion);
				enviar_contexto(pcb);
			}
			break;
		case PRINT_FILE_STATE:
			imprimir_tabla_archivos();
			enviar_contexto(pcb);
			break;
		case CREATE_SEGMENT:
			//log_info(logger, "PID: %d - Comunicacion con MEMORIA", pcb->pid);
			create_segment(contexto_actualizado,pcb);
			break;

		case DELETE_SEGMENT:
			log_info(logger,"PID: %d - Eliminar Segmento - Id Segmento: %s", contexto->pid, contexto->param1);
			delete_segment(contexto_actualizado,pcb);
			solicitar_tabla_segmentos();
			enviar_contexto(pcb);
			break;
		case PRINT_SEGMENTS:
			{
				log_info(logger, "PID: %d - Comunicacion con MEMORIA", pcb->pid);
				t_instruc_mem* instruccion = inicializar_instruc_mem();
				instruccion->pid = pcb->pid;
				copiar_instruccion_mem(instruccion,contexto_actualizado);
				serializar_instruccion_memoria(memoria_connection, instruccion);
				imprimir_tabla_segmentos();
			}
			enviar_contexto(pcb);
			break;
		case PRINT_MEMORY_DATA:
			{
				log_info(logger, "PID: %d - Comunicacion con MEMORIA", pcb->pid);
				t_instruc_mem* instruccion = inicializar_instruc_mem();
				instruccion->pid = pcb->pid;
				copiar_instruccion_mem(instruccion,contexto_actualizado);
				serializar_instruccion_memoria(memoria_connection, instruccion);
			}
			enviar_contexto(pcb);
			break;
		default:
			//aca iria logica de bloq
			break;
		}

		destruir_contexto(contexto_actualizado);
		break;

	default:
		log_error(logger, "ERROR COMUNICACION CON CPU");
		break;
	}

	destruir_contexto(contexto);
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);

	return pcb->estado_exec;
}
