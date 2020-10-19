#include "at24c02.h"
#include "iic.h"
#include "systick.h"
#include  <stdio.h>

/*
AT24C02����������
����1��u8 byte_addr���������ڵĴ洢��ַ�� AT24C02�Ĵ洢��ַ ��
����2��u8 *buff�����ݻ��������������洢�����ݵĿռ�
����3��u8 count����Ҫ��ȡ���ֽ���
����ֵ��
TRUE   ���������ɹ�
ERROR  ��ҳ������ʧ��
*/
u8 at24c02_read(u8 byte_addr,u8 *buff,u16 count)
{
	u8  ack=0;
	u16 i=0;
	/* αд���� */
	iic_start();                    //������ʼ�ź�
	ack = iic_write(Wite_ADDR);     //����д������ַ
	if( ack == NoACK ) 	 return  ERROR;
	
	ack = iic_write(byte_addr);     //���ʹ洢��ַ
	if( ack == NoACK ) 	 return  ERROR;
	
	/* ���������� */
	iic_start();                    //������ʼ�ź�
	ack = iic_write(Read_ADDR);     //����д������ַ
	if( ack == NoACK ) 	 return  ERROR;
	for(i=0;i<count-1;i++)  
	{
	  *buff = iic_read(ACK);        //ǰ�� count-1 ������ҪӦ��  
		buff++;
	}
	*buff = iic_read(NoACK);        //���һ�����ݲ���ҪӦ��
	iic_stop();                     //���ͽ����ź�
	return  TRUE;
}
/*
AT24C02����д����
����1��u8 byte_addr������Ҫ�洢���ĵط��� AT24C02�Ĵ洢��ַ ��
����2��u8 *buff�����ݻ���������������Ҫ�洢������
����3��u8 count����Ҫ�洢���ֽ���
����ֵ��
TRUE   ������д�ɹ�
ERROR  ��ҳ����дʧ��
*/
u8 at24c02_write(u8 byte_addr,u8 *buff,u16 count)
{
	u8  error=0;
	u8  i=0;
	u16 last_count = 256 - byte_addr;                 //����Ӵ˵�ַ��ʼ������оƬ����д���������
	if( last_count < count )   return  ERROR;         //�洢�ռ䲻��
	
	last_count = Page_Count -   byte_addr%Page_Count;   //����ӵ�ǰ��ַ��ʼ����ҳ����д�������
	if( count < last_count )    last_count = count;     //��ǰҳ��д�꣬���¸�ֵlast_count������ȫ��д��
	while( count )
	{		
		error = at24c02_page_program( byte_addr,buff,last_count );  //ҳ��̺���
		if( error == ERROR )                     return  ERROR;   //ҳ��̳��� 
		/* �洢��ַ�����ݻ��������ֽ�������Ҫƫ�� */
		/* ƫ����Ϊ��д����ֽ��� */
		byte_addr	 += last_count;
		buff	     += last_count;
		count      -= last_count;

		if( count>Page_Count )        last_count = Page_Count;   //ʣ����Ҫд����ֽ�����һҳ�࣬дһҳ
		else                          last_count = count;        //ʣ����Ҫд����ֽ����Ȳ���һҳ��ȫ��д��
	}
	return  TRUE;  //�����ȷ
}

/*
AT24C02ҳ��̺���
����1��u8 byte_addr������Ҫ�洢���ĵط��� AT24C02�Ĵ洢��ַ ��
����2��u8 *buff�����ݻ���������������Ҫ�洢������
����3��u8 count����Ҫ�洢���ֽ���
����ֵ��
TRUE   ��ҳ��̳ɹ�
ERROR  ��ҳ���ʧ��
*/ 
u8 at24c02_page_program(u8 byte_addr,u8 *buff,u8 count)
{
	u8 ack=0;
	u8 i=0;
	u8 last_count = Page_Count - byte_addr%Page_Count ;  //����ӵ�ǰ��ַ��ʼ����ҳ����д�������
	if( last_count < count )   return  ERROR;
	iic_start();                    //������ʼ�ź�
	ack = iic_write(Wite_ADDR);     //����д������ַ
	if( ack == NoACK ) 	 return  ERROR;
	
	ack = iic_write(byte_addr);     //���ʹ洢��ַ
	if( ack == NoACK ) 	 return  ERROR;
	
	for(i=0;i<count;i++)  
	{
		ack = iic_write(buff[i]);     //��������
		if( ack == NoACK ) 	 return  ERROR;
	}
	
	iic_stop();                     //���ͽ����ź�
	 Delay_ms(10);
	 return  TRUE;
}



