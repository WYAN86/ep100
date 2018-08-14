#ifndef __SYSTEM_PARAMETER_H
#define __SYSTEM_PARAMETER_H

#include "stm32f10x.h"
#include "IQmathLib.h"
#include "motor_parameter.h"
#include "parameter.h"
#include "pid.h"
#include "low_filter.h"
#include "rampctrl.h"

#define PI                3.14

// _IQ(1)
#define IQ_Z_1            16777216
// _IQ(-1)
#define IQ_F_1            -16777216

// _IQ(0.5)
#define IQ_Z_1_DIV_2      8388608
// _IQ(-0.5)
#define IQ_F_1_DIV_2      -8388608

// _IQ(0.8660254)
#define IQ_Z_SQRT3_DIV_2  14529495
// _IQ(-0.8660254)
#define IQ_F_SQRT3_DIV_2  -14529495

// _IQ(0.95)
#define IQ_Z_0_DOT_95     15938355
// _IQ(-0.95)
#define IQ_F_0_DOT_95     -15938355

//_IQ(0.01)
#define _IQ_Z_0_DOT_01    167772

//_IQ(0.1)
#define _IQ_Z_0_DOT_1     1677721

//_IQ(0.3)
#define _IQ_Z_0_DOT_3     5033164

//_IQ((1/sqrt(3)) / (2/pi))
#define _IQ_PM            15215251

//_IQ(0.9068)
#define _IQ_Z_0_DOT_9068  15213579

//_IQ(0.9517)
#define _IQ_Z_0_DOT_9517  15966876

//_IQ(0.9999)
#define _IQ_Z_0_DOT_9999  16777048

//_IQ(0.9095)
#define _IQ_Z_0_DOT_9095  15258877

//_IQ(-30.23)
#define _IQ_F_30_DOT_23   -507175239

//_IQ(27.94)
#define _IQ_Z_27_DOT_94   468755415

//_IQ(0.9485)
#define _IQ_Z_0_DOT_9485  15913189

//_IQ(-8.58)
#define _IQ_F_8_DOT_58    -143948513

//_IQ(8.23)
#define _IQ_Z_8_DOT_23    139586437

//_IQ(-26.43)
#define _IQ_F_26_DOT_43   -443421818

//_IQ(25.15)
#define _IQ_Z_25_DOT_15   421946982

//_IQ(0.9800)
#define _IQ_Z_0_DOT_9800  16441671

//_IQ(6.40)
#define _IQ_Z_6_DOT_40    107374182

//_IQ(6.09)
#define _IQ_Z_6_DOT_09    102173245

//_IQ(0.9975)
#define _IQ_Z_0_DOT_9975  16735272

//_IQ(11.75)
#define _IQ_Z_11_DOT_75   197132288

//_IQ(11.34)
#define _IQ_Z_11_DOT_34   190253629

//_IQ(48.96)
#define _IQ_Z_48_DOT_96   821412495

//_IQ(48.43)
#define _IQ_Z_48_DOT_43   812520570

//_IQ(pi/6)
#define _IQ_Z_pi_div_6    8784529

//_IQ(2/sqrt(3))
#define _IQ_Z_2_div_sqrt3    19372660



//--------------------------------------系统采样电流最大值----------------------
#define CURRENT_UNIT 24.0
//--------------------------------------系统采样电流最大值----------------------


//--------------------------------------PWM参数---------------------------------
#define PWM_FREQ   ( (u16) 10000)                                             // 电流环100us中断的频率(Hz)
#define CKTIM	    ( (u32) 72000000uL )                                       // 系统时钟(Hz)
#define PWM_PRSC   ( (u8) 0 )                                                 // 定时器预分频
#define PWM_PERIOD ( (u16) (CKTIM / (u32)(2 * PWM_FREQ *(PWM_PRSC+1))))       // 定时器的周期 = PWM的半周期
#define REP_RATE   ( (u8) 1)                                                  // 重复计数器，REP_RATE+1=pwm半周期
/* 死区时间计算方法*/
/*Tdts=1/72M*/
/*DTG[7:5]=0xx,  DT=DTG[7:0]*Tdgt,  Tdgt=Tdts*/
/*DTG[7:5]=10x,  DT=(64+DTG[5:0])*Tdgt,  Tdgt=2*Tdts*/
/*DTG[7:5]=101,  DT=(32+DTG[4:0])*Tdgt,  Tdgt=8*Tdts*/
/*DTG[7:5]=111,  DT=(32+DTG[4:0])*Tdgt,  Tdgt=16*Tdts*/
/*====>>>*/
/*若Tdgt=Tdts，0-1.763888(us)*/
/*若Tdgt=2*Tdts，1.777777-3.527777(us)*/
/*若Tdgt=8*Tdts，3.555555-7(us)*/
/*若Tdgt=16*Tdts，7.111111-14(us)*/
/***********************************************************/
/*#define DT_PERIOD  0xB3 */                  /* 死区周期3.2us*/
#define DT_PERIOD  0x48                     /* 死区周期1.0us*/
//------------------------------------------------------------------------------

//----------------------------------电流环参数--------------------------------------------
#define CURRENT_LOOP_FREQ       PWM_FREQ
//------------------------------------------------------------------------------

//----------------------------------速度环参数--------------------------------------------
#define SPEED_LOOP_PRESCALER          5
#define SPEED_LOOP_FREQ               ( CURRENT_LOOP_FREQ/SPEED_LOOP_PRESCALER )
//#define SPEED_CALCULATE_FACTOR        ( (float)SPEED_LOOP_FREQ*2*3.14/CNT_PER_ROUND )
//#define SPEED_VIEW_FACTOR             ( (u16) (PWM_FREQ*60/CNT_PER_ROUND) )
//#define SPEED_UNIT                    314         // 对应3000rpm
//#define SPEED_COMMAND                 ( (float) ( 16777216 / ( (float)SPEED_UNIT/PI/2*60) ) )
//------------------------------------------------------------------------------


//----------------------------------编码器参数--------------------------------------------
#define POLE                4
#define CNT_PER_ROUND       10000     /* 2500*4*/
//#define DIV_CNT_PER_ROUND   0.0001
//------------------------------------------------------------------------------



void system_parameter_init(void);



extern u16 PWM_PERIOD_FACTOR;
extern float SPEED_COMMAND_FACTOR;
extern s32 SPEED_CALC_FACTOR;
extern s32 SPEED_VIEW_CALC_FACTOR;
extern u16 SPEED_UNIT_FACTOR;
extern _iq SPEED_MAX_FACTOR;
extern _iq SPEED_MIN_FACTOR;
extern u16 AS_CALC_FACTOR;
extern _iq AS_COMPENSATE_FACTOR;
extern s32 SPEED_PID_SATURATION_TIME_FACTOR;
extern u16 SPEED_ARRIVE_FACTOR;
extern float SPEED_CMD_VIEW_FACTOR;

extern _iq INTERIOR_TORQUE_MAX_FACTOR;
extern _iq INTERIOR_TORQUE_MIN_FACTOR;
extern _iq EXTERIOR_TORQUE_MAX_FACTOR;
extern _iq EXTERIOR_TORQUE_MIN_FACTOR;
extern _iq SR_TORQUE_MAX_FACTOR;
extern _iq SR_TORQUE_MIN_FACTOR;
extern _iq OVER_LOAD_MAX_FACTOR;
extern s32 OVER_LOAD_TIME_FACTOR;
extern _iq OVER_HEAT_MAX_FACTOR;
extern s32 OVER_HEAT_TIME_FACTOR;
extern _iq OVER_CURRENT_MAX_FACTOR;
extern s32 OVER_CURRENT_TIME_FACTOR;
// 转矩显示系数
extern float MOTOR_TORQUE_VIEW_FACTOR;
// 电流显示系数
extern float MOTOR_CURRENT_VIEW_FACTOR;


extern s32 POS_ERR_MAX_FACTOR;
extern u16 POS_ARRIVE_FACTOR;

extern float ELC_GEAR_FACTOR;
extern s32 ELC_GEAR_MUL_MAX;
extern s32 ELC_GEAR_MUL_FDB;

extern u32 STOP_BRAKE_TIME_FACTOR;
extern u32 RUN_BRAKE_TIME_FACTOR;

extern u32 OV_TIME_FACTOR;
extern u32 BR_TIME_FACTOR;

#endif