#include "system_parameter.h"

// ��ʱ����������
u16 PWM_PERIOD_FACTOR = 0;

// �ٶ�ָ���������
float SPEED_COMMAND_FACTOR = 0;
// �ٶȼ�������
s32 SPEED_CALC_FACTOR = 0;
// �ٶȹ۲��������
s32 SPEED_VIEW_CALC_FACTOR = 0;
// ��λ�ٶ� rad/s
u16 SPEED_UNIT_FACTOR = 0;
// ���ת��
_iq SPEED_MAX_FACTOR = 0;
_iq SPEED_MIN_FACTOR = 0;
// ģ���ٶ�ָ���������
u16 AS_CALC_FACTOR = 0;
// ģ���ٶ�ָ�������
_iq AS_COMPENSATE_FACTOR = 0;
// �ٶ�PI����ʱ������
s32 SPEED_PID_SATURATION_TIME_FACTOR = 0;
// �ٶȵ�������
u16 SPEED_ARRIVE_FACTOR = 0;
// �ٶ�ָ����ʾ����
float SPEED_CMD_VIEW_FACTOR = 0;

// �����
_iq RATE_CURRENT_FACTOR   = 0;
// �ڲ�ת������
_iq INTERIOR_TORQUE_MAX_FACTOR = 0;
_iq INTERIOR_TORQUE_MIN_FACTOR = 0;
// �ⲿת������
_iq EXTERIOR_TORQUE_MAX_FACTOR = 0;
_iq EXTERIOR_TORQUE_MIN_FACTOR = 0;
// �ٶ�������ת������
_iq SR_TORQUE_MAX_FACTOR = 0;
_iq SR_TORQUE_MIN_FACTOR = 0;
// ������
_iq OVER_LOAD_MAX_FACTOR  = 0;
s32 OVER_LOAD_TIME_FACTOR = 0;
// �ȹ���
_iq OVER_HEAT_MAX_FACTOR  = 0;
s32 OVER_HEAT_TIME_FACTOR = 0;
// ������
_iq OVER_CURRENT_MAX_FACTOR = 0;
s32 OVER_CURRENT_TIME_FACTOR = 0;
// ת����ʾϵ��
float MOTOR_TORQUE_VIEW_FACTOR = 0;
// ������ʾϵ��
float MOTOR_CURRENT_VIEW_FACTOR = 0;

// ���λ�����
s32 POS_ERR_MAX_FACTOR = 0;
// λ�õ�������
u16 POS_ARRIVE_FACTOR = 0;

// ���ӳ��ֱ�
float ELC_GEAR_FACTOR = 0;
//���ӳ��ֱ���󹫱���
s32 ELC_GEAR_MUL_MAX = 0;
s32 ELC_GEAR_MUL_FDB = 0;

// ���ֹͣʱ�ƶ��������趨 ʱ������
u32 STOP_BRAKE_TIME_FACTOR = 0;
// �����תʱ�ƶ��������趨 ʱ������
u32 RUN_BRAKE_TIME_FACTOR  = 0;

// ��ѹʱ������
u32 OV_TIME_FACTOR = 0;

// �ƶ�ʱ������
u32 BR_TIME_FACTOR = 0;




//-----------------------------����˵��-----------------------------------------
// ִ�к���ǰ��
// �ȶ�ȡ������еĵ��������
// Ȼ���ȡ�������еĲ�����
//-----------------------------����˵��-----------------------------------------

void system_parameter_init(void)
{     
     // ��ʱ����������
     PWM_PERIOD_FACTOR = PWM_PERIOD;
     
     // ��λ�ٶ� rad/s
     SPEED_UNIT_FACTOR = (u16) (motor_parameter[parameter_table[Version]].Rate_Speed / 60 * 2 * PI);   // �ӵ���������ȡ����ת��
     // �ٶ�ָ���������
     SPEED_COMMAND_FACTOR = 16777216.0 / motor_parameter[parameter_table[Version]].Rate_Speed;
     // �ٶȼ�������
     SPEED_CALC_FACTOR = _IQ20( (float)SPEED_LOOP_FREQ*2*PI/motor_parameter[parameter_table[Version]].LineEncoder );
     // �ٶȹ۲��������
     SPEED_VIEW_CALC_FACTOR = (PWM_FREQ*60/motor_parameter[parameter_table[Version]].LineEncoder);
     // ���ת��
     SPEED_MAX_FACTOR = (s32) ( (float)parameter_table[MaxSpeed] / (float)motor_parameter[parameter_table[Version]].Rate_Speed * 16777216 );
     SPEED_MIN_FACTOR = - SPEED_MAX_FACTOR;
     // ģ���ٶ�ָ���������
     AS_CALC_FACTOR = (u16) ((float)parameter_table[AnalogSpeedGain] * 5649.655 / motor_parameter[parameter_table[Version]].Rate_Speed );
     // ģ���ٶ�ָ�������
     AS_COMPENSATE_FACTOR = (s32) ( (float)parameter_table[AnalogSpeedCommandOffsetCompensation] / motor_parameter[parameter_table[Version]].Rate_Speed * IQ_Z_1 );
     // �ٶ�PI����ʱ������
     SPEED_PID_SATURATION_TIME_FACTOR = SPEED_LOOP_FREQ/1000 * parameter_table[SpeedPidSaturationTime];
     // �ٶȵ�������
     SPEED_ARRIVE_FACTOR = parameter_table[ArrivedSpeed];
     //
     SPEED_CMD_VIEW_FACTOR = (float)motor_parameter[parameter_table[Version]].Rate_Speed / IQ_Z_1;
     
     // �����
     RATE_CURRENT_FACTOR   = (s32) ( motor_parameter[parameter_table[Version]].Rate_Current * IQ_Z_1 / CURRENT_UNIT );
     // ������
     OVER_CURRENT_MAX_FACTOR  = IQ_Z_0_DOT_95;
     OVER_CURRENT_TIME_FACTOR = PWM_FREQ/1000 * parameter_table[OverCurrentTime];            // ms ת�� PWM������;
     // �ڲ�ת������
     INTERIOR_TORQUE_MAX_FACTOR = RATE_CURRENT_FACTOR * parameter_table[InteriorCCWTorqueLimit] / 100 ;
     INTERIOR_TORQUE_MIN_FACTOR = RATE_CURRENT_FACTOR * parameter_table[InteriorCWTorqueLimit]  / 100 ;
     // �ⲿת������
     EXTERIOR_TORQUE_MAX_FACTOR = RATE_CURRENT_FACTOR * parameter_table[ExteriorCCWTorqueLimit] / 100 ;
     EXTERIOR_TORQUE_MIN_FACTOR = RATE_CURRENT_FACTOR * parameter_table[ExteriorCWTorqueLimit]  / 100 ;
     // �ٶ�������ת������
     SR_TORQUE_MAX_FACTOR = RATE_CURRENT_FACTOR * parameter_table[JOGTorqueLimit] / 100 ;
     SR_TORQUE_MIN_FACTOR = -SR_TORQUE_MAX_FACTOR;     
     // ������     
     OVER_LOAD_MAX_FACTOR  = RATE_CURRENT_FACTOR * parameter_table[UserTorqueOverloadAlarm] / 100;
     OVER_LOAD_TIME_FACTOR = PWM_FREQ/1000 * parameter_table[UserTorqueOverloadDetectTime]; //ms ת�� ������������
     // �ȹ���
     OVER_HEAT_MAX_FACTOR  = RATE_CURRENT_FACTOR * parameter_table[OverHeatAlarm] / 100;
     OVER_HEAT_TIME_FACTOR = PWM_FREQ * parameter_table[OverHeatTime]; //s ת�� ������������
     // ת����ʾϵ��
     MOTOR_TORQUE_VIEW_FACTOR = CURRENT_UNIT * 100 / motor_parameter[parameter_table[Version]].Rate_Current / IQ_Z_1;
     //
     MOTOR_CURRENT_VIEW_FACTOR = CURRENT_UNIT * 100 / IQ_Z_1;
     
     
     // λ��������ֵ
     POS_ERR_MAX_FACTOR = parameter_table[PositionToleranceDetectionRange]*100; // ��λ��100���壩 ת�� ����
     // λ�õ�������
     POS_ARRIVE_FACTOR  = parameter_table[LocationFinishRange];
    
     // ���ӳ��ֱ�
     ELC_GEAR_FACTOR = ((float)parameter_table[PositionCommandDivisionNumerator]) / ((float)parameter_table[PositionCommandDivisionDenominator]);
     //���ӳ��ֱ���󹫱���
     
     ELC_GEAR_MUL_MAX = parameter_table[PositionCommandDivisionNumerator] * parameter_table[PositionCommandDivisionDenominator];
     ELC_GEAR_MUL_FDB = parameter_table[PositionCommandDivisionNumerator] * parameter_table[PositionCommandDivisionNumerator];
     while(ELC_GEAR_MUL_MAX < 10000)
     {
          ELC_GEAR_MUL_MAX = ELC_GEAR_MUL_MAX *100;
          ELC_GEAR_MUL_FDB = ELC_GEAR_MUL_FDB *100;
     }          
          
     // ���ֹͣʱ�ƶ��������趨 ʱ������
     STOP_BRAKE_TIME_FACTOR = PWM_FREQ/100 * parameter_table[MechanicalBrakingSetWhileStop];       // 10ms ת�� PWM������
     // �����תʱ�ƶ��������趨 ʱ������
     RUN_BRAKE_TIME_FACTOR  = PWM_FREQ/100 * parameter_table[MechanicalBrakingSetWhileRun];
     
     // ��ѹʱ������
     OV_TIME_FACTOR = PWM_FREQ/1000 * parameter_table[OverVoltageTime];            // ms ת�� PWM������
     
     // �ƶ�ʱ������
     BR_TIME_FACTOR = PWM_FREQ/1000 * parameter_table[BrakeTime];            // ms ת�� PWM������
     
     float tmp;
     
     //--------------------�Ӽ���ʱ�䳣������-----------------------------------
     rampctrl_parameter.RampLowLimit = -_IQ(1);
     rampctrl_parameter.RampHighLimit = _IQ(1);
     tmp = 1000.0 / motor_parameter[parameter_table[Version]].Rate_Speed;       // 1000rpm / �ת��
     if(parameter_table[AccelerationTimeConstant]>=1)
     {
          rampctrl_parameter.acc_zero_flag=0;

          rampctrl_parameter.acc_dt = _IQ(tmp) / (SPEED_LOOP_FREQ) * 1000 / parameter_table[AccelerationTimeConstant];      //���ٲ���
     }
     else
     {
          rampctrl_parameter.acc_zero_flag=1;
     }
     if(parameter_table[DecelerationTimeConstant]>=1)
     {
          rampctrl_parameter.deacc_zero_flag=0;
          rampctrl_parameter.deacc_dt = -_IQ(tmp) / (SPEED_LOOP_FREQ) * 1000 / parameter_table[DecelerationTimeConstant];   //���ٲ���
     }
     else
     {
          rampctrl_parameter.deacc_zero_flag=1;
     }
     //--------------------�Ӽ���ʱ�䳣������-----------------------------------     
     
     //-------------------------------�˲���------------------------------------
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
     //-------------------------------�˲���------------------------------------
     
     //-------------------------------PI����------------------------------------
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
     
     // ������������ȡ�Ƕ�ƫ��ʱ�� PI
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
     //-------------------------------PI����------------------------------------
     
     
     
     /*
     //-------------------------------PI����------------------------------------
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
     
     // ������������ȡ�Ƕ�ƫ��ʱ�� PI
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
     //-------------------------------PI����------------------------------------
     */
     
          /*
     //-------------------------------�˲���------------------------------------
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
     //-------------------------------�˲���------------------------------------
     */
}
     

