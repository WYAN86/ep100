#ifndef __MUL_MOD64_H
#define __MUL_MOD64_H

#include "stm32f10x.h"

typedef struct
{
     // ----------动板信号---------
     u32  xh;
     u32  xl;
     u32  xs; //0为负 1为正
     u32  y;
     u32  zh;
     u32  zl;
     u32  zs; //0为负 1为正
} mul_mod64 ;

typedef struct
{
     // ----------动板信号---------
     u32  xh;
     u32  xl;
     u32  xs; //0为负 1为正
     u32  yh;
     u32  yl;
     u32  ys; //0为负 1为正
     u32  y;
     u32  zh;
     u32  zl;
     u32  zs; //0为负 1为正
} add_sub64 ;



#endif
