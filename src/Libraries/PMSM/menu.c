#include "menu.h"


//参数区
//二级、参数设置
u32 par_spd;
u32 par_pos_low;
u32 par_pos_high;
u32 par_cpo_low;
u32 par_cpo_high;
u32 par_epo_low;
u32 par_epo_high;
u32 par_trq;
u32 par_i;
u32 par_lsp;
u32 par_cnt;
u32 par_frq;
s32 par_cs;
s32 par_ct;
u32 par_rpo;
u32 par_in;
u32 par_out;
u32 par_cod;
u32 par_rn;
u32 par_err;
u32 par_res;

//extern float elc_gear;
extern s32 Pos_Ref;
extern s32 Pos_RefH;
extern s16 Pos_Err;

//二级、参数设置
//s32 parameter_table[MEAU_NUM];
s16 parameter_table_tmp[MEAU_NUM];  //参数表

//二级、参数管理
u32 par_set;
u8 parameter_confirm=0;

//二级、速度试运行
s32 par_tspd;

//二级、job运行
s32 par_jog;
u16 par3s=0;

//key采集时间
u32 keydelay=0;
u32 disdelay=0;
u16 keyNUM=0;
static u8 Servo_Error_last=0;

u16 key_value;
u8 err_state=0;
u8 encoder_offset_mode=0;

extern s32  encoder_offset_deta;
extern s32 elc_gear_reset_cnt;




static u8 Digital[11]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,  0x00};

// 一级菜单-------------------------------------
u8 meau_dis1[8][6] = {{0x5E, 0x73, 0x40, 0x00, 0x00, 0x00},
                      {0x73, 0x77, 0x40, 0x00, 0x00, 0x00},
                      {0x79, 0x79, 0x40, 0x00, 0x00, 0x00},
                      {0x6D, 0x50, 0x40, 0x00, 0x00, 0x00},
                      {0x0E, 0x50, 0x40, 0x00, 0x00, 0x00},
                      {0x77, 0x3E, 0x40, 0x00, 0x00, 0x00},
                      {0x39, 0x3F, 0x40, 0x00, 0x00, 0x00},
                      {0x5C, 0x38, 0x40, 0x00, 0x00, 0x00}};

//----------------------------------------------

// 二级、监视菜单-----------------------------------------
u8 meau_dis21[21][6]={{0x5E, 0x73, 0x40, 0x6D, 0x73, 0x5E},
                      {0x5E, 0x73, 0x40, 0x73, 0x5C, 0x6D},
                      {0x5E, 0x73, 0x40, 0x73, 0x5C, 0xED},
                      {0x5E, 0x73, 0x40, 0x39, 0x73, 0x5C},
                      {0x5E, 0x73, 0x40, 0x39, 0x73, 0xDC},
                      {0x5E, 0x73, 0x40, 0x79, 0x73, 0x5C},
                      {0x5E, 0x73, 0x40, 0x79, 0x73, 0xDC},
                      {0x5E, 0x73, 0x40, 0x78, 0x50, 0x67},
                      {0x5E, 0x73, 0x40, 0x00, 0x00, 0x06},
                      {0x5E, 0x73, 0x40, 0x38, 0x6D, 0x73},
                      {0x5E, 0x73, 0x40, 0x39, 0x54, 0x78},
                      {0x5E, 0x73, 0x40, 0x71, 0x50, 0x67},
                      {0x5E, 0x73, 0x40, 0x00, 0x39, 0x6D},
                      {0x5E, 0x73, 0x40, 0x00, 0x39, 0x78},
                      {0x5E, 0x73, 0x40, 0x77, 0x73, 0x5C},
                      {0x5E, 0x73, 0x40, 0x00, 0x06, 0x54},
                      {0x5E, 0x73, 0x40, 0x5C, 0x3E, 0x78},
                      {0x5E, 0x73, 0x40, 0x39, 0x5C, 0x5E},
                      {0x5E, 0x73, 0x40, 0x00, 0x50, 0x54},
                      {0x5E, 0x73, 0x40, 0x79, 0x50, 0x50},
                      {0x5E, 0x73, 0x40, 0x50, 0x79, 0x6D}};
//--------------------------------------------------------

// 二级、参数设置菜单------------------------------
u8 meau_dis22[6]={0x73, 0x77, 0x40, 0x00, 0x00, 0x3F};
//--------------------------------------------------

// 二级、参数管理菜单--------------------------------
u8 meau_dis23[5][6]  ={{0x79, 0x79, 0x40, 0x6D, 0x79, 0x78},
                      {0x79, 0x79, 0x40, 0x00, 0x50, 0x5E},
                      {0x79, 0x79, 0x40, 0x00, 0x7C, 0x77},
                      {0x79, 0x79, 0x40, 0x00, 0x50, 0x6D},
                      {0x79, 0x79, 0x40, 0x5E, 0x79, 0x71}};
//---------------------------------------------------

// 二级、辅助功能菜单--------------------------------
u8 fn_jr[6] = {0x06, 0x40, 0x00, 0x0E, 0x50, 0x40};
u8 fn_ru[6] = {0x5B, 0x40, 0x00, 0x77, 0x3E, 0x40};
u8 fn_co[6] = {0x4F, 0x40, 0x00, 0x39, 0x3F, 0x40};
u8 fn_ol[6] = {0x66, 0x40, 0x00, 0x5C, 0x38, 0x40};
//---------------------------------------------------

u8 statemeau = 1;//菜单一级二级三级
u8 statemeau1 = 1;//第一级菜单序号
u8 statemeau2[8] = {1,1,1,1,1,1,1,1};//第二级菜单序号
u8 statemeau3 = 0;//第三级菜单序号
u8 meaumax2[8]={21,MEAU_NUM_NORMAL,5,1,1,1,1,1};//最大二级菜单数目
u8 dischar[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

u8 finish[6]={0x71, 0x04, 0x54, 0x04, 0x6d, 0x76};
u8 error[6]={0x79, 0x50, 0x50, 0x04, 0x50, 0x5c};
u8 start[6]={0x00, 0x6D, 0x78, 0x77, 0x50, 0x78};





void menu_init(void)
{
          statemeau = 3;
          statemeau1 = 1;
          statemeau2[0] = parameter_table[InitialDisplay]+1;
          statemeau2[1] = 1;
          statemeau2[2] = 1;
          statemeau2[3] = 1;
          statemeau2[4] = 1;
          statemeau2[5] = 1;
          statemeau2[6] = 1;
          statemeau2[7] = 1;
          statemeau3 = 0;
}

void null_function(void)
{
}

/*void menu_display(u8 *p)
{

          led_write( CH452_DIG5 | *p );
          led_write( CH452_DIG4 | *(p+1) );
          led_write( CH452_DIG3 | *(p+2) );
          led_write( CH452_DIG2 | *(p+3) );
          led_write( CH452_DIG1 | *(p+4) );
          led_write( CH452_DIG0 | *(p+5) );
}*/

void menu_displaychar(void)
{

          led_write( CH452_DIG5 | dischar[0] );
          led_write( CH452_DIG4 | dischar[1] );
          led_write( CH452_DIG3 | dischar[2] );
          led_write( CH452_DIG2 | dischar[3] );
          led_write( CH452_DIG1 | dischar[4] );
          led_write( CH452_DIG0 | dischar[5] );
}

void clear_display(void)
{
          led_write(CH452_DIG0 | NONE);
          led_write(CH452_DIG1 | NONE);
          led_write(CH452_DIG2 | NONE);
          led_write(CH452_DIG3 | NONE);
          led_write(CH452_DIG4 | NONE);
          led_write(CH452_DIG5 | NONE);
}

//菜单主函数
void menu_function(void)
{
          if(disdelay>4000)
          {
                    disdelay=1;
                    switch (statemeau)
                    {
                              case 1:     disp_1();break;
                              case 2:     disp_2();break;
                              case 3:     disp_3();break;
                         default: break;
                    }
                  
                    if((Servo_Error_last==0) && (safe_parameter.Servo_Error==1))
                    {                              
                              statemeau = 3;
                              statemeau1 = 1;
                              statemeau2[0] = 20;
                              statemeau3 = 1;
                              Servo_Error_last=1;                    
                    }
                      if(safe_parameter.Servo_Error==0)
                    {
                              Servo_Error_last=0;   
                    }
                    
                   if(safe_parameter.Servo_Error==1)
                    {
                              if(err_state==0)
                              {
                                        dischar[0]|=0x80;
                                        dischar[1]|=0x80;
                                        dischar[2]|=0x80;
                                        dischar[3]|=0x80;
                                        //dischar[4]|=0x80;
                                        //dischar[5]|=0x80;
                                        err_state=1;
                              }
                              else
                              {
                                        dischar[0]&=0x7f;
                                        dischar[1]&=0x7f;
                                        dischar[2]&=0x7f;
                                        dischar[3]&=0x7f;
                                        dischar[4]&=0x7f;
                                        dischar[5]&=0x7f;
                                        err_state=0;
                              }
                    }
                    menu_displaychar();
          }
          
          key_value = key_read(); 
          if(key_value <=63)
          {
                    par_jog=0;
                    keydelay=10000;
                    keyNUM=0;
          }
          else
          {
               if(keydelay>=10000)
               {
                    if((key_value >31) && (keydelay>=10000))
                    {
                         if(keyNUM==1)
                         {
                              keydelay=9000;
                         }          
                         if(keyNUM==0)
                         {
                              keydelay=4000; 
                              keyNUM=1;
                         }
                    }
                    switch (statemeau)
                    {
                         case 1:     menu_1();break;
                         case 2:     menu_2();break;
                         case 3:     menu_3();break;
                         default: break;
                    } 
                    switch (statemeau)
                    {
                         case 1:     disp_1();break;
                         case 2:     disp_2();break;
                         case 3:     disp_3();break;
                         default: break;
                    }          
                    menu_displaychar();
               }
          }
}
//一级菜单
void menu_1(void)
{
          switch (key_value)
          {
                    case UP:  
                    {
                              if(statemeau1>1)
                              {
                                        statemeau1--;
                              }
                              else
                              {
                                        statemeau1=8;
                              }
                              break;
                    }
                    case DOWN:  
                    {
                              if(statemeau1<8)
                              {
                                        statemeau1++;
                              }
                              else
                              {
                                        statemeau1=1;
                              }
                              break;
                    }
                    case ESC: 
                    {
                              break;
                    }
                    case ENTER:  
                    {
                              statemeau  = 2;
                              statemeau3 = 0;
                              par_tspd = 0;
                              par_jog=0;
                              if(statemeau1 == 4)
                              {
                                   if(safe_parameter.Command_Mode == STOP_CONTROL)
                                   {
                                        safe_parameter.Command_Mode = SR_CONTROL;
                                   }
                                   else
                                   {
                                        statemeau  = 1;                                   
                                   }
                              }
                              else if(statemeau1 == 5)
                              {
                                   if(safe_parameter.Command_Mode == STOP_CONTROL)
                                   {
                                        safe_parameter.Command_Mode = JOG_CONTROL;
                                   }
                                   else
                                   {
                                        statemeau  = 1;                                   
                                   }
                              }
                              else if(statemeau1 == 7)
                              {
                                   if(parameter_table[Password] == 326 && safe_parameter.Servo_Error == 0 && safe_parameter.System_State == WAIT)
                                   {
                                        encoder_offset_mode=1;
                                   }
                                   else
                                   {
                                        statemeau  = 1;                                       
                                   }
                              }
                              
                              break;
                    }
                    default: break;
          }
}
//二级菜单
void menu_2(void)
{
          switch (statemeau1)
          {
                    case 1:  menu_21();break;
                    case 2:  menu_22();break;
                    case 3:  menu_23();break;
                    case 4:  menu_24();break;
                    case 5:  menu_25();break;
                    case 6:  menu_26();break;
                    case 7:  menu_27();break;
                    case 8:  menu_28();break;
                    default: break;
          }      
}
//二级菜单监视子菜单
void menu_21(void)
{
          
          switch ( key_value)
          {
                    case UP: 
                    {
                              if(statemeau2[0]>1)
                              {
                                        statemeau2[0]--;
                              }
                              else
                              {
                                        statemeau2[0]=meaumax2[statemeau1-1];
                              }
                              break;
                    }
                    case DOWN:  
                    {
                              if(statemeau2[0]<meaumax2[statemeau1-1])
                              {
                                        statemeau2[0]++;
                              }
                              else
                              {
                                        statemeau2[0]=1;
                              }
                              break;
                    }
                    case ESC: 
                    {
                              statemeau  = 1;
                              statemeau3 = 0;
                              break;
                    }
                    case ENTER: 
                    {
                              statemeau  = 3;
                              statemeau3 = 1;
                              break;
                    }
                    default: break;
          }
}
//二级菜单参数子菜单
void menu_22(void)
{
          u16 i;
          switch ( key_value)
          {
                    case UP:  
                    {
                              if(statemeau2[1]>1)
                              {
                                        statemeau2[1]--;
                              }
                              else
                              {
                                        statemeau2[1]=meaumax2[statemeau1-1];
                              }
                              break;
                    }
                    case DOWN:  
                    {
                              if(statemeau2[1]<meaumax2[statemeau1-1])
                              {
                                        statemeau2[1]++;
                              }
                              else
                              {
                                        statemeau2[1]=1;
                              }
                              break;
                    }
                    case ESC: 
                    {
                              statemeau  = 1;
                              statemeau3 = 0;
                              parameter_confirm=0;
                              if(statemeau1 == 2)
                              {
                                        system_parameter_init();
                //                        elc_gear = ((float)parameter_table[PositionCommandDivisionNumerator]) / ((float)parameter_table[PositionCommandDivisionDenominator]);
                              }
   
                              break;
                    }
                    case ENTER:  
                    {
                         if(parameter_table[Password] != 385)
                         {
                              if(statemeau2[1]  ==  2 )
                              {
                                   break;    
                              }
                         }
                         if(safe_parameter.Current_On == 1)
                         {
                              if(statemeau2[1]  ==  Password+1 || 
                                 statemeau2[1]  ==  Version+1 ||
                                 statemeau2[1]  ==  ControlMode ||
                                 statemeau2[1]  ==  PositionCommandDivisionNumerator+1 ||
                                 statemeau2[1]  ==  PositionCommandDivisionDenominator+1 ||
                                 statemeau2[1]  ==  PositionCommandMode+1 ||
                                 statemeau2[1]  ==  SpeedCommandChoice+1  ||
                                 statemeau2[1]  ==  InteriorSpeed1+1  ||
                                 statemeau2[1]  ==  InteriorSpeed2+1  ||
                                 statemeau2[1]  ==  InteriorSpeed3+1  ||
                                 statemeau2[1]  ==  InteriorSpeed4+1 )
                              {
                                   break;    
                              }                    
                         }
                              statemeau  = 3;
                              statemeau3 = 1;
                              parameter_confirm=0;
                              for(i=0;i<MEAU_NUM;i++)
                              {
                                        parameter_table_tmp[i]=parameter_table[i];
                              }
                              break;
                    }
                    default: break;
          }
}
//二级菜单参数存储子菜单
void menu_23(void)
{
          
          switch ( key_value)
          {
                    case UP:  
                    {
                              if(statemeau2[2]>1)
                              {
                                        statemeau2[2]--;
                              }
                              else
                              {
                                        statemeau2[2]=meaumax2[statemeau1-1];
                              }
                              break;
                    }
                    case DOWN:  
                    {
                              if(statemeau2[2]<meaumax2[statemeau1-1])
                              {
                                        statemeau2[2]++;
                              }
                              else
                              {
                                        statemeau2[2]=1;
                              }
                              break;
                    }
                    case ESC: 
                    {
                              system_parameter_init();
                              statemeau  = 1;
                              statemeau3 = 0;
                              break;
                    }
                    case ENTER: 
                    {
                              statemeau  = 3;
                              statemeau3 = 1;
                              par_set= statemeau3;
                              break;
                    }
                    default: break;
          }
}
//二级菜单速度试运行子菜单
void menu_24(void)
{
          safe_parameter.Command_Mode = SR_CONTROL;
          switch ( key_value)
          {
                    case UP: 
                    {
                              if(par_tspd>-motor_parameter[parameter_table[Version]].Rate_Speed)
                              {
                                        par_tspd-=1;
                              }
                              break;
                    }
                    case DOWN: 
                    {
                              if(par_tspd<motor_parameter[parameter_table[Version]].Rate_Speed)
                              {
                                        par_tspd+=1;
                              }
                              break;
                    }
                    case ESC:  
                    {
                              if((par_tspd>-200) && (par_tspd < 200))
                              {
                                        safe_parameter.Command_Mode = STOP_CONTROL;
                                        par_tspd = 0;
                                        statemeau  = 1;
                                        statemeau3 = 0;
                              }
                              break;
                    }
                    case ENTER:  
                    {
                              break;
                    }
                    default: break;
          }
}
//二级菜单JOG试运行子菜单
void menu_25(void)
{
          safe_parameter.Command_Mode = JOG_CONTROL;
          switch ( key_value)
          {
                    case UP:  
                    {
                              par_jog=1;
                              break;
                    }
                    case DOWN:  
                    {
                              par_jog=-1;
                              break;
                    }
                    case ESC: 
                    {
                              safe_parameter.Command_Mode = STOP_CONTROL;
                              statemeau  = 1;
                              statemeau3 = 0;
                              par_jog=0;
                              break;
                    }
                    case ENTER: 
                    {
                              break;
                    }                    
                    default: break;
          }
}

void menu_26(void)
{
          switch ( key_value)
          {
                    case UP:  
                    {
                         
                              break;
                    }
                    case DOWN: 
                    {
                              break;
                    }
                    case ESC: 
                    {
                              statemeau  = 1;
                              statemeau3 = 0;
                              break;
                    }
                    case ENTER: 
                    {
                              break;
                    }
                    default: break;
          }
}

void menu_27(void)
{
          switch ( key_value)
          {
                    case UP: 
                    {
                              break;
                    }
                    case DOWN: 
                    {
                              break;
                    }
                    case ESC: 
                    {
                              if(encoder_offset_mode == 0)
                              {
                                   statemeau  = 1;
                                   statemeau3 = 0;
                              }
                              break;
                    }
                    case ENTER: 
                    {
                              break;
                    }
                    default: break;
          }
}

void menu_28(void)
{ 
          switch ( key_value)
          {
                    case UP:
                    {
                              break;
                    } 
                    case DOWN:  
                    {       
                              break;
                    }
                    case ESC: 
                    {
                              statemeau  = 1;
                              statemeau3 = 0;
                              break;
                    }
                    case ENTER: 
                    {
                              break;
                    }
                    default: break;
          }
}

//三级子菜单
void menu_3(void)
{    
          switch (statemeau1)
          {
                    case 1:  menu_31();break;
                    case 2:  menu_32();break;
                    case 3:  menu_33();break;
                    default: break;
          }
}


//三级菜单监视子菜单
void menu_31(void)
{
          
          switch ( key_value)
          {
                    case UP: 
                    {
                              break;
                    }
                    case DOWN: 
                    {
                              break;
                    }
                    case ESC: 
                    {
                              statemeau  = 2;
                              statemeau3 = 0;
                              break;
                    }
                    case ENTER: 
                    {
                              break;
                    }
                    default: break;
          }
}
              
//三级菜单参数设置子菜单     
void menu_32(void)
{
    u16 i;
    switch ( key_value)
    {
    case UP:  {
                parameter_confirm=0;
                if(parameter_table_tmp[statemeau2[1]-1]>parameter_table_min[statemeau2[1]-1])
                {
                    parameter_table_tmp[statemeau2[1]-1]-=parameter_table_step[statemeau2[1]-1];
                }
                break;
              }
    case DOWN:  {
                parameter_confirm=0;
                if(parameter_table_tmp[statemeau2[1]-1]<parameter_table_max[statemeau2[1]-1])
                {
                    parameter_table_tmp[statemeau2[1]-1]+=parameter_table_step[statemeau2[1]-1];
                }
                break;
              }
    case ESC:  {
                statemeau  = 2;
                statemeau3 = 0;
                parameter_confirm=0;
                break;
              }
    case ENTER:  {
                if( parameter_table_tmp[PositionCommandMode]!=parameter_table[PositionCommandMode])
                {
                     if(parameter_table_tmp[PositionCommandMode]==0)
                          cmd_plus_sign_config();
                     else if(parameter_table_tmp[PositionCommandMode]==1)
                          cmd_plus_plus_config();
                     else if(parameter_table_tmp[PositionCommandMode]==2)
                          cmd_quadrature_config();
                }
                
                for(i=0;i<MEAU_NUM;i++)
                {
                     parameter_table[i]=parameter_table_tmp[i];
                }
                if(statemeau2[1] == 2)
                {
                    motor_parameter_read();
                    angle_init(&angle_parameter);
                }
                
                if( parameter_table[Password] == 327)
                {
                     meaumax2[1] = MEAU_NUM;
                }
                else
                {
                     meaumax2[1] = MEAU_NUM_NORMAL;                
                }
                
                system_parameter_init();
                parameter_confirm=1;
                break;
              }
     default: break;
    }
}

//三级菜单参数保存子菜单
void menu_33(void)
{
    switch ( key_value)
    {
    case UP:  {
              par3s=0;
                break;
              }
    case DOWN:  {
              par3s=0;
                break;
              }
    case ESC:  {
              par3s=0;
                statemeau  = 2;
                statemeau3 = 0;
                break;
              }
    case ENTER:  {
              if(par3s < 15)
              {
                        par3s++;
              }
              else
              {
                        
                        par3s = 0;
                        dischar[0]=start[0];
                        dischar[1]=start[1];                        
                        dischar[2]=start[2];
                        dischar[3]=start[3];
                        dischar[4]=start[4];
                        dischar[5]=start[5];
                        menu_displaychar();
                        safe_parameter.Eeprom_Error=AT24CXX_Check1();
                        if(safe_parameter.Eeprom_Error==1)
                        {
                                  dischar[0]=error[0];
                                  dischar[1]=error[1];
                                  dischar[2]=error[2];
                                  dischar[3]=error[3];
                                  dischar[4]=error[4];
                                  dischar[5]=error[5];
                                  menu_displaychar();
                                  break;
                        }
                        if(statemeau2[2]==1)
                        {
                                  par_to_par_region();
                        }
                        if(statemeau2[2]==2)
                        {
                                  par_region_to_par();
                        }
                        if(statemeau2[2]==3)
                        {
                                  par_to_backup_region();
                        }
                        if(statemeau2[2]==4)
                        {
                                  backup_region_to_par();
                        }
                        if(statemeau2[2]==5)
                        {
                                  default_to_all ();
                        }
                        
                        dischar[0]=finish[0];
                        dischar[1]=finish[1];                        
                        dischar[2]=finish[2];
                        dischar[3]=finish[3];
                        dischar[4]=finish[4];
                        dischar[5]=finish[5];
                        menu_displaychar();
              }
                break;
              }
              default: break;
    }
}


void disp_1(void)
{
    dischar[0]=meau_dis1[statemeau1-1][0];
    dischar[1]=meau_dis1[statemeau1-1][1];
    dischar[2]=meau_dis1[statemeau1-1][2];
    dischar[3]=meau_dis1[statemeau1-1][3];
    dischar[4]=meau_dis1[statemeau1-1][4];
    dischar[5]=meau_dis1[statemeau1-1][5];
}

void disp_2(void)
{ 
    switch (statemeau1)
    {
    case 1: { 
              dischar[0]=meau_dis21[statemeau2[0]-1][0];
              dischar[1]=meau_dis21[statemeau2[0]-1][1];
              dischar[2]=meau_dis21[statemeau2[0]-1][2];
              dischar[3]=meau_dis21[statemeau2[0]-1][3];
              dischar[4]=meau_dis21[statemeau2[0]-1][4];
              dischar[5]=meau_dis21[statemeau2[0]-1][5];
              break;
          }
    case 2: { 
              dischar[0]=meau_dis22[0];
              dischar[1]=meau_dis22[1];
              dischar[2]=meau_dis22[2];
              dischar[3]=meau_dis22[3];
              dischar[4]=Digital[(statemeau2[1]-1)%100/10];
              dischar[5]=Digital[(statemeau2[1]-1)%10];
              break;
          }
    case 3: { 
              dischar[0]=meau_dis23[statemeau2[2]-1][0];
              dischar[1]=meau_dis23[statemeau2[2]-1][1];
              dischar[2]=meau_dis23[statemeau2[2]-1][2];
              dischar[3]=meau_dis23[statemeau2[2]-1][3];
              dischar[4]=meau_dis23[statemeau2[2]-1][4];
              dischar[5]=meau_dis23[statemeau2[2]-1][5];
              break;
          }
    case 4: { 
              dischar[0]=0x6d;
              dischar[1]=par_tspd>=0?0x00:0x40;
              dischar[2]=abs(par_tspd)>=1000?Digital[abs(par_tspd)%10000/1000]:0x00;
              dischar[3]=abs(par_tspd)>=100?Digital[abs(par_tspd)%1000/100]:0x00;
              dischar[4]=abs(par_tspd)>=10?Digital[abs(par_tspd)%100/10]:0x00;
              dischar[5]=Digital[abs(par_tspd)%10];
              break;
          }
    case 5: { 
              dischar[0]=0x0e;
              dischar[1]=par_jog>=0?0x00:0x40;
              dischar[2]=abs(par_jog)>=1000?Digital[abs(par_jog)%10000/1000]:0x00;
              dischar[3]=abs(par_jog)>=100?Digital[abs(par_jog)%1000/100]:0x00;
              dischar[4]=abs(par_jog)>=10?Digital[abs(par_jog)%100/10]:0x00;
              dischar[5]=Digital[abs(par_jog)%10];
              break;
          }
    case 6: { 
              dischar[0]=Digital[statemeau1-1];
              dischar[1]=Digital[1];
              dischar[2]=Digital[statemeau2[6]-1];
              dischar[3]=Digital[3];
              dischar[4]=Digital[4];
              dischar[5]=Digital[5];
              break;
          }
    case 7: { 
              dischar[0]=encoder_offset_deta>=0?0x00:0x40;
              
              dischar[1]=abs(encoder_offset_deta)>=10000?Digital[abs(encoder_offset_deta)%100000/10000]:0x00;
              dischar[2]=abs(encoder_offset_deta)>=1000?Digital[abs(encoder_offset_deta)%10000/1000]:0x00;
              dischar[3]=abs(encoder_offset_deta)>=100?Digital[abs(encoder_offset_deta)%1000/100]:0x00;
              dischar[4]=abs(encoder_offset_deta)>=10?Digital[abs(encoder_offset_deta)%100/10]:0x00;
              dischar[5]=Digital[abs(encoder_offset_deta)%10];
              break;
          }
    case 8: { 
              dischar[0]=Digital[statemeau1-1];
              dischar[1]=Digital[1];
              dischar[2]=Digital[statemeau2[7]-1];
              dischar[3]=Digital[3];
              dischar[4]=Digital[4];
              dischar[5]=Digital[5];
              break;
          }
          default: break;
    }
    
}

void disp_3(void)
{ 
    switch (statemeau1)
    {
    case 1: { 
              disp_31();
              break;
          }
    case 2: { 
              disp_32();
              break;
          }
    case 3: { 
              break;
          }
    case 4: { 
              break;
          }
    case 5: { 
              break;
          }
    case 6: { 
              break;
          }
    case 7: { 
              break;
          }
    case 8: { 
              break;
          }
     default: break;
    }
    
}

extern s32 pid_iq_view;
extern s32 speed_cmd_view;

void disp_31(void)
{ 
double a,b,c;
s32 d,e,f,g;
    switch (statemeau2[0])
    {
              //速度
    case 1: { 
              par_spd=abs(speed_view_parameter.speed_view_after_filter);// *175690; // * 10 *60 /2 /3.14;
              dischar[0]=speed_view_parameter.speed_view_after_filter>=0?0x00:0x40;
              dischar[1]=par_spd>=10000?Digital[par_spd%100000/10000]:0x00;
              dischar[2]=par_spd>=1000?Digital[par_spd%10000/1000]:0x00;
              dischar[3]=par_spd>=100?Digital[par_spd%1000/100]:0x00;
              dischar[4]=par_spd>=10?Digital[par_spd%100/10]:0x00;
              dischar[5]=Digital[par_spd%10];
              break;
          }
    case 2: { 
              //当前位置低5位
               e= elc_gear_reset_cnt;
               f= ELC_GEAR_MUL_FDB;
               g= angle_parameter.PstFdb;
               a= (double)e * (double)f;
               b= a + (double)g;
              dischar[0]=b>=0?0x00:0x40;
               c= b/100000;
               d = (s32)c;
               c = (double)d;
               a= b- c*100000;
               d= (s32)a;
              par_pos_low=abs(d%100000);
              dischar[1]=Digital[par_pos_low%100000/10000];
              dischar[2]=Digital[par_pos_low%10000/1000];
              dischar[3]=Digital[par_pos_low%1000/100];
              dischar[4]=Digital[par_pos_low%100/10];
              dischar[5]=Digital[par_pos_low%10];
              break;
          }
    case 3: { 
              //当前位置高5位
               e= elc_gear_reset_cnt;
               f= ELC_GEAR_MUL_FDB;
               g= angle_parameter.PstFdb;
               a= (double)e * (double)f;
               b= a + (double)g;
              dischar[0]=b>=0?0x00:0x40;
               c= b/100000;
               d = (s32)c;
              par_pos_high=abs(d%100000);
              dischar[1]=par_pos_high>=10000?Digital[par_pos_high%100000/10000]:0x00;
              dischar[2]=par_pos_high>=1000?Digital[par_pos_high%10000/1000]:0x00;
              dischar[3]=par_pos_high>=100?Digital[par_pos_high%1000/100]:0x00;
              dischar[4]=par_pos_high>=10?Digital[par_pos_high%100/10]:0x00;
              dischar[5]=Digital[par_pos_high%10];
              break;
          }
    case 4: { 
              //位置指令低5位
               e= elc_gear_reset_cnt;
               f= ELC_GEAR_MUL_FDB;
               g= Pos_Ref;
               a= (double)e * (double)f;
               b= a + (double)g;
              dischar[0]=b>=0?0x00:0x40;
               c= b/100000;
               d = (s32)c;
               c = (double)d;
               a= b- c*100000;
               d= (s32)a;
               par_cpo_low=abs(d%100000);              
              dischar[1]=Digital[par_cpo_low%100000/10000];
              dischar[2]=Digital[par_cpo_low%10000/1000];
              dischar[3]=Digital[par_cpo_low%1000/100];
              dischar[4]=Digital[par_cpo_low%100/10];
              dischar[5]=Digital[par_cpo_low%10];
              break;
          }
    case 5: { 
              //位置指令高5位
               e= elc_gear_reset_cnt;
               f= ELC_GEAR_MUL_FDB;
               g= Pos_Ref;
               a= (double)e * (double)f;
               b= a + (double)g;
              dischar[0]=b>=0?0x00:0x40;
               c= b/100000;
               d = (s32)c;
              par_cpo_high=abs(d%100000);
              dischar[1]=par_cpo_high>=10000?Digital[par_cpo_high%100000/10000]:0x00;
              dischar[2]=par_cpo_high>=1000?Digital[par_cpo_high%10000/1000]:0x00;
              dischar[3]=par_cpo_high>=100?Digital[par_cpo_high%1000/100]:0x00;
              dischar[4]=par_cpo_high>=10?Digital[par_cpo_high%100/10]:0x00;
              dischar[5]=Digital[par_cpo_high%10];
              break;
          }
    case 6: { 
              //位置误差低5位
              par_epo_low=abs(Pos_Err%100000);
              dischar[0]=Pos_Err>=0?0x00:0x40;
              dischar[1]=par_epo_low>=10000?Digital[par_epo_low%100000/10000]:0x00;
              dischar[2]=par_epo_low>=1000?Digital[par_epo_low%10000/1000]:0x00;
              dischar[3]=par_epo_low>=100?Digital[par_epo_low%1000/100]:0x00;
              dischar[4]=par_epo_low>=10?Digital[par_epo_low%100/10]:0x00;
              dischar[5]=Digital[par_epo_low%10];
              break;
          }
    case 7: { 
              //位置误差高5位
              par_epo_low=abs(Pos_Err/100000);
              dischar[0]=Pos_Err>=0?0x00:0x40;
              dischar[1]=par_epo_high>=10000?Digital[par_epo_high%100000/10000]:0x00;
              dischar[2]=par_epo_high>=1000?Digital[par_epo_high%10000/1000]:0x00;
              dischar[3]=par_epo_high>=100?Digital[par_epo_high%1000/100]:0x00;
              dischar[4]=par_epo_high>=10?Digital[par_epo_high%100/10]:0x00;
              dischar[5]=Digital[par_epo_high%10];
              break;
          }
    case 8: { 
              //电机转矩
              par_trq=abs((s32)(pid_iq_view * MOTOR_TORQUE_VIEW_FACTOR));
              dischar[0]=pid_iq_view>=0?0x00:0x40;
              dischar[1]=0x00;
              dischar[2]=0x00;
              dischar[3]=0x00;
              dischar[4]=par_trq>=10?Digital[par_trq%100/10]:0x00;
              dischar[5]=Digital[par_trq%10];
              break;
          }
    case 9: { //两位小数
              //电流
              par_i=abs((s32)(pid_iq_view * MOTOR_CURRENT_VIEW_FACTOR));
              dischar[0]=pid_iq_view>=0?0x00:0x40;
              dischar[1]=0x00;
              dischar[2]=par_i>=1000?Digital[par_i%10000/1000]:0x00;
              dischar[3]=Digital[par_i%1000/100]|0x80;
              dischar[4]=Digital[par_i%100/10];
              dischar[5]=Digital[par_i%10];
              break;
          }
    case 10: { //三位小数
              par_lsp = 0;
              dischar[0]=0x38;
              dischar[1]=par_lsp>=10000?Digital[par_lsp%100000/10000]:0x00;
              dischar[2]=Digital[par_lsp%10000/1000]|0x80;
              dischar[3]=Digital[par_lsp%1000/100];
              dischar[4]=Digital[par_lsp%100/10];
              dischar[5]=Digital[par_lsp%10];
              break;
          }
    case 11: { 
              //当前控制方式
              par_cnt=parameter_table[ControlMode];
              dischar[0]=0x39;
              dischar[1]=0x54;
              dischar[2]=0x78;
              dischar[3]=0x00;
              dischar[4]=0x00;
              dischar[5]=Digital[par_cnt%10];
              break;
          }
    case 12: { //一位小数
              //
              dischar[0]=0x71;
              dischar[1]=0x00;
              dischar[2]=par_frq>=1000?Digital[par_frq%10000/1000]:0x00;
              dischar[3]=par_frq>=100?Digital[par_frq%1000/100]:0x00;
              dischar[4]=Digital[par_frq%100/10]|0x80;
              dischar[5]=Digital[par_frq%10];
              break;
          }
    case 13: { 
              //速度指令
              par_cs=(s32)(speed_cmd_view * SPEED_CMD_VIEW_FACTOR);
              dischar[0]=0xd0;
              dischar[1]=par_cs>=0?0x00:0x40;
              dischar[2]=abs(par_cs)>=1000?Digital[abs(par_cs)%10000/1000]:0x00;
              dischar[3]=abs(par_cs)>=100?Digital[abs(par_cs)%1000/100]:0x00;
              dischar[4]=abs(par_cs)>=10?Digital[abs(par_cs)%100/10]:0x00;
              dischar[5]=Digital[abs(par_cs)%10];
              break;
          }
    case 14: { 
              //转矩指令
              //par_ct=pid_iq.Ref/167772;
              par_ct = 0;
              dischar[0]=0xf8;
              dischar[1]=0x00;
              dischar[2]=0x00;
              dischar[3]=par_ct>=0?0x00:0x40;
              dischar[4]=abs(par_ct)>=10?Digital[abs(par_ct)%100/10]:0x00;
              dischar[5]=Digital[abs(par_ct)%10];
              break;
          }
    case 15: { 
              //转子一转中的位置
              par_rpo=angle_parameter.ThetaRaw;
              dischar[0]=0x77;
              dischar[1]=par_rpo>=10000?Digital[par_rpo%100000/10000]:0x00;
              dischar[2]=par_rpo>=1000?Digital[par_rpo%10000/1000]:0x00;
              dischar[3]=par_rpo>=100?Digital[par_rpo%1000/1000]:0x00;
              dischar[4]=par_rpo>=10?Digital[par_rpo%100/10]:0x00;
              dischar[5]=Digital[par_rpo%10];
              break;
          }
    case 16: { 
              //输入端子状态
              par_in=safe_parameter.Plc_In_SON + safe_parameter.Plc_In_ALRS*2 
                        + safe_parameter.Plc_In_FSTP*4 + safe_parameter.Plc_In_RSTP*8 
                                  + safe_parameter.Plc_In_CLESC1ZEROSPD*16 + safe_parameter.Plc_In_INHSC2*32 
                                            + safe_parameter.Plc_In_FIL*64 + safe_parameter.Plc_In_RIL*128;
              dischar[0]=0x06;
              dischar[1]=0x54;
              dischar[2]=0x14|((par_in&0x80)==0x80?0x20:0x00)|((par_in&0x40)==0x40?0x02:0x00);
              dischar[3]=0x14|((par_in&0x20)==0x20?0x20:0x00)|((par_in&0x10)==0x10?0x02:0x00);
              dischar[4]=0x14|((par_in&0x08)==0x08?0x20:0x00)|((par_in&0x04)==0x04?0x02:0x00);
              dischar[5]=0x14|((par_in&0x02)==0x02?0x20:0x00)|((par_in&0x01)==0x01?0x02:0x00);
              break;
          }
    case 17: { 
              //输出端子状态
              par_out=safe_parameter.Plc_Out_SRDY + safe_parameter.Plc_Out_ALM*2 + safe_parameter.Plc_Out_COIN*4 +safe_parameter.Plc_Out_BRK*8;
              dischar[0]=0x5c;
              dischar[1]=0x3e;
              dischar[2]=0x78;
              dischar[3]=0x00;
              dischar[4]=0x14|((par_out&0x08)==0x08?0x20:0x00)|((par_out&0x04)==0x04?0x02:0x00);
              dischar[5]=0x14|((par_out&0x02)==0x02?0x20:0x00)|((par_out&0x01)==0x01?0x02:0x00);
              break;
          }
    case 18: { 
              //编码器输入信号
              par_cod= safe_parameter.Encoder_Test_A + safe_parameter.Encoder_Test_B*2 + safe_parameter.Encoder_Test_Z*4 + safe_parameter.Encoder_Test_U*8 + safe_parameter.Encoder_Test_V*16 + safe_parameter.Encoder_Test_W*32;
              dischar[0]=0x39;
              dischar[1]=0x5c;
              dischar[2]=0x5e;
              dischar[3]=0x14|((par_cod&0x20)==0x20?0x20:0x00)|((par_cod&0x10)==0x10?0x02:0x00);
              dischar[4]=0x14|((par_cod&0x08)==0x08?0x20:0x00)|((par_cod&0x04)==0x04?0x02:0x00);
              dischar[5]=0x14|((par_cod&0x02)==0x02?0x20:0x00)|((par_cod&0x01)==0x01?0x02:0x00);
              break;
          }
    case 19: { 
              dischar[0]=0x50;
              dischar[1]=0x54;
              dischar[2]=0x40;
              if(safe_parameter.Drive_Lv==0)
                   {
                   dischar[3]=0x5c;
                   dischar[4]=0x71;
                   dischar[5]=0x71;
              }
              else if(safe_parameter.Current_On==0)
                   {
                   dischar[3]=0x00;
                   dischar[4]=0x39;
                   dischar[5]=0x76;
              }
              else if(safe_parameter.Current_On==1)
                   {
                   dischar[3]=0x00;
                   dischar[4]=0x5c;
                   dischar[5]=0x54;
              }
              break;
          }
    case 20: { 
              par_err=safe_parameter.Servo_Error_Code;
              dischar[0]=0x79;
              dischar[1]=0x50;
              dischar[2]=0x50;
              dischar[3]=0x00;
              if(par_err==0)
              {
              dischar[4]=0x40;
              dischar[5]=0x40; 
              }
              else
              {
              dischar[4]=par_err>=10?Digital[par_err%100/10]:0x00;
              dischar[5]=Digital[par_err%10];
              }
              break;
          }
    case 21: { 
              dischar[0]=0x3e;
              dischar[1]=0x00;
              dischar[2]=0x00;
              dischar[3]=0x00;
              dischar[4]=0x00;
              dischar[5]=Digital[0];
              break;
          }
          
    default: break;
    }
    
}


void disp_32(void)
{ 
          if((statemeau2[1] >= 54) &&(statemeau2[1] <= 58))
          {
                    dischar[0]=0x00;
                    dischar[1]=0x00;
                    dischar[2]=(((u8)parameter_table_tmp[statemeau2[1]-1])&((u8)0x08))==0x08?Digital[1]:Digital[0];
                    dischar[3]=(((u8)parameter_table_tmp[statemeau2[1]-1])&((u8)0x04))==0x04?Digital[1]:Digital[0];
                    dischar[4]=(((u8)parameter_table_tmp[statemeau2[1]-1])&((u8)0x02))==0x02?Digital[1]:Digital[0];
                    dischar[5]=(((u8)parameter_table_tmp[statemeau2[1]-1])&((u8)0x01))==0x01?Digital[1]:Digital[0];
          }
          else if((statemeau2[1] >= 69) &&(statemeau2[1] <= 74))
          {
                    dischar[0]=(((u8)parameter_table_tmp[statemeau2[1]-1])&((u8)0x20))==0x20?Digital[1]:Digital[0];
                    dischar[1]=(((u8)parameter_table_tmp[statemeau2[1]-1])&((u8)0x10))==0x10?Digital[1]:Digital[0];
                    dischar[2]=(((u8)parameter_table_tmp[statemeau2[1]-1])&((u8)0x08))==0x08?Digital[1]:Digital[0];
                    dischar[3]=(((u8)parameter_table_tmp[statemeau2[1]-1])&((u8)0x04))==0x04?Digital[1]:Digital[0];
                    dischar[4]=(((u8)parameter_table_tmp[statemeau2[1]-1])&((u8)0x02))==0x02?Digital[1]:Digital[0];
                    dischar[5]=(((u8)parameter_table_tmp[statemeau2[1]-1])&((u8)0x01))==0x01?Digital[1]:Digital[0];
          }
          else
          {
                    dischar[0]=parameter_table_tmp[statemeau2[1]-1]>=0?0x00:0x40;
                    dischar[1]=abs(parameter_table_tmp[statemeau2[1]-1])>=10000?Digital[abs(parameter_table_tmp[statemeau2[1]-1])%100000/10000]:0x00;
                    dischar[2]=abs(parameter_table_tmp[statemeau2[1]-1])>=1000?Digital[abs(parameter_table_tmp[statemeau2[1]-1])%10000/1000]:0x00;
                    dischar[3]=abs(parameter_table_tmp[statemeau2[1]-1])>=100?Digital[abs(parameter_table_tmp[statemeau2[1]-1])%1000/100]:0x00;
                    dischar[4]=abs(parameter_table_tmp[statemeau2[1]-1])>=10?Digital[abs(parameter_table_tmp[statemeau2[1]-1])%100/10]:0x00;
                    dischar[5]=Digital[abs(parameter_table_tmp[statemeau2[1]-1])%10];
          }
          
          if(parameter_confirm==0)
          {
               dischar[5]|=0x80;
          }
          
}

void disp_fault(void)
{ 
                    dischar[0]=0x71;
                    dischar[1]=0x77;
                    dischar[2]=0x3E;
                    dischar[3]=0x38;
                    dischar[4]=0x78;
                    dischar[5]=0x00;
}