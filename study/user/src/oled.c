#include "stm32f10x.h"                  // Device header
 #include "oled.h"
 #include "spi.h"
 #include "systick.h"
 #include "font.h"
/***************************************************
*函数名    :OLED_IO_init
*函数功能  :OLED所用管脚初始化配置
*函数参数  :无
*函数返回值:无
*函数描述  :CS-----PA15
            DC-----PA11
            RES----PA12
*****************************************************/
void OLED_IO_Init(void)
{
	RCC->APB2ENR |=1<<2;  //使能A时钟
 
 
	/*CS-----PA15*/ //推挽输出 50MHZ
  GPIOA->CRH &=~(0XF <<((15-8)*4));
	GPIOA->CRH |=0X3 <<((15-8)*4);
	GPIOA->ODR |=(1 <<15);    //片选拉高不选择OLED
	
	/*DC-----PA11*/ //推挽输出 50MHZ
  GPIOA->CRH &=~(0XFul<<((11-8)*4));
	GPIOA->CRH |=0X3ul<<((11-8)*4);
	GPIOA->ODR |=1<<11;  
	
	/*RES-----PA12*/ //推挽输出 50MHZ
  GPIOA->CRH &=~(0XF<<((12-8)*4));
	GPIOA->CRH |=0X3<<((12-8)*4);
	GPIOA->ODR |=1<<12;  
}



/*********************************************
*函数名    ：OLED_Reset
*函数功能  ：OLED硬件复位时序 
*函数参数  ：无
*函数返回值：无
*函数描述  ：
							复位管脚拉低
							延时100ms
							复位管脚拉高
							延时100ms
							复位管脚拉低					
*********************************************/
void OLED_Reset(void)
{
	OLED_RST_L;
	Delay_ms(100);
	OLED_RST_H;
	Delay_ms(100);
}


/*********************************************
*函数名    ：OLED_writeByte
*函数功能  ：OLED时序写数据/命令
*函数参数  ：u8 data   u8 oled_cmd_data
*函数返回值：无
*函数描述  ：
							确定发命令还是数据(命令参数)
							片选拉低
							用SPI发送命令数/命令参数
							片选拉高	

							提示：oled_cmd_data
              1   ：把命令/数据线拉高    发送的是数据
              0   ：把命令/数据线拉低    发送的是命令			
*********************************************/
void OLED_writeByte(u8 data, u8 oled_cmd_data)
{
	//确定发命令还是数据(命令参数)
	oled_cmd_data ? (OLED_CD_H) : (OLED_CD_L);
	//片选拉低
	OLED_CS_L;
	//用SPI发送命令数/命令参数
	SPI_Read_Write_Byte(data);
	//片选拉高
	OLED_CS_H;
}
	


/*********************************************
*函数名    ：OLED_Init
*函数功能  ：实现对OLED屏幕初始化配置
*函数参数  ：无
*函数返回值：无
*函数描述  ：
							①管脚初始化      //片选  res   D/C
								SPI1初始化
							②OLED硬复位
							③厂家驱动IC代码  //OLED的通信时序（包括SPI）
							④清屏clear
*********************************************/
void OLED_Init(void)
{
	//管脚初始化 
	OLED_IO_Init();
	//spi1初始化
	SPI_2_Init();
	//OLED硬复位
	OLED_Reset();
	
	//厂家驱动IC代码
	OLED_writeByte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_writeByte(0x02,OLED_CMD);//---SET low column address
	OLED_writeByte(0x10,OLED_CMD);//---SET high column address
	OLED_writeByte(0x40,OLED_CMD);//--SET start line address  SET Mapping RAM Display Start Line (0x00~0x3F)
	OLED_writeByte(0x81,OLED_CMD);//--SET contrast control register
	OLED_writeByte(0xCF,OLED_CMD); // SET SEG Output Current Brightness
	OLED_writeByte(0xA1,OLED_CMD);//--SET SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_writeByte(0xC8,OLED_CMD);//SET COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_writeByte(0xA6,OLED_CMD);//--SET normal display
	OLED_writeByte(0xA8,OLED_CMD);//--SET multiplex ratio(1 to 64)
	OLED_writeByte(0x3f,OLED_CMD);//--1/64 duty
	OLED_writeByte(0xD3,OLED_CMD);//-SET display offSET	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_writeByte(0x00,OLED_CMD);//-not offSET
	OLED_writeByte(0xd5,OLED_CMD);//--SET display clock divide ratio/oscillator frequency
	OLED_writeByte(0x80,OLED_CMD);//--SET divide ratio, SET Clock as 100 Frames/Sec
	OLED_writeByte(0xD9,OLED_CMD);//--SET pre-charge period
	OLED_writeByte(0xF1,OLED_CMD);//SET Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_writeByte(0xDA,OLED_CMD);//--SET com pins hardware configuration
	OLED_writeByte(0x12,OLED_CMD);
	OLED_writeByte(0xDB,OLED_CMD);//--SET vcomh
	OLED_writeByte(0x40,OLED_CMD);//SET VCOM Deselect Level
	OLED_writeByte(0x20,OLED_CMD);//-SET Page Addressing Mode (0x00/0x01/0x02)
	OLED_writeByte(0x02,OLED_CMD);//
	OLED_writeByte(0x8D,OLED_CMD);//--SET Charge Pump enable/disable
	OLED_writeByte(0x14,OLED_CMD);//--SET(0x10) disable
	OLED_writeByte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_writeByte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_writeByte(0xAF,OLED_CMD);//--turn on oled panel
	OLED_writeByte(0xAF,OLED_CMD); /*display ON*/ 

	//清屏函数
	OLED_clear();

}



/*********************************************
*函数名    ：OLED_clear
*函数功能  ：将整个屏幕清成某个颜色
*函数参数  ：无
*函数返回值：无
*函数描述  ：
							8次页循环
								每次页循环是132次列循环
*********************************************/
void OLED_clear(void)
{
	u8 i,n;
	//页循环
	for(i=0;i<8;i++)
	{
		//设置页地址
		OLED_writeByte(0xb0+i,OLED_CMD);
		//设置每页的列起始地址
		OLED_writeByte(0x00,OLED_CMD);     //地址编号低四位
		OLED_writeByte(0x10,OLED_CMD);     //地址编号高四位
		//每页要传送的数据
		for(n=0;n<132;n++)               
		{
			OLED_writeByte(0x00,OLED_DAT);   //某一列的数据
		}
	}
}




 








/*********************************************
*函数名    ：OLED_setstart
*函数功能  ：确定显示起始位置函数   哪页的哪列
*函数参数  ：u8 page  页号         u8 lis   列号
*函数返回值：无
*函数描述  ：
							通过此函数能确定要显示的起始位置
							发送数据，发送几次就会显示几列（纵向刷屏）
*********************************************/
void OLED_setstart(u8 page, u8 lis) 
{
	OLED_writeByte(0xb0+page,OLED_CMD);              //确定页号
	OLED_writeByte(((lis&0xf0)>>4)|0x10, OLED_CMD);  //列号
	OLED_writeByte((lis&0x0f),OLED_CMD);             //列号      
} 






/*********************************************
*函数名    ：oled_Dis_ch16
*函数功能  ：显示一个16*16的字符
*函数参数  ：u8 page  页号         u8 lis   列号    u8 ch   要显示的字符
*函数返回值：无
*函数描述  ：
							//起始位置函数  
							//发送数据                        
							-----------------------------------------字的上半部分
							//再次确定起始位置    页数+1            
							//循环发送数据（数组的后边8个元素）       
							-----------------------------------------字的下半部分
*********************************************/
void oled_Dis_ch16(u8 page ,u8 lis,u8 ch)
{
	u8 i,p;
	u8 n;
	//找到要显示的字符在ASCII码中的排名（相对空格）
	n = ch - ' ';     //
	//显示字
	for(p=0;p<16/8;p++)          //页编号循环次数
	{
		OLED_setstart(page+p,lis); //确定位置
		for(i=0;i<8;i++)
		{
			OLED_writeByte(F16X16[16*n+i+p*8],OLED_DAT);    //传对应页的数据(上半个字和下半个字)
		}
	}
	
}


 



/*********************************************
*函数名    ：oled_Dis_str16
*函数功能  ：显示一个16*16的字符串
*函数参数  ：u8 page  页号         u8 lis   列号    u8 *str   要显示的字符传首地址
*函数返回值：无
*函数描述  ：
							
*********************************************/
void oled_Dis_str16(u8 page ,u8 lis,u8 *str)
{
	while(*str != '\0')
	{
		oled_Dis_ch16(page,lis,*str);
		str++;
		lis += 8;
	}
}







/*********************************************
*函数名    ：oled_Dis_hz16
*函数功能  ：显示一个16*16的汉字
*函数参数  ：u8 page  页号         u8 lis   列号    u8 *str   要显示的汉字首地址
*函数返回值：无
*函数描述  ：					
*********************************************/
void oled_Dis_hz16(u8 page ,u8 lis,u8 *str)
{
	u16 n = 0;
	u8 p,i;
	//查找要显示的汉字的位置（与第一个汉字的偏移）
	while(1)
	{
		if((*str == hztable[n*2]) && (*(str+1) == hztable[n*2+1]))
		{
			break;
		}
		n+=1;     //对比下一个汉字
	} 
	
	//n 汉字编号
	
	//显示
	for(p=0;p<16/8;p++)
	{
		//确定位置
		OLED_setstart(page+p,lis); 
		for(i=0;i<16;i++)
		{
			OLED_writeByte(hz16[32*n+i+p*16],OLED_DAT);
		}
	}
}








/*********************************************
*函数名    ：oled_Dis_hzstr16
*函数功能  ：显示一个16*16的字符串
*函数参数  ：u8 page  页号         u8 lis   列号    u8 *str   要显示的字符传首地址
*函数返回值：无
*函数描述  ：
							
*********************************************/
void oled_Dis_hzstr16(u8 page ,u8 lis,u8 *str)
{
	while(*str != '\0')
	{
		oled_Dis_hz16(page,lis,str);
		str+=2;
		lis += 16;
	}
}











/*******************************************************************************
*函数名    ：oled_Dis_pic
*函数功能  ：显示一个任意大小的图片
*函数参数  ：u8 page  u8 lis       u8 *pic                   u8 w     u8 h
             页号     列号         要显示的图片模的首地址     图片宽    图片高
*函数返回值：无
*函数描述  ：					
**********************************************************************************************/
void oled_Dis_pic(u8 page,u8 lis,u8 *pic,u8 w,u8 h)
{
	u8 p,i;
	u8 c;
	if(h % 8 == 0)
	{
		c = h / 8;
	}
	else
	{
		c = h / 8+1;
	}
	
	
	for(p=0;p<c;p++)
	{
		//确定位置
		OLED_setstart(page+p,lis);
		for(i=0;i<w;i++)
		{
			OLED_writeByte(pic[w*p+i],OLED_DAT);
		}
	}
}