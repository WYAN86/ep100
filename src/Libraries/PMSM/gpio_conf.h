#ifndef __GPIO_CONF_H
#define __GPIO_CONF_H


#include "stm32f10x.h"

//--------------------MCO-------------------------------------------------------
#define MCO_GPIO_PIN        GPIO_Pin_8
#define MCO_GPIO_PORT       GPIOA

//--------------------ADC-------------------------------------------------------
#define AS_GPIO_PIN        GPIO_Pin_0
#define AS_GPIO_PORT       GPIOC
#define AS_ADC_CHANNEL     ADC_Channel_10

#define IV_GPIO_PIN        GPIO_Pin_1
#define IV_GPIO_PORT       GPIOC
#define IV_ADC_CHANNEL     ADC_Channel_11

#define IW_GPIO_PIN        GPIO_Pin_2
#define IW_GPIO_PORT       GPIOC
#define IW_ADC_CHANNEL     ADC_Channel_12
//------------------------------------------------------------------------------

//--------------------DAC-------------------------------------------------------
#define DA1_GPIO_PIN        GPIO_Pin_4
#define DA1_GPIO_PORT       GPIOA

#define DA2_GPIO_PIN        GPIO_Pin_5
#define DA2_GPIO_PORT       GPIOA
//------------------------------------------------------------------------------

//--------------------CMD-------------------------------------------------------
#define PLUS_CH1_GPIO_PIN        GPIO_Pin_9
#define PLUS_CH1_GPIO_PORT       GPIOE
#define SIGN_CH2_GPIO_PIN        GPIO_Pin_11
#define SIGN_CH2_GPIO_PORT       GPIOE

#define PLUS_ETR_GPIO_PIN        GPIO_Pin_7
#define PLUS_ETR_GPIO_PORT       GPIOE
#define SIGN_ETR_GPIO_PIN        GPIO_Pin_0
#define SIGN_ETR_GPIO_PORT       GPIOE
//------------------------------------------------------------------------------

//--------------------ENCODER---------------------------------------------------
#define A_GPIO_PIN    GPIO_Pin_0
#define A_GPIO_PORT   GPIOA
#define B_GPIO_PIN    GPIO_Pin_1
#define B_GPIO_PORT   GPIOA
#define Z_GPIO_PIN    GPIO_Pin_5
#define Z_GPIO_PORT   GPIOE
#define Z_PortSource  GPIO_PortSourceGPIOE
#define Z_PinSource   GPIO_PinSource5
#define Z_Line        EXTI_Line5
#define Z_IRQ         EXTI9_5_IRQn
#define U_GPIO_PIN    GPIO_Pin_4
#define U_GPIO_PORT   GPIOE
#define V_GPIO_PIN    GPIO_Pin_3
#define V_GPIO_PORT   GPIOE
#define W_GPIO_PIN    GPIO_Pin_2
#define W_GPIO_PORT   GPIOE
//------------------------------------------------------------------------------

//--------------------LED_KEY---------------------------------------------------
#define DCLK_GPIO_PIN         GPIO_Pin_3
#define DCLK_GPIO_PORT        GPIOD
#define DIN_GPIO_PIN          GPIO_Pin_2
#define DIN_GPIO_PORT         GPIOD
#define LOAD_GPIO_PIN         GPIO_Pin_1
#define LOAD_GPIO_PORT        GPIOD
#define DOUT_GPIO_PIN         GPIO_Pin_4
#define DOUT_GPIO_PORT        GPIOD

#define LED_RUN_GPIO_PIN      GPIO_Pin_10
#define LED_RUN_GPIO_PORT     GPIOD

#define LED_POWER_GPIO_PIN    GPIO_Pin_11
#define LED_POWER_GPIO_PORT   GPIOD

//------------------------------------------------------------------------------

//--------------------I2C-------------------------------------------------------
#define SDA_GPIO_PIN         GPIO_Pin_13
#define SDA_GPIO_PORT        GPIOD
#define SCL_GPIO_PIN         GPIO_Pin_14
#define SCL_GPIO_PORT        GPIOD
//------------------------------------------------------------------------------

//--------------------tim8------------------------------------------------------
#define CH1_GPIO_PIN    GPIO_Pin_6
#define CH1_GPIO_PORT   GPIOC
#define CH2_GPIO_PIN    GPIO_Pin_7
#define CH2_GPIO_PORT   GPIOC
#define CH3_GPIO_PIN    GPIO_Pin_8
#define CH3_GPIO_PORT   GPIOC
#define CH1N_GPIO_PIN   GPIO_Pin_7
#define CH1N_GPIO_PORT  GPIOA
#define CH2N_GPIO_PIN   GPIO_Pin_0
#define CH2N_GPIO_PORT  GPIOB
#define CH3N_GPIO_PIN   GPIO_Pin_1
#define CH3N_GPIO_PORT  GPIOB
#define IPM_FAULT_GPIO_PIN        GPIO_Pin_6
#define IPM_FAULT_GPIO_PORT       GPIOA
#define IPM_FAULT_PortSource      GPIO_PortSourceGPIOA
#define IPM_FAULT_PinSource       GPIO_PinSource6
#define IPM_FAULT_Line            EXTI_Line6
#define IPM_FAULT_IRQ             EXTI9_5_IRQn
//------------------------------------------------------------------------------

//--------------------SAFE------------------------------------------------------

// PLC输出引脚宏定义
#define BRK_GPIO_PIN             GPIO_Pin_15
#define BRK_GPIO_PORT            GPIOD
#define COIN_GPIO_PIN            GPIO_Pin_9
#define COIN_GPIO_PORT           GPIOC
#define ALM_GPIO_PIN             GPIO_Pin_9
#define ALM_GPIO_PORT            GPIOA
#define SRDY_GPIO_PIN            GPIO_Pin_10
#define SRDY_GPIO_PORT           GPIOA
          
// PLC输入引脚宏定义
#define SON_GPIO_PIN              GPIO_Pin_5
#define SON_GPIO_PORT             GPIOD
#define ALRS_GPIO_PIN             GPIO_Pin_6
#define ALRS_GPIO_PORT            GPIOD
#define FSTP_GPIO_PIN             GPIO_Pin_7
#define FSTP_GPIO_PORT            GPIOD
#define RSTP_GPIO_PIN             GPIO_Pin_5
#define RSTP_GPIO_PORT            GPIOB
#define CLESC1ZEROSPD_GPIO_PIN    GPIO_Pin_6
#define CLESC1ZEROSPD_GPIO_PORT   GPIOB
#define INHSC2_GPIO_PIN           GPIO_Pin_7
#define INHSC2_GPIO_PORT          GPIOB
#define FIL_GPIO_PIN              GPIO_Pin_8
#define FIL_GPIO_PORT             GPIOB
#define RIL_GPIO_PIN              GPIO_Pin_9
#define RIL_GPIO_PORT             GPIOB

// 驱动板引脚宏定义
#define OV_GPIO_PIN               GPIO_Pin_3
#define OV_GPIO_PORT              GPIOA
#define LV_GPIO_PIN               GPIO_Pin_5
#define LV_GPIO_PORT              GPIOC
#define SOFT_GPIO_PIN             GPIO_Pin_4
#define SOFT_GPIO_PORT            GPIOC
#define BR_GPIO_PIN               GPIO_Pin_2
#define BR_GPIO_PORT              GPIOA


// 编码器检测信号
#define UTEST2ARM_GPIO_PIN               GPIO_Pin_11
#define UTEST2ARM_GPIO_PORT              GPIOB
#define VTEST2ARM_GPIO_PIN               GPIO_Pin_13
#define VTEST2ARM_GPIO_PORT              GPIOE
#define WTEST2ARM_GPIO_PIN               GPIO_Pin_15
#define WTEST2ARM_GPIO_PORT              GPIOE
#define ATEST2ARM_GPIO_PIN               GPIO_Pin_14
#define ATEST2ARM_GPIO_PORT              GPIOB
#define BTEST2ARM_GPIO_PIN               GPIO_Pin_13
#define BTEST2ARM_GPIO_PORT              GPIOB
#define ZTEST2ARM_GPIO_PIN               GPIO_Pin_12
#define ZTEST2ARM_GPIO_PORT              GPIOB
//------------------------------------------------------------------------------



#endif
















