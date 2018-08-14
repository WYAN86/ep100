#ifndef __MENU_H
#define __MENU_H

#include "stm32f10x.h"
#include "IQmathLib.h"

#include "motor_parameter.h"
#include "led_key.h"
#include "safe.h"
#include "24cxx.h"
#include "parameter.h"
#include "system_parameter.h"
#include "cmd.h"



#define   UP        66
#define   DOWN      67
#define   ESC       65
#define   ENTER     64


//struct menu_item null_struct;
//struct menu_item main_menu[8];  //主菜单
//struct menu_item dp_menu[21];    //监视方式
//struct menu_item pr_menu[4];    //参数设置
//struct menu_item ee_menu[4];    //参数管理
//struct menu_item sr_menu[4];    //速度试运行
//struct menu_item jr_menu[4];    //JOG运行
//struct menu_item ru_menu[4];    //自动增益调整
//struct menu_item co_menu[4];    //编码器调零
//struct menu_item ol_menu[4];    //开环运行

extern u32 keydelay;
extern u32 disdelay;
extern u16 key_value;


void menu_init(void);
void menu_function(void);


void menu_displaychar(void);

void menu_1(void);
void menu_2(void);
void menu_21(void);
void menu_22(void);
void menu_23(void);
void menu_24(void);
void menu_25(void);
void menu_26(void);
void menu_27(void);
void menu_28(void);
void menu_3(void);
void menu_31(void);
void menu_32(void);
void menu_33(void);
void disp_1(void);
void disp_2(void);
void disp_3(void);
void disp_31(void);
void disp_32(void);

void disp_fault(void);

#endif