#include "encoder.h"

void encoder_config(void)
{
     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
     TIM_ICInitTypeDef TIM_ICInitStructure;
     GPIO_InitTypeDef GPIO_InitStructure;
     EXTI_InitTypeDef EXTI_InitStructure;
     NVIC_InitTypeDef NVIC_InitStructure;
     

     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);     
     

     // A
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = A_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(A_GPIO_PORT, &GPIO_InitStructure);
     // B
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = B_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(B_GPIO_PORT, &GPIO_InitStructure);
     
     TIM_DeInit(TIM2);
     TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);  
     TIM_TimeBaseStructure.TIM_Prescaler = 0;
     TIM_TimeBaseStructure.TIM_Period = 65535;
     TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
     TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
     
     TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
     TIM_ICStructInit(&TIM_ICInitStructure);
     TIM_ICInitStructure.TIM_ICFilter = 0;
     TIM_ICInit(TIM2, &TIM_ICInitStructure);
     
     TIM_ClearFlag(TIM2, TIM_FLAG_Update);
     TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
     
     TIM2->CNT = 0;
     TIM_Cmd(TIM2, ENABLE);

     
     //2、设置U、V、W、Z的引脚
     // U
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = U_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(U_GPIO_PORT, &GPIO_InitStructure);
     
     // V
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = V_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(V_GPIO_PORT, &GPIO_InitStructure);
     
     // W
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = W_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(W_GPIO_PORT, &GPIO_InitStructure);
     
     // Z
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = Z_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(Z_GPIO_PORT, &GPIO_InitStructure);
     
     GPIO_EXTILineConfig(Z_PortSource, Z_PinSource);
     
     EXTI_InitStructure.EXTI_Line = Z_Line; 
     EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
     EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
     EXTI_InitStructure.EXTI_LineCmd = ENABLE;
     EXTI_Init(&EXTI_InitStructure);
     
     // z中断配置
     NVIC_InitStructure.NVIC_IRQChannel = Z_IRQ;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
     
     EXTI->EMR |= 0x00000020;
}



u8 encoder_uvw_read(void)
{
     u8 tmp=0;
     // U
     if(GPIO_ReadInputDataBit(U_GPIO_PORT, U_GPIO_PIN)==1)
     {
          tmp=4;
     }
     // V
     if(GPIO_ReadInputDataBit(V_GPIO_PORT, V_GPIO_PIN)==1)
     {
          tmp=tmp+2;
     }
     // W
     if(GPIO_ReadInputDataBit(W_GPIO_PORT, W_GPIO_PIN)==1)
     {
          tmp=tmp+1;
     }
     return(tmp);
}


u16 encoder_counter_read(void)
{
     return(TIM2->CNT);
}

