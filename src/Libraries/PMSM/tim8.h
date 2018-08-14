#ifndef __TIM8_H
#define __TIM8_H

#include "stm32f10x.h"
#include "system_parameter.h"
#include "gpio_conf.h"


typedef struct
{
     s16 MfuncC1;        // Input: PWM 1&2 Duty cycle ratio (Q15)
     s16 MfuncC2;        // Input: PWM 3&4 Duty cycle ratio (Q15) 
     s16 MfuncC3;        // Input: PWM 5&6 Duty cycle ratio (Q15)
} tim8_pwm;

#define pwm_default {0, 0, 0}

extern tim8_pwm tim8_pwm_parameter;

void tim8_pwm_update(tim8_pwm *p);
void tim8_conf(void);

#endif