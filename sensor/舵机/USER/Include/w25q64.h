#ifndef W25Q64_H
#define W25Q64_H
#include "stm32f4xx.h"

#define W25Q64_PAGE      256
#define W25Q64_SECTOR    4096

u16  w25q64_read_id(void);
void w25q64_write_enable(void);
u8   w25q64_read_status(void);
void w25q64_erase_sector(u32 addr);
void w25q64_block_sector(u32 addr);
void w25q64_chip_sector(void);
u8   w25q64_page_program(u32 addr,u8 *buff,u16 num);
void w25q64_read(u32 addr,u8 *buff,u16 num);
u8   w25q64_write(u32 addr,u8 *buff,u32 num);
u8   w25q64_sector_program(u32 addr,u8 *buff);
u8   w25q64_write_No_erase(u32 addr,u8 *buff,u32 num);

#endif