#include "curve.h"

curve curve_parameter;

void  curve_init(curve *p)
{
     p->detaT=_IQ(0.0001);  ///100us
     p->Acc=_IQ(1);
     
     p->P_Obj_speed=_IQ(0.1);
     p->N_Obj_speed=_IQ(-0.1);
     p->Obj_position=450000;
     p->flag=1;
} 

void curve_calc(curve *p)
{
     if (p->flag==1)
     {
          p->Act_speed= p->Act_speed+_IQmpy(p->Acc,p->detaT);
     }
     if (p->flag==-1)
     {
          p->Act_speed= p->Act_speed-_IQmpy(p->Acc,p->detaT);
     }
     
     if (p->Act_speed>=p->P_Obj_speed)
     {
          p->Act_speed=p->P_Obj_speed;
     }
     
     if (p->Act_speed<=p->N_Obj_speed)
     {         
          p->Act_speed=p->N_Obj_speed;
     }   

     if(p->Act_position>= p->Obj_position)
     {
		p->flag=-1;
     }
     if(p->Act_position<= (- p->Obj_position))
     {
		p->flag=1;
     }
     p->TcurStepIncrement=(_IQmpy(p->Act_speed,_IQ(2000/60)))>>GLOBAL_Q;
     
     p->Act_position+=p->TcurStepIncrement;
}
