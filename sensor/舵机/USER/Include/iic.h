#ifndef IIC_H
#define IIC_H
#include "stm32f4xx.h"

#define ACK         0
#define NoACK       1

#define SCL_H()     ( GPIOB->BSRRL =1<<8 )
#define SCL_L()     ( GPIOB->BSRRH =1<<8 )
#define SDA_H()     ( GPIOB->BSRRL =1<<9 )
#define SDA_L()     ( GPIOB->BSRRH =1<<9 )
#define SDA_IN()    { SCL_L(); Delay_us(1);SDA_H();  } //拉高SDA：开漏+高阻态，输入部分正常工作
#define SDA_Read()  ( GPIOB->IDR&(1<<9)  )

void iic_init(void);
u8   iic_read(u8 ack);
u8   iic_write(u8 byte);
void iic_stop(void);
void iic_start(void);

#endif