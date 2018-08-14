#include "adc.h"


// ���������ı���
phase_current phase_current_parameter;


u16 current_sense_times_tmp = 0;

void phase_current_conf(void)
{
     ADC_InitTypeDef ADC_InitStructure;
     GPIO_InitTypeDef GPIO_InitStructure;
     
     GPIO_StructInit(&GPIO_InitStructure);
     // IV����
     GPIO_InitStructure.GPIO_Pin = IV_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
     GPIO_Init(IV_GPIO_PORT, &GPIO_InitStructure);
     // IW����
     GPIO_InitStructure.GPIO_Pin = IW_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
     GPIO_Init(IW_GPIO_PORT, &GPIO_InitStructure);
     // ADC1�ⲿ������ӳ��
     GPIO_PinRemapConfig(GPIO_Remap_ADC1_ETRGREG,ENABLE);  // �ⲿ��������ת����TIM8_TRGO����
     
     // ��λADC1��ADC3
     ADC_DeInit(ADC1);
     ADC_DeInit(ADC3);
     
     // ADC1��ADC3����
     ADC_StructInit(&ADC_InitStructure);
     ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  // ����ģʽ
     ADC_InitStructure.ADC_ScanConvMode = DISABLE;  // �ر�ɨ��ģʽ
     ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;  // ����ת��ģʽ
     ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_Ext_IT11_TIM8_TRGO;  // TIM8_TRGO
     ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Left;  // left align
     ADC_InitStructure.ADC_NbrOfChannel = 1;  // ����ͨ�����г��ȣ�1��ͨ��
     ADC_Init(ADC1, &ADC_InitStructure);
     ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T8_TRGO;
     ADC_Init(ADC3, &ADC_InitStructure);
     
     // ͨ���Ͳ���ʱ��
     ADC_RegularChannelConfig(ADC1, IV_ADC_CHANNEL,1,ADC_SampleTime_13Cycles5);
     ADC_RegularChannelConfig(ADC3, IW_ADC_CHANNEL,1,ADC_SampleTime_13Cycles5);
     
     // ���жϱ�־λ
     ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
     ADC_ClearFlag(ADC3, ADC_FLAG_EOC);
     
     // ��ֹ�ж�
     ADC_ITConfig(ADC1, ADC_IT_EOC, DISABLE);
     ADC_ITConfig(ADC3, ADC_IT_EOC, DISABLE);
     
     // ���ⲿ����ת��
     ADC_ExternalTrigConvCmd(ADC1, ENABLE);
     ADC_ExternalTrigConvCmd(ADC3, ENABLE);
     
     ADC_Cmd(ADC1, ENABLE);
     ADC_Cmd(ADC3, ENABLE);
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
}