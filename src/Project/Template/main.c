
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
     
     // ���Ƶ����ʼ��
     //control_power_check_init();
     
     // ʱ�ӳ�ʼ��
     rcc_config();
     
     id_parameter.id_set1 = 0x1E0CFF33;
     id_parameter.id_set2 = 0x36384B33;
     id_parameter.id_set3 = 0x43038538;     
     
     // �жϱ��ʼ��
     nvic_conf();
         
     // ����������ʼ��
     phase_current_conf();
     
     // ��������ʼ��
     encoder_config();
     
     //��ȫ������ʼ��
     safe_init(&safe_parameter);     
     
     
     // eeprom��ʼ��
     AT24CXX_Init();
     
     menu_init();
     
     // ����ָ���ʼ��
     cmd_config_init();
     
     // ���Ʋ�����ʼ��
     system_parameter_init();
     
     // ��ȡUVW�������ʼ�Ƕ�
     angle_parameter.Uvw = encoder_uvw_read();
     angle_init(&angle_parameter);
     angle_calc(&angle_parameter);
     
     // curve ��ʼ��
     curve_init(&curve_parameter);
     
     // ��ʱ����ʼ��
     tim8_conf();

     // ����ܺͰ�����ʼ��
     led_key_config();
     
     id_verify(&id_parameter);
     
     TIM_Cmd(TIM8, ENABLE);
     
     //TIM_Cmd(TIM3, ENABLE);
     
     // �ȴ���������ƫ�ò������
     
     
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
