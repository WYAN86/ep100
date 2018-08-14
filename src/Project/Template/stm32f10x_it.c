

#include "stm32f10x_it.h"
#include "IQmathLib.h"
#include "stm32f10x.h"

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
#include "low_filter.h"
#include "clarke.h"
#include "park.h"
#include "ipark.h"
#include "rampctrl.h"
#include "rampgen.h"
#include "pid.h"
#include "svpwm.h"
#include "speed.h"
#include "delay.h"
#include "viewer.h"
#include "error.h"


/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u16 speedloopcnt = 0;





//u8  Direction_Pre;


// ��ǰ���յ�λ���������
u16 Pos_Cnt = 0;
// ��һ�Ľ��յ�λ���������
u16 Pos_Cnt_Pre = 0;
// λ����������
s16 Cmd_Inc = 0;
// ����λ��ָ�����
s32 Pos_Cmd = 0;
// ���Ե��ӳ��ֱȺ��λ��ָ�����
s32 Pos_Ref = 0;
// λ�����
s32 Pos_Err = 0;
// λ��ָ���λ����
//s32 Pos_RefH = 0;
// λ����������־
//u8 Pos_Overflow_Err = 0;

s32 pid_iq_view = 0;
s32 pid_iq_view_add = 0;
s32 pid_iq_view_cnt = 0;

s32 speed_cmd_cnt = 0;
s32 speed_cmd_add = 0;
s32 speed_cmd_view = 0;



// ���Ա���
s32 testpoint1,testpoint2;


u16 led_delay = 0;

u16 ipm_fault_view;

// ���ӳ��ֱ�
//float elc_gear;

// ���ӳ��ֱȸ�λ����
s32 elc_gear_reset_cnt = 0;


extern s32 par_jog;
extern s32 par_tspd;

//_iq over_load_current_max;
//s32 over_load_current_time_max;

//�ڲ�ת������
//_iq interior_torque_max;
//_iq interior_torque_min;
//�ⲿת������
//_iq exterior_torque_max;
//_iq exterior_torque_min;
//������ת������
//_iq sr_torque_max;
//_iq sr_torque_min;

//����ٶ�����
//_iq speed_max_iq;
//_iq speed_min_iq;

// ģ���ٶ�ָ���������
//u16 as_calc_factor;
//_iq as_compensate_factor;

u16 led_delay;



// --------------�����������ģʽ---------------------
// �����������ģʽ��ʱ��������־
u32 encoder_offset_mode_delay;
u8  encoder_offset_mode_delay_flag;
// �����������ģʽ������������־
u32 encoder_offset_mode_run_delay;
u8  encoder_offset_mode_run_delay_flag;
// �����������ģʽ0��λ�ñ�������־
u16 encoder_offset_mode_zero_cnt;
u8  encoder_offset_mode_zero_cnt_flag;
// �����������ģʽZ��λ�ñ�������־
u16 encoder_offset_mode_z_cnt;
u8  encoder_offset_mode_z_cnt_flag;
// --------------�����������ģʽ---------------------


extern u8 encoder_offset_mode;
s32  encoder_offset_deta = 0;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/


void PVD_IRQHandler(void)
{          
}



void EXTI9_5_IRQHandler(void)
{
     angle_parameter.Uvw = encoder_uvw_read();
     
     // ��0���־��Z���־
     if(encoder_offset_mode_zero_cnt_flag == 1)
     {
          encoder_offset_mode_z_cnt_flag = 1;
     }
     
     encoder_offset_mode_z_cnt = TIM2->CNT;
     
     //z_uvw = encoder_uvw();
     
     angle_calibrate(&angle_parameter);
     
     // clear EXTI_Line5 pending flag ����жϱ�־
     EXTI->PR = 0x00000020;
     
     // exti mask �����ⲿ�ж�
     EXTI->IMR &=0xFFFFFFDF;
}


void TIM8_UP_IRQHandler(void)
{
     angle_parameter.Uvw = encoder_uvw_read();
     
     float temp;
     double temp1;
     u16 tmp1,tmp2;     
   
     // ��ģ��ָ��
     as_read(&as_parameter);
     as_filter.Input = as_parameter.ImeasAS;
     low_filter_calc(&as_filter);

     // ------------���ֶ�ʱ����--------------------------
     if(keydelay<10000) 
     {
          keydelay++;
     }
     if(disdelay<10000) 
     {
          disdelay++;
     }
     if((plc_delay_flag_1==1) && (plc_delay_1 <65534)) 
     {
          plc_delay_1++;
     }
     if((plc_delay_flag_2==1) && (plc_delay_2 <65534)) 
     {
          plc_delay_2++;
     }
     if((plc_delay_flag_3==1) && (plc_delay_3 <65534) )
     {
          plc_delay_3++;
     }
     if(encoder_check_T < 1000)
     {
         encoder_check_T++;
     }
     if( (ov_delay_flag==1) && (ov_delay <65534) )
     {
          ov_delay++;
     }
     if( (br_delay_flag==1) && (br_delay <65534) )
     {
          br_delay++;
     }
     // ------------���ֶ�ʱ����--------------------------
     
     
     // ��������λ��
     angle_parameter.QepCnt = TIM2->CNT;
     // ����Ƕ�
     angle_calc(&angle_parameter);
     
     // ------------------------�ٶȹ۲�----------------------------------------
     speed_view_parameter.Qepcnt_new = angle_parameter.QepCnt;
     speed_view_calc(&speed_view_parameter);  //2us
          
     if( abs(speed_view_parameter.speed_view_after_filter) > motor_parameter[parameter_table[Version]].Max_Speed )
     {
          ERROR_over_speed = 1;
          ERROR_over_speed_now = 1;
          TIM_CtrlPWMOutputs(TIM8, DISABLE);
     }
     else
     {
          ERROR_over_speed_now = 0;     
     }
     // ------------------------�ٶȹ۲�----------------------------------------
     
     // �������
     phase_current_read(&phase_current_parameter);//3us
     
     // ----------------------����������--------------
     if( OVER_CURRENT_TIME_FACTOR > 0)
     {
          if( (abs(phase_current_parameter.U) > OVER_CURRENT_MAX_FACTOR) || 
              (abs(phase_current_parameter.V) > OVER_CURRENT_MAX_FACTOR) || 
              (abs(phase_current_parameter.W) > OVER_CURRENT_MAX_FACTOR) )
          {
               if(ERROR_over_current_counter<60000)
               {
                    ERROR_over_current_counter++;
               }
               if(ERROR_over_current_counter > OVER_CURRENT_TIME_FACTOR)
               {
                    TIM_CtrlPWMOutputs(TIM8, DISABLE);
                    //led_run_off();
                    //safe_parameter.Servo_Error = 1;
                    //safe_parameter.Servo_Error_Code = OVER_CURRENT; // ������
                    ERROR_over_current = 1;
                    ERROR_over_current_counter = 0;
               }
          }
          else if( ERROR_over_current_counter>0 )
          {
               ERROR_over_current_counter--;
          }
     }
     // ----------------------����������--------------
     
     if( phase_current_parameter.Offset_OK == 1 )
     {
          //--------------------�������������----------------------------------
          if( encoder_offset_mode == 1 )
          {
               // -----------------------��ʱ����------------
               // ģ��5s����ʱ�����Ͽ��Ƶ���2s����ǿ�硣
               if(encoder_offset_mode_delay<20000)
                    encoder_offset_mode_delay++;
               else if(encoder_offset_mode_delay==20000)
               {                    
                    encoder_offset_mode_delay_flag = 1;
                    encoder_offset_mode_delay++;
               }
               //-------------------------------------------
               
               if( encoder_offset_mode_delay_flag == 1 )
               {
                    TIM_CtrlPWMOutputs(TIM8, ENABLE);
                    // --------LED_RUN��˸-------
                    led_delay = led_delay+1;
                    if(led_delay == 5000)
                         led_run_on();
                    else if(led_delay == 10000)
                    {
                         led_run_off();
                         led_delay = 1;
                    }
                    // --------------------------
                    
                    if( (encoder_offset_mode_run_delay_flag == 0) && (encoder_offset_mode_run_delay<30000) )
                    {
                         encoder_offset_mode_run_delay++;
                         encoder_offset_mode_zero_cnt = TIM2->CNT;
                    }
                    else if (encoder_offset_mode_run_delay == 30000)
                    {
                         // ���������ɺ��Z�����ⲿ�ж�
                         EXTI->IMR |= 0x00000020;
                         encoder_offset_mode_zero_cnt_flag = 1;
                         encoder_offset_mode_run_delay_flag = 1;
                         encoder_offset_mode_run_delay++;
                    }
                    
                    if(encoder_offset_mode_run_delay_flag ==1)
                    {
                         rampgen_parameter.StepAngleMax = _IQ_Z_0_DOT_01;
                         rampgen_parameter.Freq = _IQ_Z_0_DOT_1;
                         rampgen_calc(&rampgen_parameter);
                    }
                    
                    // clarke//1us
                    clarke_parameter.As = phase_current_parameter.U;
                    clarke_parameter.Bs = phase_current_parameter.V;
                    clarke_calc(&clarke_parameter);
                    
                    // park//4us
                    park_parameter.Alpha = clarke_parameter.Alpha;
                    park_parameter.Beta = clarke_parameter.Beta;
                    if(encoder_offset_mode_run_delay_flag == 0)
                         park_parameter.Angle = _IQ(0);                     //�����Ƕ�
                    else if(encoder_offset_mode_run_delay_flag == 1)
                         park_parameter.Angle = rampgen_parameter.Out;  //�����Ƕ�
                    park_calc(&park_parameter);
                    
                    // ------------dq�����˲�---------------
                    id_fdb_filter.Input = park_parameter.Ds;
                    iq_fdb_filter.Input = park_parameter.Qs;
                    low_filter_calc(&id_fdb_filter);
                    low_filter_calc(&iq_fdb_filter);
                    // -------------------------------------
                    
                    // pid_id
                    pid_id_encoder_offset.Ref = _IQ(0.1);  // id�ο�ֵ=0.3
                    //pid_id_encoder_offset.Fdb = park_parameter.Ds;
                    pid_id_encoder_offset.Fdb = id_fdb_filter.Output[0];
                    pid_id_encoder_offset.Err =  pid_id_encoder_offset.Ref - pid_id_encoder_offset.Fdb;
                    pi_caculation(&pid_id_encoder_offset);
                    
                    // pid_iq
                    pid_iq_encoder_offset.Ref = 0;  // iq�ο�ֵ=0
                    //pid_iq_encoder_offset.Fdb = park_parameter.Qs;
                    pid_iq_encoder_offset.Fdb = iq_fdb_filter.Output[0];
                    pid_iq_encoder_offset.Err =  pid_iq_encoder_offset.Ref - pid_iq_encoder_offset.Fdb;
                    pi_caculation(&pid_iq_encoder_offset);
                    
                    // ipark
                    ipark_parameter.Ds = pid_id_encoder_offset.Out;
                    ipark_parameter.Qs = pid_iq_encoder_offset.Out;
                    if(encoder_offset_mode_run_delay_flag == 0)
                         ipark_parameter.Angle = _IQ(0);//rampgen_parameter.Out;  //�����Ƕ�
                    else if(encoder_offset_mode_run_delay_flag == 1)
                         ipark_parameter.Angle = rampgen_parameter.Out;  //������
                    ipark_calc(&ipark_parameter);	//park��任
                    
                    // svpwm
                    svpwm_parameter.Ualpha = ipark_parameter.Alpha;
                    svpwm_parameter.Ubeta = ipark_parameter.Beta;
                    svpwm_calc(&svpwm_parameter);
                    //over_modu_calc(&svpwm_parameter);
                    
                    tim8_pwm_parameter.MfuncC1 = (s16)_IQtoIQ15(svpwm_parameter.Ta);
                    tim8_pwm_parameter.MfuncC2 = (s16)_IQtoIQ15(svpwm_parameter.Tb);
                    tim8_pwm_parameter.MfuncC3 = (s16)_IQtoIQ15(svpwm_parameter.Tc);
                    tim8_pwm_update(&tim8_pwm_parameter);
               
                    if(encoder_offset_mode_z_cnt_flag==1)
                    {
                         s32 encoder_delta_tmp;
                         TIM_CtrlPWMOutputs(TIM8, DISABLE);
                         //led_run_off();
                         //encoder_offset_deta = encoder_offset_mode_z_cnt - encoder_offset_mode_zero_cnt;
                         encoder_delta_tmp = encoder_offset_mode_zero_cnt - encoder_offset_mode_z_cnt;
                         if( encoder_delta_tmp < 0 )
                         {
                              encoder_offset_deta = 65535 + encoder_delta_tmp;
                         }
                         else if( encoder_delta_tmp <= 10000 )
                         {
                              encoder_offset_deta = encoder_delta_tmp;
                         }
                         encoder_offset_deta = encoder_offset_deta % 2500;
                              
                         encoder_offset_mode = 0;
                         encoder_offset_mode_delay = 0;
                         encoder_offset_mode_delay_flag = 0;
                         encoder_offset_mode_run_delay = 0;
                         encoder_offset_mode_run_delay_flag = 0;
                         encoder_offset_mode_zero_cnt = 0;
                         encoder_offset_mode_zero_cnt_flag = 0;
                         encoder_offset_mode_z_cnt = 0;
                         encoder_offset_mode_z_cnt_flag = 0;
                         pid_id_encoder_offset.Ui = 0;
                         pid_id_encoder_offset.Saturation_flag = 0;
                         pid_iq_encoder_offset.Ui = 0;
                         pid_iq_encoder_offset.Saturation_flag = 0;
                         id_ref_filter.Output[1] = 0;
                         id_fdb_filter.Output[1] = 0;
                         iq_ref_filter.Output[1] = 0;
                         iq_fdb_filter.Output[1] = 0;
                    }
               }
               
               if(safe_parameter.Servo_Error == 1 )
               {
                    TIM_CtrlPWMOutputs(TIM8, DISABLE);
                    //led_run_off();
                    encoder_offset_mode = 0;
                    encoder_offset_mode_delay = 0;
                    encoder_offset_mode_delay_flag = 0;
                    encoder_offset_mode_run_delay = 0;
                    encoder_offset_mode_run_delay_flag = 0;
                    encoder_offset_mode_zero_cnt = 0;
                    encoder_offset_mode_zero_cnt_flag = 0;
                    encoder_offset_mode_z_cnt = 0;
                    encoder_offset_mode_z_cnt_flag = 0;
                    pid_id_encoder_offset.Ui = 0;
                    pid_id_encoder_offset.Saturation_flag = 0;
                    pid_iq_encoder_offset.Ui = 0;
                    pid_iq_encoder_offset.Saturation_flag = 0;
                    id_ref_filter.Output[1] = 0;
                    id_fdb_filter.Output[1] = 0;
                    iq_ref_filter.Output[1] = 0;
                    iq_fdb_filter.Output[1] = 0;
               }
          }
          //--------------------�������������----------------------------------
          
          
          //---------------------λ�ú��ٶ�ģʽ---------------------------------
          else if( safe_parameter.Current_On == 1 )
          {
               TIM_CtrlPWMOutputs(TIM8, ENABLE);
               // --------LED_RUN��˸-------
               led_delay = led_delay+1;
               if(led_delay == 5000)
                    led_run_on();
               else if(led_delay == 10000)
               {
                    led_run_off();
                    led_delay = 1;
               }
               // --------------------------
               
               // clarke//1us          
               clarke_parameter.As = phase_current_parameter.U;
               clarke_parameter.Bs = phase_current_parameter.V;
               clarke_calc(&clarke_parameter);
               
               // park//4us
               park_parameter.Alpha = clarke_parameter.Alpha;
               park_parameter.Beta  = clarke_parameter.Beta;
               park_parameter.Angle = angle_parameter.ElecAngle;
               park_calc(&park_parameter);
               
               // ---------------�����ر���������ת�أ�˲ʱ��-------------------
               if( OVER_LOAD_TIME_FACTOR > 0)
               {
                    if( abs(park_parameter.Qs) > OVER_LOAD_MAX_FACTOR )
                    {
                         if(ERROR_over_load_counter<600000000)
                         {
                              ERROR_over_load_counter++;
                         }
                         if(ERROR_over_load_counter > OVER_LOAD_TIME_FACTOR)
                         {
                              ERROR_over_load = 1;
                              ERROR_over_load_counter = 0;
                         }
                    }
                    else if( ERROR_over_load_counter > 0 )
                    {
                         ERROR_over_load_counter--;
                    }
               }
               // ---------------�����ر���������ת�أ�˲ʱ��-------------------
               
               // ---------------�ȹ��ر���������ת�أ����ڣ�-------------------
               if( OVER_HEAT_TIME_FACTOR > 0)
               {
                    if( abs(park_parameter.Qs) > OVER_HEAT_MAX_FACTOR )
                    {
                         //ERROR_over_heat_now = 1;
                         if(ERROR_over_heat_counter<600000000)
                         {
                              ERROR_over_heat_counter++;
                         }
                         if(ERROR_over_heat_counter > OVER_HEAT_TIME_FACTOR)
                         {
                              ERROR_over_heat = 1;
                              ERROR_over_heat_counter = 0;
                         }
                    }
                    else if( ERROR_over_heat_counter > 0 )
                    {
                         //ERROR_over_heat_now = 0;
                         ERROR_over_heat_counter--;
                    }
               }
               // ---------------�ȹ��ر���������ת�أ����ڣ�-------------------
               
               // ------------dq�����˲�---------------
               id_fdb_filter.Input = park_parameter.Ds;
               iq_fdb_filter.Input = park_parameter.Qs;
               low_filter_calc(&id_fdb_filter);
               low_filter_calc(&iq_fdb_filter);
               // -------------------------------------
               
               // --------------------λ�û����ٶȻ�----------------------------
               // RUN״̬���Խ���ָ��
               if(safe_parameter.Command_Input == 1)
               {
                    if(speedloopcnt == SPEED_LOOP_PRESCALER)
                    {
                         // �ٶȻ���λ�û���Ƶ����
                         speedloopcnt = 1;
                         
                         switch(parameter_table[ControlMode])
                         {
                              // ---------------0 λ�ÿ��Ʒ�ʽ------------------
                              case 0:
                              {
                                   if(safe_parameter.Command_Mode == PLC_CONTROL)
                                   {
                                        //Pos_Cnt = cmd_read();
                                        if(parameter_table[PositionCommandMode] == 0)
                                        {
                                             Pos_Cnt = TIM1->CNT;
                                             if(GPIO_ReadInputDataBit(SIGN_ETR_GPIO_PORT, SIGN_ETR_GPIO_PIN) == 0)
                                             {
                                                  Cmd_Inc = Pos_Cnt - Pos_Cnt_Pre;
                                             }
                                             else
                                             {
                                                  Cmd_Inc = Pos_Cnt_Pre - Pos_Cnt;
                                             }
                                        }
                                        else if(parameter_table[PositionCommandMode] == 1)
                                        {
                                             tmp1 = TIM1->CNT;
                                             tmp2 = TIM4->CNT;
                                             Pos_Cnt = tmp1 - tmp2;
                                             Cmd_Inc = Pos_Cnt - Pos_Cnt_Pre;
                                        }
                                        else if(parameter_table[PositionCommandMode] == 2)
                                        {
                                             Pos_Cnt = TIM1->CNT;
                                             Cmd_Inc = Pos_Cnt - Pos_Cnt_Pre;
                                        }
                                        
                                        // PA15�����������巽��ȡ��
                                        if(parameter_table[PositionCommandDirection] == 1)
                                        {
                                             Cmd_Inc = - Cmd_Inc;
                                        }
                                        
                                        // CCW��ֹ��ת��ֹ
                                        if((safe_parameter.Plc_In_FSTP==0) && (Cmd_Inc > 0))
                                        {
                                             Cmd_Inc=0;
                                        }
                                        
                                        //CW��ֹ��ת��ֹ
                                        if((safe_parameter.Plc_In_RSTP==0) && (Cmd_Inc < 0))
                                        {
                                             Cmd_Inc=0;
                                        }
                                        
                                        //ָ�����������ֹ��ֹ
                                        if(safe_parameter.Plc_In_INHSC2==1)
                                        {
                                             Cmd_Inc=0;
                                        }
                                        
                                        Pos_Cmd = Pos_Cmd + Cmd_Inc;
                                        
                                        if(Pos_Cmd > ELC_GEAR_MUL_MAX)
                                        {
                                             Pos_Cmd = Pos_Cmd - ELC_GEAR_MUL_MAX ;
                                             angle_parameter.PstFdb = angle_parameter.PstFdb - ELC_GEAR_MUL_FDB;
                                             elc_gear_reset_cnt++;
                                        }
                                        else if(Pos_Cmd < -ELC_GEAR_MUL_MAX)
                                        {
                                             Pos_Cmd = Pos_Cmd + ELC_GEAR_MUL_MAX ;
                                             angle_parameter.PstFdb = angle_parameter.PstFdb + ELC_GEAR_MUL_FDB;
                                             elc_gear_reset_cnt--;
                                        }
                                        
                                        temp=((float)Pos_Cmd) * ELC_GEAR_FACTOR;
                                        Pos_Ref = (s32)temp;//1.8us 
                                        
                                        Pos_Err = Pos_Ref - angle_parameter.PstFdb;
                                        
                                        // -----------λ����������----------
                                        if( parameter_table[PositionToleranceErrorRangeValid] == 0)
                                        {
                                             //ERROR_pos_err_now = 1;
                                             if( abs(Pos_Err) >= POS_ERR_MAX_FACTOR )
                                             {
                                                  ERROR_pos_err = 1;
                                             }
                                        }
                                        // -----------λ����������----------
                                        
                                        // -----------λ�ó��������----------
                                        if( abs(angle_parameter.PstFdb) >= 20000000 )
                                        {
                                             //ERROR_pos_overflow_now = 1;
                                             ERROR_pos_overflow = 1;
                                        }
                                        // -----------λ�ó��������----------
                                        
                                        // -----------��λ��ɼ��--------------
                                        if( abs(Pos_Err) >= POS_ARRIVE_FACTOR )
                                        {
                                             coin_disable();
                                             safe_parameter.Plc_Out_COIN = 0;
                                        }
                                        else
                                        {
                                             coin_enable();
                                             safe_parameter.Plc_Out_COIN = 1;
                                        }
                                        // -----------��λ��ɼ��--------------
                                        
                                        Pos_Cnt_Pre = Pos_Cnt;
                                        
                                        temp=( (float)Cmd_Inc ) * ELC_GEAR_FACTOR;
                                        feed_forward_pos.Out = _IQ18toIQ( Pos_Err * _IQtoIQ18(feed_forward_pos.Kp)) + _IQ18toIQ( ((s32)temp) * _IQtoIQ18(feed_forward_pos.Kaf) );//1.5us
                                        
                                        speed_ref_filter.Input = feed_forward_pos.Out;
                                        low_filter_calc(&speed_ref_filter);
                                        pid_speed.Ref = speed_ref_filter.Output[0];
                                        
                                        if(pid_speed.Ref > SPEED_MAX_FACTOR)
                                        {
                                             pid_speed.Ref = SPEED_MAX_FACTOR;
                                        }
                                        else if(pid_speed.Ref < SPEED_MIN_FACTOR)
                                        {
                                             pid_speed.Ref = SPEED_MIN_FACTOR;
                                        }
                                        
                                        if(pid_speed.Ref > IQ_Z_1)
                                        {
                                             pid_speed.Ref = IQ_Z_1;
                                        }
                                        else if(pid_speed.Ref < IQ_F_1)
                                        {
                                             pid_speed.Ref = IQ_F_1;
                                        }
                                        
                                        speed_parameter.Qepcnt_new = angle_parameter.QepCnt;
                                        speed_calc(&speed_parameter);
                                        speed_fdb_filter.Input = _IQ20toIQ( _IQ20div( speed_parameter.speed , _IQ20(SPEED_UNIT_FACTOR) ) );
                                        low_filter_calc(&speed_fdb_filter);
                                        pid_speed.Fdb = speed_fdb_filter.Output[0];
                                        
                                        pid_speed.Err = pid_speed.Ref - pid_speed.Fdb;
                                        pi_caculation(&pid_speed);
                                   }
                                   break;
                              }
                              // ---------------0 λ�ÿ��Ʒ�ʽ------------------                         
                         
                              // ---------------1 �ٶȿ��Ʒ�ʽ------------------
                              case 1:
                              {
                                   // ----------------�ٶȵ�����--------------
                                   if( abs(speed_view_parameter.speed_view_after_filter) > SPEED_ARRIVE_FACTOR )
                                   {
                                        coin_enable();
                                        safe_parameter.Plc_Out_COIN = 1;
                                   }
                                   else
                                   {
                                        coin_disable();
                                        safe_parameter.Plc_Out_COIN = 0;
                                   }
                                   // ----------------�ٶȵ�����--------------
                                    
                                   if(safe_parameter.Command_Mode == PLC_CONTROL)
                                   {
                                        speed_parameter.Qepcnt_new = angle_parameter.QepCnt;
                                        speed_calc(&speed_parameter);
                                        speed_fdb_filter.Input = _IQ20toIQ( _IQ20div( speed_parameter.speed , _IQ20(SPEED_UNIT_FACTOR) ) );
                                        low_filter_calc(&speed_fdb_filter);
                                        pid_speed.Fdb = speed_fdb_filter.Output[0];
                                        
                                        switch(parameter_table[SpeedCommandChoice])
                                        {
                                             //�ڲ��ٶ�
                                             case 0:
                                             {
                                                  if((safe_parameter.Plc_In_CLESC1ZEROSPD==0)&&(safe_parameter.Plc_In_INHSC2==0))
                                                  {                  
                                                       rampctrl_parameter.SetpointValue = pid_speed.Ref;
                                                       temp1= parameter_table[InteriorSpeed1] * SPEED_COMMAND_FACTOR;
                                                       rampctrl_parameter.TargetValue = (s32)temp1;
                                                       rampctrl_calc(&rampctrl_parameter);
                                                       if(rampctrl_parameter.EqualFlag == 1)
                                                       {
                                                            pid_speed.Ref = rampctrl_parameter.TargetValue;
                                                       }
                                                       else
                                                       {
                                                            pid_speed.Ref = rampctrl_parameter.SetpointValue;
                                                       }
                                                  }
                                                  if((safe_parameter.Plc_In_CLESC1ZEROSPD==1)&&(safe_parameter.Plc_In_INHSC2==0))
                                                  {
                                                       rampctrl_parameter.SetpointValue = pid_speed.Ref;
                                                       temp1= parameter_table[InteriorSpeed2] * SPEED_COMMAND_FACTOR;
                                                       rampctrl_parameter.TargetValue = (s32)temp1;
                                                       rampctrl_calc(&rampctrl_parameter);
                                                       if(rampctrl_parameter.EqualFlag == 1)
                                                       {
                                                            pid_speed.Ref = rampctrl_parameter.TargetValue;
                                                       }
                                                       else
                                                       {
                                                            pid_speed.Ref = rampctrl_parameter.SetpointValue;
                                                       }
                                                  }
                                                  if((safe_parameter.Plc_In_CLESC1ZEROSPD==0)&&(safe_parameter.Plc_In_INHSC2==1))
                                                  {                  
                                                       rampctrl_parameter.SetpointValue = pid_speed.Ref;
                                                       temp1= parameter_table[InteriorSpeed3] * SPEED_COMMAND_FACTOR;
                                                       rampctrl_parameter.TargetValue = (s32)temp1;
                                                       rampctrl_calc(&rampctrl_parameter);
                                                       if(rampctrl_parameter.EqualFlag == 1)
                                                       {
                                                            pid_speed.Ref = rampctrl_parameter.TargetValue;
                                                       }
                                                       else
                                                       {
                                                            pid_speed.Ref = rampctrl_parameter.SetpointValue;
                                                       }
                                                  }
                                                  if((safe_parameter.Plc_In_CLESC1ZEROSPD==1)&&(safe_parameter.Plc_In_INHSC2==1))
                                                  {
                                                       rampctrl_parameter.SetpointValue = pid_speed.Ref;
                                                       temp1= parameter_table[InteriorSpeed4] * SPEED_COMMAND_FACTOR;
                                                       rampctrl_parameter.TargetValue = (s32)temp1;
                                                       rampctrl_calc(&rampctrl_parameter);
                                                       if(rampctrl_parameter.EqualFlag == 1)
                                                       {
                                                            pid_speed.Ref = rampctrl_parameter.TargetValue;
                                                       }
                                                       else
                                                       {
                                                            pid_speed.Ref = rampctrl_parameter.SetpointValue;
                                                       }
                                                  }
                                                  break;
                                             }
                                             
                                             //�ⲿģ�����ٶ�ָ��
                                             case 1:
                                             {
                                                  //as_read(&as_parameter);
                                                  //as_filter.Input = as_parameter.ImeasAS;
                                                  //low_filter_calc(&as_filter);
                                                  pid_speed.Ref = as_filter.Output[0]*AS_CALC_FACTOR + AS_COMPENSATE_FACTOR;                                                  
                                                  if( parameter_table[AnalogSpeedCommandDirectionReverse] == 1)
                                                  {
                                                       pid_speed.Ref = -pid_speed.Ref;
                                                  }
                                                  if( safe_parameter.Plc_In_CLESC1ZEROSPD == 1 )
                                                  {
                                                       pid_speed.Ref = 0;
                                                  }
                                                  break;
                                             }
                                             //�ⲿģ�����ٶ�ָ������Է�����FIL��RIL������ӿ���
                                             case 2:
                                             {
                                                  if(as_filter.Output[0] < 0)
                                                  {
                                                       pid_speed.Ref = 0;
                                                  }
                                                  else
                                                  {
                                                       if( GPIO_ReadInputDataBit(FIL_GPIO_PORT, FIL_GPIO_PIN)==0 && GPIO_ReadInputDataBit(RIL_GPIO_PORT, RIL_GPIO_PIN)==0)
                                                            pid_speed.Ref = 0;
                                                       else if( GPIO_ReadInputDataBit(FIL_GPIO_PORT, FIL_GPIO_PIN)==1 && GPIO_ReadInputDataBit(RIL_GPIO_PORT, RIL_GPIO_PIN)==1)
                                                            pid_speed.Ref = 0;
                                                       else if( GPIO_ReadInputDataBit(FIL_GPIO_PORT, FIL_GPIO_PIN)==0 && GPIO_ReadInputDataBit(RIL_GPIO_PORT, RIL_GPIO_PIN)==1)
                                                            pid_speed.Ref = abs(as_filter.Output[0]*AS_CALC_FACTOR + AS_COMPENSATE_FACTOR);
                                                       else if( GPIO_ReadInputDataBit(FIL_GPIO_PORT, FIL_GPIO_PIN)==1 && GPIO_ReadInputDataBit(RIL_GPIO_PORT, RIL_GPIO_PIN)==0)
                                                            pid_speed.Ref = -1*abs(as_filter.Output[0]*AS_CALC_FACTOR + AS_COMPENSATE_FACTOR);
                                                  }
                                                  if( parameter_table[AnalogSpeedCommandDirectionReverse] == 1)
                                                  {
                                                       pid_speed.Ref = -pid_speed.Ref;
                                                  }
                                                  if( safe_parameter.Plc_In_CLESC1ZEROSPD == 1 )
                                                  {
                                                       pid_speed.Ref = 0;
                                                  }
                                                  break;
                                             }
                                             default:
                                             {
                                                  parameter_table[SpeedCommandChoice] = 0;
                                                  break;
                                             }
                                        }
                                        
                                        //CCW��ֹ��ת��ֹ
                                        if((safe_parameter.Plc_In_FSTP==0) && (pid_speed.Ref > 0))
                                        {
                                             pid_speed.Ref=0;
                                        }
                                        
                                        //CW��ֹ��ת��ֹ
                                        if((safe_parameter.Plc_In_RSTP==0) && (pid_speed.Ref < 0))
                                        {
                                             pid_speed.Ref=0;     
                                        }
                                        
                                        if(pid_speed.Ref > SPEED_MAX_FACTOR)
                                        {
                                             pid_speed.Ref = SPEED_MAX_FACTOR;
                                        }
                                        else if(pid_speed.Ref < SPEED_MIN_FACTOR)
                                        {
                                             pid_speed.Ref = SPEED_MIN_FACTOR;
                                        }
                                        
                                        if(pid_speed.Ref > IQ_Z_1)
                                        {
                                             pid_speed.Ref = IQ_Z_1;
                                        }
                                        else if(pid_speed.Ref < IQ_F_1)
                                        {
                                             pid_speed.Ref = IQ_F_1;
                                        }
                                        
                                        pid_speed.Err = pid_speed.Ref - pid_speed.Fdb;
                                        pi_caculation(&pid_speed);
                                   }
                                   break;
                              }
                              // ---------------1 �ٶȿ��Ʒ�ʽ------------------
                                                  
                              // ---------------2 �����п��Ʒ�ʽ----------------
                              case 2:
                              {
                                   // ----------------�ٶȵ�����--------------
                                   if( abs(speed_view_parameter.speed_view_after_filter) > SPEED_ARRIVE_FACTOR )
                                   {
                                        coin_enable();
                                        safe_parameter.Plc_Out_COIN = 1;
                                   }
                                   else
                                   {
                                        coin_disable();
                                        safe_parameter.Plc_Out_COIN = 0;
                                   }
                                   // ----------------�ٶȵ�����--------------
                                   if(safe_parameter.Command_Mode == SR_CONTROL)
                                   {
                                        speed_parameter.Qepcnt_new = angle_parameter.QepCnt;
                                        speed_calc(&speed_parameter);
                                        speed_fdb_filter.Input = _IQ20toIQ( _IQ20div( speed_parameter.speed , _IQ20(SPEED_UNIT_FACTOR) ) );
                                        low_filter_calc(&speed_fdb_filter);
                                        pid_speed.Fdb = speed_fdb_filter.Output[0];
                                        //pid_speed.Fdb = _IQ20toIQ( _IQ20div( speed_parameter.speed , _IQ20(SPEED_UNIT_FACTOR) ) );
                                        
                                        temp1= par_tspd * SPEED_COMMAND_FACTOR;
                                        pid_speed.Ref = (s32)temp1;
                                        //pid_speed.Ref = _IQ(0.1);
                                        
                                        //CCW��ֹ��ת��ֹ
                                        if((safe_parameter.Plc_In_FSTP==0) && (pid_speed.Ref > 0))
                                        {
                                             pid_speed.Ref=0;
                                        }
                                        
                                        //CW��ֹ��ת��ֹ
                                        if((safe_parameter.Plc_In_RSTP==0) && (pid_speed.Ref < 0))
                                        {
                                             pid_speed.Ref=0;     
                                        }
                                        
                                        if(pid_speed.Ref > SPEED_MAX_FACTOR)
                                        {
                                             pid_speed.Ref = SPEED_MAX_FACTOR;
                                        }
                                        else if(pid_speed.Ref < SPEED_MIN_FACTOR)
                                        {
                                             pid_speed.Ref = SPEED_MIN_FACTOR;
                                        }
                                        
                                        if(pid_speed.Ref > IQ_Z_1)
                                        {
                                             pid_speed.Ref = IQ_Z_1;
                                        }
                                        else if(pid_speed.Ref < IQ_F_1)
                                        {
                                             pid_speed.Ref = IQ_F_1;
                                        }
                                        
                                        pid_speed.Err = pid_speed.Ref - pid_speed.Fdb;
                                        pi_caculation(&pid_speed);
                                   }
                                   break;
                              }
                              // ---------------2 �����п��Ʒ�ʽ----------------
                              
                              // ---------------3 JOG���Ʒ�ʽ-------------------
                              case 3:
                              {
                                   // ----------------�ٶȵ�����--------------
                                   if( abs(speed_view_parameter.speed_view_after_filter) > SPEED_ARRIVE_FACTOR )
                                   {
                                        coin_enable();
                                        safe_parameter.Plc_Out_COIN = 1;
                                   }
                                   else
                                   {
                                        coin_disable();
                                        safe_parameter.Plc_Out_COIN = 0;
                                   }
                                   // ----------------�ٶȵ�����--------------
                                   if(safe_parameter.Command_Mode == JOG_CONTROL)
                                   {
                                        if(par_jog == 1)
                                        {
                                             temp1= parameter_table[JOGSpeed] * SPEED_COMMAND_FACTOR;
                                             pid_speed.Ref = (s32)temp1;
                                        }
                                        else if(par_jog == -1)
                                        {
                                             temp1= -parameter_table[JOGSpeed] * SPEED_COMMAND_FACTOR;
                                             pid_speed.Ref = (s32)temp1;
                                        }
                                        else 
                                        {
                                             pid_speed.Ref = _IQ(0);
                                        }
                                        
                                        speed_parameter.Qepcnt_new = angle_parameter.QepCnt;
                                        speed_calc(&speed_parameter);
                                        speed_fdb_filter.Input = _IQ20toIQ( _IQ20div( speed_parameter.speed , _IQ20(SPEED_UNIT_FACTOR) ) );
                                        low_filter_calc(&speed_fdb_filter);
                                        pid_speed.Fdb = speed_fdb_filter.Output[0];
                                        
                                        //CCW��ֹ��ת��ֹ
                                        if((safe_parameter.Plc_In_FSTP==0) && (pid_speed.Ref > 0))
                                        {
                                             pid_speed.Ref=0;
                                        }
                                        
                                        //CW��ֹ��ת��ֹ
                                        if((safe_parameter.Plc_In_RSTP==0) && (pid_speed.Ref < 0))
                                        {
                                             pid_speed.Ref=0;     
                                        }
                                        
                                        if(pid_speed.Ref > SPEED_MAX_FACTOR)
                                        {
                                             pid_speed.Ref = SPEED_MAX_FACTOR;
                                        }
                                        else if(pid_speed.Ref < SPEED_MIN_FACTOR)
                                        {
                                             pid_speed.Ref = SPEED_MIN_FACTOR;
                                        }
                                        
                                        if(pid_speed.Ref > IQ_Z_1)
                                        {
                                             pid_speed.Ref = IQ_Z_1;
                                        }
                                        else if(pid_speed.Ref < IQ_F_1)
                                        {
                                             pid_speed.Ref = IQ_F_1;
                                        }
                                        
                                        pid_speed.Err = pid_speed.Ref - pid_speed.Fdb;
                                        pi_caculation(&pid_speed);
                                   }
                                   break;
                              }
                              // ---------------3 JOG���Ʒ�ʽ-------------------                         
                         
                              // ---------------4 ������������Ʒ�ʽ------------
                              case 4:
                              {
                                   break;
                              }
                              // ---------------4 ������������Ʒ�ʽ------------                              
                         
                              // ----5 �������п��Ʒ�ʽ�����ڲ��Ե����������---
                              case 5:
                              {
                                   break;
                              }
                              // ----5 �������п��Ʒ�ʽ�����ڲ��Ե����������---
                              
                              // ---------------6 ת�ؿ��Ʒ�ʽ------------------
                              case 6:
                              {
                                   break;
                              }
                              // ---------------6 ת�ؿ��Ʒ�ʽ------------------
                              
                         
                              // ---------------7 �������Կ��Ʒ�ʽ--------------
                              case 7:
                              {
                                   break;
                              }
                              // ---------------7 �������Կ��Ʒ�ʽ--------------                      
                        
                              default:
                              {
                                   parameter_table[ControlMode] = 0;
                                   break;
                              }
                         }
                    }
                    else
                    {
                         speedloopcnt++;
                    }
               }
               else
               {
                    // ʹ�ܺ����û����ָ��ģʽ������ָ��Ϊ0
                    pid_speed.Out = 0;
               }
               
               // ----------------------�ٶ�PI���ͱ���--------------------------
               if( SPEED_PID_SATURATION_TIME_FACTOR > 0)
               {
                     //ERROR_speed_pid_saturation_now = 1;
                    if( pid_speed.Saturation_flag == 1 )
                    {
                         if( ERROR_speed_pid_saturation_counter < 60000 )
                         {
                              ERROR_speed_pid_saturation_counter++;
                         }
                         if(ERROR_speed_pid_saturation_counter > SPEED_PID_SATURATION_TIME_FACTOR)
                         {
                              ERROR_speed_pid_saturation = 1;
                              ERROR_speed_pid_saturation_counter = 0;
                         }
                    }
                    else if(ERROR_speed_pid_saturation_counter>0)
                    {
                         ERROR_speed_pid_saturation_counter--;
                    }
               }
               // ----------------------�ٶ�PI���ͱ���--------------------------
               
               // pid_id
               pid_id.Ref = 0;  // id�ο�ֵ=0
               //pid_id.Fdb = park_parameter.Ds;
               pid_id.Fdb = id_fdb_filter.Output[0];
               pid_id.Err =  pid_id.Ref - pid_id.Fdb;
               pi_caculation(&pid_id);
               
               // pid_iq
               iq_ref_filter.Input = pid_speed.Out;
               low_filter_calc(&iq_ref_filter);
               pid_iq.Ref = iq_ref_filter.Output[0];  // speed���ڷ���ֵ
               
               // �ڲ�ת������
               if(pid_iq.Ref > INTERIOR_TORQUE_MAX_FACTOR)
               {
                    pid_iq.Ref = INTERIOR_TORQUE_MAX_FACTOR;
               }
               else if(pid_iq.Ref < INTERIOR_TORQUE_MIN_FACTOR)
               {
                    pid_iq.Ref = INTERIOR_TORQUE_MIN_FACTOR;
               }
               
               // �ⲿת������
               // �ٶ�ģʽ�ڶ��֣��ⲿת�ز�������
               if( parameter_table[ControlMode] == 1 && parameter_table[SpeedCommandChoice] == 2)
               {
               }
               else
               {
                    if( (safe_parameter.Plc_In_FIL == 1) && (pid_iq.Ref >  EXTERIOR_TORQUE_MAX_FACTOR))
                    {
                         pid_iq.Ref = EXTERIOR_TORQUE_MAX_FACTOR;
                    }
                    else if( (safe_parameter.Plc_In_RIL == 1) && (pid_iq.Ref < EXTERIOR_TORQUE_MIN_FACTOR))
                    {
                         pid_iq.Ref = EXTERIOR_TORQUE_MIN_FACTOR;
                    }
               }
               
               if( ( (parameter_table[ControlMode] == 2) || (parameter_table[ControlMode] == 3)) && (pid_iq.Ref >  SR_TORQUE_MAX_FACTOR))
               {
                    pid_iq.Ref = SR_TORQUE_MAX_FACTOR;
               }
               else if( ( (parameter_table[ControlMode] == 2) || (parameter_table[ControlMode] == 3)) && (pid_iq.Ref <  SR_TORQUE_MIN_FACTOR))
               {
                    pid_iq.Ref = SR_TORQUE_MIN_FACTOR;
               }
               
               //pid_iq.Ref = _IQ(0.0);
               //pid_iq.Ref = pid_speed.Out;
               //pid_iq.Ref = _IQ(-0.06);  // iq�ο�ֵ=0.1
               //pid_iq.Fdb = park_parameter.Qs;
               pid_iq.Fdb = iq_fdb_filter.Output[0];
               pid_iq.Err =  pid_iq.Ref - pid_iq.Fdb;
               pi_caculation(&pid_iq);
               
               // ipark
               ipark_parameter.Ds = pid_id.Out;
               ipark_parameter.Qs = pid_iq.Out;
               ipark_parameter.Angle = angle_parameter.ElecAngle;  //�ջ��Ƕ�
               ipark_calc(&ipark_parameter);	//park��任
               
               // svpwm
               svpwm_parameter.Ualpha = ipark_parameter.Alpha;
               svpwm_parameter.Ubeta = ipark_parameter.Beta;
               svpwm_calc(&svpwm_parameter);
               //over_modu_calc(&svpwm_parameter);
               
               tim8_pwm_parameter.MfuncC1 = (s16)_IQtoIQ15(svpwm_parameter.Ta);
               tim8_pwm_parameter.MfuncC2 = (s16)_IQtoIQ15(svpwm_parameter.Tb);
               tim8_pwm_parameter.MfuncC3 = (s16)_IQtoIQ15(svpwm_parameter.Tc);
               tim8_pwm_update(&tim8_pwm_parameter);
          }
          //---------------------λ�ú��ٶ�ģʽ---------------------------------
          
          else
          {
               //led_run_off();
               TIM_CtrlPWMOutputs(TIM8, DISABLE);
          }
     }
     
     pid_iq_view_cnt++;
     if(pid_iq_view_cnt <= 1024)
     {
          pid_iq_view_add += (pid_iq.Fdb >> 10);
     }
     else
     {
          pid_iq_view_cnt = 0;
          pid_iq_view = pid_iq_view_add;
          pid_iq_view_add = 0;
     }
     
     speed_cmd_cnt++;
     if(speed_cmd_cnt <= 1024 )
     {
          speed_cmd_add += (pid_speed.Ref >> 10);
     }
     else
     {
          speed_cmd_cnt = 0;
          speed_cmd_view = speed_cmd_add;
          speed_cmd_add = 0;
     }
     
     // ��ն�ʱ�жϱ�־λ
     TIM_ClearITPendingBit(TIM8, TIM_IT_Update);  // �������� 0.8us
     
     // ---------------------------�۲�-----------------------------------------
     //testpoint1 = 100;
     //testpoint2 = Pos_Ref;     
     //viewer(128, 128);
     // ---------------------------�۲�-----------------------------------------
}



/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval : None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval : None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {       
       TIM_CtrlPWMOutputs(TIM8, DISABLE);
       led_run_off();
       disp_fault();
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval : None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval : None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval : None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval : None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval : None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval : None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval : None
  */
void SysTick_Handler(void)
{
}



/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
