#include "rampctrl.h"


rampctrl rampctrl_parameter;


void rampctrl_calc(rampctrl *v)
{
          _iq tmp;
          
          tmp = v->TargetValue - v->SetpointValue;
          
          if(tmp>=0 && v->acc_zero_flag==1)
          {
                v->SetpointValue=v->TargetValue;
                v->EqualFlag = 1;
          }
          else if (tmp >= v->acc_dt)
          {
               v->EqualFlag = 0;
               if (v->TargetValue >= v->SetpointValue)
               {
                    v->SetpointValue += v->acc_dt;       
                    if (v->SetpointValue > v->RampHighLimit)
                    {
                         v->SetpointValue = v->RampHighLimit;   
                    }
               }
          }
          else  if(tmp>=0)
          {
               v->EqualFlag = 1;
          }
          
          
          if(tmp<0 && v->deacc_zero_flag==1)
          {
                v->SetpointValue=v->TargetValue;
                v->EqualFlag = 1;
          }
          else if (tmp <= v->deacc_dt)
          {
               v->EqualFlag = 0;
               if (v->TargetValue <= v->SetpointValue)
               {
                    v->SetpointValue += v->deacc_dt;       
                    if (v->SetpointValue < v->RampLowLimit)
                    {
                         v->SetpointValue = v->RampLowLimit;
                    }
               }
          }
          else   if(tmp<0)
          {
               v->EqualFlag = 1;
          }
}

