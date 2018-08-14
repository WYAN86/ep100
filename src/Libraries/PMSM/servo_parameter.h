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
          
          s16 PositionGain; //0,位置比例增益
          int16 PositionFeedFowardGain;//1,比例前馈增益
          int16 SpeedGain;//2,速度比例增益
          int16 SpeedIntegralCons;//3,速度积分常数
          int16 SpeedFdbFilterFactor;//4,速度反馈滤波因子
          int16 MaxTorqueCurrentLimit;//5,最大转矩电流限制
          int16 AccelerationTimeCons;//6,加速时间常常(最大可以容许的指令加速度pulse/0.1ms)
          int16 SpeedCommandInputGain;//7,速度输入比例增益
          int16 SpeedCommandZeroDriftCompensation;//8,速度指令零漂补偿
          int16 ToruqeCommandInputGain;//9,力矩指令增益
          int16 TorqueCommandZeroDriftCompensation;//10,力矩指令零漂补偿
          int16 PositionSpeedReachRange;//11,定位完成范围,或速度完成范围
          int16 PositionToleranceTestRange;//12,位置超差检测范围
          int16 PositionCommandNum;//13,位置指令分频分子
          int16 PositionCommandDen;//14,位置指令分频分母
          int16 PosTorqueLimit;//15,正力矩限制
          int16 NegTorqueLimit;//16,负力矩限制
          int16 MaxSpeedLimit;//17,最大速度限制
          int16 OverloadCurrentSet;//18,过电流设置
          int16 SoftOverloadTimeSet;//19,软件过载时间限制
          int16 InsideSpeedSet;//20,内部速度
          int16 JogSpeedSet;//21,Jog速度
          int16 PositionCommandMode;//22,位置命令输入方式
          int16 ControlMode;//23,控制模式
          int16 MotorPole;//24,电机极对数
          int16 EncoderResolution;//25,编码器分辨率
          int16 NetworkCommuPeriod;//26网络通讯周期
          int16 CurrentControlGain;//27,电流控制增益
          int16 CurrentControlIntigral;//28,电流控制积分
          int16 SecondPositionCommandNum;//29,第二位置指令分频分子
          int16 MotorAntivoltageCons;//30,电机反电动势常数
          int16 NetWorkAlmMaxTime;//31网络报警最大允许次数（1代表不允许网络出错）
          int16 FeedforwardFilterCons;//32,前馈滤波常数
          int16 TorqueCommandFilterCons;//33,力矩指令滤波常数
          int16 TrapFilterFreq;//34,陷波器频率
          int16 PositionCommandFilterCons;//35,位置指令滤波时间常数
          int16 InertiaRate;//36,负载转动惯量比
          int16 LoadStiffness;//37,负载刚性
          int16 DecelerationTimeCons;//38,减速时间常数
          int16 NetworkAddress;//39网络地址
          int16 NetworkTotalPoint;//40 总节点数
          int16 PhyDelayCons;     //41 Phy延时时间常数
          int16 PosDifferentialCons;//42 位置微分系数
          int16 PosIntegralCons; //43
          union CONTL_PARAM_MODE ControlParametMode;//44控制参数模式设置
          union FAILURE_ALARM FailureAlarm;//45故障报警
          
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