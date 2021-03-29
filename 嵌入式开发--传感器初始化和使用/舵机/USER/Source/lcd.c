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

/****************** ���㺯�� ******************
Xpos��X����
Ypos��Y����
Color�����ص���ɫ
***********************************************/
void LCD_Draw_Point(u16 Xpos, u16 Ypos, u16 Color)
{
	/* ������������ */
	LCD_ILI9486_CMD(0x2A);                        //�����������X������
	LCD_ILI9486_Parameter((Xpos & 0xff00) >> 8);    //������ʼ����ĸ�8λ
	LCD_ILI9486_Parameter((Xpos & 0x00ff));         //������ʼ����ĵ�8λ
	LCD_ILI9486_Parameter((Xpos & 0xff00) >> 8);    //���ͽ�������ĸ�8λ
	LCD_ILI9486_Parameter((Xpos & 0x00ff));         //���ͽ�������ĵ�8λ
	
	LCD_ILI9486_CMD(0x2B);                        //�����������Y������
	LCD_ILI9486_Parameter((Ypos & 0xff00) >> 8);    //������ʼ����ĸ�8λ
	LCD_ILI9486_Parameter((Ypos & 0x00ff));         //������ʼ����ĵ�8λ
	LCD_ILI9486_Parameter((Ypos & 0xff00) >> 8);    //���ͽ�������ĸ�8λ
	LCD_ILI9486_Parameter((Ypos & 0x00ff));         //���ͽ�������ĵ�8λ
	
	LCD_ILI9486_CMD(0x2C);                        //�������������ɫ
	LCD_ILI9486_Parameter(Color);                 //�������ص���ɫ
}



/************************ LCD��ʾ8X16�ַ� ***********************************
Xpos��X����
Ypos��Y����
str�� ��Ҫ��ʾ������
Pcolor��������ɫ
Bcolor��������ɫ
****************************************************************************/
void LCD_Dis_8x16Ascill(u16 Xpos, u16 Ypos, char str, u16 Pcolor, u16 Bcolor)
{
	u8 buff[16];    //�����Ҫ��ʾ���ַ���ģ
	u8 x,y;
	str = str - 32;    //�õ�Ascill��ֵ��ƫ����
	memcpy((char *)buff,&ascill[str * 16],16);    //����Ҫ��ʾ����ģ������ȡ����ʾ���� 
	for(y = 0; y < 16; y++)   //ѭ��д���ַ���Ԫ��
	{
		for(x = 0; x < 8; x++)
		{
			if(buff[y] & (0x80 >> x))  //
			{ 
				LCD_Draw_Point(Xpos + x, Ypos + y, Pcolor);   //��ʾ������ɫ
			}
			else
			{
				LCD_Draw_Point(Xpos + x, Ypos + y, Bcolor);  //��ʾ������ɫ
			}
		}
	}
}

/************************ LCD��ʾ16X32�ַ� ***********************************
Xpos��X����
Ypos��Y����
str�� ��Ҫ��ʾ������
Pcolor��������ɫ
Bcolor��������ɫ
****************************************************************************/
void LCD_Dis_16x32Ascill(u16 Xpos, u16 Ypos, char str, u16 Pcolor, u16 Bcolor)
{
	u8 buff[64];    //�����Ҫ��ʾ���ַ���ģ
	u8 j=0;
	u16 i=0;
	str = str - 32;    //�õ�Ascill��ֵ��ƫ����
	memcpy((char *)buff,&ascill16x32[str * 64],64);    //����Ҫ��ʾ����ģ������ȡ����ʾ���� 
		/*****************************************************/
	LCD_ILI9486_CMD(0x2A);           //�����е�ַ����ʼ��ַ
	LCD_ILI9486_Parameter(Xpos>>8);      
	LCD_ILI9486_Parameter(Xpos&(0xFF));
	//�����е�ַ�Ľ�����ַ
	LCD_ILI9486_Parameter((Xpos+16-1)>>8);      
	LCD_ILI9486_Parameter((Xpos+16-1)&(0xFF));

	/*****************************************************/
	LCD_ILI9486_CMD(0x2B);          //�����е�ַ����ʼ��ַ
	LCD_ILI9486_Parameter(Ypos>>8);      
	LCD_ILI9486_Parameter(Ypos&(0xFF));
  //�����е�ַ�Ľ�����ַ
	LCD_ILI9486_Parameter((Ypos+32-1)>>8);      
	LCD_ILI9486_Parameter((Ypos+32-1)&(0xFF));
	
	LCD_ILI9486_CMD(0x2C);         //д�Դ������
	for(i=0;i<(16*32);i++)         //ѭ���ж�ÿ�����ص�Ӧ�ô������ɫֵ������ɫ����������ɫ
															   //ͨ��ȡģ���ݵ�ÿ��λ�ж���Ҫ����ʲô����
	{
		if( (buff[i/8]) & (0x80>>j) )  // i/8��ʾ���ص��Ŷ�Ӧ���������ݵ��±꣬ǰ0~7�����ص��Ӧbuff[0]
		{                              // �����Դ�����
			LCD_ILI9486_Parameter(Pcolor); 
		}
		else
		{
			LCD_ILI9486_Parameter(Bcolor); 
		}
		j++;
		if(j == 8)             //�Ѿ�ʹ����һ���ֽڵ�ȡģ���ݣ���Ҫ�л�����һ���ֽ�
		{
			j = 0;
		}
	}
}


/************************ LCD��ʾ�ַ��� ***********************************
Xpos��X����
Ypos��Y����
*str�� ��Ҫ��ʾ������
Pcolor��������ɫ
Bcolor��������ɫ
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
				Ypos+=font_size; //����	
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
				Ypos+=font_size; //����	
			} 
		}
	}
}

/************************* ��ʾָ����СͼƬ **********************************
Xpos��X����
Ypos��Y����
Pic_x��ͼƬ��x���С
Pic_y��ͼƬ��y���С
*p����Ҫ��ʾ��ͼƬ
******************************************************************************/
void Show_Picture(u32 Xpos, u32 Ypos, u32 Pic_x, u32 Pic_y, const unsigned char *p)
{
		u32 i;
	/*****************************************************/
	LCD_ILI9486_CMD(0x2A);           //�����е�ַ����ʼ��ַ
	LCD_ILI9486_Parameter(Xpos>>8);      
	LCD_ILI9486_Parameter(Xpos&(0xFF));
	//�����е�ַ�Ľ�����ַ
	LCD_ILI9486_Parameter((Xpos+Pic_x-1)>>8);      
	LCD_ILI9486_Parameter((Xpos+Pic_x-1)&(0xFF));

	/*****************************************************/
	LCD_ILI9486_CMD(0x2B);          //�����е�ַ����ʼ��ַ
	LCD_ILI9486_Parameter(Ypos>>8);      
	LCD_ILI9486_Parameter(Ypos&(0xFF));
  //�����е�ַ�Ľ�����ַ
	LCD_ILI9486_Parameter((Ypos+Pic_y-1)>>8);      
	LCD_ILI9486_Parameter((Ypos+Pic_y-1)&(0xFF));
	
	LCD_ILI9486_CMD(0x2C);         //д�Դ������
	for(i=0;i<( Pic_x*Pic_y);i++) 
	{
		LCD_ILI9486_Parameter( ( *p<<8 ) | ( *(p+1) ) );  
		p	+=2;	
	}
}

/****************** ���ߺ��� ******************
Xpos��X����
Ypos��Y����
Color�����ص���ɫ
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


//x��y�ַ���һ���ַ������Ͻǵ�����
/***
pointColor: Ҫ��ʾ���ַ�����ɫ
backColor�� �ַ��ı�����ɫ
*pChineseData ���ַ�ȡģ����
***/
//fontSize : �����С��16��ʾ 16*16�����壬32��ʾ32*32�����壬64��ʾ64*64�����壬
void LCD_ShowChinese(u16 x,u16 y,u8 fontSize,u16 pointColor,u16 backColor,u8 *pChineseData)
{
	u32 i;
	u8 j =0;
	/*****************************************************/
	LCD_ILI9486_CMD(0x2A);           //�����е�ַ����ʼ��ַ
	LCD_ILI9486_Parameter(x>>8);      
	LCD_ILI9486_Parameter(x&(0xFF));
	//�����е�ַ�Ľ�����ַ
	LCD_ILI9486_Parameter((x+fontSize-1)>>8);      
	LCD_ILI9486_Parameter((x+fontSize-1)&(0xFF));

	/*****************************************************/
	LCD_ILI9486_CMD(0x2B);          //�����е�ַ����ʼ��ַ
	LCD_ILI9486_Parameter(y>>8);      
	LCD_ILI9486_Parameter(y&(0xFF));
  //�����е�ַ�Ľ�����ַ
	LCD_ILI9486_Parameter((y+fontSize-1)>>8);      
	LCD_ILI9486_Parameter((y+fontSize-1)&(0xFF));
	
	LCD_ILI9486_CMD(0x2C);         //д�Դ������
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


//x��y�ַ���һ���ַ������Ͻǵ�����
/***
pointColor: Ҫ��ʾ���ַ�����ɫ
backColor�� �ַ��ı�����ɫ
*pChineseData ���ַ�ȡģ����
***/
//fontSize : �����С��16��ʾ 16*16�����壬32��ʾ32*32�����壬64��ʾ64*64�����壬
void LCD_ShowChinese_fill(u16 x,u16 y,u8 fontSize,u16 pointColor,u16 backColor,u8 *pChineseData)
{
	u32 i;  
	u8 j =0;
	u8 k =0;     //���㵱ǰ�ֽڴ��ڸ��е�λ��(�ڼ����ֽ�)
	u8 d =0;     //���㵱ǰ�ֽڴ��ڵڼ���

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
			k++;		       //���㵱ǰ�ֽڴ��ڸ��е�λ��
      if(k>=(fontSize/8))		
			{
				k=0;	       //���㵱ǰ�ֽڴ��ڸ��е�λ��
				d++;         //���㵱ǰ�ֽڴ��ڵڼ��е�λ��
			}
		}
	}
}
