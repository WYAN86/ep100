#include "cmd.h"


void cmd_config_init(void)
{
     if(parameter_table[PositionCommandMode]==0)
          cmd_plus_sign_config();
     else if(parameter_table[PositionCommandMode]==1)
               cmd_plus_plus_config();
     else if(parameter_table[PositionCommandMode]==2)
          cmd_quadrature_config();
}

u16 cmd_read(void)
{
     u16 tmp,tmp1,tmp2;
     if(parameter_table[PositionCommandMode]==0)
          tmp = TIM1->CNT;
     else if(parameter_table[PositionCommandMode]==1)
     {
          tmp1 = TIM1->CNT;
          tmp2 = TIM4->CNT;
          tmp = tmp1 - tmp2;
     }
     else if(parameter_table[PositionCommandMode]==2)
          tmp = TIM1->CNT;
     return tmp;
}

void cmd_quadrature_config(void)
{
     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
     TIM_ICInitTypeDef TIM_ICInitStructure;
     GPIO_InitTypeDef GPIO_InitStructure;
     
     // 打开tim1时钟
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
     
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = PLUS_CH1_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(PLUS_CH1_GPIO_PORT, &GPIO_InitStructure);
     
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = SIGN_CH2_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(SIGN_CH2_GPIO_PORT, &GPIO_InitStructure);
     
     // tim1重映射
     GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);
     
     TIM_DeInit(TIM1);
     TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
     TIM_TimeBaseStructure.TIM_Prescaler = 0;
     TIM_TimeBaseStructure.TIM_Period = 65535;
     TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
     TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
     
     TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
     
     TIM_ICStructInit(&TIM_ICInitStructure);
     TIM_ICInitStructure.TIM_ICFilter = 0;
     TIM_ICInit(TIM1, &TIM_ICInitStructure);
     
     TIM_ClearFlag(TIM1, TIM_FLAG_Update);
     TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);
     
     TIM1->CNT = 0;
     TIM_Cmd(TIM1, ENABLE);          
}

void cmd_plus_sign_config(void)
{
     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
     TIM_ICInitTypeDef TIM_ICInitStructure;
     GPIO_InitTypeDef GPIO_InitStructure;
     
     // 打开tim1时钟
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
     
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = PLUS_ETR_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(PLUS_ETR_GPIO_PORT, &GPIO_InitStructure);
     
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = SIGN_ETR_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(SIGN_ETR_GPIO_PORT, &GPIO_InitStructure);
     
     // tim1重映射
     GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);
     
     TIM_DeInit(TIM1);
     TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
     TIM_TimeBaseStructure.TIM_Prescaler = 0;
     TIM_TimeBaseStructure.TIM_Period = 65535;
     TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
     TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
     //TIM_SelectInputTrigger(TIM1, TIM_TS_ETRF);  // 外部触发输入
     
     TIM_ETRClockMode2Config(TIM1, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x0F);    
     
     TIM_ICStructInit(&TIM_ICInitStructure);
     TIM_ICInitStructure.TIM_ICFilter = 0;
     TIM_ICInit(TIM1, &TIM_ICInitStructure);
     
     TIM1->CNT = 0;
     
     TIM_Cmd(TIM1, ENABLE);
}

void cmd_plus_plus_config(void)
{
     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
     TIM_ICInitTypeDef TIM_ICInitStructure;
     GPIO_InitTypeDef GPIO_InitStructure;
     
     // 打开tim1时钟
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
     // 打开tim4时钟
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
     
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = PLUS_ETR_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(PLUS_ETR_GPIO_PORT, &GPIO_InitStructure);
     
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = SIGN_ETR_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(SIGN_ETR_GPIO_PORT, &GPIO_InitStructure);
     
     // tim1重映射
     GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);
     
     TIM_DeInit(TIM1);
     TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
     TIM_TimeBaseStructure.TIM_Prescaler = 0;
     TIM_TimeBaseStructure.TIM_Period = 65535;
     TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
     TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
     TIM_DeInit(TIM4);
     TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
     TIM_TimeBaseStructure.TIM_Prescaler = 0;
     TIM_TimeBaseStructure.TIM_Period = 65535;
     TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
     TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
     //TIM_SelectInputTrigger(TIM1, TIM_TS_ETRF);  // 外部触发输入
     
     TIM_ETRClockMode2Config(TIM1, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x0F);
     TIM_ETRClockMode2Config(TIM4, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x0F);
     
     TIM_ICStructInit(&TIM_ICInitStructure);
     TIM_ICInitStructure.TIM_ICFilter = 0;
     TIM_ICInit(TIM1, &TIM_ICInitStructure);
     
     TIM_ICStructInit(&TIM_ICInitStructure);
     TIM_ICInitStructure.TIM_ICFilter = 0;
     TIM_ICInit(TIM4, &TIM_ICInitStructure);
     
     TIM1->CNT = 0;
     TIM4->CNT = 0;
     
     TIM_Cmd(TIM1, ENABLE);
     TIM_Cmd(TIM4, ENABLE);
}
















/*

void cmd_config(void)
{
     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
     TIM_ICInitTypeDef TIM_ICInitStructure;
     GPIO_InitTypeDef GPIO_InitStructure;
     
     // 设置TIM1的ETR输入计数
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOA, &GPIO_InitStructure);
     
     
     
     TIM_DeInit(TIM1);
     //TIM_SelectInputTrigger(TIM1, TIM_TS_ETRF);  // 外部触发输入
     
     TIM_ETRClockMode2Config(TIM1, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x0F);     
     TIM_Cmd(TIM1, ENABLE);
     
     // 指令接收用TIM4
     //1、设置TIM4为编码器模式
     
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOB, &GPIO_InitStructure);
     
     TIM_DeInit(TIM4);
     TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
     TIM_TimeBaseStructure.TIM_Prescaler = 0;
     TIM_TimeBaseStructure.TIM_Period = 65535;
     TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
     TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
     
     TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
     TIM_ICStructInit(&TIM_ICInitStructure);
     TIM_ICInitStructure.TIM_ICFilter = 0;
     TIM_ICInit(TIM4, &TIM_ICInitStructure);
     
     TIM_ClearFlag(TIM4, TIM_FLAG_Update);
     TIM_ITConfig(TIM4, TIM_IT_Update, DISABLE);
     
     TIM4->CNT = 0;
     TIM_Cmd(TIM4, ENABLE);
}*/