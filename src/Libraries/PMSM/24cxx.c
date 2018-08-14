#include "24cxx.h" 

//u8 eeprom_err = 0;


/*初始化IIC接口*/
void AT24CXX_Init(void)
{
     u8 i;
     IIC_Init();
     i=AT24CXX_Check();
     
     /* 参数读取：参数区到参数表*/
     if(i == 0)
     {
          par_region_to_par();
     }
     /* 参数写入：参数表到参数区*/
     if(i == 1)
     {
          par_to_par_region();
     }
     if(i == 2)
     {
          ERROR_eeprom = 1;
     }        
}

/*在AT24CXX指定地址读出一个数据*/
/*ReadAddr:开始读数的地址  */
/*返回值  :读到的数据*/
static u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{
     u8 temp=0;
     IIC_Start();  
     if(EE_TYPE>AT24C16)
     {
          IIC_Send_Byte(0XA0);	   /*发送写命令*/
          IIC_Wait_Ack();
          IIC_Send_Byte(ReadAddr>>8);/*发送高地址*/
          IIC_Wait_Ack();		 
     }
     else
     {
          IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   /*发送器件地址0XA0,写数据*/
          IIC_Wait_Ack();  	
     }
     
     IIC_Send_Byte(ReadAddr%256);   /*发送低地址*/
     IIC_Wait_Ack();	    
     IIC_Start();  	 	  
     IIC_Send_Byte(0XA1);           /*进入接收模式	*/	 
     IIC_Wait_Ack();	 
     temp=IIC_Read_Byte(0);		  
     IIC_Stop();/*产生一个停止条件	*/   
     return temp;
}




/*在AT24CXX指定地址写入一个数据*/
/*WriteAddr  :写入数据的目的地址  */  
/*DataToWrite:要写入的数据*/
static void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{
     u16 i;
     IIC_Start();  
     if(EE_TYPE>AT24C16)
     {
          IIC_Send_Byte(0XA0);	    /*发送写命令*/
          IIC_Wait_Ack();
          IIC_Send_Byte(WriteAddr>>8);/*发送高地址*/
          IIC_Wait_Ack();	
     }
     else
     {
          IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   /*发送器件地址0XA0,写数据 */
          IIC_Wait_Ack();
     }	 
     IIC_Send_Byte(WriteAddr%256);   /*发送低地址*/
     IIC_Wait_Ack(); 	 		
     IIC_Send_Byte(DataToWrite);     /*发送字节*/
     IIC_Wait_Ack();  		
     IIC_Stop();/*产生一个停止条件 */
     for(i=0;i<60;i++)
     {
          delay_200us();
     }
}

/*在AT24CXX里面的指定地址开始写入长度为Len的数据*/
/*该函数用于写入16bit或者32bit的数据.*/
/*WriteAddr  :开始写入的地址  */
/*DataToWrite:数据数组首地址*/
/*Len        :要写入数据的长度2,4*/
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

/*在AT24CXX里面的指定地址开始读出长度为Len的数据*/
/*该函数用于读出16bit或者32bit的数据.*/
/*ReadAddr   :开始读出的地址 */
/*返回值     :数据*/
/*Len        :要读出数据的长度2,4*/
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
/*检查AT24CXX是否正常*/
/*这里用了24XX的最后一个地址(255)来存储标志字.*/
/*如果用其他24C系列,这个地址要修改*/
/*返回1:检测失败*/
/*返回0:检测成功*/
static u8 AT24CXX_Check(void)
{
	u8 temp,return_temp;
     if( AT24CXX_Check1() == 0 )
     {
          temp=AT24CXX_ReadOneByte(1000);/*避免每次开机都写AT24CXX	*/
          if(temp==0X33)
          {
               return_temp=0;
          }        
          else/*排除第一次初始化的情况*/
          {
               AT24CXX_WriteOneByte(1000,0X33);
               temp=AT24CXX_ReadOneByte(1000);
               if(temp==0X33)
               {
                    return_temp=1;
               }
               else
               {
                    ERROR_eeprom = 1;
                    return_temp=2;
               }               
          }
     }
     else
     {
          ERROR_eeprom = 1;
          return_temp = 2;     
     }
     return return_temp;
}

/*检查AT24CXX是否正常*/
/*这里用了24XX的最后一个地址(255)来存储标志字.*/
/*如果用其他24C系列,这个地址要修改*/
/*返回1:检测失败*/
/*返回0:检测成功*/
u8 AT24CXX_Check1(void)
{
	u8 temp,return_temp;
     return_temp=0;
	AT24CXX_WriteOneByte(999,0XAC);
	temp=AT24CXX_ReadOneByte(999);/*避免每次开机都写AT24CXX*/
     if(temp!=0XAC)
     {
          //safe_parameter.Servo_Error = 1;
          //safe_parameter.Servo_Error_Code = EEPROM_ERR;
          ERROR_eeprom = 1;
          return_temp=1;
     }
	AT24CXX_WriteOneByte(999,0X53);
	temp=AT24CXX_ReadOneByte(999);/*避免每次开机都写AT24CXX	*/	
     if(temp!=0X53)
     {
          //safe_parameter.Servo_Error = 1;
          //safe_parameter.Servo_Error_Code = EEPROM_ERR;
          ERROR_eeprom = 1;
          return_temp=1;
     }
     return return_temp;
}

/*在AT24CXX里面的指定地址开始读出指定个数的数据*/
/*ReadAddr :开始读出的地址 对24c02为0~255*/
/*pBuffer  :数据数组首地址*/
/*NumToRead:要读出数据的个数*/
/*void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
} */ 
/*在AT24CXX里面的指定地址开始写入指定个数的数据*/
/*WriteAddr :开始写入的地址 对24c02为0~255*/
/*pBuffer   :数据数组首地址*/
/*NumToWrite:要写入数据的个数*/
/*
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}*/
 

/*参数写入：参数表到参数区*/
void par_to_par_region(void)
{
     u16 j,temp; 
     for(j=0;j<MEAU_NUM-1;j++)
     {
          temp=(u16)((s32)parameter_table[j]+32768);
          AT24CXX_WriteOneByte(j*2,(u8)(temp%256));
          AT24CXX_WriteOneByte(j*2+1,(u8)(temp>>8));
     }   
     parameter_table[Password] = 315;
}


/*参数备份：参数表到备份区*/
void par_to_backup_region(void)
{
     u16 j,temp; 
     AT24CXX_Check();
     for(j=0;j<MEAU_NUM-1;j++)
     {
          temp=(u16)((s32)parameter_table[j]+32768);
          AT24CXX_WriteOneByte(j*2+400,(u8)(temp%256));
          AT24CXX_WriteOneByte(j*2+1+400,(u8)(temp>>8));
     }   
     parameter_table[Password] = 315;
}

/*参数读取：参数区到参数表*/
void par_region_to_par(void)
{
     u16 j;
     for(j=0;j<MEAU_NUM-1;j++)
     {
          parameter_table[j]=(s16)((s32)( (u16)AT24CXX_ReadOneByte(j*2)+(u16)AT24CXX_ReadOneByte(j*2+1)*256 )-32768); /*先写低位 后写高位*/
     }
     parameter_table[Password] = 315;
     system_parameter_init();
}

/*恢复备份：备份区到参数表*/
void backup_region_to_par(void)
{
     u16 j;
     for(j=0;j<MEAU_NUM-1;j++)
     {
          parameter_table[j]=(s16)((s32)( (u16)AT24CXX_ReadOneByte(j*2+400)+(u16)AT24CXX_ReadOneByte(j*2+1+400)*256 )-32768); /*先写低位 后写高位*/
     }
     parameter_table[Password] = 315;   
     system_parameter_init();  
}

/*恢复缺省：值默认值到备份区参数区参数表*/
void default_to_all (void)
{ 
     u16 j;
     for(j=0;j<MEAU_NUM-1;j++)
     {
          parameter_table[j]=parameter_table_default[j];
     }
     par_to_par_region();
     par_to_backup_region();
     parameter_table[Password] = 315;
     system_parameter_init();
}
