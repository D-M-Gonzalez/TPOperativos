#include "../../../includes/code_reader.h"

int ejecutar_inc(uint32_t pid, char* param1, char* param2){
	int valor = atoi(param2);

	log_info(logger, "PID: %d - Ejecutando INC - [%s %d]", pid, param1, valor);

	incrementar_registro(seleccionar_registro(param1),valor);

	ip++;

	return 0;
}

void incrementar_registro(char* registro, int valor){
	int valor_registro = atoi(registro);
	valor_registro += valor;
	int largo_registro = strlen(registro);
	char* valor_string = malloc(largo_registro);
	sprintf(valor_string,"%d",valor_registro);
	int largo_valor = strlen(valor_string);

	for(int i = 0; i<largo_valor; i++){
		registro[largo_registro - largo_valor + i] = valor_string[i];
	}

	free(valor_string);
}
