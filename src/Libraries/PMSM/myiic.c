#include "myiic.h"
#include "delay.h"
//STM32软件模拟IIC，STM32的硬件IIC太难用了！
//Mini STM32开发板
//IIC 驱动函数
//正点原子@ALIENTEK
//2010/6/10 
//初始化IIC

void sda_set_in(void)
{
     GPIO_InitTypeDef GPIO_InitStructure;
     
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = SDA_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(SDA_GPIO_PORT, &GPIO_InitStructure);
}


void sda_set_out(void)
{
     GPIO_InitTypeDef GPIO_InitStructure;
     
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = SDA_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(SDA_GPIO_PORT, &GPIO_InitStructure);
}

void scl_set_out(void)
{
     GPIO_InitTypeDef GPIO_InitStructure;
     
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = SCL_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(SCL_GPIO_PORT, &GPIO_InitStructure);
}




void IIC_Init(void)
{
     //RCC->APB2ENR|=1<<4;//先使能外设IO PORTC时钟 							 
	//GPIOC->CRH&=0XFFF00FFF;//PC11/12 推挽输出
	//GPIOC->CRH|=0X00033000;	   
	//GPIOC->ODR|=3<<11;     //PC11,12 输出高  
     sda_set_out();
     scl_set_out();
     GPIO_SetBits(SDA_GPIO_PORT, SDA_GPIO_PIN);
     GPIO_SetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
}


//产生IIC起始信号
void IIC_Start(void)
{
     //SDA_OUT();     //sda线输出
     sda_set_out();
     //IIC_SDA=1;
     GPIO_SetBits(SDA_GPIO_PORT, SDA_GPIO_PIN);
     //IIC_SCL=1;
     GPIO_SetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
     delay_2us();
     delay_2us();
     //IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
     GPIO_ResetBits(SDA_GPIO_PORT, SDA_GPIO_PIN);
     delay_2us();
     delay_2us();
     //IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
     GPIO_ResetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
}	  

//产生IIC停止信号
void IIC_Stop(void)
{   
     //SDA_OUT();//sda线输出
     sda_set_out();
     //IIC_SCL=0;
     GPIO_ResetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
     //IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
     GPIO_ResetBits(SDA_GPIO_PORT, SDA_GPIO_PIN);
     delay_2us();
     delay_2us();
     //IIC_SCL=1; 
     GPIO_SetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
     //IIC_SDA=1;//发送I2C总线结束信号
     GPIO_SetBits(SDA_GPIO_PORT, SDA_GPIO_PIN);
     delay_2us();
     delay_2us();
}


//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
     u8 ucErrTime=0;
     u8 return_temp=0;
     //SDA_IN();      //SDA设置为输入  
     sda_set_in();
     //IIC_SDA=1;
     GPIO_SetBits(SDA_GPIO_PORT, SDA_GPIO_PIN);
     delay_1us();
     //IIC_SCL=1;
     GPIO_SetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
     delay_1us(); 
     //while(READ_SDA)
     while (GPIO_ReadInputDataBit(SDA_GPIO_PORT, SDA_GPIO_PIN))
     {
          ucErrTime++;
          if(ucErrTime>250)
          {
               IIC_Stop();
               return_temp=1;
          }
     }
     //IIC_SCL=0;//时钟输出0 	   
     GPIO_ResetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
     return return_temp;  
} 


//产生ACK应答
void IIC_Ack(void)
{
     //IIC_SCL=0;
     GPIO_ResetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
     //SDA_OUT();
     sda_set_out();
     //IIC_SDA=0;
     GPIO_ResetBits(SDA_GPIO_PORT, SDA_GPIO_PIN);
     delay_2us();
     //IIC_SCL=1;
     GPIO_SetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
     delay_2us();
     //IIC_SCL=0;
     GPIO_ResetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
}


//不产生ACK应答		    
void IIC_NAck(void)
{
     //IIC_SCL=0;
     GPIO_ResetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
     //SDA_OUT();
     sda_set_out();
     //IIC_SDA=1;
     GPIO_SetBits(SDA_GPIO_PORT, SDA_GPIO_PIN);
     delay_2us();
     //IIC_SCL=1;
     GPIO_SetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
     delay_2us();
     //IIC_SCL=0;
     GPIO_ResetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
}		


//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{
     u8 t;   
     //SDA_OUT(); 
     sda_set_out();
     //IIC_SCL=0;//拉低时钟开始数据传输
     GPIO_ResetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
     for(t=0;t<8;t++)
     {              
          //IIC_SDA=(txd&0x80)>>7;
          if((txd&0x80)>>7)
          {
               GPIO_SetBits(SDA_GPIO_PORT, SDA_GPIO_PIN);
          }
          else
          {
               GPIO_ResetBits(SDA_GPIO_PORT, SDA_GPIO_PIN);  
          }
          txd<<=1; 	  
          delay_2us();
          //IIC_SCL=1;
          GPIO_SetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
          delay_2us();
          //IIC_SCL=0;
          GPIO_ResetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
          delay_2us();
     }	 
} 	    



//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(u8 ack)
{
     u8 i,receive=0;
     //SDA_IN();//SDA设置为输入
     sda_set_in();
     for(i=0;i<8;i++ )
     {
          //IIC_SCL=0; 
          GPIO_ResetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
          delay_2us();
          //IIC_SCL=1;
          GPIO_SetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
          receive<<=1;
          if(GPIO_ReadInputDataBit(SDA_GPIO_PORT, SDA_GPIO_PIN))        
          {
               receive++;
          }
          delay_1us();
     }		
     if (!ack)
     {
          IIC_NAck();//发送nACK
     }
     else
     {
          IIC_Ack(); //发送ACK 
     }
     return receive;
}



























