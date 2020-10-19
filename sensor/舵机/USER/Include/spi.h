#ifndef SPI_H
#define SPI_H
#include "stm32f4xx.h"

#define Flash_CS_H()     ( GPIOB->BSRRL = 1<<14 )
#define Flash_CS_L()     ( GPIOB->BSRRH = 1<<14 )

void spi_init(void);
u8   spi_send_read(u8 byte);

#endif