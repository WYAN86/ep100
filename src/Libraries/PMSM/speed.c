#include "speed.h"

speed speed_parameter;
speed_view speed_view_parameter;
speed_view speed_view_parameter1;



void speed_calc(speed *p)
{
     p->Qepcnt_deta = p->Qepcnt_old - p->Qepcnt_new;
     
     if( abs(p->Qepcnt_deta) > 400)
     {
          p->Qepcnt_deta = 0;
     }
     
     p->Qepcnt_old = p->Qepcnt_new;
     
     // 速度转换成rad/s
     //p->speed = p->Qepcnt_deta * _IQ20( (float)SPEED_LOOP_FREQ*2*3.14/angle_parameter.LineEncoder );
     p->speed = p->Qepcnt_deta * SPEED_CALC_FACTOR;
}

void speed_view_calc(speed_view *p)
{
     p->Qepcnt_deta = p->Qepcnt_old - p->Qepcnt_new;
     
     p->Qepcnt_old = p->Qepcnt_new;
     
     // 速度转换成rpm
     //p->speed_view = p->Qepcnt_deta * (PWM_FREQ*60/angle_parameter.LineEncoder);
     p->speed_view = p->Qepcnt_deta * SPEED_VIEW_CALC_FACTOR;
     
     p->speed_view_delay++;
     if(p->speed_view_delay <= 256)
     {
          p->speed_view_add += p->speed_view;
     }
     else
     {
          p->speed_view_delay = 0;
          p->speed_view_after_filter = p->speed_view_add/256;
          p->speed_view_add = 0;
     }
     
     //p->speed_view_after_filter = (28*p->speed_view + 100*(p->speed_view_after_filter))/128;
}

