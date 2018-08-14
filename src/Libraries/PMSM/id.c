#include "id.h"

id id_parameter;

void id_verify(id *v)
{
     v->id_read1 = *(vu32*)(0x1FFFF7E8);
     v->id_read2 = *(vu32*)(0x1FFFF7EC);
     v->id_read3 = *(vu32*)(0x1FFFF7F0);
     
     if( (v->id_set1 != v->id_read1) || (v->id_set2 != v->id_read2) || (v->id_set2 != v->id_read2) )
     {
          while(1)
          {
               led_write( CH452_DIG5 | 0x79 );
               led_write( CH452_DIG4 | 0x50 );
               led_write( CH452_DIG3 | 0x50 );
               led_write( CH452_DIG2 | 0x00 );
               led_write( CH452_DIG1 | 0x4F );
               led_write( CH452_DIG0 | 0x4F );
          }          
     }
}

