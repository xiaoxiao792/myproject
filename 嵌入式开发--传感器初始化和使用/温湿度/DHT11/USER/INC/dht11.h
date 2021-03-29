#ifndef DHT11_H
#define DHT11_H

#define DAT_H() (GPIOC->BSRRL = 1<<4)         //À­¸ßPG.4
#define DAT_L() (GPIOC->BSRRH = 1<<4)         //À­µÍPG.4
#define DAT_Read() (!!(GPIOC->IDR & (1<<4)))
#include "stm32f4xx.h"
extern float  temperature;
extern float humidity;
u8 DHT11_Init(void);
void DHT11_Start(void);
u8 DHT11_Check(void);
u8 DHT11_Read_Bit(void);
u8 DHT11_Read_Byte(void);
//u8 DHT11_Read_Data(u8 *temp,u8 *humi);
void DHT11_Show_Data(void);
u8 DHT11_Read_Data(float *temp,float *humi);

#endif
