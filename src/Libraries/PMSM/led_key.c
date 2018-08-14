#include "led_key.h"


void led_key_config(void)
{
     GPIO_InitTypeDef GPIO_InitStructure;
     
     //********************************led�ӿ����Ŷ���*******************************
     GPIO_StructInit(&GPIO_InitStructure);
     // CH452��DCLK�����
     GPIO_InitStructure.GPIO_Pin = DCLK_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //���츴�����
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(DCLK_GPIO_PORT, &GPIO_InitStructure);
     // CH452��DIN�����
     GPIO_InitStructure.GPIO_Pin = DIN_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //���츴�����
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(DIN_GPIO_PORT, &GPIO_InitStructure);
     // CH452��LOAD�����
     GPIO_InitStructure.GPIO_Pin = LOAD_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //���츴�����
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(LOAD_GPIO_PORT, &GPIO_InitStructure);
     // CH452��DOUT������
     GPIO_InitStructure.GPIO_Pin = DOUT_GPIO_PIN;
     //   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //���츴�����
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(DOUT_GPIO_PORT, &GPIO_InitStructure);
     //******************************************************************************
     
     
     /* //delay��������
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  //���츴�����
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOF, &GPIO_InitStructure);*/
     
     led_write(CH452_RESET);
     led_write(CH452_SYSON2);
     //led_write(CH452_BCD);
     led_write(CH452_NO_BCD);
}

//������������ӳ���
//����һ�޷������ͱ����洢12�ֽڵ������֡�
void led_write(u16 cmd)
{
     u16 i;
     GPIO_ResetBits(LOAD_GPIO_PORT, LOAD_GPIO_PIN);
     for(i=0;i!=12;i++)		//����12λ���ݣ���λ��ǰ
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
     delay_10us();				//�������ݼ������ڲ�С��6US,CH451����Ҫ������
}

//���밴�������ӳ��򣬴�CH452��ȡ
u8 key_read(void)
{
     u16 i;
     u8 cmd,keycode;		//���������֣������ݴ洢��
     cmd=0x07;			               //��������������
     GPIO_ResetBits(LOAD_GPIO_PORT, LOAD_GPIO_PIN);
     for(i=0;i!=4;i++)  // ֻ��Ҫ������4λ,�෢Ҳ����,��Ӧ��ȷ��������µ�4λ�Ǹ�������
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
          cmd>>=1;			      //������һλ
          GPIO_SetBits(DCLK_GPIO_PORT, DCLK_GPIO_PIN);
          }
     GPIO_SetBits(LOAD_GPIO_PORT, LOAD_GPIO_PIN);
     delay_1us();	
     keycode=0;				      //���keycode
     for(i=0;i!=7;i++)
     {
          keycode<<=1;	      //��������keycode,��λ��ǰ,��λ�ں�
          if(GPIO_ReadInputDataBit(DOUT_GPIO_PORT, DOUT_GPIO_PIN)==1)
          {
               keycode++;
          }
          GPIO_ResetBits(DCLK_GPIO_PORT, DCLK_GPIO_PIN);
          GPIO_SetBits(DCLK_GPIO_PORT, DCLK_GPIO_PIN);
     }
     return(keycode);			     //���ؼ�ֵ
}


