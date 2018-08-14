#ifndef __CURVE_H__
#define __CURVE_H__

#include "stm32f10x.h"
#include "IQmathLib.h"

typedef struct 
{  
          s32  Obj_position;   			
          s32  Act_position;   			
          _iq  P_Obj_speed;				
          _iq  N_Obj_speed;				
          _iq  Act_speed;
          _iq  Acc;
          _iq  detaT;				 
          s16  TcurStepIncrement;   			
          s16  flag;
} curve;	            

typedef curve *curve_handle;
                    
#define curve_default {0, 0, 0, 0, 0, 0, 0, 0, 0}

extern curve curve_parameter;

void curve_calc(curve *p);
void  curve_init(curve *p);

#endif 
