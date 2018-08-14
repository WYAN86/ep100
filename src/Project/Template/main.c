
#include "stm32f10x.h"
#include "IQmathLib.h"


#include "rcc_conf.h"
#include "nvic_conf.h"
#include "tim8.h"
#include "adc.h"
#include "encoder.h"
#include "cmd.h"
#include "led_key.h"
#include "24cxx.h"
#include "safe.h"
#include "system_parameter.h"
#include "angle.h"
#include "curve.h"
#include "menu.h"
#include "id.h"





int main(void)
{
     /* Setup STM32 system (clock, PLL and Flash configuration) */
     //  SystemInit();
     
     // 控制电检测初始化
     //control_power_check_init();
     
     // 时钟初始化
     rcc_config();
     
     id_parameter.id_set1 = 0x1E0CFF33;
     id_parameter.id_set2 = 0x36384B33;
     id_parameter.id_set3 = 0x43038538;     
     
     // 中断表初始化
     nvic_conf();
         
     // 电流采样初始化
     phase_current_conf();
     
     // 编码器初始化
     encoder_config();
     
     //安全保护初始化
     safe_init(&safe_parameter);     
     
     
     // eeprom初始化
     AT24CXX_Init();
     
     menu_init();
     
     // 脉冲指令初始化
     cmd_config_init();
     
     // 控制参数初始化
     system_parameter_init();
     
     // 获取UVW，计算初始角度
     angle_parameter.Uvw = encoder_uvw_read();
     angle_init(&angle_parameter);
     angle_calc(&angle_parameter);
     
     // curve 初始化
     curve_init(&curve_parameter);
     
     // 定时器初始化
     tim8_conf();

     // 数码管和案件初始化
     led_key_config();
     
     id_verify(&id_parameter);
     
     TIM_Cmd(TIM8, ENABLE);
     
     //TIM_Cmd(TIM3, ENABLE);
     
     // 等待电流采样偏置采样完毕
     
     
     /* Infinite loop */
     while (1)
     {       
          
          menu_function();
          
          safe_function();
          
          //asm("nop");
     }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
