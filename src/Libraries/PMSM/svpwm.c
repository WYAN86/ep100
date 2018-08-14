#include "svpwm.h"



svpwm svpwm_parameter = svpwm_default;

void svpwm_calc(svpwm *v)
{
     _iq Va,Vb,Vc,t1,t2,tmp;
     
     u32 Sector = 0;  

     
     Va = v->Ubeta;
     Vb = _IQmpy(IQ_F_1_DIV_2,v->Ubeta) + _IQmpy(IQ_Z_SQRT3_DIV_2,v->Ualpha);
     Vc = _IQmpy(IQ_F_1_DIV_2,v->Ubeta) + _IQmpy(IQ_F_SQRT3_DIV_2,v->Ualpha);
     
     
     if (Va>_IQ(0))
     {
          Sector = 1;
     }
     
     if (Vb>_IQ(0))
     {
          Sector = Sector + 2;
     }
     
     if (Vc>_IQ(0))
     {
          Sector = Sector + 4;
     }
     
     
     Va = v->Ubeta;                                                            
     Vb = _IQmpy(IQ_Z_1_DIV_2,v->Ubeta) + _IQmpy(IQ_Z_SQRT3_DIV_2,v->Ualpha);   
     Vc = _IQmpy(IQ_Z_1_DIV_2,v->Ubeta) - _IQmpy(IQ_Z_SQRT3_DIV_2,v->Ualpha);  
     
     if (Sector==0)  
     {
          
          v->Ta = IQ_Z_1_DIV_2;
          v->Tb = IQ_Z_1_DIV_2;
          v->Tc = IQ_Z_1_DIV_2;
     }
     if (Sector==1)  
     {
          
          t1 = Vc;
          t2 = Vb;
          tmp = t1 + t2;
          if( tmp > IQ_Z_1 )
          {
               t1 = _IQdiv( t1, tmp );
               t2 = _IQdiv( t2, tmp );
          }
          v->Tb = _IQmpy(IQ_Z_1_DIV_2,(IQ_Z_1-t1-t2));      
          v->Ta = v->Tb+t1;                             
          v->Tc = v->Ta+t2;                             
     }
     else if (Sector==2)  
     {
          
          t1 = Vb;
          t2 = -Va;
          tmp = t1 + t2;
          if( tmp > IQ_Z_1 )
          {
               t1 = _IQdiv( t1, tmp );
               t2 = _IQdiv( t2, tmp );
          }
          v->Ta = _IQmpy(IQ_Z_1_DIV_2,(IQ_Z_1-t1-t2));      
          v->Tc = v->Ta+t1;                             
          v->Tb = v->Tc+t2;                             
     }  
     else if (Sector==3)  
     {
          
          
          
          t1 = -Vc;
          t2 = Va;
          tmp = t1 + t2;
          if( tmp > IQ_Z_1 )
          {
               t1 = _IQdiv( t1, tmp );
               t2 = _IQdiv( t2, tmp );
          }
          v->Ta = _IQmpy(IQ_Z_1_DIV_2,(IQ_Z_1-t1-t2));      
          v->Tb = v->Ta+t1;                             
          v->Tc = v->Tb+t2;                             
     }  
     else if (Sector==4)  
     {
          
          t1 = -Va;
          t2 = Vc;
          tmp = t1 + t2;
          if( tmp > IQ_Z_1 )
          {
               t1 = _IQdiv( t1, tmp );
               t2 = _IQdiv( t2, tmp );
          }
          v->Tc = _IQmpy(IQ_Z_1_DIV_2,(IQ_Z_1-t1-t2));      
          v->Tb = v->Tc+t1;                             
          v->Ta = v->Tb+t2;                             
     }
     else if (Sector==5)  
     {
          
          t1 = Va;
          t2 = -Vb;
          tmp = t1 + t2;
          if( tmp > IQ_Z_1 )
          {
               t1 = _IQdiv( t1, tmp );
               t2 = _IQdiv( t2, tmp );
          }
          v->Tb = _IQmpy(IQ_Z_1_DIV_2,(IQ_Z_1-t1-t2));      
          v->Tc = v->Tb+t1;                             
          v->Ta = v->Tc+t2;                             
     }   
     else if (Sector==6)  
     {
          
          t1 = -Vb;
          t2 = -Vc;
          tmp = t1 + t2;
          if( tmp > IQ_Z_1 )
          {
               t1 = _IQdiv( t1, tmp );
               t2 = _IQdiv( t2, tmp );
          }
          v->Tc = _IQmpy(IQ_Z_1_DIV_2,(IQ_Z_1-t1-t2));     
          v->Ta = v->Tc+t1;                             
          v->Tb = v->Ta+t2;                             
     }
     
     if(v->Ta<0)
     {
          v->Ta = 0;
     }
     else if(v->Ta>IQ_Z_1)
     {
          v->Ta = IQ_Z_1;
     }
     
     if(v->Tb<0)
     {
          v->Tb = 0;
     }
     else if(v->Tb>IQ_Z_1)
     {
          v->Tb = IQ_Z_1;
     }
     
     if(v->Tc<0)
     {
          v->Tc = 0;
     }
     else if(v->Tc>IQ_Z_1)
     {
          v->Tc = IQ_Z_1;
     }     
     
   
}