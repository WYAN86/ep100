#ifndef __SAFE_H
#define __SAFE_H

#include "stm32f10x.h"
#include "IQmathLib.h"
#include "gpio_conf.h"


#include "parameter.h"
#include "speed.h"
#include "adc.h"
#include "angle.h"
#include "pid.h"
#include "low_filter.h"
#include "error.h"


// �������
#define NORMAL                0
#define OVER_SPEED            1
#define OVER_VOLTAGE          2
#define LACK_OF_VOLTAGE       3
#define ENCODER_ERROR         9
#define IPM_FAULT             11
#define POSITION_ERROR        4
#define SPEED_PID_SATURATION  6
#define CWCCW_ERR             7
#define POSITION_OVERFLOW     8         // �Զ���
#define OVER_LOAD             13
#define OVER_CURRENT          12
#define OVER_HEAT             16
#define EEPROM_ERR            20

/* ϵͳ״̬*/
#define INITIAL 1
#define WAIT    2
#define READY   3
#define RUN     4
#define STOP    5
#define END     6

#define STOP_CONTROL 255       //???
#define PLC_CONTROL 0
#define SR_CONTROL  1
#define JOG_CONTROL 2

#define NO_GRADE_ERROR    0
#define HIGH_GRADE_ERROR  1
#define LOW_GRADE_ERROR   2

typedef struct
{
     // ----------�����ź�---------
     u8  Drive_Soft;
     u8  Drive_Lv;
     u16 Drive_Lv_Cnt;
     u8  Drive_Power_On_Once;
     u8  Drive_Power_On_Once_Cnt;
     u8  Drive_Ov;
     u16 Drive_Ov_Cnt;
     u8  Drive_Br;
     u8  Drive_Ipm_Fault;
     // ----------�����ź�---------
     
     // ----------PLC�ź�----------
     u8 Plc_In_SON;                  //�ŷ�ʹ��
     u8 Plc_In_ALRS;                 //�������
     u8 Plc_In_FSTP;                 // CCW������ֹ
     u8 Plc_In_RSTP;                 // CW������ֹ
     u8 Plc_In_CLESC1ZEROSPD;        // ƫ����������㡢�ٶ�ѡ��1��������λ
     u8 Plc_In_INHSC2;               // ָ�������ֹ���ٶ�ѡ��2
     u8 Plc_In_FIL;                  // CCWת�ؽ�ֹ
     u8 Plc_In_RIL;                  // CWת�ؽ�ֹ
     u8 Plc_Out_ALM;
     u8 Plc_Out_SRDY;
     u8 Plc_Out_BRK;
     u8 Plc_Out_COIN;
     // ----------PLC�ź�----------
     
     // ----------������-----------
     u8  Encoder_Test_A;
     u8  Encoder_Test_B;
     u8  Encoder_Test_Z;
     u8  Encoder_Test_U;
     u8  Encoder_Test_V;
     u8  Encoder_Test_W;
     u16 Encoder_Test_Cnt;
     // ----------������-----------
     
     // ----------���ư��ź�-------
     u8 Control_Power_On;
     u8 Eeprom_Error;
     // ----------���ư��ź�-------
     
     // ----------ϵͳ״̬---------
     u8 Current_On;
     u8 Servo_Error_Grade;
     u8 Servo_Error;
     u8 Servo_Error_Code;
     u8 System_State;               // �ŷ�״̬
     u8 Command_Input;              // ����ָ���־
     u8 Command_Mode;               // 0��PLC���� 1��SR 2:JOG
     // ----------ϵͳ״̬---------
} safe;

#define safe_default {0 , 0}

extern safe safe_parameter;

extern u8  plc_delay_flag_1;
extern u32 plc_delay_1;
extern u8  plc_delay_flag_2;
extern u32 plc_delay_2;
extern u8  plc_delay_flag_3;
extern u32 plc_delay_3;
extern u32 encoder_check_T;

extern u8  ov_delay_flag;
extern u32 ov_delay;

extern u8  br_delay_flag;
extern u32 br_delay;

void safe_function(void);
void system_error_function(safe *v);
void system_initial_state(safe *v);
void system_wait_state(safe *v);
void system_ready_state(safe *v);
void system_run_state(safe *v);
void system_stop_state(safe *v);
void system_end_state(safe *v);

void plc_calc(safe *v);
void led_twinkle(u16 x_ms);
void safe_init(safe *v);
void encoder_check(safe *v);
void drive_check(safe *v);
void plc_check(safe *v);
void safe_calc(safe *p);
void control_power_check_init(void);
//void speed_check(speed_view *p,safe *v);
void speed_arrive_check(void);
void position_arrive_check(void);
void safe_speed_pid_saturation(void);
void cwccw_check(safe *v);
void coin_enable(void);
void coin_disable(void);

void led_conf(void);
void led_run_on(void);
void led_run_off(void);
void led_power_on(void);
void led_power_off(void);

//void output_test(void);

#endif