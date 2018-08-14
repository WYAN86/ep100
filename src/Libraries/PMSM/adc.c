#include "adc.h"


// 电流采样的变量
phase_current phase_current_parameter;
as as_parameter = as_default;


u16 current_sense_times_tmp = 0;
u16 as_sense_times_tmp = 0;

void phase_current_conf(void)
{
     ADC_InitTypeDef ADC_InitStructure;
     GPIO_InitTypeDef GPIO_InitStructure;
     

     RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2 | RCC_APB2Periph_ADC3, ENABLE);
     
     
     // IV引脚
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = IV_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
     GPIO_Init(IV_GPIO_PORT, &GPIO_InitStructure);
     // IW引脚
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = IW_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
     GPIO_Init(IW_GPIO_PORT, &GPIO_InitStructure);

     GPIO_PinRemapConfig(GPIO_Remap_ADC1_ETRGREG,ENABLE);
     

     ADC_DeInit(ADC1);
     ADC_DeInit(ADC3);
     

     ADC_StructInit(&ADC_InitStructure);
     ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
     ADC_InitStructure.ADC_ScanConvMode = DISABLE;  
     ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
     ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_Ext_IT11_TIM8_TRGO;
     ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Left;
     ADC_InitStructure.ADC_NbrOfChannel = 1;
     ADC_Init(ADC1, &ADC_InitStructure);
     ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T8_TRGO;
     ADC_Init(ADC3, &ADC_InitStructure);
     

     ADC_RegularChannelConfig(ADC1, IV_ADC_CHANNEL,1,ADC_SampleTime_13Cycles5);
     ADC_RegularChannelConfig(ADC3, IW_ADC_CHANNEL,1,ADC_SampleTime_13Cycles5);
     

     ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
     ADC_ClearFlag(ADC3, ADC_FLAG_EOC);
     

     ADC_ITConfig(ADC1, ADC_IT_EOC, DISABLE);
     ADC_ITConfig(ADC3, ADC_IT_EOC, DISABLE);
     

     ADC_ExternalTrigConvCmd(ADC1, ENABLE);
     ADC_ExternalTrigConvCmd(ADC3, ENABLE);
     
     ADC_Cmd(ADC1, ENABLE);
     ADC_Cmd(ADC3, ENABLE);
     
     //-------------------------------------------------------------------------
     // AS引脚
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = AS_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
     GPIO_Init(AS_GPIO_PORT, &GPIO_InitStructure);
     
     ADC_DeInit(ADC2);
     

     ADC_StructInit(&ADC_InitStructure);
     ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
     ADC_InitStructure.ADC_ScanConvMode = DISABLE;
     ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
     ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
     ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Left;
     ADC_InitStructure.ADC_NbrOfChannel = 1;
     ADC_Init(ADC2, &ADC_InitStructure);
     
     ADC_RegularChannelConfig(ADC2, AS_ADC_CHANNEL, 1, ADC_SampleTime_13Cycles5);
     
     ADC_Cmd(ADC2, ENABLE);
     
     ADC_ResetCalibration(ADC2);
     while(ADC_GetResetCalibrationStatus(ADC2));
     
     ADC_StartCalibration(ADC2);
     while(ADC_GetCalibrationStatus(ADC2));  
  
     ADC_SoftwareStartConvCmd(ADC2, ENABLE);
     //-------------------------------------------------------------------------
}


void phase_current_read(phase_current *v)
{
     s16 B_dataQ15,A_dataQ15;
     
     while(! ( ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) & ADC_GetFlagStatus(ADC3,ADC_FLAG_EOC) ) )
     {
     }
     
     A_dataQ15 = (ADC_GetConversionValue(ADC1))^0x8000;
     v->ImeasA =  _IQ15toIQ(A_dataQ15);
     B_dataQ15 = (ADC_GetConversionValue(ADC3))^0x8000;
     v->ImeasB =  _IQ15toIQ(B_dataQ15);
     
     if(v->Offset_OK == 0)
     {          
          if(current_sense_times_tmp == 1024)
          {
               v->PhaseAOffset = (s32) v->ImeasAAcc >> 10;
               v->PhaseBOffset = (s32) v->ImeasBAcc >> 10;
               
               v->PhaseAOffset = _IQ15toIQ(v->PhaseAOffset);
               v->PhaseBOffset = _IQ15toIQ(v->PhaseBOffset);
               v->Offset_OK = 1;
          }
          else
          {
               v->ImeasAAcc += A_dataQ15;
               v->ImeasBAcc += B_dataQ15;
          }
          current_sense_times_tmp = current_sense_times_tmp + 1;
     }
     else if(v->Offset_OK == 1)
     {
          v->ImeasA = v->ImeasA - v->PhaseAOffset;
          v->ImeasB = v->ImeasB - v->PhaseBOffset;
     }
     
     v->U = v->ImeasA + v->ImeasB;
     v->V = -v->ImeasA;
     v->W = -v->ImeasB;
     
     ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
     ADC_ClearFlag(ADC3, ADC_FLAG_EOC);
     
     ADC_SoftwareStartConvCmd(ADC2, ENABLE);
}


void as_read(as *v)
{
     s16 tmp;
     
     while( ! ( ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC) ) )
     {
     }
     
     tmp = (ADC_GetConversionValue(ADC2))^0x8000;
     
     if(v->Offset_OK == 0)
     {
          if(as_sense_times_tmp == 1024)
          {
               v->ASOffset = (s32) v->ASAcc >> 10;
               v->Offset_OK = 1;
          }
          else
          {
               v->ASAcc += tmp;
          }
          as_sense_times_tmp = as_sense_times_tmp + 1;
     }
     else if(v->Offset_OK == 1)
     {
          v->ImeasAS = v->ASOffset - tmp;
     }
     
     ADC_ClearFlag(ADC2, ADC_FLAG_EOC);
}