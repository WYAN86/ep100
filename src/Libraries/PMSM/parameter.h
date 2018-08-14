#ifndef __PARAMETER_H
#define __PARAMETER_H

#include "stm32f10x.h"
//#include "param.h"
#include "motor_parameter.h"


/*********************************菜单参数个数**********************************/
#define MEAU_NUM            80
#define MEAU_NUM_NORMAL            60



#define Password 0                                /* 0密码*/
#define Version 1                                /* 1型号*/
#define SoftwareVersion 2                       /* 2软件版本*/
#define InitialDisplay 3                         /* 3初始显示状态*/
#define ControlMode 4                           /* 4控制方式*/
#define SpeedGain 5                             /* 5速度增益*/
#define SpeedIntegral 6                          /* 6速度积分*/
#define TorqueFilter  7                          /* 7转矩指令滤波器*/
#define SpeedCheckFilter 8                       /* 8速度检测滤波器*/
#define PositionGain 9                           /* 9位置增益*/
#define PositionFeedforwardGain 10                /* 10位置前馈增益*/
#define PositionFeedforwardFilterFrequency 11     /* 11位置前馈滤波器截止频率*/
#define PositionCommandDivisionNumerator 12       /* 12位置指令脉冲分频分子*/
#define PositionCommandDivisionDenominator 13     /* 13位置指令脉冲分频分母*/
#define PositionCommandMode 14                   /* 14位置指令脉冲输入方式*/
#define PositionCommandDirection 15             /* 15位置指令脉冲方向*/
#define LocationFinishRange 16                   /* 16定位完成范围*/
#define PositionToleranceDetectionRange 17       /* 17位置超差检测范围*/
#define PositionToleranceErrorRangeValid 18           /* 18位置超差错误无效*/
#define PositionCommandFilter 19                 /* 19位置指令滤波器*/
#define DriveForbiddenInvalid 20                  /* 20驱动禁止输入无效*/
#define JOGSpeed 21                              /* 21JOG运行速度*/
#define SpeedCommandChoice 22                     /* 22内外速度指令选择*/
#define MaxSpeed 23                               /* 23 最高速度限制*/
#define InteriorSpeed1 24                       /* 24内部速度1*/
#define InteriorSpeed2 25                        /* 25内部速度2*/
#define InteriorSpeed3 26                        /* 26内部速度3*/
#define InteriorSpeed4 27                        /* 27内部速度4*/
#define ArrivedSpeed  28                         /* 28到达速度*/
#define AnalogTorqueGain 29                       /* 29模拟量转矩指令输入增益*/
#define UserTorqueOverloadAlarm  30                /* 30用户转矩过载报警*/
#define UserTorqueOverloadDetectTime 31          /* 31用户转矩过载报警检测时间*/
#define ControlModeSwitchEnable 32               /* 32控制方式切换允许*/
#define AnalogTorqueCommandDirectionReverse 33    /* 33模拟量转矩指令方向取反*/
#define InteriorCCWTorqueLimit 34                /* 34内部CCW转矩限制*/
#define InteriorCWTorqueLimit 35                /* 35内部CW转矩限制*/
#define ExteriorCCWTorqueLimit 36                /* 36外部CCW转矩限制*/
#define ExteriorCWTorqueLimit 37                 /* 37外部CW转矩限制*/
#define JOGTorqueLimit 38                       /* 38速度试运行、JOG运行转矩限制*/
#define AnalogTorqueCommandOffsetCompensation 39  /* 39模拟转矩指令零偏补偿*/
#define AccelerationTimeConstant 40              /* 40加速时间常数*/
#define DecelerationTimeConstant 41              /* 41减速时间常数*/
#define STypeAccelerationDecelerationTimeConstant 42 /*42S型加减速时间常数*/
#define AnalogSpeedGain 43                        /* 43模拟量速度指令输入增益*/
#define AnalogSpeedCommandDirectionReverse 44    /* 44模拟量速度指令方向取反*/
#define AnalogSpeedCommandOffsetCompensation 45  /* 45模拟转速度令零偏补偿*/
#define AnalogSpeedCommandFilter 46               /* 46模拟速度指令滤波*/
#define MechanicalBrakingSetWhileStop 47          /* 47电机停止时机械制动器动作设定*/
#define MechanicalBrakingSetWhileRun 48          /* 48电机运转时机械制动器动作设定*/
#define MechanicalBrakingSpeedWhileStop 49        /* 49电机运转时机械制动器动作速度*/
#define SpeedLimitWhileTorqueControl 50           /* 50转矩控制室速度限制;*/
#define ElectronicGearValid 51                   /* 51动态电子齿轮有效*/
#define SecondPositionCommandDivisionNumerator 52 /* 52第二位置指令脉冲分频分子*/
#define Lower4BitInputON 53                       /* 53低四位输入端子强制ON控制字*/
#define Upper4BitInputON 54                      /* 54高四位输入端子强制ON控制字*/
#define Lower4BitInputReverse 55                 /* 55低四位输入端子取反控制字*/
#define Upper4BitInputReverse 56                  /* 56高四位输入端子取反控制字*/
#define OutputReverse 57                         /* 57输出端子取反控制字;*/
#define InputFilter 58                           /* 58输入端子去抖时间常数;*/
#define Show 59      
#define CurrentGain 60                             /* 60电流增益*/
#define CurrentIntegral 61                         /* 61电流积分*/
#define OverVoltageTime 62                                  /* 62过压报警时间 */
#define OverCurrentTime 63                                  /* 63过电流报警时间 */
#define OverHeatAlarm   64                          /* 64热过载报警阀值 */
#define OverHeatTime    65                          /* 65热过载报警时间 */
#define SpeedPidSaturationTime 66                   /* 66速度PID饱和报警时间 */
#define BrakeTime 67                                 /* 67制动报警时间 */
#define ErrMask1to6 68                               /* 68报警屏蔽1-6 */
#define ErrMask7to12 69                               /* 69报警屏蔽7-12 */
#define ErrMask13to18 70                              /* 70报警屏蔽13-18 */
#define ErrMask19to24 71                              /* 71报警屏蔽19-24 */
#define ErrMask25to30 72                              /* 72报警屏蔽25-30 */
#define ErrMask31to36 73                              /* 73报警屏蔽31-36 */



extern u16 plc_delay_1ms;
extern u16 plc_delay_1ms_flag;





/*参数表*/
extern s16 parameter_table[MEAU_NUM];
extern s16 parameter_table_max[MEAU_NUM];
extern s16 parameter_table_min[MEAU_NUM];
extern s16 parameter_table_step[MEAU_NUM];
extern const s16 parameter_table_default[MEAU_NUM];

void motor_parameter_read (void);


#endif