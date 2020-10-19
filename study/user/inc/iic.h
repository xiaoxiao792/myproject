#ifndef IIC_H
#define IIC_H

  
#include "stm32f10x.h"
 

#define SDA_IN  	{GPIOB->CRL&=~(0XF<<((5)*4)); GPIOB->CRL|=0x4<<((5)*4);}
#define SDA_OUT   {GPIOB->CRL&=~(0XF<<((5)*4)); GPIOB->CRL|=0x3<<((5)*4);}
#define READ_SDA() (GPIOB->IDR& 1<<5)

#define SDA_H  GPIOB->ODR|=1<<5
#define CLK_H  GPIOB->ODR|=1<<4

#define SDA_L  GPIOB->ODR&=~(1<<5)
#define CLK_L  GPIOB->ODR&=~(1<<4)
 
void IIC_Init(void);
void IIC_Stop(void);
void IIC_Start(void);
void IIC_Send_Data(u8 dat);
u8 IIC_Read_Data(u8 ack);
u8 IIC_Get_ACK(void);
 
#endif 
