#include "led_key.h"


void led_key_config(void)
{
     GPIO_InitTypeDef GPIO_InitStructure;
     
     //********************************led接口引脚定义*******************************
     GPIO_StructInit(&GPIO_InitStructure);
     // CH452的DCLK，输出
     GPIO_InitStructure.GPIO_Pin = DCLK_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽复用输出
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(DCLK_GPIO_PORT, &GPIO_InitStructure);
     // CH452的DIN，输出
     GPIO_InitStructure.GPIO_Pin = DIN_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽复用输出
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(DIN_GPIO_PORT, &GPIO_InitStructure);
     // CH452的LOAD，输出
     GPIO_InitStructure.GPIO_Pin = LOAD_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽复用输出
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(LOAD_GPIO_PORT, &GPIO_InitStructure);
     // CH452的DOUT，输入
     GPIO_InitStructure.GPIO_Pin = DOUT_GPIO_PIN;
     //   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //推挽复用输出
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(DOUT_GPIO_PORT, &GPIO_InitStructure);
     //******************************************************************************
     
     
     /* //delay引脚配置
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  //推挽复用输出
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOF, &GPIO_InitStructure);*/
     
     led_write(CH452_RESET);
     led_write(CH452_SYSON2);
     //led_write(CH452_BCD);
     led_write(CH452_NO_BCD);
}

//输出操作命令子程序
//定义一无符号整型变量存储12字节的命令字。
void led_write(u16 cmd)
{
     u16 i;
     GPIO_ResetBits(LOAD_GPIO_PORT, LOAD_GPIO_PIN);
     for(i=0;i!=12;i++)		//送入12位数据，低位在前
     {
          if(cmd&1) 
          {
               GPIO_SetBits(DIN_GPIO_PORT, DIN_GPIO_PIN);
          }
          else
          {
               GPIO_ResetBits(DIN_GPIO_PORT, DIN_GPIO_PIN);
          }
          GPIO_ResetBits(DCLK_GPIO_PORT, DCLK_GPIO_PIN);
          cmd>>=1;
          GPIO_SetBits(DCLK_GPIO_PORT, DCLK_GPIO_PIN);
     }
     GPIO_SetBits(LOAD_GPIO_PORT, LOAD_GPIO_PIN);
     delay_10us();				//命令数据加载周期不小于6US,CH451不需要该周期
}

//输入按键代码子程序，从CH452读取
u8 key_read(void)
{
     u16 i;
     u8 cmd,keycode;		//定义命令字，和数据存储器
     cmd=0x07;			               //读按键的命令字
     GPIO_ResetBits(LOAD_GPIO_PORT, LOAD_GPIO_PIN);
     for(i=0;i!=4;i++)  // 只需要发出高4位,多发也可以,但应该确保最后留下的4位是该命令码
     {
          if(cmd&1)
          {
               GPIO_SetBits(DIN_GPIO_PORT, DIN_GPIO_PIN);
          }
          else
          {
               GPIO_ResetBits(DIN_GPIO_PORT, DIN_GPIO_PIN);
          }          
          GPIO_ResetBits(DCLK_GPIO_PORT, DCLK_GPIO_PIN);
          cmd>>=1;			      //往右移一位
          GPIO_SetBits(DCLK_GPIO_PORT, DCLK_GPIO_PIN);
          }
     GPIO_SetBits(LOAD_GPIO_PORT, LOAD_GPIO_PIN);
     delay_1us();	
     keycode=0;				      //清除keycode
     for(i=0;i!=7;i++)
     {
          keycode<<=1;	      //数据移入keycode,高位在前,低位在后
          if(GPIO_ReadInputDataBit(DOUT_GPIO_PORT, DOUT_GPIO_PIN)==1)
          {
               keycode++;
          }
          GPIO_ResetBits(DCLK_GPIO_PORT, DCLK_GPIO_PIN);
          GPIO_SetBits(DCLK_GPIO_PORT, DCLK_GPIO_PIN);
     }
     return(keycode);			     //反回键值
}


