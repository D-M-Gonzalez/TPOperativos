#include "../../../includes/code_reader.h"

int ejecutar_jz(uint32_t pid, char* param1){
	log_info(logger, "PID: %d - Ejecutando JZ - [%s]", pid, param1);

	int new_ip = atoi(param1);

	if(ZF == 1)ip = new_ip;
	else ip++;

	return 0;
}
