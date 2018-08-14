#include "viewer.h"


void viewer_conf(void)
{
     DAC_InitTypeDef DAC_InitStructure;
     GPIO_InitTypeDef GPIO_InitStructure;
     
     // 打开DAC的时钟
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);     
     
     // DA1引脚
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = DA1_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
     GPIO_Init(DA1_GPIO_PORT, &GPIO_InitStructure);
     // DA2引脚
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = DA2_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
     GPIO_Init(DA2_GPIO_PORT, &GPIO_InitStructure);
     
     // DAC 设置
     DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
     DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
     DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
     DAC_Init(DAC_Channel_1, &DAC_InitStructure);
     
     DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
     DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
     DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
     DAC_Init(DAC_Channel_2, &DAC_InitStructure);
}


void viewer(u8 channel1, u8 channel2)
{
     DAC_SetChannel1Data(DAC_Align_8b_R, channel1);
     DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);
     DAC_SetChannel2Data(DAC_Align_8b_R, channel2);
     DAC_SoftwareTriggerCmd(DAC_Channel_2,ENABLE);
}
