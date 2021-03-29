#ifndef __LCD_H__
#define __LCD_H__
#include <stm32f4xx.h>
#include "ILI9486.h"

#define					WHITE         	 0xFFFF
#define					BLACK         	 0x0000	  
#define					BLUE         	 0x001F  
#define					BRED            0XF81F
#define					GRED 	         0XFFE0
#define					GBLUE		     0X07FF
#define					RED           	 0xF800
#define					MAGENTA       0xF81F
#define					GREEN         	 0x07E0
#define					CYAN          	 0x7FFF
#define					YELLOW         0xFFE0
#define					BROWN 		 0XBC40 //×ØÉ«
#define					BRRED 		     0XFC07 //×ØºìÉ«
#define					GRAY  		     0X8430 //»ÒÉ«


void LCD_Draw_Cross(u16 Xpos, u16 Ypos, u16 Color);
void LCD_Draw_Point(u16 Xpos, u16 Ypos, u16 Color);
void LCD_Dis_8x16Ascill(u16 Xpos, u16 Ypos, char str, u16 Pcolor, u16 Bcolor);
void Show_Picture(u32 Xpos, u32 Ypos, u32 Pic_x, u32 Pic_y, const unsigned char *p);
void LCD_Daw_Line(int x1, int y1, int x2, int y2,u16 bkColor);
void LCD_ShowChinese(u16 x,u16 y,u8 fontSize,u16 pointColor,u16 backColor,u8 *pChineseData);
void LCD_String(u16 Xpos, u16 Ypos, u8* str, u16 Pcolor, u16 Bcolor,u8 font_size);

#endif
