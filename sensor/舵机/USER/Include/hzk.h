#ifndef HZK_H
#define HZK_H
#include "stm32f4xx.h"

void hzk_erase(void);
u8   hzk_write_byte(u32 addr,u8 byte);
#endif