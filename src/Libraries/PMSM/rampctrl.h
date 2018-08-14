#ifndef __RAMPCTRL_H
#define __RAMPCTRL_H

#include "stm32f10x.h"
#include "IQmathLib.h"


typedef struct
{
  _iq    TargetValue; 	
  u32 RampDelayMax;	    			
  _iq    RampLowLimit;					  
  _iq    RampHighLimit;	
  u32 RampDelayCount;    
  _iq    SetpointValue;			 
  u32 EqualFlag;		
  _iq acc_dt;           
  _iq deacc_dt;       
  u16 acc_zero_flag;
  u16 deacc_zero_flag;
} rampctrl;	            


            

extern rampctrl rampctrl_parameter;

void rampctrl_calc(rampctrl *v);


#endif