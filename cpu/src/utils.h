#ifndef UTILS_H_
#define UTILS_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

t_log* iniciar_logger(void);
t_config* iniciar_config(void);
#endif /* CLIENT_H_ */