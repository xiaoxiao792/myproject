#include "w25q64.h"
#include "spi.h"
u8 secotr_buff[4096];

u8 w25q64_write_No_erase(u32 addr,u8 *buff,u32 num)
{
	u32 i=0;
	u8  error=0;
	u16 count;
	u32 last_count= 0x800000 - addr; 
	if( last_count < num )  return 1;	          //�Ӵ˵�ַ��ʼ��оƬ�޷�д��ȫ������
	last_count = addr%W25Q64_SECTOR;            //����˵�ַ��������λ��
	count = W25Q64_SECTOR -  last_count;        //��������ʣ��ռ�
	if( num<count )  count = num;
	while( num )
	{
		w25q64_read( addr&0xFFF000, secotr_buff,W25Q64_SECTOR); //���ݱ���
		for(i=last_count;i<(last_count+count);i++)
			secotr_buff[i] = buff[i-last_count];  //�����滻
		w25q64_erase_sector(addr);              //��������
		error = w25q64_sector_program(addr,secotr_buff); //����д��	
		if( error )    return 1; //д��ʧ��
		addr +=count;
		buff +=count;
		num  -=count;
		last_count = 0;
		if( num<W25Q64_SECTOR )  count = num;
		else                     count = W25Q64_SECTOR;
	}
	return 0;
}
u8 w25q64_sector_program(u32 addr,u8 *buff)
{
	u8 i=0;
	u8 error=0;
	addr &=0xFFF000; //�õ������׵�ַ
	for(i=0;i<16;i++)
	{
		error= w25q64_page_program(addr,buff,W25Q64_PAGE);
		if(error)   return 1;
		addr +=W25Q64_PAGE;
		buff +=W25Q64_PAGE;
	}
	return 0;
}


/* ����д */
u8 w25q64_write(u32 addr,u8 *buff,u32 num)
{
	u32 i=0;
	u8  error=0;
	u32 last_count = 0x800000 - addr; 
	if( last_count < num )  return 1;	          //�Ӵ˵�ַ��ʼ��оƬ�޷�д��ȫ������
	last_count = W25Q64_PAGE- addr%W25Q64_PAGE; //����˵�ַ����ҳ��д����ֽ���
	if( num < last_count )  last_count=num;
	while( num )
	{
		error = w25q64_page_program(addr,buff,last_count);
		if( error )    return 1; //д��ʧ��
		addr +=last_count;
		buff +=last_count;
		num  -=last_count;
		if( num>W25Q64_PAGE )  last_count=W25Q64_PAGE;
		else                   last_count=num;
	}
	return 0;
}

/* ҳ������ */
void w25q64_read(u32 addr,u8 *buff,u16 num)
{	
	u32 i=0;
	Flash_CS_L();
	spi_send_read(0x03);	
	spi_send_read( addr>>16); 
	spi_send_read( addr>>8); 
	spi_send_read( addr>>0); 
	for(i=0;i<num;i++) 
	{
		*buff = spi_send_read( 0xFF ); 
		buff++;
	}
	Flash_CS_H();
}


/* 
ҳ��� 
����ֵ��
0��  ҳ��̳ɹ�
1��  ҳ���ʧ��
*/
u8 w25q64_page_program(u32 addr,u8 *buff,u16 num)
{
	u8  status=0;
	u16 i=0;
	u16 last_count=W25Q64_PAGE- addr%W25Q64_PAGE;
	if( last_count < num )  return 1;	
	w25q64_write_enable();     //дʹ��
	do
	{
		status = w25q64_read_status();
	}while( 0 == ( status&(1<<1) ) ); //�ȴ�����дʹ��
	Flash_CS_L();
	spi_send_read(0x02);	
	spi_send_read( addr>>16); 
	spi_send_read( addr>>8); 
	spi_send_read( addr>>0); 
	for(i=0;i<num;i++) 
	{
		spi_send_read( *buff ); 
		buff++;
	}
	Flash_CS_H();
	do
	{
		status = w25q64_read_status();
	}while( status&(1<<0)  ); //�ȴ�оƬæ��	
}
/* оƬ���� */
void w25q64_chip_sector(void)
{
	u8 status=0;
	w25q64_write_enable();     //дʹ��
	do
	{
		status = w25q64_read_status();
	}while( 0 == ( status&(1<<1) ) ); //�ȴ�����дʹ��
	Flash_CS_L();
	spi_send_read(0xC7);	
	Flash_CS_H();
	do
	{
		status = w25q64_read_status();
	}while( status&(1<<0)  ); //�ȴ�оƬæ��
}
/* ����� */
void w25q64_block_sector(u32 addr)
{
	u8 status=0;
	w25q64_write_enable();     //дʹ��
	do
	{
		status = w25q64_read_status();
	}while( 0 == ( status&(1<<1) ) ); //�ȴ�����дʹ��
	Flash_CS_L();
	spi_send_read(0xD8);	
	spi_send_read( addr>>16); 
	spi_send_read( addr>>8); 
	spi_send_read( addr>>0); 
	Flash_CS_H();
	do
	{
		status = w25q64_read_status();
	}while( status&(1<<0)  ); //�ȴ�оƬæ��
}

/* �������� */
void w25q64_erase_sector(u32 addr)
{
	u8 status=0;
	w25q64_write_enable();
	do
	{
		status = w25q64_read_status();
	}while( 0 == ( status&(1<<1) ) ); //�ȴ�����дʹ��
	Flash_CS_L();
	spi_send_read(0x20);	
	spi_send_read( addr>>16); 
	spi_send_read( addr>>8); 
	spi_send_read( addr>>0); 
	Flash_CS_H();
	do
	{
		status = w25q64_read_status();
	}while( status&(1<<0)  ); //�ȴ�оƬæ��
}

/* ��״̬�Ĵ��� */
u8 w25q64_read_status(void)
{
	u8 status=0;
	Flash_CS_L();
	spi_send_read(0x05);
	status = spi_send_read(0xFF); //���͵�����Ч����,��������
	Flash_CS_H();
	return status;
}

/*дʹ��*/
void w25q64_write_enable(void)
{
	Flash_CS_L();
	spi_send_read(0x06);
	Flash_CS_H();
}

/*  ��ȡW25Q64����ID ��ȷ����0xEF16 */
u16 w25q64_read_id(void)
{
	u16 device_id=0;
	u8 device_id_h=0,device_id_l=0;
	Flash_CS_L();
	spi_send_read(0x90);
	spi_send_read(0x00);
	spi_send_read(0x00);
	spi_send_read(0x00);
	device_id_h = spi_send_read(0xFF);
	device_id_l = spi_send_read(0xFF);
	Flash_CS_H();
	device_id = (device_id_h<<8) | device_id_l;
	return device_id;
}