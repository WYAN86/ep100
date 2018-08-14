#ifndef __SVPWM_H
#define __SVPWM_H

#include "stm32f10x.h"
#include "IQmathLib.h"
#include "system_parameter.h"


typedef struct
{
     _iq  Ualpha; 			
     _iq  Ubeta;			
     _iq  Ta;				
     _iq  Tb;			
     _iq  Tc;			
} svpwm;

typedef svpwm *svpwm_handle;

#define svpwm_default {0,0,0,0,0}

extern svpwm svpwm_parameter;

void svpwm_calc(svpwm *v);
void over_modu_calc(svpwm *v);

#endif