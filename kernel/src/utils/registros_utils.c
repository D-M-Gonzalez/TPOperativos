#include "../../includes/utils.h"

t_registros* inicializar_registros()
{
	t_registros *registros = malloc(sizeof(t_registros));

	registros->ip = 0;
	memcpy(registros->ax, "0000", (sizeof(char) * 5));
	memcpy(registros->bx, "0000", (sizeof(char) * 5));
	memcpy(registros->cx, "0000", (sizeof(char) * 5));
	memcpy(registros->dx, "0000", (sizeof(char) * 5));
	memcpy(registros->eax, "00000000", (sizeof(char) * 9));
	memcpy(registros->ebx, "00000000", (sizeof(char) * 9));
	memcpy(registros->ecx, "00000000", (sizeof(char) * 9));
	memcpy(registros->edx, "00000000", (sizeof(char) * 9));
	memcpy(registros->rax, "0000000000000000", (sizeof(char) * 17));
	memcpy(registros->rbx, "0000000000000000", (sizeof(char) * 17));
	memcpy(registros->rcx, "0000000000000000", (sizeof(char) * 17));
	memcpy(registros->rdx, "0000000000000000", (sizeof(char) * 17));

	return registros;
}

void copiar_registros(t_registros *to_registros, t_registros *from_registros)
{
	to_registros->ip = from_registros->ip;
	copiar_string(from_registros->ax, to_registros->ax);
	copiar_string(from_registros->bx, to_registros->bx);
	copiar_string(from_registros->cx, to_registros->cx);
	copiar_string(from_registros->dx, to_registros->dx);
	copiar_string(from_registros->eax, to_registros->eax);
	copiar_string(from_registros->ebx, to_registros->ebx);
	copiar_string(from_registros->ecx, to_registros->ecx);
	copiar_string(from_registros->edx, to_registros->edx);
	copiar_string(from_registros->rax, to_registros->rax);
	copiar_string(from_registros->rbx, to_registros->rbx);
	copiar_string(from_registros->rcx, to_registros->rcx);
	copiar_string(from_registros->rdx, to_registros->rdx);
}
