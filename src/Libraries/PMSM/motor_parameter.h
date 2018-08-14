#ifndef __MOTOR_PARAMETER_H
#define __MOTOR_PARAMETER_H

#include "stm32f10x.h"
#include "IQmathLib.h"

//#include "parameter.h"
//#include "angle.h"


/*********************************�˵���������**********************************/
#define MOTOR_PARAMETER_NUM            14
#define MOTOR_NUM                      24

typedef struct
{
     u16  Type_Num; 		//�ͺŴ���
     float  Rate_Current;   // ����� A
     float  U_reverse;      // ���綯�� V/krpm
     s16  Max_Torque;       // ���ת�� %
     u16  Rate_Speed;		// �ת�� r/min
     s16  Max_Speed;		// ���ת�� r/min
     u16  LineEncoder;      //���������� p/r
     u16  Pole_Num;         //��������� �Լ�
     u16  UVW_Flag;         //���������� 1����UVW 0��ʡ��ʽ
     u16  Encoder_Offset;   //��������λ
     s16  Kp_Current;	     // ����������
     s16  Ki_Current;	     // ���������� (ʱ�䳣��)
     s16  Kp_Speed;	     // �ٶȻ�����
     s16  Ki_Speed;	     // �ٶȻ����� (ʱ�䳣��)
} motor;

extern const motor motor_parameter[MOTOR_NUM];


#endif