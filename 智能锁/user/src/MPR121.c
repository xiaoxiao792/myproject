#include "stm32f10x.h"                  // Device header
#include "MPR121.h"
#include "systick.h"
#include "iic.h"

/*******************************************************************
* 函数名：      MPR_Init()
* 功能描述 ：   电容按键及设置初始化
* 参数说明：     无
* 返回值说明：   无
* 修改记录：
*******************************************************************/
void MPR_Init()
{
	 // Section A
  // This group controls filtering when data is > baseline.
  MPR_write(MPR_ADD,MHD_R, 0x01);
  MPR_write(MPR_ADD,NHD_R, 0x01);
  MPR_write(MPR_ADD,NCL_R, 0x00);
  MPR_write(MPR_ADD,FDL_R, 0x00);

  // Section B
  // This group controls filtering when data is < baseline.
  MPR_write(MPR_ADD,MHD_F, 0x01);
  MPR_write(MPR_ADD,NHD_F, 0x01);
  MPR_write(MPR_ADD,NCL_F, 0xFF);
  MPR_write(MPR_ADD,FDL_F, 0x02);
  
  // Section C
  // This group sets touch and release thresholds for each electrode
  MPR_write(MPR_ADD,ELE0_T, TOU_THRESH);
  MPR_write(MPR_ADD,ELE0_R, REL_THRESH);
  MPR_write(MPR_ADD,ELE1_T, TOU_THRESH);
  MPR_write(MPR_ADD,ELE1_R, REL_THRESH);
  MPR_write(MPR_ADD,ELE2_T, TOU_THRESH);
  MPR_write(MPR_ADD,ELE2_R, REL_THRESH);
  MPR_write(MPR_ADD,ELE3_T, TOU_THRESH);
  MPR_write(MPR_ADD,ELE3_R, REL_THRESH);
  MPR_write(MPR_ADD,ELE4_T, TOU_THRESH);
  MPR_write(MPR_ADD,ELE4_R, REL_THRESH);
  MPR_write(MPR_ADD,ELE5_T, TOU_THRESH);
  MPR_write(MPR_ADD,ELE5_R, REL_THRESH);
  MPR_write(MPR_ADD,ELE6_T, TOU_THRESH);
  MPR_write(MPR_ADD,ELE6_R, REL_THRESH);
  MPR_write(MPR_ADD,ELE7_T, TOU_THRESH);
  MPR_write(MPR_ADD,ELE7_R, REL_THRESH);
  MPR_write(MPR_ADD,ELE8_T, TOU_THRESH);
  MPR_write(MPR_ADD,ELE8_R, REL_THRESH);
  MPR_write(MPR_ADD,ELE9_T, TOU_THRESH);
  MPR_write(MPR_ADD,ELE9_R, REL_THRESH);
  MPR_write(MPR_ADD,ELE10_T, TOU_THRESH);
  MPR_write(MPR_ADD,ELE10_R, REL_THRESH);
  MPR_write(MPR_ADD,ELE11_T, TOU_THRESH);
  MPR_write(MPR_ADD,ELE11_R, REL_THRESH);
  
  // Section D
  // Set the Filter Configuration
  // Set ESI2
  MPR_write(MPR_ADD,FIL_CFG, 0x04);
  MPR_write(MPR_ADD,ELE_CFG, 0x0C);	// Enables all 12 Electrodes
}

/*******************************************************************
* 函数名：      MPR_write()
* 功能描述 ：   发送数据到MPR
* 参数说明：     无
* 返回值说明：   无
* 修改记录：
* 其他：
*******************************************************************/
void MPR_write(u8 ADD,u8 add,u8 data)
{
		IIC_Start();
		IIC_Send_Data(ADD);
		IIC_Get_ACK();
		IIC_Send_Data(add);
		IIC_Get_ACK();
		IIC_Send_Data(data);
		IIC_Get_ACK();
		IIC_Stop();
}

/*******************************************************************
* 函数名：      MPR_read()
* 功能描述 ：   从MPR读数据
* 参数说明：     无
* 返回值说明：   无
* 修改记录：
* 其他：
*******************************************************************/
u8 MPR_read(u8 ADD,u8 add)
{
	  u8 data; 
		IIC_Start();
		IIC_Send_Data(ADD);
		IIC_Get_ACK();
		IIC_Send_Data(add);
		IIC_Get_ACK();
	
		IIC_Start();
		IIC_Send_Data(ADD|0x01);
		IIC_Get_ACK();
		data=IIC_Read_Data(0);
		IIC_Stop();
		return data;
}

/*******************************************************************
* 函数名：      MPR_GetKey()
* 功能描述 ：   读取按键按下的值
* 参数说明：     无
* 返回值说明：   无
* 修改记录：
* 其他：
*******************************************************************/
u8 MPR_GetKey()
{
	u16 data=0;
	data=MPR_read(MPR_ADD,0x01)<<8;
	data|=MPR_read(MPR_ADD,0x00);

	
	if(data&0x0001)      return '1';//1
	else if(data&0x0002) return '4';//4
	else if(data&0x0004) return '7';//7
	else if(data&0x0008) return '*';//11
	else if(data&0x0010) return '5';//5
	else if(data&0x0020) return '2';//5
	else if(data&0x0040) return '8';//8
	else if(data&0x0080) return '0';//10
	else if(data&0x0100) return '#';//12
	else if(data&0x0200) return '9';//9
	else if(data&0x0400) return '6';//6
	else if(data&0x0800) return '3';//3
	return 0;
}
 
