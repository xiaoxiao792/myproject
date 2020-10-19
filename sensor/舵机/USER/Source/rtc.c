#include "rtc.h"
#include "string.h"
#include "stdio.h"
rtc_par Rtc_Init_Struct={18,8,23,4,16,29,50 };

//Time:2018-08-23-4-16-50-45#
void usart_to_rtc(u8 *buff)
{
	rtc_par rtc_buff;
	if( 0== memcmp(buff,"Time",4) )
	{
		buff +=7;
		rtc_buff.year   = ( *buff-'0' )*10 + ( *(buff+1)-'0' );
		buff +=3;
		rtc_buff.month  = ( *buff-'0' )*10 + ( *(buff+1)-'0' );
		buff +=3;
		rtc_buff.day    = ( *buff-'0' )*10 + ( *(buff+1)-'0' );
		buff +=3;
		rtc_buff.week   =( *buff-'0' );
		buff +=2;
		rtc_buff.hour   =( *buff-'0' )*10 + ( *(buff+1)-'0' );
		buff +=3;
		rtc_buff.minute =( *buff-'0' )*10 + ( *(buff+1)-'0' );
		buff +=3;
		rtc_buff.second =( *buff-'0' )*10 + ( *(buff+1)-'0' );		
		rtc_set(&rtc_buff);
		printf("�޸ĳɹ����ʱ���ǣ�");
		printf("20%2d-%2d-%2d-week%2d ",rtc_buff.year,rtc_buff.month,rtc_buff.day,rtc_buff.week);
		printf("%2d:%2d:%2d\r\n",rtc_buff.hour,rtc_buff.minute,rtc_buff.second);
	}
	else printf("ERROR");
}
void rtc_init(void)
{
	if( 0== ( RTC->ISR &(1<<4))  )
	{
		RCC->APB1ENR  |=1<<28; //ʹ�ܵ�Դ������ʱ��
		PWR->CR       |=1<<8;  //ʹ�ܶ�RTC�Ĵ�����д����
		/* RTCʱ������ */
		RCC->BDCR     &=~(3<<8);
		RCC->BDCR     |=1<<8;   //ѡ��LSE��ΪRTCʱ��
		RCC->BDCR     |=1<<0;   //����LSEʱ��
		while( 0==( RCC->BDCR&(1<<1)) ) ; //�ȴ�LSEʱ�Ӿ���
		RCC->BDCR     |=1<<15;  //ʹ��RTCʱ��
		RTC->WPR       =0xCA;
		RTC->WPR       =0x53;  //����RTCд����
		
		/* RTC��ʼ������*/
		RTC->ISR      |=1<<7;  //�����ʼ��ģʽ
		while( 0==( RTC->ISR&(1<<6)) ); //�ȴ������ʼ��
		RTC->PRER      =127<<16; //�����첽Ԥ��Ƶ
		RTC->PRER     |=255<<0;  //����ͬ��Ԥ��Ƶ
		RTC->CR       &=~(1<<6); //ʹ��24Сʱ��
		RTC->CR       &=~(1<<5); //����ֵ����Ӱ�ӼĴ���
		RTC->ISR      &=~(1<<7);  //�����ʼ��ģʽ
		
		RTC->WPR       =0;        //����RTCд����	
		PWR->CR       &=~(1<<8);  //��ֹд����
		rtc_set(&Rtc_Init_Struct);
	}
}

void rtc_get(rtc_par *rtc_infor)
{
	u32 date=0;
	u32 time=0;
	while( 0== ( RTC->ISR &(1<<5) )  ) ;  //�ȴ������Ĵ���ͬ��
	RTC->ISR &=~(1<<5);
	date = RTC->DR  ;
	time = RTC->TR ;
	rtc_infor->year   =  ( (date>>20)&0xF )*10 + ( (date>>16)&0xF );
	rtc_infor->month  =  ( (date>>12)&0x1 )*10 + ( (date>>8)&0xF ); 
	rtc_infor->day    =  ( (date>>4)&0x3 )*10  + ( (date>>0)&0xF ); 
	rtc_infor->week   =  ( (date>>13)&0x7 ); 
	rtc_infor->hour   =  ( (time>>20)&0x3 )*10 + ( (time>>16)&0xF );
	rtc_infor->minute =  ( (time>>12)&0x7 )*10 + ( (time>>8)&0xF ); 
	rtc_infor->second =  ( (time>>4)&0x7 )*10  + ( (time>>0)&0xF ); 
}


void rtc_set(rtc_par *rtc_infor)
{
	u32 date=0;
	u32 time=0;
	RCC->APB1ENR  |=1<<28; //ʹ�ܵ�Դ������ʱ��
	PWR->CR       |=1<<8;  //ʹ�ܶ�RTC�Ĵ�����д����
	RTC->WPR       =0xCA;
	RTC->WPR       =0x53;  //����RTCд����
	/* RTC��ʼ������*/
	RTC->ISR      |=1<<7;  //�����ʼ��ģʽ
	while( 0==( RTC->ISR&(1<<6)) ); //�ȴ������ʼ��
	
	date  |=  ( ( rtc_infor->year/10 )<<20 )  | ( ( rtc_infor->year%10)<<16 );
	date  |=  ( ( rtc_infor->month/10 )<<12 ) | ( ( rtc_infor->month%10)<<8 );
	date  |=  ( ( rtc_infor->day/10 )<<4 )    | ( ( rtc_infor->day%10)<<0 );
	date  |=  rtc_infor->week <<13 ;
	RTC->DR   = date;
	
	time  |=  ( ( rtc_infor->hour/10 )<<20 )   | ( ( rtc_infor->hour%10)<<16 );
	time  |=  ( ( rtc_infor->minute/10 )<<12 ) | ( ( rtc_infor->minute%10)<<8 );
	time  |=  ( ( rtc_infor->second/10 )<<4 )  | ( ( rtc_infor->second%10)<<0 );
	RTC->TR   = time;
	
	
	RTC->ISR      &=~(1<<7);  //�����ʼ��ģʽ
	RTC->WPR       =0;        //����RTCд����	
	PWR->CR       &=~(1<<8);  //��ֹд����
}




