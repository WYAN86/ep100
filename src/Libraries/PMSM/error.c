#include "error.h"

// 1 超速错误
u8  ERROR_over_speed = 0;
// 2 过压错误
u8  ERROR_over_voltage = 0;
// 3 欠压错误
u8  ERROR_lack_voltage = 0;
// 4 位置误差错误
u8  ERROR_pos_err = 0;
// 5 过热错误
u8  ERROR_over_heat = 0;
u32 ERROR_over_heat_counter = 0;
// 6 速度PID饱和错误
u8  ERROR_speed_pid_saturation = 0;
u32 ERROR_speed_pid_saturation_counter = 0;
// 7 驱动禁止异常
u8  ERROR_cwccw = 0;
// 8 位置溢出错误
u8  ERROR_pos_overflow = 0;
// 9 编码器错误
u8  ERROR_encoder = 0;
// 10 控制电源错误
u8  ERROR_control_power = 0;
// 11 IPM错误
u8  ERROR_ipm = 0;
// 12 过电流错误
u8  ERROR_over_current = 0;
u32 ERROR_over_current_counter = 0;
// 13 过负载错误
u8  ERROR_over_load = 0;
u32 ERROR_over_load_counter = 0;
// 14 制动错误
u8  ERROR_brake = 0;
// 15 编码器计数错误
u8  ERROR_encoder_count = 0;
// 16 过热错误
//u8  ERROR_over_heat = 0;           // 跟5是重复的
// 20 eeprom错误
u8  ERROR_eeprom = 0;
// 29 用户转矩过载错误
u8  ERROR_over_user_load = 0;
// 30 Z脉冲丢失错误
u8  ERROR_z = 0;



// 1 超速错误
u8  ERROR_over_speed_now = 0;
// 2 过压错误
u8  ERROR_over_voltage_now = 0;
// 3 欠压错误
u8  ERROR_lack_voltage_now = 0;
// 4 位置误差错误
//u8  ERROR_pos_err_now = 0;
// 5 过热错误
//u8  ERROR_over_heat_now = 0;
// 6 速度PID饱和错误
//u8  ERROR_speed_pid_saturation_now = 0;
// 7 驱动禁止异常
u8  ERROR_cwccw_now = 0;
// 8 位置溢出错误
//u8  ERROR_pos_overflow_now = 0;



u8 ERROR_high_grade_code[20];
u8 ERROR_low_grade_code[10];

u8 temp_mask;
void error_calc(void)
{
     u8 i = 0;
     u8 j = 0;
     
     for(i=0; i<20; i++)
     {
          ERROR_high_grade_code[i] = 0;
     }

     for(i=0; i<10; i++)
     {
          ERROR_low_grade_code[i] = 0;
     }
     
     i = 0;
     
     
     // ---------------------------高等级错误----------------------------------
     if( ERROR_over_speed==1 )
     {
          temp_mask = (u8)parameter_table[ErrMask1to6]&0x01;
          if(temp_mask == 0)
          {
               ERROR_high_grade_code[i] = 1;
               i++;
          }
     }
     
     if( ERROR_speed_pid_saturation == 1)
     {
          temp_mask = (u8)parameter_table[ErrMask1to6]&0x20;
          if(temp_mask == 0)
          {
               ERROR_high_grade_code[i] = 6;
               i++;
          }
     }
     
     if( ERROR_cwccw == 1)
     {
          temp_mask = (u8)parameter_table[ErrMask7to12]&0x01;
          if(temp_mask == 0)
          {
               ERROR_high_grade_code[i] = 7;
               i++;
          }
     }
     
     if( ERROR_pos_overflow == 1)
     {
          temp_mask = (u8)parameter_table[ErrMask7to12]&0x02;
          if(temp_mask == 0)
          {
               ERROR_high_grade_code[i] = 8;
               i++;
          }
     }
     

     if( ERROR_encoder==1)
     {          
          temp_mask = (u8)parameter_table[ErrMask7to12]&0x04;
          if(temp_mask == 0)
          {
               ERROR_high_grade_code[i] = 9;
               i++;
          }
     }

     if( ERROR_control_power == 1)
     {
          temp_mask = (u8)parameter_table[ErrMask7to12]&0x08;
          if(temp_mask == 0)
          {
               ERROR_high_grade_code[i] = 10;
               i++;
          }
     }
     
     if( ERROR_ipm == 1)
     {
          ERROR_high_grade_code[i] = 11;
          i++;
     }
     
     if( ERROR_over_current == 1)
     {
          ERROR_high_grade_code[i] = 12;
          i++;
     }
     
     if( ERROR_brake == 1)
     {
          temp_mask = (u8)parameter_table[ErrMask13to18]&0x02;
          if(temp_mask == 0)
          {
               ERROR_high_grade_code[i] = 14;
               i++;
          }
     }
     
     if( ERROR_encoder_count == 1)
     {
          ERROR_high_grade_code[i] = 15;
          i++;
     }
     
     if( ERROR_eeprom == 1)
     {
          ERROR_high_grade_code[i] = 20;
          i++;
     }
     
     if( ERROR_over_user_load == 1)
     {
          temp_mask = (u8)parameter_table[ErrMask25to30]&0x10;
          if(temp_mask == 0)
          {
               ERROR_high_grade_code[i] = 29;
               i++;
          }
     }
     
     if( ERROR_z == 1)
     {
          temp_mask = (u8)parameter_table[ErrMask25to30]&0x20;
          if(temp_mask == 0)
          {
               ERROR_high_grade_code[i] = 30;
               i++;
          }
     }
     // ---------------------------高等级错误----------------------------------
     
     // ---------------------------低等级错误----------------------------------
     if( ERROR_over_voltage == 1)
     {
          temp_mask = (u8)parameter_table[ErrMask1to6]&0x02;
          if(temp_mask == 0)
          {
               ERROR_low_grade_code[i] = 2;
               j++;
          }
     }
     
     if( ERROR_lack_voltage == 1)
     {
          temp_mask = (u8)parameter_table[ErrMask1to6]&0x04;
          if(temp_mask == 0)
          {
               ERROR_low_grade_code[i] = 3;
               j++;
          }
     }
     
     if( ERROR_pos_err == 1)
     {
          temp_mask = (u8)parameter_table[ErrMask1to6]&0x08;
          if(temp_mask == 0)
          {
               ERROR_low_grade_code[i] = 4;
               j++;
          }
     }
     
     if( ERROR_over_heat == 1)
     {
          temp_mask = (u8)parameter_table[ErrMask1to6]&0x10;
          if(temp_mask == 0)
          {
               ERROR_low_grade_code[i] = 5;
               j++;
          }
     }
     
     if( ERROR_over_load == 1)
     {
          temp_mask = (u8)parameter_table[ErrMask13to18]&0x01;
          if(temp_mask == 0)
          {
               ERROR_low_grade_code[i] = 13;
               j++;
          }
     }
     // ---------------------------低等级错误----------------------------------
}
          
          



void error_reset(void)
{
     // 1 超速错误
     if((ERROR_over_speed == 1) && (ERROR_over_speed_now == 0))
     {
          ERROR_over_speed = 0;
     }
     // 2 过压错误
     if((ERROR_over_voltage == 1) && (ERROR_over_voltage_now == 0))
     {
          ERROR_over_voltage = 0;
     }
     // 3 欠压错误
     if((ERROR_lack_voltage == 1) && (ERROR_lack_voltage_now == 0))
     {
          ERROR_lack_voltage = 0;
     }
     // 4 位置误差错误
     ERROR_pos_err = 0;
     // 5 过热错误     
     ERROR_over_heat = 0;
     ERROR_over_heat_counter = 0;
     // 6 速度PID饱和错误     
     ERROR_speed_pid_saturation = 0;
     ERROR_speed_pid_saturation_counter = 0;
     // 7 驱动禁止异常     
     if((ERROR_cwccw == 1) && (ERROR_cwccw_now == 0))
     {
          ERROR_cwccw = 0;
     }     
     // 8 位置溢出错误   
     ERROR_pos_overflow = 0;
}
