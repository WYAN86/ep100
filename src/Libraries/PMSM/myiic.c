#include "myiic.h"
#include "delay.h"
//STM32���ģ��IIC��STM32��Ӳ��IIC̫�����ˣ�
//Mini STM32������
//IIC ��������
//����ԭ��@ALIENTEK
//2010/6/10 
//��ʼ��IIC

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
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //����
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(SDA_GPIO_PORT, &GPIO_InitStructure);
}

void scl_set_out(void)
{
     GPIO_InitTypeDef GPIO_InitStructure;
     
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = SCL_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //����
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(SCL_GPIO_PORT, &GPIO_InitStructure);
}




void IIC_Init(void)
{
     //RCC->APB2ENR|=1<<4;//��ʹ������IO PORTCʱ�� 							 
	//GPIOC->CRH&=0XFFF00FFF;//PC11/12 �������
	//GPIOC->CRH|=0X00033000;	   
	//GPIOC->ODR|=3<<11;     //PC11,12 �����  
     sda_set_out();
     scl_set_out();
     GPIO_SetBits(SDA_GPIO_PORT, SDA_GPIO_PIN);
     GPIO_SetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
}


//����IIC��ʼ�ź�
void IIC_Start(void)
{
     //SDA_OUT();     //sda�����
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
     //IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
     GPIO_ResetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
}	  

//����IICֹͣ�ź�
void IIC_Stop(void)
{   
     //SDA_OUT();//sda�����
     sda_set_out();
     //IIC_SCL=0;
     GPIO_ResetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
     //IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
     GPIO_ResetBits(SDA_GPIO_PORT, SDA_GPIO_PIN);
     delay_2us();
     delay_2us();
     //IIC_SCL=1; 
     GPIO_SetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
     //IIC_SDA=1;//����I2C���߽����ź�
     GPIO_SetBits(SDA_GPIO_PORT, SDA_GPIO_PIN);
     delay_2us();
     delay_2us();
}


//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
     u8 ucErrTime=0;
     u8 return_temp=0;
     //SDA_IN();      //SDA����Ϊ����  
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
     //IIC_SCL=0;//ʱ�����0 	   
     GPIO_ResetBits(SCL_GPIO_PORT, SCL_GPIO_PIN);
     return return_temp;  
} 


//����ACKӦ��
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


//������ACKӦ��		    
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


//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{
     u8 t;   
     //SDA_OUT(); 
     sda_set_out();
     //IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
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



//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(u8 ack)
{
     u8 i,receive=0;
     //SDA_IN();//SDA����Ϊ����
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
          IIC_NAck();//����nACK
     }
     else
     {
          IIC_Ack(); //����ACK 
     }
     return receive;
}



























