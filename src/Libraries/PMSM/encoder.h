#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h"
#include "gpio_conf.h"


void encoder_config(void);
u8   encoder_uvw_read(void);
u16  encoder_counter_read(void);


#endif