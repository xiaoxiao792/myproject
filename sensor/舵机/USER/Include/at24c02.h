#ifndef AT24C02_H
#define AT24C02_H
#include "stm32f4xx.h"

#define Wite_ADDR  0xA0
#define Read_ADDR  0xA1
#define TRUE   0
#define ERROR  1
#define Page_Count  8
u8 at24c02_write(u8 byte_addr,u8 *buff,u16 count);
u8 at24c02_read(u8 byte_addr,u8 *buff,u16 count);
u8 at24c02_page_program(u8 byte_addr,u8 *buff,u8 count);

#endif