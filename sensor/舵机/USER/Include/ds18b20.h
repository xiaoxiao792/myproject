#ifndef DS18B20_h
#define DS18B20_h
#include <stm32f4xx.h>
#include "iobit.h"

 
#define DQ_in  PBin(12)
#define DQ_out PBout(12)


u8 ds18b20_init(void);
void ds18b20_reset(void);
void io_in(void);
void io_out(void);
void  writebyte(u8 data);
void ds18b20_convert(void);
u8 readbyte(void);
u8 readbit(void);
u8 ds18b20_cheak(void);
float get_temperature(void);


#endif

