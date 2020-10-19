#ifndef RTC_H
#define RTC_H
#include "stm32f4xx.h"
typedef struct
{
	u8 year;
	u8 month;
	u8 day;
	u8 week;
	u8 hour;
	u8 minute;
	u8 second;
}rtc_par;
extern rtc_par Rtc_Init_Struct;
void rtc_init(void);
void rtc_set(rtc_par *rtc_infor);
void rtc_get(rtc_par *rtc_infor);
void usart_to_rtc(u8 *buff);
#endif