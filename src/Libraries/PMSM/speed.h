#ifndef __SPEED_H
#define __SPEED_H

#include "stm32f10x.h"
#include "IQmathLib.h"

#include "system_parameter.h"
#include "angle.h"

typedef struct
{
     u16    Qepcnt_new;      
     u16    Qepcnt_old;       
     s16    Qepcnt_deta;  
     _iq    speed;
} speed;

typedef struct
{
     u16    Qepcnt_new;      
     u16    Qepcnt_old;     
     s16    Qepcnt_deta;      
     s32    speed_view;
     s32    speed_view_after_filter;
     //u8     over_speed_err;
     s32    speed_view_add;
     s32    speed_view_delay;
} speed_view;


typedef speed *speed_handle;


// speed
extern speed speed_parameter;
extern speed_view speed_view_parameter;



void speed_calc(speed *p);
void speed_view_calc(speed_view *p);



           
#endif 