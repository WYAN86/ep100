#include "svpwm.h"

void over_modu_calc(svpwm *v)
{
     
     _iq Va,Vb,Vc,t1,t2,tmp,tmp1,tmp2;
     
     u32 Sector = 0;  

 u32  Mode = 0;
 _iq alphar = 0;
 _iq alphah = 0;
 _iq VM = 0;
 _iq Ualpha_tmp = 0;
 _iq Ubeta_tmp  = 0;
//_iq Va = 0;
//_iq Vb = 0;
//_iq Vc = 0;
//_iq tsum = 0;
//_iq t1 = 0;
//_iq t2 = 0;
//_iq t1_tmp = 0;
//_iq t2_tmp = 0;
 _iq TM = 1; 
//_iq Ta = 0;
//_iq Tb = 0;
//_iq Tc = 0;
 
 
 _iq V = 0;
 
 _iq M = 0;
     
 
 //V = sqrt(Ualpha*Ualpha + Ubeta*Ubeta);
      tmp1 =_IQmpy(v->Ualpha, v->Ualpha ) + _IQmpy(v->Ubeta, v->Ubeta ) ;
      V = _IQsqrt(tmp1);
      
//M = (V/sqrt(3)) / (2/pi);
     M = _IQmpy( V, _IQ_PM);

/* 
if ( M<=0.9068 )
     Mode = 0;
 elseif ( M>0.9068 && M<=0.9517 )
     Mode = 1;
 elseif ( M>0.9517 && M<=1)
     Mode = 2;
 else
     Mode = 2;
     M = 0.9999;
 end
*/
      
if ( M<=_IQ_Z_0_DOT_9068 )
{
     Mode = 0;
}
else if ( (M>_IQ_Z_0_DOT_9068) && (M<=_IQ_Z_0_DOT_9517) )
{
     Mode = 1;
}
else if ( (M>_IQ_Z_0_DOT_9517) && (M<=IQ_Z_1))
{
     Mode = 2;
}
else
{
     Mode = 2;
     M = _IQ_Z_0_DOT_9999;
}
      
 /*
 if (Mode == 1)
     if( M>=0.9068 && M<0.9095 )
         alphar = -30.23*M + 27.94;
     elseif( M>=0.9095 && M<0.9485 )
         alphar = -8.58*M + 8.23;
     elseif( M>=0.9485 && M<0.9517 )
         alphar = -26.43*M + 25.15;
     end
 elseif (Mode == 2)
     if( M>=0.9517 && M<0.9800 )
         alphah = 6.40*M - 6.09;
     elseif( M>=0.9800 && M<0.9975 )
         alphah = 11.75*M - 11.34;
     elseif( M>=0.9975 && M<1 )
         alphah = 48.96*M - 48.43;
     end
     if(alphah<0)
         alphah = 0;
     elseif(alphah>pi/6)
         alphah = pi/6;
     end
 end*/
 
 if (Mode == 1)
 {
     if( (M>=_IQ_Z_0_DOT_9068) && (M < _IQ_Z_0_DOT_9095) )
     {
         alphar = _IQmpy(_IQ_F_30_DOT_23, M) + _IQ_Z_27_DOT_94;
     }
     else if( (M>=_IQ_Z_0_DOT_9095) && (M<_IQ_Z_0_DOT_9485) )
     {
         alphar = _IQmpy(_IQ_F_8_DOT_58, M) + _IQ_Z_8_DOT_23;
     }
     else if( (M>=_IQ_Z_0_DOT_9485) && (M<_IQ_Z_0_DOT_9517) )
     {
         alphar = _IQmpy(_IQ_F_26_DOT_43, M) + _IQ_Z_25_DOT_15;
     }
 }     
 else if (Mode == 2)
 {
     if( (M>=_IQ_Z_0_DOT_9517) && (M<_IQ_Z_0_DOT_9800) )
     {
         alphah = _IQmpy(_IQ_Z_6_DOT_40, M) - _IQ_Z_6_DOT_09;
     }
     else if( (M>=_IQ_Z_0_DOT_9800) && (M<_IQ_Z_0_DOT_9975) )
     {
         alphah = _IQmpy(_IQ_Z_11_DOT_75,M) - _IQ_Z_11_DOT_34;
     }
     else if( (M>=_IQ_Z_0_DOT_9975) && (M<IQ_Z_1) )
     {
         alphah = _IQmpy(_IQ_Z_48_DOT_96,M) - _IQ_Z_48_DOT_43;
     }
     if(alphah<0)
     {
         alphah = 0;
     }
     else if( alphah>_IQ_Z_pi_div_6 )
     {
         alphah = _IQ_Z_pi_div_6;
     }
}
 
     
     
if(Mode == 0)
{
     Sector = 0;  

     
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
else if(Mode == 1)
{
/*
     VM = 1/cos(pi/6-alphar);
     Ualpha_tmp = Ualpha * VM / V;
     Ubeta_tmp  = Ubeta  * VM / V;
     */
     
     tmp1 = _IQ_Z_pi_div_6 - alphar;
     tmp2 = _IQcos(tmp1);
     VM = _IQdiv(IQ_Z_1, tmp2);
          
     tmp1 = _IQmpy(v->Ualpha,VM);
     Ualpha_tmp = _IQdiv(tmp1,V);
     
     tmp1 = _IQmpy(v->Ubeta,VM);
     Ubeta_tmp  = _IQdiv(tmp1,V);

     /*
     Va = Ubeta_tmp;
     Vb = (-0.5) * Ubeta_tmp + 0.8660254 * Ualpha_tmp;
     Vc = (-0.5) * Ubeta_tmp - 0.8660254 * Ualpha_tmp;
     */
     
     Va = Ubeta_tmp;
     Vb = _IQmpy(IQ_F_1_DIV_2,Ubeta_tmp) + _IQmpy(IQ_Z_SQRT3_DIV_2,Ualpha_tmp);
     Vc = _IQmpy(IQ_F_1_DIV_2,Ubeta_tmp) + _IQmpy(IQ_F_SQRT3_DIV_2,Ualpha_tmp);
     
     
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
     
     
     Va = Ubeta_tmp;                                                            
     Vb = _IQmpy(IQ_Z_1_DIV_2,Ubeta_tmp) + _IQmpy(IQ_Z_SQRT3_DIV_2,Ualpha_tmp);   
     Vc = _IQmpy(IQ_Z_1_DIV_2,Ubeta_tmp) - _IQmpy(IQ_Z_SQRT3_DIV_2,Ualpha_tmp);  
     
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
     

else if(Mode == 2)
{
/*
     VM = 2/sqrt(3);
     TM = ( sqrt(3)/2*cos(alphah) - sin(alphah)/2 ) / ( sqrt(3)/2*cos(alphah) + sin(alphah)/2 );
     Ualpha_tmp = Ualpha * VM / V;
     Ubeta_tmp  = Ubeta  * VM / V;
     */
     
     VM = _IQ_Z_2_div_sqrt3;
     
     tmp1 = _IQmpy(IQ_Z_SQRT3_DIV_2, _IQcos(alphah)) - _IQsin(alphah)/2;
     tmp2 = _IQmpy(IQ_Z_SQRT3_DIV_2, _IQcos(alphah)) + _IQsin(alphah)/2;
     TM = _IQdiv(tmp1,tmp2);
     
          
     tmp1 = _IQmpy(v->Ualpha,VM);
     Ualpha_tmp = _IQdiv(tmp1,V);
     
     tmp1 = _IQmpy(v->Ubeta,VM);
     Ubeta_tmp  = _IQdiv(tmp1,V);

     /*
     Va = Ubeta_tmp;
     Vb = (-0.5) * Ubeta_tmp + 0.8660254 * Ualpha_tmp;
     Vc = (-0.5) * Ubeta_tmp - 0.8660254 * Ualpha_tmp;
     */
     
     Va = Ubeta_tmp;
     Vb = _IQmpy(IQ_F_1_DIV_2,Ubeta_tmp) + _IQmpy(IQ_Z_SQRT3_DIV_2,Ualpha_tmp);
     Vc = _IQmpy(IQ_F_1_DIV_2,Ubeta_tmp) + _IQmpy(IQ_F_SQRT3_DIV_2,Ualpha_tmp);
     
     
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
     
     
     Va = Ubeta_tmp;                                                            
     Vb = _IQmpy(IQ_Z_1_DIV_2,Ubeta_tmp) + _IQmpy(IQ_Z_SQRT3_DIV_2,Ualpha_tmp);   
     Vc = _IQmpy(IQ_Z_1_DIV_2,Ubeta_tmp) - _IQmpy(IQ_Z_SQRT3_DIV_2,Ualpha_tmp);  
     
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
         if(t1>=TM)
         {
             t1 = IQ_Z_1;
             t2 = 0;
         }
         else if(t2>=TM)
         {
             t2 = IQ_Z_1;
             t1 = 0;
         }
         else
         {
               tmp = t1 + t2;
               if( tmp > IQ_Z_1 )
               {
                    t1 = _IQdiv( t1, tmp );
                    t2 = _IQdiv( t2, tmp );
               }
         }
          v->Tb = _IQmpy(IQ_Z_1_DIV_2,(IQ_Z_1-t1-t2));      
          v->Ta = v->Tb+t1;                             
          v->Tc = v->Ta+t2;                             
     }
     else if (Sector==2)  
     {
          
          t1 = Vb;
          t2 = -Va;
         if(t1>=TM)
         {
             t1 = IQ_Z_1;
             t2 = 0;
         }
         else if(t2>=TM)
         {
             t2 = IQ_Z_1;
             t1 = 0;
         }
         else
         {
               tmp = t1 + t2;
               if( tmp > IQ_Z_1 )
               {
                    t1 = _IQdiv( t1, tmp );
                    t2 = _IQdiv( t2, tmp );
               }
         }
          v->Ta = _IQmpy(IQ_Z_1_DIV_2,(IQ_Z_1-t1-t2));      
          v->Tc = v->Ta+t1;                             
          v->Tb = v->Tc+t2;                             
     }  
     else if (Sector==3)  
     {
          
          
          
          t1 = -Vc;
          t2 = Va;
         if(t1>=TM)
         {
             t1 = IQ_Z_1;
             t2 = 0;
         }
         else if(t2>=TM)
         {
             t2 = IQ_Z_1;
             t1 = 0;
         }
         else
         {
               tmp = t1 + t2;
               if( tmp > IQ_Z_1 )
               {
                    t1 = _IQdiv( t1, tmp );
                    t2 = _IQdiv( t2, tmp );
               }
         }
          v->Ta = _IQmpy(IQ_Z_1_DIV_2,(IQ_Z_1-t1-t2));      
          v->Tb = v->Ta+t1;                             
          v->Tc = v->Tb+t2;                             
     }  
     else if (Sector==4)  
     {
          
          t1 = -Va;
          t2 = Vc;
         if(t1>=TM)
         {
             t1 = IQ_Z_1;
             t2 = 0;
         }
         else if(t2>=TM)
         {
             t2 = IQ_Z_1;
             t1 = 0;
         }
         else
         {
               tmp = t1 + t2;
               if( tmp > IQ_Z_1 )
               {
                    t1 = _IQdiv( t1, tmp );
                    t2 = _IQdiv( t2, tmp );
               }
         }
          v->Tc = _IQmpy(IQ_Z_1_DIV_2,(IQ_Z_1-t1-t2));      
          v->Tb = v->Tc+t1;                             
          v->Ta = v->Tb+t2;                             
     }
     else if (Sector==5)  
     {
          
          t1 = Va;
          t2 = -Vb;
         if(t1>=TM)
         {
             t1 = IQ_Z_1;
             t2 = 0;
         }
         else if(t2>=TM)
         {
             t2 = IQ_Z_1;
             t1 = 0;
         }
         else
         {
               tmp = t1 + t2;
               if( tmp > IQ_Z_1 )
               {
                    t1 = _IQdiv( t1, tmp );
                    t2 = _IQdiv( t2, tmp );
               }
         }
          v->Tb = _IQmpy(IQ_Z_1_DIV_2,(IQ_Z_1-t1-t2));      
          v->Tc = v->Tb+t1;                             
          v->Ta = v->Tc+t2;                             
     }   
     else if (Sector==6)  
     {
          
          t1 = -Vb;
          t2 = -Vc;
         if(t1>=TM)
         {
             t1 = IQ_Z_1;
             t2 = 0;
         }
         else if(t2>=TM)
         {
             t2 = IQ_Z_1;
             t1 = 0;
         }
         else
         {
               tmp = t1 + t2;
               if( tmp > IQ_Z_1 )
               {
                    t1 = _IQdiv( t1, tmp );
                    t2 = _IQdiv( t2, tmp );
               }
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