#include "touch.h"
#include "systick.h"
#include "stdlib.h"
#include "lcd.h"
#include  <stdio.h>
#include "at24c02.h"
u8 Touch_Flag =0;
Adjust_Per adjust_per;
	u16 xlcdval,ylcdval;
u8 touch_scan(u16 xpos,u16 ypos,u16 x_len,u16 y_len)
{
		printf("Xlcdval=%d\r\n",xlcdval);
		printf("Ylcdval=%d\r\n",ylcdval);
		if( ( xlcdval >= xpos ) && (xlcdval <= (xpos+x_len) ) && (ylcdval >= ypos) && (ylcdval<=( ypos+ y_len)) )  
			return 1;
		else  return 0;
}

void touch_get_xylcdval(u16 *Xlcdval,u16 *Ylcdval)
{
	u16 Xadval,Yadval;
	touch_get_xyadval(&Xadval,&Yadval);
	*Xlcdval = Xadval*adjust_per.X_scale + adjust_per.X_dev ;
	if( *Xlcdval>319 )   *Xlcdval = 319;
	*Ylcdval = Yadval*adjust_per.Y_scale + adjust_per.Y_dev ;
	if( *Ylcdval>479 )   *Ylcdval = 479;
}

void touch_adjust(void)
{
	u8 i=0;
	const u16 lcd_buff[4][2]={{20,20},{300,20},{20,460},{300,460}};
	u16 ad_buff[4][2]={0};
	at24c02_read(adjust_addr,(u8*)&adjust_per,sizeof(adjust_per));
	if( adjust_per.flag != adjust_OK)
	{
	ADJUST:
	for(i=0;i<4;i++)
	{
		LCD_Draw_Cross(lcd_buff[i][0], lcd_buff[i][1], RED);
		while( touch_pen() ==0 );  //�ȴ����£�������ʱ����
		touch_get_xyadval(&ad_buff[i][0],&ad_buff[i][1]);
		printf("X%d��%d,",i,ad_buff[i][0]);
		printf("Y%d��%d     ",i,ad_buff[i][1]);
		if(i%2!=0)     printf("\r\n");
		while( T_PEN == 0 );       //�ȴ��ɿ�
		LCD_Draw_Cross(lcd_buff[i][0], lcd_buff[i][1], WHITE);
	}
	printf("*********");
	if(  ( abs( ad_buff[0][1] -ad_buff[1][1] ) > 80 )   // y0-y1<80,˵�����ε�����һ������LCD��X��ƽ��
   	|| ( abs( ad_buff[2][1] -ad_buff[3][1] ) > 80 )   // y2-y3<80,˵�����ε�����һ������LCD��X��ƽ��
		|| ( abs( ad_buff[0][0] -ad_buff[2][0] ) > 80 )   // x0-x2<80,˵�����ε����һ������LCD��Y��ƽ��
		|| ( abs( ad_buff[1][0] -ad_buff[3][0] ) > 80 )   // x1-x2<80,˵�����ε��ұ�һ������LCD��Y��ƽ��
	  || ( abs( ad_buff[0][0] -ad_buff[1][0] ) <3000 )  //�жϾ��εĿ��
		|| ( abs( ad_buff[0][1] -ad_buff[2][1] ) <3000 )  //�жϾ��εĸ߶�
	)   goto ADJUST;//˵����Щ�㲻���Ͼ��α�׼
	    //ע��80��3000�ǲ��Եõ��ľ���ֵ
		adjust_per.X_scale = (lcd_buff[1][0] - lcd_buff[0][0])/( (float)ad_buff[1][0] - ad_buff[0][0] );
		adjust_per.X_dev   = lcd_buff[0][0]  - adjust_per.X_scale*ad_buff[0][0];
		adjust_per.Y_scale = (lcd_buff[2][1] - lcd_buff[0][1])/( (float)ad_buff[2][1] - ad_buff[0][1] );
		adjust_per.Y_dev   = lcd_buff[0][1]  - adjust_per.Y_scale*ad_buff[0][1];
		adjust_per.flag    = adjust_OK;
		at24c02_write(adjust_addr,(u8*)&adjust_per,sizeof(adjust_per));
	}
}

void touch_get_xyadval(u16 *Xadval,u16 *Yadval)
{
	u16 buff[2]={0};
	u16 temp=0;
	GET_Xadval:	
	buff[0] = touch_get_adval(CMD_X);
	buff[1] = touch_get_adval(CMD_X);
	if( abs( buff[0] -buff[1] ) > 50 )
		goto GET_Xadval;
	*Xadval  = (buff[0]+buff[1])/2;
	GET_Yadval:	
	buff[0] = touch_get_adval(CMD_Y);
	buff[1] = touch_get_adval(CMD_Y);
	if( abs( buff[0] -buff[1] ) > 50 )
		goto GET_Yadval;
	*Yadval  = (buff[0]+buff[1])/2;
}


u16 touch_get_adval(u8 cmd)
{
	u16 adval;
	T_CS_L();
	touch_send_cmd(cmd);
	touch_delay(100);
	adval = touch_get_data();
	T_CS_H();
	adval  >>=3;
	adval  &=0xFFF;
	return adval;
}

u16 touch_get_data(void)
{
	u8  i=0;
	u16 data=0;
	for(i=0;i<16;i++)
	{
		T_SCK_L();
		touch_delay(10);
		T_SCK_H();
		if(T_MISO() )    data |=0x8000>>i; //1000 0000 0000 0000
//		else             data &=~(0x8000>>i); 
		touch_delay(10);
	}
	T_SCK_L();
	return data;
}


void touch_send_cmd(u8 cmd)
{
	u8 i=0;
	for(i=0;i<8;i++)
	{
		T_SCK_L();
		if( cmd&0x80 )      T_MOSI_H();
		else                T_MOSI_L();
		touch_delay(10);
		T_SCK_H();
		touch_delay(10);
		cmd <<=1;
	}
	T_SCK_L();
}

void touch_init(void)
{
	RCC->AHB1ENR   |=(1<<1)|(1<<2)|(1<<5) ;
	/* CS PC13 */
	GPIOC->MODER   &=~(3<<(13*2));
	GPIOC->MODER   |=1<<(13*2);
	GPIOC->OTYPER  &=~(1<<13);
	T_CS_H();
	/* SCK PB0 */
	GPIOB->MODER  &=~(3<<(0*2));
	GPIOB->MODER  |=1<<(0*2);
	GPIOB->OTYPER  &=~(1<<0);
	T_SCK_L();  //���߿���
	/* MISO PE5 */
	GPIOE->MODER  &=~(3<<(5*2));
	GPIOE->PUPDR  &=~(3<<(5*2));
	/* MOSI PE6 */
	GPIOE->MODER  &=~(3<<(6*2));
	GPIOE->MODER  |=1<<(6*2);
	GPIOE->OTYPER  &=~(1<<6);
	/* T_PEN PB1 */
	GPIOB->MODER  &=~(3<<(1*2));
	GPIOB->PUPDR  &=~(3<<(1*2));
//	GPIOB->PUPDR  |=1<<(1*2);    //PB1�������룬T_PEN
	touch_adjust();
	tim6_delay(8400-1,10);  //2ms�����ж�
}

void TIM6_DAC_IRQHandler(void)
{
	static u8 touch_sta=1;
	static u8 cnt=0;
	if( TIM6->SR &(1<<0) )
	{
		TIM6->SR &=~(1<<0); //���־λ
		if( (T_PEN==0) && touch_sta )
		{
			cnt++;
			if(cnt==8)  //����8����Ч���£��жϴ�������
			{
				Touch_Flag = Touch_OK ;
				cnt =0;	
				touch_sta=0;
			}
		}
		if( T_PEN )  touch_sta=1;    //��������
	}
}

//����84��Ƶ������84-1������0~65535
void tim6_delay(u16 psc,u16 arr)
{
	RCC->APB1ENR |=1<<4;//��ʱ��ʱ��Դʹ��
	//��ʱ��ģʽ���ã�CR1�Ĵ�����
	TIM6->CR1    |=1<<7;    //ʹ��Ӱ�ӼĴ���
	TIM6->CR1    &=~(1<<3); //ѭ������
	TIM6->CR1    &=~(1<<2); //ѡ�����Դ
	TIM6->CR1    &=~(1<<1); //ʹ�ܸ���Դ
	//ʱ����Ԫ���ã�����ֵ��Ԥ��Ƶϵ����
	TIM6->ARR     = arr;
	TIM6->PSC     = psc;
	//�ֶ����£����־λ
	TIM6->EGR    |=1<<0;    //�ֶ�����
	TIM6->SR     &=~(1<<0);
	TIM6->DIER   |=1<<0;    //�����ж�ʹ��
	
	NVIC_SetPriority(TIM6_DAC_IRQn, NVIC_EncodePriority(7-2, 0, 1));     //���þ�����ж�Դ
	NVIC_EnableIRQ(TIM6_DAC_IRQn);       //ʹ�ܾ����ж�Դ
	
	TIM6->CR1    |=1<<0;    //ʹ�ܶ�ʱ��	
}

/*
���жϼ��ܽ�
����ֵ��
0��û�д�������
1���д�������
*/
u8 touch_pen(void)
{
	static u8 sta=1;
	static u8 cnt=0;
	if( (T_PEN==0)&&sta ) //�д�������
	{
		Delay_ms(2);
		if( T_PEN==0 ) //�д�������
		{
			cnt++;
			if(	cnt==5)
			{
				sta = 0;
				return 1;
			}
		}
	}
	else if( T_PEN )  
	{
		cnt=0;
		sta = 1;
	}
	return 0;
}

void touch_delay(u8 t)
{
	while(t--);
}


