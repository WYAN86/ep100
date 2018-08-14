#include "angle.h"



angle angle_parameter;

void angle_init(angle *p)
{
     u16 tmp;
     
     //p->MechScaler= _IQ30(DIV_CNT_PER_ROUND);             
     
     p->CalibrateAngle = motor_parameter[parameter_table[Version]].Encoder_Offset;
     
     p->LineEncoder = motor_parameter[parameter_table[Version]].LineEncoder;
     
     p->MechScaler= _IQ30(1)/p->LineEncoder;          
     
     p->Pole = motor_parameter[parameter_table[Version]].Pole_Num;
     
     p->pst[0]=0;
     p->pst[1]=0;
     
     tmp = (u16) (p->LineEncoder / p->Pole / 12);
     
     switch(p->Uvw)
     {
          case 1 : p->ThetaRaw = tmp*1 + p->CalibrateAngle ; break;
          case 3 : p->ThetaRaw = tmp*3 + p->CalibrateAngle ; break;
          case 2 : p->ThetaRaw = tmp*5 + p->CalibrateAngle ; break;
          case 6 : p->ThetaRaw = tmp*7 + p->CalibrateAngle ; break;
          case 4 : p->ThetaRaw = tmp*9 + p->CalibrateAngle ; break;
          case 5 : p->ThetaRaw = tmp*11 + p->CalibrateAngle ; break;
          default: break;
     }
     // 要修改
     EXTI->IMR |=0x00000020;   //重新检测Z脉冲
}


void angle_calc(angle *p)
{
     s16 Tmp;
     
     p->pst[0] = p->QepCnt;
     
     p->PstInc = p->pst[1] - p->pst[0];      
     
     p->PstFdb = p->PstFdb + p->PstInc;
     
     p->ThetaRaw = p->ThetaRaw + p->PstInc;
     
     p->pst[1] = p->pst[0];
     
     if(p->ThetaRaw > ((s32) p->LineEncoder))
     {
          p->ThetaRaw = p->ThetaRaw - p->LineEncoder;
     }
     if(p->ThetaRaw < 0)
     {
          p->ThetaRaw = p->ThetaRaw +  p->LineEncoder;
     }
     
     Tmp = ( (s32) (p->MechScaler * p->ThetaRaw) ) >> 15;
     
     p->ElecTheta = ((Tmp * p->Pole) & 0x7FFF);
     
     p->ElecAngle = ( (s32) p->ElecTheta) << (GLOBAL_Q-15);
}





void angle_calibrate(angle *p)
{
     p->ThetaRaw = p->CalibrateAngle;
}