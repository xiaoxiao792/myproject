#include "hzk.h"
#include "w25q64.h"
#include "spi.h"

u8 hzk_write_byte(u32 addr,u8 byte)
{
	u8  status=0;
	u16 i=0;
	w25q64_write_enable();     //写使能
	do
	{
		status = w25q64_read_status();
	}while( 0 == ( status&(1<<1) ) ); //等待进入写使能
	Flash_CS_L();
	spi_send_read(0x02);	
	spi_send_read( addr>>16); 
	spi_send_read( addr>>8); 
	spi_send_read( addr>>0); 	
	spi_send_read( byte); 
	Flash_CS_H();
	do
	{
		status = w25q64_read_status();
	}while( status&(1<<0)  ); //等待芯片忙完	
}

void hzk_erase(void)
{
	u8 i=0;
	for(i=0;i<20;i++) w25q64_block_sector(i*65536);
}

