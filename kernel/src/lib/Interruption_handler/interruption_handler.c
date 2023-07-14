#include "../../../includes/interruption_handler.h"

contexto_estado_t resumir_ejecucion(pcb_t* pcb){
	t_contexto *contexto = obtener_contexto_pcb(pcb);

	switch(pcb->estado_exec){
		case WAIT:
			enviar_contexto(pcb);
			break;
		case F_OPEN:
			manejar_archivo(contexto,pcb);
			enviar_contexto(pcb);
			break;
		default:
			break;
	}

	destruir_contexto(contexto);

	return pcb->estado_exec;
}
