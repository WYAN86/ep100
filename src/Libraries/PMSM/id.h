#ifndef __ID_H
#define __ID_H


#include "stm32f10x.h"
#include "menu.h"

typedef struct
{
     u32  id_set1;
     u32  id_set2;
     u32  id_set3;
     u32  id_read1;
     u32  id_read2;
     u32  id_read3;
}id;

extern id id_parameter;

void id_verify(id *v);



#endif