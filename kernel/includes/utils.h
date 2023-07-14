#ifndef UTILS_H_
#define UTILS_H_

#include "../../shared/includes/tad.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>
#include <commons/collections/list.h>
#include <pthread.h>

#include "general_planification_utils.h"
#include "comm_Mem.h"
#include "file_utils.h"

extern t_lista_mutex* lista_tabla_segmentos;
extern int memoria_connection;
extern t_lista_mutex* lista_tabla_segmentos;
extern t_list* tabla_global_archivos_abiertos;
extern t_lista_mutex* lista_recursos;

//general_utils
void copiar_string(char *origen, char *destino);
char* copiar_char_puntero(const char *param);
char* armar_lista_pids(t_list* lista);
void destroy_proceso(pcb_t* proceso);
void imprimir_recursos(pcb_t* pcb);

//init_utils
t_log* iniciar_logger(void);
t_config* iniciar_config(char * path_config);
t_lista_mutex* init_list_mutex();

//mutex_utils
void list_push(t_lista_mutex * list , void* info);
void * list_pop(t_lista_mutex * list);
void list_mutex_destroy(t_lista_mutex * list);
bool list_mutex_is_empty(t_lista_mutex * list);
int list_mutex_size(t_lista_mutex * list);
void* list_mutex_get(t_lista_mutex *list, int index);

//contexto_utils
t_contexto* inicializar_contexto();
void duplicar_contexto(t_contexto* contexto_destino, t_contexto* contexto_origen);
void destruir_contexto(t_contexto* contexto);

//recursos_utils
char* crear_recurso(const char *nombre_recurso);
t_recurso* buscar_recurso(t_lista_mutex*lista_recursos, const char *nombre_recurso);
bool recurso_existe_en_lista(t_lista_mutex* lista_recursos, const char* nombre_recurso);
void restar_instancia(t_lista_mutex* lista_recursos, const char *nombre_recurso);
void sumar_instancia(t_lista_mutex* lista_recursos, const char *nombre_recurso);
int obtener_instancias(t_lista_mutex* lista_recurso, const char* nombre_recurso);
void asignar_recurso(pcb_t *pcb, const char *nombre_recurso);
void desasignar_recurso_si_lo_tiene_asignado(pcb_t *pcb, const char* nombre_recurso);
void devolver_instancias(pcb_t* pcb, t_lista_mutex *lista_recursos);
void liberar_proceso_de_bloqueados_si_necesario(const char* recurso, int instancias_recurso);

//instruc_utils
t_instruc_file* inicializar_instruc_file();
t_instruc_mem* inicializar_instruc_mem();
void copiar_instruccion_mem(t_instruc_mem* instruccion, t_contexto* contexto);
t_list* copiar_lista_instrucciones(t_list* nueva_lista, t_list* lista_instrucciones);
void copiar_instruccion_mem(t_instruc_mem* instruccion, t_contexto* contexto);
void instrucciones_destroy(t_instruc* instruccion);
void destruir_instruc_mem(t_instruc_mem* instruccion);
void destruir_instruc_file(t_instruc_file* instruccion);

//registros_utils
t_registros* inicializar_registros(void);
void copiar_registros(t_registros* to_registros, t_registros* from_registros);

//segmentos_utils
void eliminar_tabla_segmentos(pcb_t* proceso);
void copiar_tabla_segmentos(tabla_segmentos_t* tabla_contexto,tabla_segmentos_t* tabla_pcb);
tabla_segmentos_t* buscar_tabla_segmentos(t_list* lista_tablas, int pid);
bool existe_tabla_segmentos(t_list* lista_tablas, int pid);
tabla_segmentos_t* solicitar_segmento_0(int pid);
void delete_segment(t_contexto* contexto, pcb_t* pcb);
void imprimir_tabla_segmentos();
void duplicar_tabla_segmentos(tabla_segmentos_t* tabla_origen, tabla_segmentos_t* tabla_destino);

//archivos_utils
char* buscar_archivo(t_list *tabla_archivos_abiertos, const char *nombre_archivo);
bool archivo_existe_en_tabla(t_list *tabla_archivos_abiertos, const char *nombre_archivo);
archivo_abierto_t* buscar_archivo_abierto_t (t_list *tabla_archivos_abiertos, const char *nombre_archivo);
void eliminar_archivo_abierto_t(t_list *tabla_archivos_abiertos, const char *nombre_archivo);
void imprimir_tabla_archivos();

#endif /* CLIENT_H_ */
