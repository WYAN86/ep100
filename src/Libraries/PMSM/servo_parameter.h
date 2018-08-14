#ifndef __SERVO_PARAMETER_H
#define __SERVO_PARAMETER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "IQmathLib.h"
#include "system_parameter.h"
#include "pid.h"
#include "low_filter.h"
#include "parameter.h"
#include "rampctrl.h"
#include "speed.h"


//void control_parameter_config(void);

//extern parameter_list servo_parameter_list;

#endif




/*
          
          s16 PositionGain; //0,λ�ñ�������
          int16 PositionFeedFowardGain;//1,����ǰ������
          int16 SpeedGain;//2,�ٶȱ�������
          int16 SpeedIntegralCons;//3,�ٶȻ��ֳ���
          int16 SpeedFdbFilterFactor;//4,�ٶȷ����˲�����
          int16 MaxTorqueCurrentLimit;//5,���ת�ص�������
          int16 AccelerationTimeCons;//6,����ʱ�䳣��(�����������ָ����ٶ�pulse/0.1ms)
          int16 SpeedCommandInputGain;//7,�ٶ������������
          int16 SpeedCommandZeroDriftCompensation;//8,�ٶ�ָ����Ư����
          int16 ToruqeCommandInputGain;//9,����ָ������
          int16 TorqueCommandZeroDriftCompensation;//10,����ָ����Ư����
          int16 PositionSpeedReachRange;//11,��λ��ɷ�Χ,���ٶ���ɷ�Χ
          int16 PositionToleranceTestRange;//12,λ�ó����ⷶΧ
          int16 PositionCommandNum;//13,λ��ָ���Ƶ����
          int16 PositionCommandDen;//14,λ��ָ���Ƶ��ĸ
          int16 PosTorqueLimit;//15,����������
          int16 NegTorqueLimit;//16,����������
          int16 MaxSpeedLimit;//17,����ٶ�����
          int16 OverloadCurrentSet;//18,����������
          int16 SoftOverloadTimeSet;//19,�������ʱ������
          int16 InsideSpeedSet;//20,�ڲ��ٶ�
          int16 JogSpeedSet;//21,Jog�ٶ�
          int16 PositionCommandMode;//22,λ���������뷽ʽ
          int16 ControlMode;//23,����ģʽ
          int16 MotorPole;//24,���������
          int16 EncoderResolution;//25,�������ֱ���
          int16 NetworkCommuPeriod;//26����ͨѶ����
          int16 CurrentControlGain;//27,������������
          int16 CurrentControlIntigral;//28,�������ƻ���
          int16 SecondPositionCommandNum;//29,�ڶ�λ��ָ���Ƶ����
          int16 MotorAntivoltageCons;//30,������綯�Ƴ���
          int16 NetWorkAlmMaxTime;//31���籨��������������1���������������
          int16 FeedforwardFilterCons;//32,ǰ���˲�����
          int16 TorqueCommandFilterCons;//33,����ָ���˲�����
          int16 TrapFilterFreq;//34,�ݲ���Ƶ��
          int16 PositionCommandFilterCons;//35,λ��ָ���˲�ʱ�䳣��
          int16 InertiaRate;//36,����ת��������
          int16 LoadStiffness;//37,���ظ���
          int16 DecelerationTimeCons;//38,����ʱ�䳣��
          int16 NetworkAddress;//39�����ַ
          int16 NetworkTotalPoint;//40 �ܽڵ���
          int16 PhyDelayCons;     //41 Phy��ʱʱ�䳣��
          int16 PosDifferentialCons;//42 λ��΢��ϵ��
          int16 PosIntegralCons; //43
          union CONTL_PARAM_MODE ControlParametMode;//44���Ʋ���ģʽ����
          union FAILURE_ALARM FailureAlarm;//45���ϱ���
          
          int16 his0;//46
          int16 his1;//
          int16 his2;
          int16 his3;
          int16 his4;
          int16 his5;
          int16 his6;
          int16 his7;
          int16 his8;
          int16 his9;//55
          int16 Para_crcdata1;//56
          void  (*init)();
          void  (*update)();
}SERVOPARAM;
*/