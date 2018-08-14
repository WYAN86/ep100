#ifndef __MOTOR_PARAMETER_H
#define __MOTOR_PARAMETER_H

#include "stm32f10x.h"
#include "IQmathLib.h"

//#include "parameter.h"
//#include "angle.h"


/*********************************菜单参数个数**********************************/
#define MOTOR_PARAMETER_NUM            14
#define MOTOR_NUM                      24

typedef struct
{
     u16  Type_Num; 		//型号代码
     float  Rate_Current;   // 额定电流 A
     float  U_reverse;      // 反电动势 V/krpm
     s16  Max_Torque;       // 最大转矩 %
     u16  Rate_Speed;		// 额定转速 r/min
     s16  Max_Speed;		// 最大转速 r/min
     u16  LineEncoder;      //编码器线数 p/r
     u16  Pole_Num;         //电机极对数 对极
     u16  UVW_Flag;         //编码器类型 1：有UVW 0：省线式
     u16  Encoder_Offset;   //编码器零位
     s16  Kp_Current;	     // 电流环增益
     s16  Ki_Current;	     // 电流环积分 (时间常数)
     s16  Kp_Speed;	     // 速度环增益
     s16  Ki_Speed;	     // 速度环积分 (时间常数)
} motor;

extern const motor motor_parameter[MOTOR_NUM];


#endif