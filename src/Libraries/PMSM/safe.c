#include "safe.h"


extern s16 Cmd_Inc;
extern s32 Pos_Cmd;
extern s32 Pos_Ref;
//extern s32 Pos_RefH;
extern s32 Pos_Err;
extern s32 elc_gear_reset_cnt;

extern u16 Pos_Cnt_Pre;
extern u16 Pos_Cnt;

u8  plc_delay_flag_1=0;
u32 plc_delay_1=0;
u8  plc_delay_flag_2=0;
u32 plc_delay_2=0;
u8  plc_delay_flag_3=0;
u32 plc_delay_3=0;
u32 encoder_check_T=0;

u8  ov_delay_flag=0;
u32 ov_delay=0;

u8  br_delay_flag=0;
u32 br_delay=0;

void safe_function(void);
void srdy_enable(void);
void srdy_disable(void);
void alm_enable(void);
void alm_disable(void);
void brk_enable(void);
void brk_disable(void);
void Plc_Out (safe *v);

void clear_parameter(void);

// safe
safe safe_parameter;


void safe_function(void)
{
     // PLC信号
     plc_check(&safe_parameter);
     // 驱动板信号
     drive_check(&safe_parameter);
     // 编码器信号
     encoder_check(&safe_parameter);
     // 驱动禁止异常
     cwccw_check(&safe_parameter);
     
     error_calc();
     
     if(ERROR_high_grade_code[0] != 0)
     {
          safe_parameter.Servo_Error = 1;
          safe_parameter.Servo_Error_Grade = HIGH_GRADE_ERROR;
          safe_parameter.Servo_Error_Code  = ERROR_high_grade_code[0];
     }
     else if(ERROR_low_grade_code[0] != 0)
     {
          safe_parameter.Servo_Error = 1;
          safe_parameter.Servo_Error_Grade = LOW_GRADE_ERROR;
          safe_parameter.Servo_Error_Code  = ERROR_low_grade_code[0];
     }
     else
     {
          safe_parameter.Servo_Error = 0;
          safe_parameter.Servo_Error_Grade = NO_GRADE_ERROR;
          safe_parameter.Servo_Error_Code  = NORMAL;
          
          alm_disable();
          safe_parameter.Plc_Out_ALM = 0;
          
     }
     
     system_initial_state(&safe_parameter);
     system_error_function(&safe_parameter);
     system_wait_state(&safe_parameter);
     system_ready_state(&safe_parameter);
     system_run_state(&safe_parameter);
     system_stop_state(&safe_parameter);
     system_end_state(&safe_parameter);
     
     Plc_Out(&safe_parameter);
}



void safe_init(safe *v)
{
     GPIO_InitTypeDef GPIO_InitStructure;
     
     led_conf();          
          
     //-----------------------------------------------------------
     // 驱动板信号
     
     // OV
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = OV_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(OV_GPIO_PORT, &GPIO_InitStructure);
     
     // LV
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = LV_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(LV_GPIO_PORT, &GPIO_InitStructure);
     
     // SOFT
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = SOFT_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(SOFT_GPIO_PORT, &GPIO_InitStructure);
     
     // BRK
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = BR_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(BR_GPIO_PORT, &GPIO_InitStructure);
     
     // BRK
     GPIO_SetBits(BRK_GPIO_PORT, BRK_GPIO_PIN);
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = BRK_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(BRK_GPIO_PORT, &GPIO_InitStructure);
     
     // COIN
     GPIO_SetBits(COIN_GPIO_PORT, COIN_GPIO_PIN);
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = COIN_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(COIN_GPIO_PORT, &GPIO_InitStructure);
     
     // ALM
     GPIO_SetBits(ALM_GPIO_PORT, ALM_GPIO_PIN);
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = ALM_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(ALM_GPIO_PORT, &GPIO_InitStructure);
     
     // SRDY
     GPIO_SetBits(SRDY_GPIO_PORT, SRDY_GPIO_PIN);
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = SRDY_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(SRDY_GPIO_PORT, &GPIO_InitStructure); 
     
     srdy_disable();
          v->Plc_Out_SRDY = 0;
     alm_disable();
          v->Plc_Out_ALM = 0;
     coin_disable(); 
     v->Plc_Out_COIN = 0;
     brk_enable();   // 抱闸
          v->Plc_Out_BRK = 1;
     
     // SON2ARM
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = SON_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(SON_GPIO_PORT, &GPIO_InitStructure);
     
     // ALRS2ARM
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = ALRS_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(ALRS_GPIO_PORT, &GPIO_InitStructure);
     
     // FSTP2ARM
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = FSTP_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(FSTP_GPIO_PORT, &GPIO_InitStructure);
     
     // RSTP2ARM
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = RSTP_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(RSTP_GPIO_PORT, &GPIO_InitStructure);
     
     // CLESC1ZEROSPD2ARM
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = CLESC1ZEROSPD_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(CLESC1ZEROSPD_GPIO_PORT, &GPIO_InitStructure);
     
     // INHSC22ARM
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = INHSC2_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(INHSC2_GPIO_PORT, &GPIO_InitStructure);
     
     // FIL2ARM
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = FIL_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(FIL_GPIO_PORT, &GPIO_InitStructure);
     
     // RIL2ARM
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = RIL_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(RIL_GPIO_PORT, &GPIO_InitStructure);     
     //-----------------------------------------------------------
     
     //-----------------------------------------------------------
     // 编码器信号
     
     // ATEST2ARM
     GPIO_StructInit(&GPIO_InitStructure);     
     GPIO_InitStructure.GPIO_Pin = ATEST2ARM_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(ATEST2ARM_GPIO_PORT, &GPIO_InitStructure);
     
     // BTEST2ARM
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = BTEST2ARM_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(BTEST2ARM_GPIO_PORT, &GPIO_InitStructure);
     
     // ZTEST2ARM
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = ZTEST2ARM_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(ZTEST2ARM_GPIO_PORT, &GPIO_InitStructure);
     
     // UTEST2ARM
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = UTEST2ARM_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(UTEST2ARM_GPIO_PORT, &GPIO_InitStructure);
     
     // VTEST2ARM
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = VTEST2ARM_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(VTEST2ARM_GPIO_PORT, &GPIO_InitStructure);
     
     // WTEST2ARM
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = WTEST2ARM_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(WTEST2ARM_GPIO_PORT, &GPIO_InitStructure);     
     //-----------------------------------------------------------
     
     v->System_State = INITIAL;
     v->Command_Mode = STOP_CONTROL;
}

//void speed_check(speed_view *p, safe *v)
void speed_arrive_check(void)
{
     //if( abs(speed_view_parameter.speed_view_after_filter) >= parameter_table[MaxSpeed]*12/10 )
     //{
          //v->Servo_Error = 1;
          //v->Servo_Error_Code = OVER_SPEED;
     //     speed_view_parameter.over_speed_err = 1;
     //}
     
     // 在定时中断做
     /*
     if(parameter_table[ControlMode]!=0)
     {
          if( abs(speed_view_parameter.speed_view_after_filter) >= parameter_table[ArrivedSpeed] )
          {
               coin_disable();
          }
          else
          {
               coin_enable();
          }
     }*/
}

// ???
void position_arrive_check(void)
{
     // 在主中断里面做了
     //if( (parameter_table[PositionToleranceErrorRangeValid]==0) && (parameter_table[ControlMode]==0) )
     //{
     //     if( Pos_Err >= (parameter_table[PositionToleranceDetectionRange]*100) )
     //     {
               //v->Servo_Error = 1;
               //v->Servo_Error_Code = POSITION_ERROR;
     //          Pos_Err_Err = 1;
     //     }
     //} 
     
     // 位置溢出的定义跟迈信不一样，在主中断里面做了
     /*
     if( Pos_Err >= 1073741824 ) //1073741824
     {
          v->Servo_Error = 1;
          v->Servo_Error_Code = POSITION_OVERFLOW;
     }
     */
     
     // 在定时中断做
     /*
     if(parameter_table[ControlMode]==0)
     {
          if( Pos_Err >= parameter_table[LocationFinishRange] )
          {
               coin_disable();
          }
          else
          {
               coin_enable();
          }
     }*/
}

// ???

void safe_speed_pid_saturation(void)
{
     // 在pi_caculation里面做了
     /*
     if( (pid_speed.Out <= _IQ(-0.8)) || (pid_speed.Out >= _IQ(0.8)) )
     {
          //v->Servo_Error = 1;
          //v->Servo_Error_Code = SPEED_PID_SATURATION;
          pid_speed.Saturation_err = 1;
     }
     else if(v->Servo_Error_Code == SPEED_PID_SATURATION)
     {
          v->Servo_Error = 0;
          v->Servo_Error_Code = NORMAL;
     }
     */     
}


void cwccw_check(safe *v)
{
     if( (v->Plc_In_FSTP==0) && (v->Plc_In_RSTP==0) )
     {
          ERROR_cwccw_now = 1;
          ERROR_cwccw = 1;
     }
     else
     {
          ERROR_cwccw_now = 0;
          ERROR_cwccw = 0;
     }
}


void led_twinkle(u16 x_ms)
{
     //GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);
     //delay_x_ms(x_ms);
     //GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
     //delay_x_ms(x_ms);
}

// 检测PLC信号
// 1有效，0无效
void plc_check(safe *v)
{
     // SON
     if( (((u8)parameter_table[Lower4BitInputON])&((u8)0x01))==0x01 )
     {              
          v->Plc_In_SON = 1;
     }
     else 
     {
          if( GPIO_ReadInputDataBit(SON_GPIO_PORT, SON_GPIO_PIN)==0 )
          {
               v->Plc_In_SON = 1;
          }
          else
          {
               v->Plc_In_SON = 0;
          }
          if((((u8)parameter_table[Lower4BitInputReverse])&((u8)0x01))==0x01 )
          {
               v->Plc_In_SON =  v->Plc_In_SON == 1 ? 0 : 1;
          }
     }
     
     // ALRS
     if( (((u8)parameter_table[Lower4BitInputON])&((u8)0x02))==0x02 )
     {
          v->Plc_In_ALRS = 1;
     }
     else 
     {
          if( GPIO_ReadInputDataBit(ALRS_GPIO_PORT, ALRS_GPIO_PIN)==0 )
          {
               v->Plc_In_ALRS = 1;
          }
          else
          {
               v->Plc_In_ALRS = 0;
          }
          if((((u8)parameter_table[Lower4BitInputReverse])&((u8)0x02))==0x02 )
          {
               v->Plc_In_ALRS =  v->Plc_In_ALRS == 1 ? 0 : 1;
          }
     }
     
     // FSTP
     if(parameter_table[DriveForbiddenInvalid]==0)
     {
          if( (((u8)parameter_table[Lower4BitInputON])&((u8)0x04))==0x04 )
          {
               v->Plc_In_FSTP = 1;
          }
          else 
          {
               if( GPIO_ReadInputDataBit(FSTP_GPIO_PORT, FSTP_GPIO_PIN)==0 )
               {
                    v->Plc_In_FSTP = 1;
               }
               else
               {
                    v->Plc_In_FSTP = 0;
               }
               if((((u8)parameter_table[Lower4BitInputReverse])&((u8)0x04))==0x04 )
               {
                    v->Plc_In_FSTP =  v->Plc_In_FSTP == 1 ? 0 : 1;
               }
          }
     }
     else
     {
          v->Plc_In_FSTP = 1;
     }
     
     // RSTP
     if(parameter_table[DriveForbiddenInvalid]==0)
     {
          if( (((u8)parameter_table[Lower4BitInputON])&((u8)0x08))==0x08 )
          {
               v->Plc_In_RSTP = 1;
          }
          else 
          {
               if( GPIO_ReadInputDataBit(RSTP_GPIO_PORT, RSTP_GPIO_PIN)==0 )
               {
                    v->Plc_In_RSTP = 1;
               }
               else
               {
                    v->Plc_In_RSTP = 0;
               }
               if((((u8)parameter_table[Lower4BitInputReverse])&((u8)0x08))==0x08 )
               {
                    v->Plc_In_RSTP =  v->Plc_In_RSTP == 1 ? 0 : 1;
               }
          }
     }
     else 
     {
          v->Plc_In_RSTP = 1; 
     }
     
     // CLESC1ZEROSPD
     if( (((u8)parameter_table[Upper4BitInputON])&((u8)0x01))==0x01 )
     {
          v->Plc_In_CLESC1ZEROSPD = 1;
     }
     else 
     {
          if( GPIO_ReadInputDataBit(CLESC1ZEROSPD_GPIO_PORT, CLESC1ZEROSPD_GPIO_PIN)==0 )
          {
               v->Plc_In_CLESC1ZEROSPD = 1;
          }
          else
          {
               v->Plc_In_CLESC1ZEROSPD = 0;
          }
          if((((u8)parameter_table[Upper4BitInputReverse])&((u8)0x01))==0x01 )
          {
               v->Plc_In_CLESC1ZEROSPD =  v->Plc_In_CLESC1ZEROSPD == 1 ? 0 : 1;
          }
     }
     
     // INHSC2
     if( (((u8)parameter_table[Upper4BitInputON])&((u8)0x02))==0x02 )
     {
          v->Plc_In_INHSC2 = 1;
     }
     else 
     {
          if( GPIO_ReadInputDataBit(INHSC2_GPIO_PORT, INHSC2_GPIO_PIN)==0 )
          {
               v->Plc_In_INHSC2 = 1;
          }
          else
          {
               v->Plc_In_INHSC2 = 0;
          }
          if((((u8)parameter_table[Upper4BitInputReverse])&((u8)0x02))==0x02 )
          {
               v->Plc_In_INHSC2 =  v->Plc_In_INHSC2 == 1 ? 0 : 1;
          }
     }
     
     // FIL
     if( (((u8)parameter_table[Upper4BitInputON])&((u8)0x04))==0x04 )
     {
          v->Plc_In_FIL = 1;
     }
     else 
     {
          if( GPIO_ReadInputDataBit(FIL_GPIO_PORT, FIL_GPIO_PIN)==0 )
          {
               v->Plc_In_FIL = 1;
          }
          else
          {
               v->Plc_In_FIL = 0;
          }
          if((((u8)parameter_table[Upper4BitInputReverse])&((u8)0x04))==0x04 )
          {
               v->Plc_In_FIL =  v->Plc_In_FIL == 1 ? 0 : 1;
          }
     }
     
     // RIL
     if( (((u8)parameter_table[Upper4BitInputON])&((u8)0x08))==0x08 )
     {
          v->Plc_In_RIL = 1;
     }
     else 
     {     
          if( GPIO_ReadInputDataBit(RIL_GPIO_PORT, RIL_GPIO_PIN)==0 )
          {
               v->Plc_In_RIL = 1;
          }
          else
          {
               v->Plc_In_RIL = 0;
          }
          if((((u8)parameter_table[Upper4BitInputReverse])&((u8)0x08))==0x08 )
          {
               v->Plc_In_RIL =  v->Plc_In_RIL == 1 ? 0 : 1;
          }
     }
}

// 检测驱动板信号
// 1有效，0无效
void drive_check(safe *v)
{
     // IPM fault
     if( TIM_GetFlagStatus(TIM8, TIM_FLAG_Break) == 1)
     {
          ERROR_ipm = 1;
     }
     
     // 欠压
     if(GPIO_ReadInputDataBit(LV_GPIO_PORT, LV_GPIO_PIN)==1)
     {
          ERROR_lack_voltage_now = 1;
          led_power_off();
          v->Drive_Lv_Cnt  ++;
          if( v->Drive_Lv_Cnt >= 10000)
          {
               v->Drive_Lv = 0;
               ERROR_lack_voltage = 1;
               v->Drive_Lv_Cnt = 0;
          }
     }
     else
     {
          ERROR_lack_voltage_now = 0;
          led_power_on();
          v->Drive_Lv = 1;
          ERROR_lack_voltage = 0;
          v->Drive_Lv_Cnt = 0;
     }
     
     // 过压     
     if(GPIO_ReadInputDataBit(OV_GPIO_PORT, OV_GPIO_PIN)==1)
     {
          ERROR_over_voltage_now = 1;
          ov_delay_flag = 1;
          if(ov_delay >= OV_TIME_FACTOR)
          {
               v->Drive_Ov = 1;
               ERROR_over_voltage = 1;
               TIM_CtrlPWMOutputs(TIM8, DISABLE);
          }
     }
     else
     {
          ERROR_over_voltage_now = 0;
          v->Drive_Ov = 0;
          ov_delay_flag = 0;
          ov_delay = 0;
     }
     
     // 制动
     if(GPIO_ReadInputDataBit(BR_GPIO_PORT, BR_GPIO_PIN)==1)
     {
          v->Drive_Br = 1;
          br_delay_flag = 1;
          if(br_delay >= BR_TIME_FACTOR)
          {               
               ERROR_brake = 1;
               TIM_CtrlPWMOutputs(TIM8, DISABLE);
          }
     }
     else
     {
          v->Drive_Br = 0;
          br_delay_flag = 0;
          br_delay = 0;
     }     
     
/*     // 没有正常上过电
     if(v->Drive_Power_On_Once == 0)
     {
          // 如果没有正常上过一次强电，不算欠压          
          if( GPIO_ReadInputDataBit(LV_GPIO_PORT, LV_GPIO_PIN) == 0)            // 大于欠压电压
          {
               v->Drive_Power_On_Once_Cnt ++;
          }
          else
          {
               v->Drive_Power_On_Once_Cnt = 0;
          }
          if( v->Drive_Power_On_Once_Cnt == 255)
          {
               v->Drive_Power_On_Once = 1;
               ERROR_lack_voltage = 0;
          }
     }*/
}

void encoder_check(safe *v)
{
     if(encoder_check_T>100)
     {
          encoder_check_T = 0;
          if(GPIO_ReadInputDataBit(ATEST2ARM_GPIO_PORT, ATEST2ARM_GPIO_PIN) == 0)
          {
               v->Encoder_Test_A = 0;
          }
          else
          {
               v->Encoder_Test_A = 1;
          }
          
          if(GPIO_ReadInputDataBit(BTEST2ARM_GPIO_PORT, BTEST2ARM_GPIO_PIN) == 0)
          {
               v->Encoder_Test_B = 0;
          }
          else
          {
               v->Encoder_Test_B = 1;
          }
          
          if(GPIO_ReadInputDataBit(ZTEST2ARM_GPIO_PORT, ZTEST2ARM_GPIO_PIN) == 0)
          {
               v->Encoder_Test_Z = 0;
          }
          else
          {
               v->Encoder_Test_Z = 1;
          }
          
          if(GPIO_ReadInputDataBit(UTEST2ARM_GPIO_PORT, UTEST2ARM_GPIO_PIN) == 0)
          {
               v->Encoder_Test_U = 0;
          }
          else
          {
               v->Encoder_Test_U= 1;
          }
          
          if(GPIO_ReadInputDataBit(VTEST2ARM_GPIO_PORT, VTEST2ARM_GPIO_PIN) == 0)
          {
               v->Encoder_Test_V = 0;
          }
          else
          {
               v->Encoder_Test_V = 1;
          }
          
          if(GPIO_ReadInputDataBit(WTEST2ARM_GPIO_PORT, WTEST2ARM_GPIO_PIN) == 0)
          {
               v->Encoder_Test_W = 0;
          }
          else
          {
               v->Encoder_Test_W = 1;
          }          
                       
          if( (v->Encoder_Test_A == 0) || (v->Encoder_Test_B == 0) || (v->Encoder_Test_Z == 0) || (v->Encoder_Test_U == 0) || (v->Encoder_Test_V == 0) || (v->Encoder_Test_W == 0) )
          {
               v->Encoder_Test_Cnt ++;
          }
          else
          {
               v->Encoder_Test_Cnt = 0;
          }
          if( v->Encoder_Test_Cnt >= 10)
          {
               ERROR_encoder = 1;
          }
     }
}

// -------------------初始状态-----------------------------------
void system_initial_state(safe *v)
{
     if(v->System_State == INITIAL)
     {
          //encoder_check(v);   // 已经检测过
          //drive_check(v);     // 已经检测过
          if(  v->Servo_Error==0 )
          {
               alm_disable();
               v->Plc_Out_ALM = 0;
               v->System_State = WAIT;
          }
     }
}
// -------------------初始状态-----------------------------------



extern s32 Pos_Cmd;

void system_end_state(safe *v)
{
     if(v->System_State == END)
     {
          led_run_off();
          
          coin_disable();
          v->Plc_Out_COIN = 0;
          
          v->Command_Mode = STOP_CONTROL;
          
          if(v->Servo_Error == 0)
          {     
               v->System_State = WAIT;
               plc_delay_flag_1=0;
               plc_delay_1=0;
               plc_delay_flag_2=0;
               plc_delay_2=0;
               plc_delay_flag_3=0;
               plc_delay_3=0;
          }
     }
}

void system_ready_state(safe *v)
{
     if(v->System_State == READY)
     {
          plc_delay_flag_1=1;
          if(plc_delay_1>=600)
          {
               v->Current_On = 1;
               plc_delay_flag_2=1;
               if(plc_delay_2>=40)
               {
                    brk_disable();
                    v->Plc_Out_BRK = 0;
                    plc_delay_flag_3=1;
                    if(plc_delay_3>=1000)
                    {
                         // 保证速度计算变量与编码器同步
                         speed_parameter.Qepcnt_old = angle_parameter.QepCnt;
                         
                         clear_parameter();
                         
                         v->System_State = RUN;
                         plc_delay_flag_1=0;
                         plc_delay_1=0;
                         plc_delay_flag_2=0;
                         plc_delay_2=0;
                         plc_delay_flag_3=0;
                         plc_delay_3=0;
                    }
               }
          }
     }                                        
}

void system_run_state(safe *v)
{
     if(v->System_State == RUN)
     {
          v->Command_Input = 1;
          if(v->Command_Mode == PLC_CONTROL)
          {
               if(v->Plc_In_SON == 0)
               {
                    // SON保持20ms
                    plc_delay_flag_1=1;
                    if(plc_delay_1>=200)
                    {
                         //if(v->Plc_In_SON == 0)
                         //{
                              v->System_State = STOP;
                              plc_delay_flag_1=0;
                              plc_delay_1=0;
                         //}
                    }
               }
          }
          else if(v->Command_Mode == STOP_CONTROL)
          {
               v->System_State = STOP;
               plc_delay_flag_1=0;
               plc_delay_1=0;
               plc_delay_flag_2=0;
               plc_delay_2=0;
               plc_delay_flag_3=0;
               plc_delay_3=0;
          }
     }
}

void system_stop_state(safe *v)
{
     if(v->System_State == STOP)
     {
          // 不接收位置和速度指令，只剩下iq=0的电流环
          v->Command_Input = 0;
          
          // 速度小于30rpm
          if( abs(speed_view_parameter.speed_view_after_filter) < 30 )
          {
               // 制动保持
               brk_enable();
               v->Plc_Out_BRK = 1;
               plc_delay_flag_1=1;
               if( plc_delay_1 >= STOP_BRAKE_TIME_FACTOR)
               {
                    clear_parameter();
                    // 不通电
                    v->Current_On = 0;
                    v->System_State = END;
                    
                    plc_delay_flag_1=0;
                    plc_delay_1=0;
                    plc_delay_flag_2=0;
                    plc_delay_2=0;
                    plc_delay_flag_3=0;
                    plc_delay_3=0;
               }
          }
          else
          {
               // 不通电
               v->Current_On = 0;
               plc_delay_flag_2 = 1;
               if( plc_delay_2 >= RUN_BRAKE_TIME_FACTOR )
               {
                    // 制动保持
                    brk_enable();
                    v->Plc_Out_BRK = 1;
                    
                    clear_parameter();
                    v->System_State = END;
                    
                    plc_delay_flag_1=0;
                    plc_delay_1=0;
                    plc_delay_flag_2=0;
                    plc_delay_2=0;
                    plc_delay_flag_3=0;
                    plc_delay_3=0;
               }
               if( abs(speed_view_parameter.speed_view_after_filter) <= parameter_table[MechanicalBrakingSpeedWhileStop] )
               {
                    brk_enable();
                    v->Plc_Out_BRK = 1;
                    
                    clear_parameter();
                    v->System_State = END;
                    
                    plc_delay_flag_1=0;
                    plc_delay_1=0;
                    plc_delay_flag_2=0;
                    plc_delay_2=0;
                    plc_delay_flag_3=0;
                    plc_delay_3=0;
               }
          }
     }
}

// ???
void system_error_function(safe *v)
{
     // 报警清除函数
     // 故障代码小于等于8，报警可清除
     if((v->Plc_In_ALRS == 1) && ( (v->System_State == END) || (v->System_State == INITIAL) ) )
     {
          error_reset();
          
          clear_parameter();
          
          // ALRS保持200ms
          plc_delay_flag_1 = 1;
          if(plc_delay_1>=2000)
          {
               if(v->Servo_Error == 0)
               {
                    // 不报警
                    alm_disable();
                    v->Plc_Out_ALM = 0;
                    //v->Servo_Error = 0;
                    //v->System_State = WAIT;                    
               }
               plc_delay_flag_1=0;
               plc_delay_1=0;
               plc_delay_flag_2=0;
               plc_delay_2=0;
               plc_delay_flag_3=0;
               plc_delay_3=0;
          }
     }
     
     
     // 错误报警函数
     if( (v->Servo_Error == 1) && (v->System_State != END) )
     {
          // 报警
          alm_enable();
          v->Plc_Out_ALM = 1;
          // 不输出SRDY
          srdy_disable();
          v->Plc_Out_SRDY = 0;
//          if(v->Drive_Power_On_Once == 1)
//         {
               v->System_State = STOP;
               plc_delay_flag_1=0;
               plc_delay_1=0;
               plc_delay_flag_2=0;
               plc_delay_2=0;
               plc_delay_flag_3=0;
               plc_delay_3=0;
//          }
     }
     else if( (v->Servo_Error == 1) && (v->System_State == END) )
     {
          // 报警
          alm_enable();
          v->Plc_Out_ALM = 1;
          // 不输出SRDY
          srdy_disable();
          v->Plc_Out_SRDY = 0;
     }          
}


// --------------------伺服等待状态------------------------
void system_wait_state(safe *v)
{
     if(v->System_State == WAIT)
     {
          plc_delay_flag_1=1;
          if(plc_delay_1>=10000)  // 延时1s
          {
               // 输出SRDY
               srdy_enable();
               v->Plc_Out_SRDY = 1;
               if( (v->Plc_In_SON==1) && ( (parameter_table[ControlMode]==0)||(parameter_table[ControlMode]==1) ) && (v->Command_Mode==STOP_CONTROL) )
               {
                    v->Command_Mode = PLC_CONTROL;
                    if(phase_current_parameter.Offset_OK == 1)
                    {
                         clear_parameter();
                         
                         v->System_State = READY;
                    }
               }
               else if( ( (v->Command_Mode == SR_CONTROL) && (parameter_table[ControlMode] == 2) ) || ( (v->Command_Mode == JOG_CONTROL) && (parameter_table[ControlMode] == 3)))
               {
                    if(phase_current_parameter.Offset_OK == 1)
                    {
                         clear_parameter();
                         
                         v->System_State = READY;
                    }
               }
          }
     }
}

// --------------------伺服等待状态------------------------


void srdy_enable(void)
{
     if( (((u8)parameter_table[OutputReverse])&((u8)0x01))==0x00 )
     {
          GPIO_ResetBits(SRDY_GPIO_PORT, SRDY_GPIO_PIN);  // 输出导通、输出SRDY
     }
     else
     {
          GPIO_SetBits(SRDY_GPIO_PORT, SRDY_GPIO_PIN);  // 输出导通、输出SRDY     
     }
}
void srdy_disable(void)
{
     if( (((u8)parameter_table[OutputReverse])&((u8)0x01))==0x00 )
     {
          GPIO_SetBits(SRDY_GPIO_PORT, SRDY_GPIO_PIN); // 输出截止、不输出SRDY
     }
     else
     {
          GPIO_ResetBits(SRDY_GPIO_PORT, SRDY_GPIO_PIN);  // 输出截止、不输出SRDY    
     }
}

void alm_enable(void)
{
     if( (((u8)parameter_table[OutputReverse])&((u8)0x02))==0x00 )
     {
          GPIO_SetBits(ALM_GPIO_PORT, ALM_GPIO_PIN);      // 输出截止、不输出ALM、有报警
     }
     else
     {
          GPIO_ResetBits(ALM_GPIO_PORT, ALM_GPIO_PIN);      // 输出截止、不输出ALM、有报警  
     }
}
void alm_disable(void)
{
     if( (((u8)parameter_table[OutputReverse])&((u8)0x02))==0x00 )
     {
          GPIO_ResetBits(ALM_GPIO_PORT, ALM_GPIO_PIN);    // 输出导通、输出ALM、没有报警
     }
     else
     {
          GPIO_SetBits(ALM_GPIO_PORT, ALM_GPIO_PIN);    // 输出导通、输出ALM、没有报警
     }
}

void brk_enable(void)
{
     if( (((u8)parameter_table[OutputReverse])&((u8)0x08))==0x00 )
     {
          GPIO_SetBits(BRK_GPIO_PORT, BRK_GPIO_PIN);      // 输出截止、不输出BRK、制动有效
     }
     else
     {
          GPIO_ResetBits(BRK_GPIO_PORT, BRK_GPIO_PIN);      // 输出截止、不输出BRK、制动有效
     }
}
void brk_disable(void)
{
     if( (((u8)parameter_table[OutputReverse])&((u8)0x08))==0x00 )
     {
          GPIO_ResetBits(BRK_GPIO_PORT, BRK_GPIO_PIN);    // 输出导通、输出BRK、制动无效
     }
     else
     {
          GPIO_SetBits(BRK_GPIO_PORT, BRK_GPIO_PIN);    // 输出导通、输出BRK、制动无效
     }
}

void coin_enable(void)
{
     if( (((u8)parameter_table[OutputReverse])&((u8)0x04))==0x00 )
     {
          GPIO_ResetBits(COIN_GPIO_PORT, COIN_GPIO_PIN);
     }
     else
     {
          GPIO_SetBits(COIN_GPIO_PORT, COIN_GPIO_PIN);
     }
}

void coin_disable(void)
{
     if( (((u8)parameter_table[OutputReverse])&((u8)0x04))==0x00 )
     {
          GPIO_SetBits(COIN_GPIO_PORT, COIN_GPIO_PIN);
     }
     else
     {
          GPIO_ResetBits(COIN_GPIO_PORT, COIN_GPIO_PIN);
     }
}


// ------------------------------LED相关函数------------------------------------
void led_conf(void)
{
     GPIO_InitTypeDef GPIO_InitStructure;     
     
     LED_RUN_GPIO_PORT->ODR = LED_RUN_GPIO_PORT->ODR & (~LED_RUN_GPIO_PIN);     
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = LED_RUN_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(LED_RUN_GPIO_PORT, &GPIO_InitStructure);
     
     led_run_off();
     LED_POWER_GPIO_PORT->ODR = LED_POWER_GPIO_PORT->ODR & (~LED_POWER_GPIO_PIN);
     GPIO_StructInit(&GPIO_InitStructure);
     GPIO_InitStructure.GPIO_Pin = LED_POWER_GPIO_PIN;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(LED_POWER_GPIO_PORT, &GPIO_InitStructure);
   
     led_power_off();
}

void led_run_on(void)
{
     LED_RUN_GPIO_PORT->BRR = LED_RUN_GPIO_PIN;
}

void led_run_off(void)
{
     LED_RUN_GPIO_PORT->BSRR = LED_RUN_GPIO_PIN;
}

void led_power_on(void)
{
     LED_POWER_GPIO_PORT->BRR = LED_POWER_GPIO_PIN;
}

void led_power_off(void)
{
     LED_POWER_GPIO_PORT->BSRR = LED_POWER_GPIO_PIN;
}
// ------------------------------LED相关函数------------------------------------

void Plc_Out (safe *v)
{
     if(v->Plc_Out_ALM == 0)
     {
          alm_disable();
     }
     else
     {
          alm_enable();     
     }
     
     if(v->Plc_Out_SRDY == 0)
     {
          srdy_disable();
     }
     else
     {
          srdy_enable();  
     }
     
     if(v->Plc_Out_BRK == 0)
     {
          brk_disable();
     }
     else
     {
          brk_enable();   
     }
     
     if(v->Plc_Out_COIN == 0)
     {
          coin_disable();
     }
     else
     {
          coin_enable();     
     }

}




void clear_parameter(void)
{
     // ---------复位角度计算和位置反馈--------
     //TIM2->CNT = 0;
     //angle_parameter.QepCnt = 0;
     //angle_parameter.pst[0] = 0;
     //angle_parameter.pst[1] = 0;
     angle_parameter.PstFdb = 0;
     // ---------复位角度计算和位置反馈--------
     
     // --------复位速度观测-------------------
     //speed_view_parameter.Qepcnt_new = 0;
     //speed_view_parameter.Qepcnt_old = 0;
     //speed_view_parameter.Qepcnt_deta = 0;
     //speed_view_parameter.speed_view = 0;
     //speed_view_parameter.speed_view_after_filter = 0;
     // --------复位速度观测-------------------
     
     // -------复位速度计算--------------------
     //speed_parameter.Qepcnt_new = 0;
     //speed_parameter.Qepcnt_old = 0;
     //speed_parameter.Qepcnt_deta = 0;
     // -------复位速度计算--------------------
     
     // ------复位位置计算---------------------
     TIM1->CNT = 0;
     TIM4->CNT = 0;
     Pos_Cnt = 0;
     Pos_Cnt_Pre = 0;
     Cmd_Inc = 0;
     Pos_Cmd = 0;
     Pos_Ref = 0;
     Pos_Err = 0;
     elc_gear_reset_cnt = 0;
     // ------复位位置计算---------------------
     
     // -----复位PI和滤波----------------------------
     pid_speed.Ref = 0;
     pid_speed.Fdb = 0;
     pid_speed.Ui  = 0;
     pid_speed.Saturation_flag = 0;
     pid_iq.Ref = 0;
     pid_iq.Fdb = 0;
     pid_iq.Ui  = 0;
     pid_iq.Saturation_flag = 0;
     pid_id.Ref = 0;
     pid_id.Fdb = 0;
     pid_id.Ui  = 0;
     pid_id.Saturation_flag = 0;
     id_ref_filter.Input     = 0;
     id_ref_filter.Output[1] = 0;
     id_fdb_filter.Input     = 0;
     id_fdb_filter.Output[1] = 0;
     iq_ref_filter.Input     = 0;
     iq_ref_filter.Output[1] = 0;
     iq_fdb_filter.Input     = 0;
     iq_fdb_filter.Output[1] = 0;
     speed_ref_filter.Input     = 0;
     speed_ref_filter.Output[1] = 0;
     speed_fdb_filter.Input     = 0;
     speed_fdb_filter.Output[1] = 0;
     // -----复位PI和滤波----------------------------
     
     // -----复位PLC定时变量-------------------
     plc_delay_flag_1=0;
     plc_delay_1=0;
     plc_delay_flag_2=0;
     plc_delay_2=0;
     plc_delay_flag_3=0;
     plc_delay_3=0;
     // -----复位PLC定时变量-------------------
     
     feed_forward_pos.Out = 0;
     
     TIM8->CCR1 = 0;
     TIM8->CCR2 = 0;
     TIM8->CCR3 = 0;
}