#include "pid.h"

// pid
pid pid_id;
pid pid_iq;
pid pid_id_encoder_offset;
pid pid_iq_encoder_offset;
pid pid_speed;
pid pid_pos;

feed_forward feed_forward_pos;




void pi_caculation(pid *v)
{
     // 比例
     v->Up = _IQmpy(v->Kp, v->Err);
     
     // 积分
     if(v->Saturation_flag == 0)
     {
          v->Ui = v->Ui + _IQmpy(v->Ki, v->Err);
     }
     
     // 比例+积分
     v->OutPreSat = v->Up + v->Ui;
     
     // Saturate the output
     if (v->OutPreSat > v->OutMax)
     {
          v->Saturation_flag = 1;
          v->Out =  v->OutMax;
          //v->Ui_flag = 1;
     }
     else if (v->OutPreSat < v->OutMin)
     {
          v->Saturation_flag = 1;
          v->Out =  v->OutMin;
          //v->Ui_flag = 1;
     }
     else
     {
          v->Saturation_flag = 0;
          v->Out = v->OutPreSat;
          //v->Ui_flag = 0;
     }
}