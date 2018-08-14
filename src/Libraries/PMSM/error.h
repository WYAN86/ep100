#ifndef __ERROR_H
#define __ERROR_H

#include "stm32f10x.h"
#include "IQmathLib.h"
#include "parameter.h"


extern u8 ERROR_high_grade_code[20];
extern u8 ERROR_low_grade_code[10];


// 1 超速错误
extern u8  ERROR_over_speed;
// 2 过压错误
extern u8  ERROR_over_voltage;
// 3 欠压错误
extern u8  ERROR_lack_voltage;
// 4 位置误差错误
extern u8  ERROR_pos_err;
// 5 过热错误
extern u8  ERROR_over_heat;
extern u32 ERROR_over_heat_counter;
// 6 速度PID饱和错误
extern u8  ERROR_speed_pid_saturation;
extern u32 ERROR_speed_pid_saturation_counter;
// 7 驱动禁止异常
extern u8  ERROR_cwccw;
// 8 位置溢出错误
extern u8  ERROR_pos_overflow;
// 9 编码器错误
extern u8  ERROR_encoder;
// 10 控制电源错误
extern u8  ERROR_control_power;
// 11 IPM错误
extern u8  ERROR_ipm;
// 12 过电流错误
extern u8  ERROR_over_current;
extern u32 ERROR_over_current_counter;
// 13 过负载错误
extern u8  ERROR_over_load;
extern u32 ERROR_over_load_counter;
// 14 制动错误
extern u8  ERROR_brake;
// 15 编码器计数错误
extern u8  ERROR_encoder_count;
// 16 过热错误
//extern u8  ERROR_over_heat;           // 跟5是重复的
// 20 eeprom错误
extern u8  ERROR_eeprom;
// 29 用户转矩过载错误
extern u8  ERROR_over_user_load;
// 30 Z脉冲丢失错误
extern u8  ERROR_z;



// 1 超速错误
extern u8  ERROR_over_speed_now;
// 2 过压错误
extern u8  ERROR_over_voltage_now;
// 3 欠压错误
extern u8  ERROR_lack_voltage_now;
// 4 位置误差错误
//extern u8  ERROR_pos_err_now;
// 5 过热错误
//extern u8  ERROR_over_heat_now;
// 6 速度PID饱和错误
//extern u8  ERROR_speed_pid_saturation_now;
// 7 驱动禁止异常
extern u8  ERROR_cwccw_now;
// 8 位置溢出错误
//extern u8  ERROR_pos_overflow_now;


void error_calc(void);
void error_reset(void);


#endif