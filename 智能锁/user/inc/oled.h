#ifndef _OLED_H
#define _OLED_H
#include "stm32f10x.h"  
 

//复位管脚宏定义
#define OLED_RST_L  (GPIOA->ODR &= ~(1 << 12))
#define OLED_RST_H  (GPIOA->ODR |= 1 <<12)

//命令数标识宏定义
#define OLED_CMD   0
#define OLED_DAT   1

//命令数据选择线宏定义
#define OLED_CD_H  (GPIOA->ODR |= 1 << 11)
#define OLED_CD_L  (GPIOA->ODR &= ~(1 << 11))

//片选宏定义
#define OLED_CS_H  (GPIOA->ODR |= 1 <<15)
#define OLED_CS_L  (GPIOA->ODR &= ~(1 <<15))



void OLED_IO_Init(void);
void OLED_Reset(void);
void OLED_writeByte(u8 data, u8 oled_cmd_data);
void OLED_Init(void);
void OLED_clear(void);

void OLED_setstart(u8 page, u8 lis) ;

void oled_Dis_ch16(u8 page ,u8 lis,u8 ch);
void oled_Dis_str16(u8 page ,u8 lis,u8 *str);

void oled_Dis_hz16(u8 page ,u8 lis,u8 *str);
void oled_Dis_hzstr16(u8 page ,u8 lis,u8 *str);

void oled_Dis_pic(u8 page,u8 lis,u8 *pic,u8 w,u8 h);
 


#endif






 

