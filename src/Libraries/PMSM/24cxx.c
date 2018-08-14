#include "24cxx.h" 

//u8 eeprom_err = 0;


/*��ʼ��IIC�ӿ�*/
void AT24CXX_Init(void)
{
     u8 i;
     IIC_Init();
     i=AT24CXX_Check();
     
     /* ������ȡ����������������*/
     if(i == 0)
     {
          par_region_to_par();
     }
     /* ����д�룺������������*/
     if(i == 1)
     {
          par_to_par_region();
     }
     if(i == 2)
     {
          ERROR_eeprom = 1;
     }        
}

/*��AT24CXXָ����ַ����һ������*/
/*ReadAddr:��ʼ�����ĵ�ַ  */
/*����ֵ  :����������*/
static u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{
     u8 temp=0;
     IIC_Start();  
     if(EE_TYPE>AT24C16)
     {
          IIC_Send_Byte(0XA0);	   /*����д����*/
          IIC_Wait_Ack();
          IIC_Send_Byte(ReadAddr>>8);/*���͸ߵ�ַ*/
          IIC_Wait_Ack();		 
     }
     else
     {
          IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   /*����������ַ0XA0,д����*/
          IIC_Wait_Ack();  	
     }
     
     IIC_Send_Byte(ReadAddr%256);   /*���͵͵�ַ*/
     IIC_Wait_Ack();	    
     IIC_Start();  	 	  
     IIC_Send_Byte(0XA1);           /*�������ģʽ	*/	 
     IIC_Wait_Ack();	 
     temp=IIC_Read_Byte(0);		  
     IIC_Stop();/*����һ��ֹͣ����	*/   
     return temp;
}




/*��AT24CXXָ����ַд��һ������*/
/*WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ  */  
/*DataToWrite:Ҫд�������*/
static void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{
     u16 i;
     IIC_Start();  
     if(EE_TYPE>AT24C16)
     {
          IIC_Send_Byte(0XA0);	    /*����д����*/
          IIC_Wait_Ack();
          IIC_Send_Byte(WriteAddr>>8);/*���͸ߵ�ַ*/
          IIC_Wait_Ack();	
     }
     else
     {
          IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   /*����������ַ0XA0,д���� */
          IIC_Wait_Ack();
     }	 
     IIC_Send_Byte(WriteAddr%256);   /*���͵͵�ַ*/
     IIC_Wait_Ack(); 	 		
     IIC_Send_Byte(DataToWrite);     /*�����ֽ�*/
     IIC_Wait_Ack();  		
     IIC_Stop();/*����һ��ֹͣ���� */
     for(i=0;i<60;i++)
     {
          delay_200us();
     }
}

/*��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������*/
/*�ú�������д��16bit����32bit������.*/
/*WriteAddr  :��ʼд��ĵ�ַ  */
/*DataToWrite:���������׵�ַ*/
/*Len        :Ҫд�����ݵĳ���2,4*/
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

/*��AT24CXX�����ָ����ַ��ʼ��������ΪLen������*/
/*�ú������ڶ���16bit����32bit������.*/
/*ReadAddr   :��ʼ�����ĵ�ַ */
/*����ֵ     :����*/
/*Len        :Ҫ�������ݵĳ���2,4*/
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
/*���AT24CXX�Ƿ�����*/
/*��������24XX�����һ����ַ(255)���洢��־��.*/
/*���������24Cϵ��,�����ַҪ�޸�*/
/*����1:���ʧ��*/
/*����0:���ɹ�*/
static u8 AT24CXX_Check(void)
{
	u8 temp,return_temp;
     if( AT24CXX_Check1() == 0 )
     {
          temp=AT24CXX_ReadOneByte(1000);/*����ÿ�ο�����дAT24CXX	*/
          if(temp==0X33)
          {
               return_temp=0;
          }        
          else/*�ų���һ�γ�ʼ�������*/
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

/*���AT24CXX�Ƿ�����*/
/*��������24XX�����һ����ַ(255)���洢��־��.*/
/*���������24Cϵ��,�����ַҪ�޸�*/
/*����1:���ʧ��*/
/*����0:���ɹ�*/
u8 AT24CXX_Check1(void)
{
	u8 temp,return_temp;
     return_temp=0;
	AT24CXX_WriteOneByte(999,0XAC);
	temp=AT24CXX_ReadOneByte(999);/*����ÿ�ο�����дAT24CXX*/
     if(temp!=0XAC)
     {
          //safe_parameter.Servo_Error = 1;
          //safe_parameter.Servo_Error_Code = EEPROM_ERR;
          ERROR_eeprom = 1;
          return_temp=1;
     }
	AT24CXX_WriteOneByte(999,0X53);
	temp=AT24CXX_ReadOneByte(999);/*����ÿ�ο�����дAT24CXX	*/	
     if(temp!=0X53)
     {
          //safe_parameter.Servo_Error = 1;
          //safe_parameter.Servo_Error_Code = EEPROM_ERR;
          ERROR_eeprom = 1;
          return_temp=1;
     }
     return return_temp;
}

/*��AT24CXX�����ָ����ַ��ʼ����ָ������������*/
/*ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255*/
/*pBuffer  :���������׵�ַ*/
/*NumToRead:Ҫ�������ݵĸ���*/
/*void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
} */ 
/*��AT24CXX�����ָ����ַ��ʼд��ָ������������*/
/*WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255*/
/*pBuffer   :���������׵�ַ*/
/*NumToWrite:Ҫд�����ݵĸ���*/
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
 

/*����д�룺������������*/
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


/*�������ݣ�������������*/
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

/*������ȡ����������������*/
void par_region_to_par(void)
{
     u16 j;
     for(j=0;j<MEAU_NUM-1;j++)
     {
          parameter_table[j]=(s16)((s32)( (u16)AT24CXX_ReadOneByte(j*2)+(u16)AT24CXX_ReadOneByte(j*2+1)*256 )-32768); /*��д��λ ��д��λ*/
     }
     parameter_table[Password] = 315;
     system_parameter_init();
}

/*�ָ����ݣ���������������*/
void backup_region_to_par(void)
{
     u16 j;
     for(j=0;j<MEAU_NUM-1;j++)
     {
          parameter_table[j]=(s16)((s32)( (u16)AT24CXX_ReadOneByte(j*2+400)+(u16)AT24CXX_ReadOneByte(j*2+1+400)*256 )-32768); /*��д��λ ��д��λ*/
     }
     parameter_table[Password] = 315;   
     system_parameter_init();  
}

/*�ָ�ȱʡ��ֵĬ��ֵ��������������������*/
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
