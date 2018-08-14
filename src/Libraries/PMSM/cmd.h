#ifndef __CMD_H
#define __CMD_H

#include "stm32f10x.h"
#include "gpio_conf.h"
#include "parameter.h"

void cmd_quadrature_config(void);
void cmd_plus_sign_config(void);
void cmd_plus_plus_config(void);
void cmd_config_init(void);
u16 cmd_read(void);

#endif