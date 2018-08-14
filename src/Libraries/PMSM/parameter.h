#ifndef __PARAMETER_H
#define __PARAMETER_H

#include "stm32f10x.h"
//#include "param.h"
#include "motor_parameter.h"


/*********************************�˵���������**********************************/
#define MEAU_NUM            80
#define MEAU_NUM_NORMAL            60



#define Password 0                                /* 0����*/
#define Version 1                                /* 1�ͺ�*/
#define SoftwareVersion 2                       /* 2����汾*/
#define InitialDisplay 3                         /* 3��ʼ��ʾ״̬*/
#define ControlMode 4                           /* 4���Ʒ�ʽ*/
#define SpeedGain 5                             /* 5�ٶ�����*/
#define SpeedIntegral 6                          /* 6�ٶȻ���*/
#define TorqueFilter  7                          /* 7ת��ָ���˲���*/
#define SpeedCheckFilter 8                       /* 8�ٶȼ���˲���*/
#define PositionGain 9                           /* 9λ������*/
#define PositionFeedforwardGain 10                /* 10λ��ǰ������*/
#define PositionFeedforwardFilterFrequency 11     /* 11λ��ǰ���˲�����ֹƵ��*/
#define PositionCommandDivisionNumerator 12       /* 12λ��ָ�������Ƶ����*/
#define PositionCommandDivisionDenominator 13     /* 13λ��ָ�������Ƶ��ĸ*/
#define PositionCommandMode 14                   /* 14λ��ָ���������뷽ʽ*/
#define PositionCommandDirection 15             /* 15λ��ָ�����巽��*/
#define LocationFinishRange 16                   /* 16��λ��ɷ�Χ*/
#define PositionToleranceDetectionRange 17       /* 17λ�ó����ⷶΧ*/
#define PositionToleranceErrorRangeValid 18           /* 18λ�ó��������Ч*/
#define PositionCommandFilter 19                 /* 19λ��ָ���˲���*/
#define DriveForbiddenInvalid 20                  /* 20������ֹ������Ч*/
#define JOGSpeed 21                              /* 21JOG�����ٶ�*/
#define SpeedCommandChoice 22                     /* 22�����ٶ�ָ��ѡ��*/
#define MaxSpeed 23                               /* 23 ����ٶ�����*/
#define InteriorSpeed1 24                       /* 24�ڲ��ٶ�1*/
#define InteriorSpeed2 25                        /* 25�ڲ��ٶ�2*/
#define InteriorSpeed3 26                        /* 26�ڲ��ٶ�3*/
#define InteriorSpeed4 27                        /* 27�ڲ��ٶ�4*/
#define ArrivedSpeed  28                         /* 28�����ٶ�*/
#define AnalogTorqueGain 29                       /* 29ģ����ת��ָ����������*/
#define UserTorqueOverloadAlarm  30                /* 30�û�ת�ع��ر���*/
#define UserTorqueOverloadDetectTime 31          /* 31�û�ת�ع��ر������ʱ��*/
#define ControlModeSwitchEnable 32               /* 32���Ʒ�ʽ�л�����*/
#define AnalogTorqueCommandDirectionReverse 33    /* 33ģ����ת��ָ���ȡ��*/
#define InteriorCCWTorqueLimit 34                /* 34�ڲ�CCWת������*/
#define InteriorCWTorqueLimit 35                /* 35�ڲ�CWת������*/
#define ExteriorCCWTorqueLimit 36                /* 36�ⲿCCWת������*/
#define ExteriorCWTorqueLimit 37                 /* 37�ⲿCWת������*/
#define JOGTorqueLimit 38                       /* 38�ٶ������С�JOG����ת������*/
#define AnalogTorqueCommandOffsetCompensation 39  /* 39ģ��ת��ָ����ƫ����*/
#define AccelerationTimeConstant 40              /* 40����ʱ�䳣��*/
#define DecelerationTimeConstant 41              /* 41����ʱ�䳣��*/
#define STypeAccelerationDecelerationTimeConstant 42 /*42S�ͼӼ���ʱ�䳣��*/
#define AnalogSpeedGain 43                        /* 43ģ�����ٶ�ָ����������*/
#define AnalogSpeedCommandDirectionReverse 44    /* 44ģ�����ٶ�ָ���ȡ��*/
#define AnalogSpeedCommandOffsetCompensation 45  /* 45ģ��ת�ٶ�����ƫ����*/
#define AnalogSpeedCommandFilter 46               /* 46ģ���ٶ�ָ���˲�*/
#define MechanicalBrakingSetWhileStop 47          /* 47���ֹͣʱ��е�ƶ��������趨*/
#define MechanicalBrakingSetWhileRun 48          /* 48�����תʱ��е�ƶ��������趨*/
#define MechanicalBrakingSpeedWhileStop 49        /* 49�����תʱ��е�ƶ��������ٶ�*/
#define SpeedLimitWhileTorqueControl 50           /* 50ת�ؿ������ٶ�����;*/
#define ElectronicGearValid 51                   /* 51��̬���ӳ�����Ч*/
#define SecondPositionCommandDivisionNumerator 52 /* 52�ڶ�λ��ָ�������Ƶ����*/
#define Lower4BitInputON 53                       /* 53����λ�������ǿ��ON������*/
#define Upper4BitInputON 54                      /* 54����λ�������ǿ��ON������*/
#define Lower4BitInputReverse 55                 /* 55����λ�������ȡ��������*/
#define Upper4BitInputReverse 56                  /* 56����λ�������ȡ��������*/
#define OutputReverse 57                         /* 57�������ȡ��������;*/
#define InputFilter 58                           /* 58�������ȥ��ʱ�䳣��;*/
#define Show 59      
#define CurrentGain 60                             /* 60��������*/
#define CurrentIntegral 61                         /* 61��������*/
#define OverVoltageTime 62                                  /* 62��ѹ����ʱ�� */
#define OverCurrentTime 63                                  /* 63����������ʱ�� */
#define OverHeatAlarm   64                          /* 64�ȹ��ر�����ֵ */
#define OverHeatTime    65                          /* 65�ȹ��ر���ʱ�� */
#define SpeedPidSaturationTime 66                   /* 66�ٶ�PID���ͱ���ʱ�� */
#define BrakeTime 67                                 /* 67�ƶ�����ʱ�� */
#define ErrMask1to6 68                               /* 68��������1-6 */
#define ErrMask7to12 69                               /* 69��������7-12 */
#define ErrMask13to18 70                              /* 70��������13-18 */
#define ErrMask19to24 71                              /* 71��������19-24 */
#define ErrMask25to30 72                              /* 72��������25-30 */
#define ErrMask31to36 73                              /* 73��������31-36 */



extern u16 plc_delay_1ms;
extern u16 plc_delay_1ms_flag;





/*������*/
extern s16 parameter_table[MEAU_NUM];
extern s16 parameter_table_max[MEAU_NUM];
extern s16 parameter_table_min[MEAU_NUM];
extern s16 parameter_table_step[MEAU_NUM];
extern const s16 parameter_table_default[MEAU_NUM];

void motor_parameter_read (void);


#endif