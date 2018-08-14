#ifndef __RAMPGEN_H
#define __RAMPGEN_H

#include "stm32f10x.h"
#include "IQmathLib.h"

typedef struct
{
  _iq  Freq;          
  _iq  StepAngleMax;  
  _iq  Angle;         
  _iq  Gain;          
  _iq  Out;  	     
  _iq  Offset;        
} rampgen;

typedef rampgen *rampgen_handle;

#define rampgen_default {0,0,0,_IQ(1),0,0}

extern rampgen rampgen_parameter;

void rampgen_calc(rampgen_handle);

#endif