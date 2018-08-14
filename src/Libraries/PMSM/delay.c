#include "delay.h"

//************************************不精确延时函数****************************

void delay_1us(void)
{
     u16 time1;
     for(time1=0;time1<8;time1++)
     {
          asm("nop");
          asm("nop");
          //GPIOF->BSRR = GPIO_Pin_0;
          //GPIOF->BRR = GPIO_Pin_0;
     }
}

void delay_2us(void)
{
     u16 time1;
     for(time1=0;time1<16;time1++)
     {      
          asm("nop");asm("nop");
          //GPIOF->BSRR = GPIO_Pin_0;
          //GPIOF->BRR = GPIO_Pin_0;
     }
}

void delay_10us(void)
{
     u16 time1;
     for(time1=0;time1<80;time1++)
     {     
          asm("nop");asm("nop");
          //GPIOF->BSRR = GPIO_Pin_0;
          //GPIOF->BRR = GPIO_Pin_0;
     }
}

void delay_50us(void)
{
     u16 time1;
     for(time1=0;time1<400;time1++)
     {     
          asm("nop");asm("nop");
          //GPIOF->BSRR = GPIO_Pin_0;
          //GPIOF->BRR = GPIO_Pin_0;
     }
}

void delay_200us(void)
{
     u16 time1;
     for(time1=0;time1<1600;time1++)
     { 
          asm("nop");asm("nop"); 
          //GPIOF->BSRR = GPIO_Pin_0;
          //GPIOF->BRR = GPIO_Pin_0;
     }
}

/*
void delay(u16 count)
{
          for(count=0;time<count;count++)
                    delay_1us();          
}
*/

/*
void delay_x_ms(u16 x)
{
          u16 y=0;
          while(y != x)
                    if( delay_1ms_flag == 1)
                    {
                              delay_1ms_flag =0;
                              delay_1ms = 1;
                              y++;
                    }
}
*/


/*
void plc_delay_ms(u16 x)
{
          u16 y=0;
          while(y != x)
                    if( plc_delay_1ms_flag == 1)
                    {
                              plc_delay_1ms_flag =0;
                              plc_delay_1ms = 1;
                              y++;
                    }
}
*/
//******************************************************************************