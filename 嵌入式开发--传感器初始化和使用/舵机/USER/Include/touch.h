#ifndef TOUCH_H
#define TOUCH_H
#include "stm32f4xx.h"

#define T_CS_H()     ( GPIOC->BSRRL = 1<<13 )
#define T_CS_L()     ( GPIOC->BSRRH = 1<<13 )
#define T_SCK_H()    ( GPIOB->BSRRL = 1<<0  )
#define T_SCK_L()    ( GPIOB->BSRRH = 1<<0  )
#define T_MOSI_H()   ( GPIOE->BSRRL = 1<<6  )
#define T_MOSI_L()   ( GPIOE->BSRRH = 1<<6  )
#define T_MISO()     (!!(GPIOE->IDR &(1<<5)))
#define T_PEN        ( GPIOB->IDR &(1<<1) )
#define Touch_OK      0xFF
#define adjust_addr   0x96
#define adjust_OK     0x66
#define CMD_X         0xD0
#define CMD_Y         0x90

typedef struct 
{
	float X_scale; //X轴比例系数
	float X_dev;   //X轴偏移量
	float Y_scale;
	float Y_dev;
	u8    flag;
}Adjust_Per;
extern u8 Touch_Flag;
extern u16 xlcdval,ylcdval;
void touch_init(void);
u8   touch_pen(void);
void touch_delay(u8 t);
void touch_send_cmd(u8 cmd);
u16  touch_get_data(void);
u16  touch_get_adval(u8 cmd);
void touch_get_xyadval(u16 *Xadval,u16 *Yadval);
void touch_adjust(void);
void touch_get_xylcdval(u16 *Xlcdval,u16 *Ylcdval);
u8 	 touch_scan(u16 xpos,u16 ypos,u16 x_len,u16 y_len);
void tim6_delay(u16 psc,u16 arr);
#endif
