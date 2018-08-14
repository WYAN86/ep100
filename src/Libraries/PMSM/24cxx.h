#ifndef __24CXX_H
#define __24CXX_H
#include "myiic.h"

#include "stm32f10x.h"
#include "delay.h"
#include "error.h"
#include "safe.h"

//extern u8 eeprom_err;


#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	        8191
#define AT24C128	16383
#define AT24C256	32767
#define EE_TYPE AT24C64

static u8 AT24CXX_ReadOneByte(u16 ReadAddr);							/*ָ����ַ��ȡһ���ֽ�*/
static void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite);		/*ָ����ַд��һ���ֽ�*/
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len);/*ָ����ַ��ʼд��ָ�����ȵ�����*/
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len);					/*ָ����ַ��ʼ��ȡָ����������*/
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);	/*��ָ����ַ��ʼд��ָ�����ȵ�����*/
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead);   	/*��ָ����ַ��ʼ����ָ�����ȵ�����*/

static u8 AT24CXX_Check(void);  /*�������*/
void AT24CXX_Init(void); /*��ʼ��IIC*/

u8 AT24CXX_Check1(void);

/*����д�룺������������*/
void par_to_par_region(void);

/*�������ݣ�������������*/
void par_to_backup_region(void);

/*������ȡ����������������*/
void par_region_to_par(void);

/*�ָ����ݣ���������������*/
void backup_region_to_par(void);

/*�ָ�ȱʡֵ��Ĭ��ֵ��������������������*/
void default_to_all (void);
#endif
















