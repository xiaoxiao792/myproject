#ifndef __ILI9486_H__
#define __ILI9486_H__

#include <stm32f4xx.h>
#include "systick.h"

void LCD_ILI9486_CMD(u16 common);
void LCD_ILI9486_Parameter(u16 data);
void LCD_Clear(u16 SX, u16 EX, u16 SY, u16 EY, u16 Color);
void LCD_Init(void);
void LCD_Rectang(u16 SX, u16 EX, u16 SY, u16 EY, u16 Color);


#endif

