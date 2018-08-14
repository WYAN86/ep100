#ifndef __ANGLE_H
#define __ANGLE_H

#include "stm32f10x.h"
#include "IQmathLib.h"

#include "motor_parameter.h"
#include "parameter.h"

typedef struct 
{
     s16 ElecTheta;
     s32 CalibrateAngle;
     s16 Uvw;
     u16 QepCnt;
     s32 ThetaRaw;
     u16 pst[2];
     s16 PstInc;
     u32 LineEncoder;
     u32 MechScaler;
     _iq ElecAngle;
     s32 PstFdb;
     u16 Pole;
} angle;

extern angle angle_parameter;

void angle_init(angle *p);                                              
void angle_calc(angle *p);
void angle_calibrate(angle *p);




           
#endif 




