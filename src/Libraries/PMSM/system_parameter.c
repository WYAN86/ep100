#include "system_parameter.h"

// 定时器计数周期
u16 PWM_PERIOD_FACTOR = 0;

// 速度指令计算因子
float SPEED_COMMAND_FACTOR = 0;
// 速度计算因子
s32 SPEED_CALC_FACTOR = 0;
// 速度观测计算因子
s32 SPEED_VIEW_CALC_FACTOR = 0;
// 单位速度 rad/s
u16 SPEED_UNIT_FACTOR = 0;
// 最大转速
_iq SPEED_MAX_FACTOR = 0;
_iq SPEED_MIN_FACTOR = 0;
// 模拟速度指令计算因子
u16 AS_CALC_FACTOR = 0;
// 模拟速度指令补偿因子
_iq AS_COMPENSATE_FACTOR = 0;
// 速度PI饱和时间因子
s32 SPEED_PID_SATURATION_TIME_FACTOR = 0;
// 速度到达因子
u16 SPEED_ARRIVE_FACTOR = 0;
// 速度指令显示因子
float SPEED_CMD_VIEW_FACTOR = 0;

// 额定电流
_iq RATE_CURRENT_FACTOR   = 0;
// 内部转矩限制
_iq INTERIOR_TORQUE_MAX_FACTOR = 0;
_iq INTERIOR_TORQUE_MIN_FACTOR = 0;
// 外部转矩限制
_iq EXTERIOR_TORQUE_MAX_FACTOR = 0;
_iq EXTERIOR_TORQUE_MIN_FACTOR = 0;
// 速度试运行转矩限制
_iq SR_TORQUE_MAX_FACTOR = 0;
_iq SR_TORQUE_MIN_FACTOR = 0;
// 过负载
_iq OVER_LOAD_MAX_FACTOR  = 0;
s32 OVER_LOAD_TIME_FACTOR = 0;
// 热过载
_iq OVER_HEAT_MAX_FACTOR  = 0;
s32 OVER_HEAT_TIME_FACTOR = 0;
// 过电流
_iq OVER_CURRENT_MAX_FACTOR = 0;
s32 OVER_CURRENT_TIME_FACTOR = 0;
// 转矩显示系数
float MOTOR_TORQUE_VIEW_FACTOR = 0;
// 电流显示系数
float MOTOR_CURRENT_VIEW_FACTOR = 0;

// 最大位置误差
s32 POS_ERR_MAX_FACTOR = 0;
// 位置到达因子
u16 POS_ARRIVE_FACTOR = 0;

// 电子齿轮比
float ELC_GEAR_FACTOR = 0;
//电子齿轮比最大公倍数
s32 ELC_GEAR_MUL_MAX = 0;
s32 ELC_GEAR_MUL_FDB = 0;

// 电机停止时制动器动作设定 时间因子
u32 STOP_BRAKE_TIME_FACTOR = 0;
// 电机运转时制动器动作设定 时间因子
u32 RUN_BRAKE_TIME_FACTOR  = 0;

// 过压时间因子
u32 OV_TIME_FACTOR = 0;

// 制动时间因子
u32 BR_TIME_FACTOR = 0;




//-----------------------------函数说明-----------------------------------------
// 执行函数前，
// 先读取电机表中的电机参数，
// 然后读取参数表中的参数。
//-----------------------------函数说明-----------------------------------------

void system_parameter_init(void)
{     
     // 定时器计数周期
     PWM_PERIOD_FACTOR = PWM_PERIOD;
     
     // 单位速度 rad/s
     SPEED_UNIT_FACTOR = (u16) (motor_parameter[parameter_table[Version]].Rate_Speed / 60 * 2 * PI);   // 从电机参数表读取电机额定转速
     // 速度指令计算因子
     SPEED_COMMAND_FACTOR = 16777216.0 / motor_parameter[parameter_table[Version]].Rate_Speed;
     // 速度计算因子
     SPEED_CALC_FACTOR = _IQ20( (float)SPEED_LOOP_FREQ*2*PI/motor_parameter[parameter_table[Version]].LineEncoder );
     // 速度观测计算因子
     SPEED_VIEW_CALC_FACTOR = (PWM_FREQ*60/motor_parameter[parameter_table[Version]].LineEncoder);
     // 最大转速
     SPEED_MAX_FACTOR = (s32) ( (float)parameter_table[MaxSpeed] / (float)motor_parameter[parameter_table[Version]].Rate_Speed * 16777216 );
     SPEED_MIN_FACTOR = - SPEED_MAX_FACTOR;
     // 模拟速度指令计算因子
     AS_CALC_FACTOR = (u16) ((float)parameter_table[AnalogSpeedGain] * 5649.655 / motor_parameter[parameter_table[Version]].Rate_Speed );
     // 模拟速度指令补偿因子
     AS_COMPENSATE_FACTOR = (s32) ( (float)parameter_table[AnalogSpeedCommandOffsetCompensation] / motor_parameter[parameter_table[Version]].Rate_Speed * IQ_Z_1 );
     // 速度PI饱和时间因子
     SPEED_PID_SATURATION_TIME_FACTOR = SPEED_LOOP_FREQ/1000 * parameter_table[SpeedPidSaturationTime];
     // 速度到达因子
     SPEED_ARRIVE_FACTOR = parameter_table[ArrivedSpeed];
     //
     SPEED_CMD_VIEW_FACTOR = (float)motor_parameter[parameter_table[Version]].Rate_Speed / IQ_Z_1;
     
     // 额定电流
     RATE_CURRENT_FACTOR   = (s32) ( motor_parameter[parameter_table[Version]].Rate_Current * IQ_Z_1 / CURRENT_UNIT );
     // 过电流
     OVER_CURRENT_MAX_FACTOR  = IQ_Z_0_DOT_95;
     OVER_CURRENT_TIME_FACTOR = PWM_FREQ/1000 * parameter_table[OverCurrentTime];            // ms 转成 PWM周期数;
     // 内部转矩限制
     INTERIOR_TORQUE_MAX_FACTOR = RATE_CURRENT_FACTOR * parameter_table[InteriorCCWTorqueLimit] / 100 ;
     INTERIOR_TORQUE_MIN_FACTOR = RATE_CURRENT_FACTOR * parameter_table[InteriorCWTorqueLimit]  / 100 ;
     // 外部转矩限制
     EXTERIOR_TORQUE_MAX_FACTOR = RATE_CURRENT_FACTOR * parameter_table[ExteriorCCWTorqueLimit] / 100 ;
     EXTERIOR_TORQUE_MIN_FACTOR = RATE_CURRENT_FACTOR * parameter_table[ExteriorCWTorqueLimit]  / 100 ;
     // 速度试运行转矩限制
     SR_TORQUE_MAX_FACTOR = RATE_CURRENT_FACTOR * parameter_table[JOGTorqueLimit] / 100 ;
     SR_TORQUE_MIN_FACTOR = -SR_TORQUE_MAX_FACTOR;     
     // 过负载     
     OVER_LOAD_MAX_FACTOR  = RATE_CURRENT_FACTOR * parameter_table[UserTorqueOverloadAlarm] / 100;
     OVER_LOAD_TIME_FACTOR = PWM_FREQ/1000 * parameter_table[UserTorqueOverloadDetectTime]; //ms 转成 电流环周期数
     // 热过载
     OVER_HEAT_MAX_FACTOR  = RATE_CURRENT_FACTOR * parameter_table[OverHeatAlarm] / 100;
     OVER_HEAT_TIME_FACTOR = PWM_FREQ * parameter_table[OverHeatTime]; //s 转成 电流环周期数
     // 转矩显示系数
     MOTOR_TORQUE_VIEW_FACTOR = CURRENT_UNIT * 100 / motor_parameter[parameter_table[Version]].Rate_Current / IQ_Z_1;
     //
     MOTOR_CURRENT_VIEW_FACTOR = CURRENT_UNIT * 100 / IQ_Z_1;
     
     
     // 位置误差最大值
     POS_ERR_MAX_FACTOR = parameter_table[PositionToleranceDetectionRange]*100; // 单位（100脉冲） 转成 脉冲
     // 位置到达因子
     POS_ARRIVE_FACTOR  = parameter_table[LocationFinishRange];
    
     // 电子齿轮比
     ELC_GEAR_FACTOR = ((float)parameter_table[PositionCommandDivisionNumerator]) / ((float)parameter_table[PositionCommandDivisionDenominator]);
     //电子齿轮比最大公倍数
     
     ELC_GEAR_MUL_MAX = parameter_table[PositionCommandDivisionNumerator] * parameter_table[PositionCommandDivisionDenominator];
     ELC_GEAR_MUL_FDB = parameter_table[PositionCommandDivisionNumerator] * parameter_table[PositionCommandDivisionNumerator];
     while(ELC_GEAR_MUL_MAX < 10000)
     {
          ELC_GEAR_MUL_MAX = ELC_GEAR_MUL_MAX *100;
          ELC_GEAR_MUL_FDB = ELC_GEAR_MUL_FDB *100;
     }          
          
     // 电机停止时制动器动作设定 时间因子
     STOP_BRAKE_TIME_FACTOR = PWM_FREQ/100 * parameter_table[MechanicalBrakingSetWhileStop];       // 10ms 转成 PWM周期数
     // 电机运转时制动器动作设定 时间因子
     RUN_BRAKE_TIME_FACTOR  = PWM_FREQ/100 * parameter_table[MechanicalBrakingSetWhileRun];
     
     // 过压时间因子
     OV_TIME_FACTOR = PWM_FREQ/1000 * parameter_table[OverVoltageTime];            // ms 转成 PWM周期数
     
     // 制动时间因子
     BR_TIME_FACTOR = PWM_FREQ/1000 * parameter_table[BrakeTime];            // ms 转成 PWM周期数
     
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
     as_filter.FilterTs = _IQ( (1.0/(CURRENT_LOOP_FREQ)) );
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
     pid_id.Kp = _IQ( ((float)parameter_table[CurrentGain]) / 10.0);
     pid_id.Ki = _IQ(0.0001 * 100000.0 / ((float)parameter_table[CurrentIntegral]) );
     pid_id.Kd = _IQ(0);
     pid_id.Kc = _IQ(0);
     pid_id.OutMax = _IQ(0.3);
     pid_id.OutMin = _IQ(-0.3);
     
     // pid for iq
     pid_iq.Kp = _IQ(((float)parameter_table[CurrentGain]) / 10.0);
     pid_iq.Ki = _IQ(0.0001 * 100000.0 / ((float)parameter_table[CurrentIntegral]) );
     pid_iq.Kd = _IQ(0);
     pid_iq.Kc = _IQ(0);
     pid_iq.OutMax = _IQ(0.95);
     pid_iq.OutMin = _IQ(-0.95);
     
     // 编码器开环获取角度偏置时的 PI
     pid_id_encoder_offset.Kp = _IQ( ((float)parameter_table[CurrentGain]) / 10.0);
     pid_id_encoder_offset.Ki = _IQ(0.0001 * 100000.0 / ((float)parameter_table[CurrentIntegral]));
     pid_id_encoder_offset.Kd = _IQ(0);
     pid_id_encoder_offset.Kc = _IQ(0);
     pid_id_encoder_offset.OutMax = _IQ(0.5);
     pid_id_encoder_offset.OutMin = _IQ(-0.5);
     
     pid_iq_encoder_offset.Kp = _IQ( ((float)parameter_table[CurrentGain]) / 10.0);
     pid_iq_encoder_offset.Ki = _IQ(0.0001 * 100000.0 / ((float)parameter_table[CurrentIntegral]));
     pid_iq_encoder_offset.Kd = _IQ(0);
     pid_iq_encoder_offset.Kc = _IQ(0);
     pid_iq_encoder_offset.OutMax = _IQ(0.5);
     pid_iq_encoder_offset.OutMin = _IQ(-0.5);     
     
     // pid for speed
     pid_speed.Kp = _IQ( ((float)parameter_table[SpeedGain]) / 10.0);
     pid_speed.Ki = _IQ(0.0005 * 100000.0 / ((float)parameter_table[SpeedIntegral]) );
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
     
     
     
     /*
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
     */
     
          /*
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
     */
}
     

