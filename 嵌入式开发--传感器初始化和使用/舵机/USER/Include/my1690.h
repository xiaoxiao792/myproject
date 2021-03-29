#ifndef MY1690_H
#define MY1690_H

#include <stm32f4xx.h>
void send_cmd(u8 cmd);
void send_3dat_cmd(u8 cmd,u8 jy);
void send_4dat_cmd(u8 cmd,u8 cs,u8 jy );
void send_5dat_cmd(u8 cmd,u8 cs,u8 gq,u8 jy );

#endif