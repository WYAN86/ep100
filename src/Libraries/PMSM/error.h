#ifndef __ERROR_H
#define __ERROR_H

#include "stm32f10x.h"
#include "IQmathLib.h"
#include "parameter.h"


extern u8 ERROR_high_grade_code[20];
extern u8 ERROR_low_grade_code[10];


// 1 ���ٴ���
extern u8  ERROR_over_speed;
// 2 ��ѹ����
extern u8  ERROR_over_voltage;
// 3 Ƿѹ����
extern u8  ERROR_lack_voltage;
// 4 λ��������
extern u8  ERROR_pos_err;
// 5 ���ȴ���
extern u8  ERROR_over_heat;
extern u32 ERROR_over_heat_counter;
// 6 �ٶ�PID���ʹ���
extern u8  ERROR_speed_pid_saturation;
extern u32 ERROR_speed_pid_saturation_counter;
// 7 ������ֹ�쳣
extern u8  ERROR_cwccw;
// 8 λ���������
extern u8  ERROR_pos_overflow;
// 9 ����������
extern u8  ERROR_encoder;
// 10 ���Ƶ�Դ����
extern u8  ERROR_control_power;
// 11 IPM����
extern u8  ERROR_ipm;
// 12 ����������
extern u8  ERROR_over_current;
extern u32 ERROR_over_current_counter;
// 13 �����ش���
extern u8  ERROR_over_load;
extern u32 ERROR_over_load_counter;
// 14 �ƶ�����
extern u8  ERROR_brake;
// 15 ��������������
extern u8  ERROR_encoder_count;
// 16 ���ȴ���
//extern u8  ERROR_over_heat;           // ��5���ظ���
// 20 eeprom����
extern u8  ERROR_eeprom;
// 29 �û�ת�ع��ش���
extern u8  ERROR_over_user_load;
// 30 Z���嶪ʧ����
extern u8  ERROR_z;



// 1 ���ٴ���
extern u8  ERROR_over_speed_now;
// 2 ��ѹ����
extern u8  ERROR_over_voltage_now;
// 3 Ƿѹ����
extern u8  ERROR_lack_voltage_now;
// 4 λ��������
//extern u8  ERROR_pos_err_now;
// 5 ���ȴ���
//extern u8  ERROR_over_heat_now;
// 6 �ٶ�PID���ʹ���
//extern u8  ERROR_speed_pid_saturation_now;
// 7 ������ֹ�쳣
extern u8  ERROR_cwccw_now;
// 8 λ���������
//extern u8  ERROR_pos_overflow_now;


void error_calc(void);
void error_reset(void);


#endif