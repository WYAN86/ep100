#ifndef __MUL_MOD64_H
#define __MUL_MOD64_H

#include "stm32f10x.h"

typedef struct
{
     // ----------�����ź�---------
     u32  xh;
     u32  xl;
     u32  xs; //0Ϊ�� 1Ϊ��
     u32  y;
     u32  zh;
     u32  zl;
     u32  zs; //0Ϊ�� 1Ϊ��
} mul_mod64 ;

typedef struct
{
     // ----------�����ź�---------
     u32  xh;
     u32  xl;
     u32  xs; //0Ϊ�� 1Ϊ��
     u32  yh;
     u32  yl;
     u32  ys; //0Ϊ�� 1Ϊ��
     u32  y;
     u32  zh;
     u32  zl;
     u32  zs; //0Ϊ�� 1Ϊ��
} add_sub64 ;



#endif
