#include "rcc_conf.h"

void rcc_config(void)
{
     ErrorStatus HSEStartUpStatus;  
     GPIO_InitTypeDef GPIO_InitStructure;
     
     
     /* RCC system reset(for debug purpose) */
     //RCC_DeInit();
     
 
     RCC_HSEConfig(RCC_HSE_ON);
     
     HSEStartUpStatus = RCC_WaitForHSEStartUp();
     
     if(HSEStartUpStatus == SUCCESS)
     {
        
          FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
          
         
          FLASH_SetLatency(FLASH_Latency_2);
          
         
          RCC_HCLKConfig(RCC_SYSCLK_Div1); 
          
          
          RCC_PCLK2Config(RCC_HCLK_Div1); 
          
          
          RCC_PCLK1Config(RCC_HCLK_Div2);
          
         RCC_ADCCLKConfig(RCC_PCLK2_Div6);
          
         
          RCC_MCOConfig(RCC_MCO_PLLCLK_Div2);
          
                    
          RCC->CIR = 0x00000000;
          
          
          RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
          
        
          RCC_PLLCmd(ENABLE);
          
          
          while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
          {
          }
          
          
          RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
          
          
          while(RCC_GetSYSCLKSource() != 0x08)
          {
          }
     }
     
    
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
     
 
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
                            RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF |
                            RCC_APB2Periph_GPIOG, ENABLE);
     
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = MCO_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(MCO_GPIO_PORT, &GPIO_InitStructure);
     
    
}