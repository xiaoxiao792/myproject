#include "lcd.h"
#include "font.h"
#include <string.h>
#include "YM_Image.h"
#include "w25q64.h"


void LCD_Draw_Cross(u16 Xpos, u16 Ypos, u16 Color)
{
	LCD_Daw_Line(Xpos-8,Ypos ,Xpos+8,Ypos,Color);	
	LCD_Daw_Line(Xpos,Ypos-8 ,Xpos,Ypos+8,Color);	
}

/****************** 画点函数 ******************
Xpos：X坐标
Ypos：Y坐标
Color：像素点颜色
***********************************************/
void LCD_Draw_Point(u16 Xpos, u16 Ypos, u16 Color)
{
	/* 设置清屏坐标 */
	LCD_ILI9486_CMD(0x2A);                        //发送命令，设置X轴坐标
	LCD_ILI9486_Parameter((Xpos & 0xff00) >> 8);    //发送起始坐标的高8位
	LCD_ILI9486_Parameter((Xpos & 0x00ff));         //发送起始坐标的低8位
	LCD_ILI9486_Parameter((Xpos & 0xff00) >> 8);    //发送结束坐标的高8位
	LCD_ILI9486_Parameter((Xpos & 0x00ff));         //发送结束坐标的低8位
	
	LCD_ILI9486_CMD(0x2B);                        //发送命令，设置Y轴坐标
	LCD_ILI9486_Parameter((Ypos & 0xff00) >> 8);    //发送起始坐标的高8位
	LCD_ILI9486_Parameter((Ypos & 0x00ff));         //发送起始坐标的低8位
	LCD_ILI9486_Parameter((Ypos & 0xff00) >> 8);    //发送结束坐标的高8位
	LCD_ILI9486_Parameter((Ypos & 0x00ff));         //发送结束坐标的低8位
	
	LCD_ILI9486_CMD(0x2C);                        //发送命令，设置颜色
	LCD_ILI9486_Parameter(Color);                 //输入像素点颜色
}



/************************ LCD显示8X16字符 ***********************************
Xpos：X坐标
Ypos：Y坐标
str： 需要显示的内容
Pcolor：字体颜色
Bcolor：背景颜色
****************************************************************************/
void LCD_Dis_8x16Ascill(u16 Xpos, u16 Ypos, char str, u16 Pcolor, u16 Bcolor)
{
	u8 buff[16];    //存放需要显示的字符字模
	u8 x,y;
	str = str - 32;    //得到Ascill码值的偏移量
	memcpy((char *)buff,&ascill[str * 16],16);    //把需要显示的字模数据提取到显示数组 
	for(y = 0; y < 16; y++)   //循环写入字符的元素
	{
		for(x = 0; x < 8; x++)
		{
			if(buff[y] & (0x80 >> x))  //
			{ 
				LCD_Draw_Point(Xpos + x, Ypos + y, Pcolor);   //显示字体颜色
			}
			else
			{
				LCD_Draw_Point(Xpos + x, Ypos + y, Bcolor);  //显示背景颜色
			}
		}
	}
}

/************************ LCD显示16X32字符 ***********************************
Xpos：X坐标
Ypos：Y坐标
str： 需要显示的内容
Pcolor：字体颜色
Bcolor：背景颜色
****************************************************************************/
void LCD_Dis_16x32Ascill(u16 Xpos, u16 Ypos, char str, u16 Pcolor, u16 Bcolor)
{
	u8 buff[64];    //存放需要显示的字符字模
	u8 j=0;
	u16 i=0;
	str = str - 32;    //得到Ascill码值的偏移量
	memcpy((char *)buff,&ascill16x32[str * 64],64);    //把需要显示的字模数据提取到显示数组 
		/*****************************************************/
	LCD_ILI9486_CMD(0x2A);           //设置列地址的起始地址
	LCD_ILI9486_Parameter(Xpos>>8);      
	LCD_ILI9486_Parameter(Xpos&(0xFF));
	//设置列地址的结束地址
	LCD_ILI9486_Parameter((Xpos+16-1)>>8);      
	LCD_ILI9486_Parameter((Xpos+16-1)&(0xFF));

	/*****************************************************/
	LCD_ILI9486_CMD(0x2B);          //设置行地址的起始地址
	LCD_ILI9486_Parameter(Ypos>>8);      
	LCD_ILI9486_Parameter(Ypos&(0xFF));
  //设置行地址的结束地址
	LCD_ILI9486_Parameter((Ypos+32-1)>>8);      
	LCD_ILI9486_Parameter((Ypos+32-1)&(0xFF));
	
	LCD_ILI9486_CMD(0x2C);         //写显存的命令
	for(i=0;i<(16*32);i++)         //循环判断每个像素点应该传入的颜色值：背景色或者字体颜色
															   //通过取模数据的每个位判断需要传入什么数据
	{
		if( (buff[i/8]) & (0x80>>j) )  // i/8表示像素点编号对应的数组数据的下标，前0~7个像素点对应buff[0]
		{                              // 其他以此类推
			LCD_ILI9486_Parameter(Pcolor); 
		}
		else
		{
			LCD_ILI9486_Parameter(Bcolor); 
		}
		j++;
		if(j == 8)             //已经使用完一个字节的取模数据，需要切换到下一个字节
		{
			j = 0;
		}
	}
}


/************************ LCD显示字符串 ***********************************
Xpos：X坐标
Ypos：Y坐标
*str： 需要显示的内容
Pcolor：字体颜色
Bcolor：背景颜色
****************************************************************************/
void LCD_String(u16 Xpos, u16 Ypos, u8* str, u16 Pcolor, u16 Bcolor,u8 font_size)
{
	u8  i=0;
	u8  buff[128];
	u32 addr=0;
	while(*str !='\0')
	{
		if( *str < 128 )
		{
			if( font_size ==16)
				LCD_Dis_8x16Ascill(Xpos,Ypos,*str, Pcolor, Bcolor);
			else
				LCD_Dis_16x32Ascill(Xpos,Ypos,*str, Pcolor, Bcolor);
			str  +=1; 
			Xpos +=font_size/2;
			if(Xpos>(319-(font_size/2)))
			{
				Xpos=0;
				Ypos+=font_size; //换行	
			} 
		}
		else
		{
			if( font_size ==16 )
				addr = ( ( *str-0xA1)*94+ (*(str+1)-0xA1) )*32;
			else 
				addr = ( ( *str-0xA1)*94+ (*(str+1)-0xA1) )*128 + 0x3FE42;
			
			w25q64_read(addr,buff,font_size*font_size/8);
			LCD_ShowChinese(Xpos,Ypos,font_size,Pcolor, Bcolor,buff);
			str +=2; 
			Xpos+=font_size;
			if(Xpos>(319-font_size))
			{
				Xpos=0;
				Ypos+=font_size; //换行	
			} 
		}
	}
}

/************************* 显示指定大小图片 **********************************
Xpos：X坐标
Ypos：Y坐标
Pic_x：图片的x轴大小
Pic_y：图片的y轴大小
*p：需要显示的图片
******************************************************************************/
void Show_Picture(u32 Xpos, u32 Ypos, u32 Pic_x, u32 Pic_y, const unsigned char *p)
{
		u32 i;
	/*****************************************************/
	LCD_ILI9486_CMD(0x2A);           //设置列地址的起始地址
	LCD_ILI9486_Parameter(Xpos>>8);      
	LCD_ILI9486_Parameter(Xpos&(0xFF));
	//设置列地址的结束地址
	LCD_ILI9486_Parameter((Xpos+Pic_x-1)>>8);      
	LCD_ILI9486_Parameter((Xpos+Pic_x-1)&(0xFF));

	/*****************************************************/
	LCD_ILI9486_CMD(0x2B);          //设置行地址的起始地址
	LCD_ILI9486_Parameter(Ypos>>8);      
	LCD_ILI9486_Parameter(Ypos&(0xFF));
  //设置行地址的结束地址
	LCD_ILI9486_Parameter((Ypos+Pic_y-1)>>8);      
	LCD_ILI9486_Parameter((Ypos+Pic_y-1)&(0xFF));
	
	LCD_ILI9486_CMD(0x2C);         //写显存的命令
	for(i=0;i<( Pic_x*Pic_y);i++) 
	{
		LCD_ILI9486_Parameter( ( *p<<8 ) | ( *(p+1) ) );  
		p	+=2;	
	}
}

/****************** 画线函数 ******************
Xpos：X坐标
Ypos：Y坐标
Color：像素点颜色
***********************************************/

void LCD_Daw_Line(int x1, int y1, int x2, int y2,u16 bkColor)
{
int x,y,dx,dy,Dx,Dy,e,i;
  Dx=x2-x1;
  Dy=y2-y1;
      if(Dx < 0)
        dx=(x1-x2);
      else dx=(x2-x1);    
      if(Dy < 0)
        dy=(y1-y2);  
      else dy=(y2-y1);

  x=x1;
  y=y1;
  if(dy>dx)
  {
    e=-dy;
   for(i=0;i<dy;i++)
    {
   LCD_Draw_Point(x,y,bkColor);
     if(Dy>=0)y++;  
     else y--;   
     e+=2*dx;
     if(e>=0)
     {
       if(Dx>=0) x++;
       else x--; 
       e-=2*dy;
     }
    }
  }
  else
  {
    e=-dx;
   for(i=0;i<dx;i++)
    {
     LCD_Draw_Point(x,y,bkColor);
     if(Dx>=0) x++;
     else x--;
     e+=2*dy;
     if(e>=0)
     { 
       if(Dy>=0) y++;
       else y--;
       e-=2*dx;
     }
    }
  }
}


//x、y字符的一个字符的左上角的坐标
/***
pointColor: 要显示的字符的颜色
backColor： 字符的背景颜色
*pChineseData ：字符取模数据
***/
//fontSize : 字体大小：16表示 16*16的字体，32表示32*32的字体，64表示64*64的字体，
void LCD_ShowChinese(u16 x,u16 y,u8 fontSize,u16 pointColor,u16 backColor,u8 *pChineseData)
{
	u32 i;
	u8 j =0;
	/*****************************************************/
	LCD_ILI9486_CMD(0x2A);           //设置列地址的起始地址
	LCD_ILI9486_Parameter(x>>8);      
	LCD_ILI9486_Parameter(x&(0xFF));
	//设置列地址的结束地址
	LCD_ILI9486_Parameter((x+fontSize-1)>>8);      
	LCD_ILI9486_Parameter((x+fontSize-1)&(0xFF));

	/*****************************************************/
	LCD_ILI9486_CMD(0x2B);          //设置行地址的起始地址
	LCD_ILI9486_Parameter(y>>8);      
	LCD_ILI9486_Parameter(y&(0xFF));
  //设置行地址的结束地址
	LCD_ILI9486_Parameter((y+fontSize-1)>>8);      
	LCD_ILI9486_Parameter((y+fontSize-1)&(0xFF));
	
	LCD_ILI9486_CMD(0x2C);         //写显存的命令
	for(i=0;i<(fontSize*fontSize);i++)
	{
		
		if((*pChineseData)&(1<<(7-j)))
		{
			LCD_ILI9486_Parameter(pointColor); 
		}
		else
		{
			LCD_ILI9486_Parameter(backColor); 
		}
		j = j + 1;
		if(j == 8)
		{
			j = 0;
			pChineseData++;
		}
	}
}


//x、y字符的一个字符的左上角的坐标
/***
pointColor: 要显示的字符的颜色
backColor： 字符的背景颜色
*pChineseData ：字符取模数据
***/
//fontSize : 字体大小：16表示 16*16的字体，32表示32*32的字体，64表示64*64的字体，
void LCD_ShowChinese_fill(u16 x,u16 y,u8 fontSize,u16 pointColor,u16 backColor,u8 *pChineseData)
{
	u32 i;  
	u8 j =0;
	u8 k =0;     //计算当前字节处于该行的位置(第几个字节)
	u8 d =0;     //计算当前字节处于第几列

	for(i=0;i<(fontSize*fontSize);i++)
	{
		if((*pChineseData)&(1<<(7-j)))
		{
			LCD_Draw_Point(x+j+k*8, y+d, pointColor);
		}
		else
		{
			LCD_Draw_Point(x+j+k*8, y+d, backColor);
		}
		j = j + 1;
		if(j == 8)
		{	
			j = 0;
			pChineseData++;
			k++;		       //计算当前字节处于该行的位置
      if(k>=(fontSize/8))		
			{
				k=0;	       //计算当前字节处于该行的位置
				d++;         //计算当前字节处于第几列的位置
			}
		}
	}
}
