#include "../../../includes/code_reader.h"

int ejecutar_ip(uint32_t pid, char* param1){
	log_info(logger, "PID: %d - Ejecutando IP - [%s]", pid, param1);

	int new_ip = atoi(param1);

	ip = new_ip;

	return 0;
}
