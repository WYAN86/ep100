#include "servo_parameter.h"

//s16 *data = (s16 *)&servo_parameter;
//s16 *data_tmp =(s16*)&servo_parameter_tmp;

//extern float elc_gear;

//extern _iq over_load_current_max;
//extern s32 over_load_current_time_max;

//extern _iq interior_torque_max;
//extern _iq interior_torque_min;
//外部转矩限制
//extern _iq exterior_torque_max;
//extern _iq exterior_torque_min;
//试运行转矩限制
//extern _iq sr_torque_max;
//extern _iq sr_torque_min;

//最高速度限制
//extern _iq speed_max_iq;
//extern _iq speed_min_iq;

// 模拟速度指令
//extern u16 as_calc_factor;
//extern _iq as_compensate_factor;
/*
void control_parameter_config(void)
{
     float tmp;
     
     //--------------------加减速时间常数计算-----------------------------------
     rampctrl_parameter.RampLowLimit = -_IQ(1);
     rampctrl_parameter.RampHighLimit = _IQ(1);
     tmp = 1000.0 / motor_parameter[parameter_table[Version]].Rate_Speed;       // 1000rpm / 额定转速
     if(parameter_table[AccelerationTimeConstant]>=1)
     {
          rampctrl_parameter.acc_zero_flag=0;

          rampctrl_parameter.acc_dt = _IQ(tmp) / (SPEED_LOOP_FREQ) * 1000 / parameter_table[AccelerationTimeConstant];      //加速步长
     }
     else
     {
          rampctrl_parameter.acc_zero_flag=1;
     }
     if(parameter_table[DecelerationTimeConstant]>=1)
     {
          rampctrl_parameter.deacc_zero_flag=0;
          rampctrl_parameter.deacc_dt = -_IQ(tmp) / (SPEED_LOOP_FREQ) * 1000 / parameter_table[DecelerationTimeConstant];   //减速步长
     }
     else
     {
          rampctrl_parameter.deacc_zero_flag=1;
     }
     //--------------------加减速时间常数计算-----------------------------------
     
     
     
     //-------------------------------滤波器------------------------------------
     as_filter.FilterTs = _IQ( (1.0/(SPEED_LOOP_FREQ)) );
     as_filter.FilterTf = _IQ( ((float)parameter_table[AnalogSpeedCommandFilter]) / 100000.0);
     low_filter_init(&as_filter);
     
     speed_ref_filter.FilterTs = _IQ( (1.0/(SPEED_LOOP_FREQ)) );
     speed_ref_filter.FilterTf = _IQ( ((float)parameter_table[SpeedCheckFilter]) / 100000.0);
     low_filter_init(&speed_ref_filter);
     
     speed_fdb_filter.FilterTs = _IQ( (1.0/(SPEED_LOOP_FREQ)) );
     speed_fdb_filter.FilterTf = _IQ( ((float)parameter_table[SpeedCheckFilter]) / 100000.0);
     low_filter_init(&speed_fdb_filter);
     
     iq_ref_filter.FilterTs = _IQ( (1.0/PWM_FREQ) );
     iq_ref_filter.FilterTf = _IQ( ((float)parameter_table[TorqueFilter]) / 100000.0);
     low_filter_init(&iq_ref_filter);
     
     iq_fdb_filter.FilterTs = _IQ( (1.0/PWM_FREQ) );
     iq_fdb_filter.FilterTf = _IQ( ((float)parameter_table[TorqueFilter]) / 100000.0);
     low_filter_init(&iq_fdb_filter);
     
     id_fdb_filter.FilterTs = _IQ( (1.0/PWM_FREQ) );
     id_fdb_filter.FilterTf = _IQ( ((float)parameter_table[TorqueFilter]) / 100000.0);
     low_filter_init(&id_fdb_filter);
     //-------------------------------滤波器------------------------------------
     
     
     //-------------------------------PI参数------------------------------------
     // pid for id
     pid_id.Kp = _IQ(((float)parameter_table[CurrentGain]) / 1000.0);
     pid_id.Ki = _IQ(0.0001*1000000.0/((float)parameter_table[CurrentIntegral]));
     pid_id.Kd = _IQ(0);
     pid_id.Kc = _IQ(0);
     pid_id.OutMax = _IQ(0.3);
     pid_id.OutMin = _IQ(-0.3);
     
     // pid for iq
     pid_iq.Kp = _IQ(((float)parameter_table[CurrentGain]) / 1000.0);
     pid_iq.Ki = _IQ(0.0001*1000000.0/((float)parameter_table[CurrentIntegral]));
     pid_iq.Kd = _IQ(0);
     pid_iq.Kc = _IQ(0);
     pid_iq.OutMax = _IQ(0.95);
     pid_iq.OutMin = _IQ(-0.95);
     
     // 编码器开环获取角度偏置时的 PI
     pid_id_encoder_offset.Kp = _IQ(((float)parameter_table[CurrentGain]) / 1000.0);
     pid_id_encoder_offset.Ki = _IQ(0.0001*1000000.0/((float)parameter_table[CurrentIntegral]));
     pid_id_encoder_offset.Kd = _IQ(0);
     pid_id_encoder_offset.Kc = _IQ(0);
     pid_id_encoder_offset.OutMax = _IQ(0.5);
     pid_id_encoder_offset.OutMin = _IQ(-0.5);
     
     pid_iq_encoder_offset.Kp = _IQ(((float)parameter_table[CurrentGain]) / 1000.0);
     pid_iq_encoder_offset.Ki = _IQ(0.0001*1000000.0/((float)parameter_table[CurrentIntegral]));
     pid_iq_encoder_offset.Kd = _IQ(0);
     pid_iq_encoder_offset.Kc = _IQ(0);
     pid_iq_encoder_offset.OutMax = _IQ(0.5);
     pid_iq_encoder_offset.OutMin = _IQ(-0.5);
     
     
     // pid for speed
     pid_speed.Kp = _IQ( ((float)parameter_table[SpeedGain]) / 100.0);
     pid_speed.Ki = _IQ(0.0005*1000000.0/((float)parameter_table[SpeedIntegral]) );
     pid_speed.Kd = _IQ(0);
     pid_speed.Kc = _IQ(0);
     pid_speed.OutMax = _IQ(0.95);
     pid_speed.OutMin = _IQ(-0.95);
     
     
     // feedforward for position
     feed_forward_pos.Kp  =  _IQ( ((float)parameter_table[PositionGain]) / 1000000.0);
     feed_forward_pos.Kaf =  _IQ( ((float)parameter_table[PositionFeedforwardGain]) / 1000000.0);
     feed_forward_pos.Ki  =  _IQ(0);
     feed_forward_pos.Kd  =  _IQ(0);
     feed_forward_pos.OutMax = _IQ(1);
     feed_forward_pos.OutMin = _IQ(-1);
     //-------------------------------PI参数------------------------------------
}
*/