#ifndef __ADC_H
#define __ADC_H


#include "stm32f10x.h"
#include "IQmathLib.h"
#include "gpio_conf.h"


typedef struct
{
     _iq  ImeasA;
     _iq  ImeasB;
     _iq  U;
     _iq  V;
     _iq  W;
     //u32  Over_Current_Cnt;    // 过流计算变量
     //u32  Over_Load_Cnt;       // 过负载计数变量
     //u32  Over_Heat_Cnt;       // 过热计算变量
     //u8   Over_Current_Err;    // 过流错误标志
     //u8   Over_Load_Err;       // 过负载错误标志
     //u8   Over_Heat_Err;       // 过热错误标志
     u16  Offset_OK;           // 电压偏置读取完成标志
     _iq  PhaseAOffset;
     _iq  PhaseBOffset;
     s32  ImeasAAcc;
     s32  ImeasBAcc;
}phase_current;

typedef struct
{
     _iq15  ImeasAS;
     u16    Offset_OK;
     _iq15  ASOffset;
     s32    ASAcc;
}as;

#define as_default {0, 0, 0, 0}

#define phase_current_default {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

extern phase_current phase_current_parameter;
extern as as_parameter;

void phase_current_conf(void);
void phase_current_read(phase_current *v);
void as_read(as *v);


#endif