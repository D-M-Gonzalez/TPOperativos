#include "../../../includes/code_reader.h"

int ejecutar_cmp(uint32_t pid, char* param1, char* param2){
	log_info(logger, "PID: %d - Ejecutando CMP - [%s %s]", pid, param1, param2);
	log_info(logger, "PID: %d - Valores - [%s %s]", pid, seleccionar_registro(param1), seleccionar_registro(param2));

	int comp = strcmp(seleccionar_registro(param1),seleccionar_registro(param2));

	if(comp == 0){
		ZF = 1;
		CF = 0;
	}
	else if(comp < 0){
		ZF = 0;
		CF = 1;
	} else {
		ZF = 0;
		CF = 0;
	}

	ip++;

	return 0;
}
