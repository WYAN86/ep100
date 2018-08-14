#include "tim8.h"

tim8_pwm tim8_pwm_parameter;


void tim8_conf(void)
{
     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
     TIM_OCInitTypeDef TIM_OCInitStructure;
     TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
     GPIO_InitTypeDef GPIO_InitStructure;
     NVIC_InitTypeDef NVIC_InitStructure;
 
     
    
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 , ENABLE);
     
     TIM_DeInit(TIM8);
     
     
     TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
     TIM_TimeBaseStructure.TIM_Prescaler = PWM_PRSC;                        
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;  
     TIM_TimeBaseStructure.TIM_Period = PWM_PERIOD_FACTOR;                            
     TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                  
     TIM_TimeBaseStructure.TIM_RepetitionCounter = REP_RATE;                  
     TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
     
     
     TIM_OCStructInit(&TIM_OCInitStructure);
     TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                      
     TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;          
     TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;       
     TIM_OCInitStructure.TIM_Pulse = 0;                                  
     TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;              
     TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;            
     TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;           
     TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;          
     TIM_OC1Init(TIM8, &TIM_OCInitStructure);
    
     TIM_OCInitStructure.TIM_Pulse = 0;
     TIM_OC2Init(TIM8, &TIM_OCInitStructure);
     
     TIM_OCInitStructure.TIM_Pulse = 0;
     TIM_OC3Init(TIM8, &TIM_OCInitStructure);
     
    
     TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
     TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
     TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
     
     TIM_ARRPreloadConfig(TIM8, ENABLE);
     
     GPIO_StructInit(&GPIO_InitStructure);
     // CH1
     GPIO_InitStructure.GPIO_Pin = CH1_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(CH1_GPIO_PORT, &GPIO_InitStructure);
     // CH2
     GPIO_InitStructure.GPIO_Pin = CH2_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(CH2_GPIO_PORT, &GPIO_InitStructure);
     // CH3
     GPIO_InitStructure.GPIO_Pin = CH3_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(CH3_GPIO_PORT, &GPIO_InitStructure);
     // CH1N
     GPIO_InitStructure.GPIO_Pin = CH1N_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(CH1N_GPIO_PORT, &GPIO_InitStructure);
     // CH2N
     GPIO_InitStructure.GPIO_Pin = CH2N_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(CH2N_GPIO_PORT, &GPIO_InitStructure);
     // CH3N
     GPIO_InitStructure.GPIO_Pin = CH3N_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(CH3N_GPIO_PORT, &GPIO_InitStructure);
     // IPM_FAULT
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = IPM_FAULT_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(IPM_FAULT_GPIO_PORT, &GPIO_InitStructure);
     
     
     TIM_BDTRStructInit(&TIM_BDTRInitStructure);
     TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
     TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
     TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
     TIM_BDTRInitStructure.TIM_DeadTime = DT_PERIOD;                       
     TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;                  
     TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;    
     TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
     TIM_BDTRConfig(TIM8, &TIM_BDTRInitStructure);    
  
     TIM_ClearITPendingBit(TIM8, TIM_IT_Break);             
     TIM_ITConfig(TIM8, TIM_IT_Break, ENABLE);             
     
     GPIO_EXTILineConfig(IPM_FAULT_PortSource, IPM_FAULT_PinSource);
     
  
     
     
     NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
     
     TIM_ClearITPendingBit(TIM8, TIM_IT_Update);            
     TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);           
     
    
     TIM_SelectOutputTrigger(TIM8, TIM_TRGOSource_Update);
}



void tim8_pwm_update(tim8_pwm *p)
{
     u16 Tmp;    
     
     Tmp = (u16) ( (PWM_PERIOD_FACTOR*p->MfuncC1)>>15 );
     TIM8->CCR1 = Tmp;
     
     Tmp = (u16) ( (PWM_PERIOD_FACTOR*p->MfuncC2)>>15 );
     TIM8->CCR2 = Tmp;
     
     Tmp = (u16) ( (PWM_PERIOD_FACTOR*p->MfuncC3)>>15 );
     TIM8->CCR3 = Tmp;
}