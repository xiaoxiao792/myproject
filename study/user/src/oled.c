#include "stm32f10x.h"                  // Device header
 #include "oled.h"
 #include "spi.h"
 #include "systick.h"
 #include "font.h"
/***************************************************
*������    :OLED_IO_init
*��������  :OLED���ùܽų�ʼ������
*��������  :��
*��������ֵ:��
*��������  :CS-----PA15
            DC-----PA11
            RES----PA12
*****************************************************/
void OLED_IO_Init(void)
{
	RCC->APB2ENR |=1<<2;  //ʹ��Aʱ��
 
 
	/*CS-----PA15*/ //������� 50MHZ
  GPIOA->CRH &=~(0XF <<((15-8)*4));
	GPIOA->CRH |=0X3 <<((15-8)*4);
	GPIOA->ODR |=(1 <<15);    //Ƭѡ���߲�ѡ��OLED
	
	/*DC-----PA11*/ //������� 50MHZ
  GPIOA->CRH &=~(0XFul<<((11-8)*4));
	GPIOA->CRH |=0X3ul<<((11-8)*4);
	GPIOA->ODR |=1<<11;  
	
	/*RES-----PA12*/ //������� 50MHZ
  GPIOA->CRH &=~(0XF<<((12-8)*4));
	GPIOA->CRH |=0X3<<((12-8)*4);
	GPIOA->ODR |=1<<12;  
}



/*********************************************
*������    ��OLED_Reset
*��������  ��OLEDӲ����λʱ�� 
*��������  ����
*��������ֵ����
*��������  ��
							��λ�ܽ�����
							��ʱ100ms
							��λ�ܽ�����
							��ʱ100ms
							��λ�ܽ�����					
*********************************************/
void OLED_Reset(void)
{
	OLED_RST_L;
	Delay_ms(100);
	OLED_RST_H;
	Delay_ms(100);
}


/*********************************************
*������    ��OLED_writeByte
*��������  ��OLEDʱ��д����/����
*��������  ��u8 data   u8 oled_cmd_data
*��������ֵ����
*��������  ��
							ȷ�������������(�������)
							Ƭѡ����
							��SPI����������/�������
							Ƭѡ����	

							��ʾ��oled_cmd_data
              1   ��������/����������    ���͵�������
              0   ��������/����������    ���͵�������			
*********************************************/
void OLED_writeByte(u8 data, u8 oled_cmd_data)
{
	//ȷ�������������(�������)
	oled_cmd_data ? (OLED_CD_H) : (OLED_CD_L);
	//Ƭѡ����
	OLED_CS_L;
	//��SPI����������/�������
	SPI_Read_Write_Byte(data);
	//Ƭѡ����
	OLED_CS_H;
}
	


/*********************************************
*������    ��OLED_Init
*��������  ��ʵ�ֶ�OLED��Ļ��ʼ������
*��������  ����
*��������ֵ����
*��������  ��
							�ٹܽų�ʼ��      //Ƭѡ  res   D/C
								SPI1��ʼ��
							��OLEDӲ��λ
							�۳�������IC����  //OLED��ͨ��ʱ�򣨰���SPI��
							������clear
*********************************************/
void OLED_Init(void)
{
	//�ܽų�ʼ�� 
	OLED_IO_Init();
	//spi1��ʼ��
	SPI_2_Init();
	//OLEDӲ��λ
	OLED_Reset();
	
	//��������IC����
	OLED_writeByte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_writeByte(0x02,OLED_CMD);//---SET low column address
	OLED_writeByte(0x10,OLED_CMD);//---SET high column address
	OLED_writeByte(0x40,OLED_CMD);//--SET start line address  SET Mapping RAM Display Start Line (0x00~0x3F)
	OLED_writeByte(0x81,OLED_CMD);//--SET contrast control register
	OLED_writeByte(0xCF,OLED_CMD); // SET SEG Output Current Brightness
	OLED_writeByte(0xA1,OLED_CMD);//--SET SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_writeByte(0xC8,OLED_CMD);//SET COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_writeByte(0xA6,OLED_CMD);//--SET normal display
	OLED_writeByte(0xA8,OLED_CMD);//--SET multiplex ratio(1 to 64)
	OLED_writeByte(0x3f,OLED_CMD);//--1/64 duty
	OLED_writeByte(0xD3,OLED_CMD);//-SET display offSET	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_writeByte(0x00,OLED_CMD);//-not offSET
	OLED_writeByte(0xd5,OLED_CMD);//--SET display clock divide ratio/oscillator frequency
	OLED_writeByte(0x80,OLED_CMD);//--SET divide ratio, SET Clock as 100 Frames/Sec
	OLED_writeByte(0xD9,OLED_CMD);//--SET pre-charge period
	OLED_writeByte(0xF1,OLED_CMD);//SET Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_writeByte(0xDA,OLED_CMD);//--SET com pins hardware configuration
	OLED_writeByte(0x12,OLED_CMD);
	OLED_writeByte(0xDB,OLED_CMD);//--SET vcomh
	OLED_writeByte(0x40,OLED_CMD);//SET VCOM Deselect Level
	OLED_writeByte(0x20,OLED_CMD);//-SET Page Addressing Mode (0x00/0x01/0x02)
	OLED_writeByte(0x02,OLED_CMD);//
	OLED_writeByte(0x8D,OLED_CMD);//--SET Charge Pump enable/disable
	OLED_writeByte(0x14,OLED_CMD);//--SET(0x10) disable
	OLED_writeByte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_writeByte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_writeByte(0xAF,OLED_CMD);//--turn on oled panel
	OLED_writeByte(0xAF,OLED_CMD); /*display ON*/ 

	//��������
	OLED_clear();

}



/*********************************************
*������    ��OLED_clear
*��������  ����������Ļ���ĳ����ɫ
*��������  ����
*��������ֵ����
*��������  ��
							8��ҳѭ��
								ÿ��ҳѭ����132����ѭ��
*********************************************/
void OLED_clear(void)
{
	u8 i,n;
	//ҳѭ��
	for(i=0;i<8;i++)
	{
		//����ҳ��ַ
		OLED_writeByte(0xb0+i,OLED_CMD);
		//����ÿҳ������ʼ��ַ
		OLED_writeByte(0x00,OLED_CMD);     //��ַ��ŵ���λ
		OLED_writeByte(0x10,OLED_CMD);     //��ַ��Ÿ���λ
		//ÿҳҪ���͵�����
		for(n=0;n<132;n++)               
		{
			OLED_writeByte(0x00,OLED_DAT);   //ĳһ�е�����
		}
	}
}




 








/*********************************************
*������    ��OLED_setstart
*��������  ��ȷ����ʾ��ʼλ�ú���   ��ҳ������
*��������  ��u8 page  ҳ��         u8 lis   �к�
*��������ֵ����
*��������  ��
							ͨ���˺�����ȷ��Ҫ��ʾ����ʼλ��
							�������ݣ����ͼ��ξͻ���ʾ���У�����ˢ����
*********************************************/
void OLED_setstart(u8 page, u8 lis) 
{
	OLED_writeByte(0xb0+page,OLED_CMD);              //ȷ��ҳ��
	OLED_writeByte(((lis&0xf0)>>4)|0x10, OLED_CMD);  //�к�
	OLED_writeByte((lis&0x0f),OLED_CMD);             //�к�      
} 






/*********************************************
*������    ��oled_Dis_ch16
*��������  ����ʾһ��16*16���ַ�
*��������  ��u8 page  ҳ��         u8 lis   �к�    u8 ch   Ҫ��ʾ���ַ�
*��������ֵ����
*��������  ��
							//��ʼλ�ú���  
							//��������                        
							-----------------------------------------�ֵ��ϰ벿��
							//�ٴ�ȷ����ʼλ��    ҳ��+1            
							//ѭ���������ݣ�����ĺ��8��Ԫ�أ�       
							-----------------------------------------�ֵ��°벿��
*********************************************/
void oled_Dis_ch16(u8 page ,u8 lis,u8 ch)
{
	u8 i,p;
	u8 n;
	//�ҵ�Ҫ��ʾ���ַ���ASCII���е���������Կո�
	n = ch - ' ';     //
	//��ʾ��
	for(p=0;p<16/8;p++)          //ҳ���ѭ������
	{
		OLED_setstart(page+p,lis); //ȷ��λ��
		for(i=0;i<8;i++)
		{
			OLED_writeByte(F16X16[16*n+i+p*8],OLED_DAT);    //����Ӧҳ������(�ϰ���ֺ��°����)
		}
	}
	
}


 



/*********************************************
*������    ��oled_Dis_str16
*��������  ����ʾһ��16*16���ַ���
*��������  ��u8 page  ҳ��         u8 lis   �к�    u8 *str   Ҫ��ʾ���ַ����׵�ַ
*��������ֵ����
*��������  ��
							
*********************************************/
void oled_Dis_str16(u8 page ,u8 lis,u8 *str)
{
	while(*str != '\0')
	{
		oled_Dis_ch16(page,lis,*str);
		str++;
		lis += 8;
	}
}







/*********************************************
*������    ��oled_Dis_hz16
*��������  ����ʾһ��16*16�ĺ���
*��������  ��u8 page  ҳ��         u8 lis   �к�    u8 *str   Ҫ��ʾ�ĺ����׵�ַ
*��������ֵ����
*��������  ��					
*********************************************/
void oled_Dis_hz16(u8 page ,u8 lis,u8 *str)
{
	u16 n = 0;
	u8 p,i;
	//����Ҫ��ʾ�ĺ��ֵ�λ�ã����һ�����ֵ�ƫ�ƣ�
	while(1)
	{
		if((*str == hztable[n*2]) && (*(str+1) == hztable[n*2+1]))
		{
			break;
		}
		n+=1;     //�Ա���һ������
	} 
	
	//n ���ֱ��
	
	//��ʾ
	for(p=0;p<16/8;p++)
	{
		//ȷ��λ��
		OLED_setstart(page+p,lis); 
		for(i=0;i<16;i++)
		{
			OLED_writeByte(hz16[32*n+i+p*16],OLED_DAT);
		}
	}
}








/*********************************************
*������    ��oled_Dis_hzstr16
*��������  ����ʾһ��16*16���ַ���
*��������  ��u8 page  ҳ��         u8 lis   �к�    u8 *str   Ҫ��ʾ���ַ����׵�ַ
*��������ֵ����
*��������  ��
							
*********************************************/
void oled_Dis_hzstr16(u8 page ,u8 lis,u8 *str)
{
	while(*str != '\0')
	{
		oled_Dis_hz16(page,lis,str);
		str+=2;
		lis += 16;
	}
}











/*******************************************************************************
*������    ��oled_Dis_pic
*��������  ����ʾһ�������С��ͼƬ
*��������  ��u8 page  u8 lis       u8 *pic                   u8 w     u8 h
             ҳ��     �к�         Ҫ��ʾ��ͼƬģ���׵�ַ     ͼƬ��    ͼƬ��
*��������ֵ����
*��������  ��					
**********************************************************************************************/
void oled_Dis_pic(u8 page,u8 lis,u8 *pic,u8 w,u8 h)
{
	u8 p,i;
	u8 c;
	if(h % 8 == 0)
	{
		c = h / 8;
	}
	else
	{
		c = h / 8+1;
	}
	
	
	for(p=0;p<c;p++)
	{
		//ȷ��λ��
		OLED_setstart(page+p,lis);
		for(i=0;i<w;i++)
		{
			OLED_writeByte(pic[w*p+i],OLED_DAT);
		}
	}
}