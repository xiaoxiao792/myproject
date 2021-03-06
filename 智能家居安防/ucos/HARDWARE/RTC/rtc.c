#include "stm32f4xx.h"
#include "sys.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "includes.h"
#include "usart.h"
static NVIC_InitTypeDef		NVIC_InitStructure;
static RTC_AlarmTypeDef     RTC_AlarmStructure;
static EXTI_InitTypeDef		EXTI_InitStructure;
static RTC_TimeTypeDef  	RTC_TimeStructure;
static RTC_DateTypeDef  	RTC_DateStructure;
static RTC_InitTypeDef  	RTC_InitStructure;
extern OS_FLAG_GRP g_flag_grp;

void rtc_init(void)
{
	//ʹ��rtc��Ӳ��ʱ��
	
	/* Enable the PWR clock��ʹ�ܵ�Դ����ʱ�� */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	/* Allow access to RTC���������RTC */
	PWR_BackupAccessCmd(ENABLE);
	
#if 1
	/* ʹ��LSE*/
	RCC_LSEConfig(RCC_LSE_ON);
	
	/* ����LSE�Ƿ���Ч*/  
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

	/* ѡ��LSE��ΪRTC��Ӳ��ʱ��Դ*/
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	

#else  //��LSE�޷������������ڲ�LSI
	/* ʹ��LSI*/
	RCC_LSICmd(ENABLE);
	
	/* ����LSI�Ƿ���Ч*/  
	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);

	/* ѡ��LSI��ΪRTC��Ӳ��ʱ��Դ*/
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
	

#endif
	
	/* Enable the RTC Clock��ʹ��RTC��Ӳ��ʱ�� */
	RCC_RTCCLKCmd(ENABLE);
	
	/* Wait for RTC APB registers synchronisation���ȴ�����RTC��ؼĴ������� */
	RTC_WaitForSynchro();
	
	//����Ƶ��1Hz
	/* ck_spre(1Hz) = RTCCLK(LSE) /(uwAsynchPrediv + 1)*(uwSynchPrediv + 1)*/
	//32768Hz/(127+1)/(255+1)=1Hz
	RTC_InitStructure.RTC_AsynchPrediv = 127;
	RTC_InitStructure.RTC_SynchPrediv = 255;
	RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
	RTC_Init(&RTC_InitStructure);
	
	if (RTC_ReadBackupRegister(RTC_BKP_DR0) != 0x9999)
	{
			
		//��������
		RTC_DateStructure.RTC_Year = 0x20;				//2020��
		RTC_DateStructure.RTC_Month = RTC_Month_March;	//3�·�
		RTC_DateStructure.RTC_Date = 0x23;				//��23��/23��/23��
		RTC_DateStructure.RTC_WeekDay = RTC_Weekday_Monday;//����һ
		RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);
		
		
		//����ʱ�� 14:15:30
		RTC_TimeStructure.RTC_H12     = RTC_H12_PM;
		RTC_TimeStructure.RTC_Hours   = 0x14;
		RTC_TimeStructure.RTC_Minutes = 0x15;
		RTC_TimeStructure.RTC_Seconds = 0x30; 
		RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);  
	}
	
	RTC_WakeUpCmd(DISABLE);
	
	//����ʱ��Դ��Ӳ��ʱ��Ƶ��Ϊ1Hz
	RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits);
	
	//ֻ����һ�μ���
	RTC_SetWakeUpCounter(0);

	//���RTC�����жϱ�־
	RTC_ClearITPendingBit(RTC_IT_WUT);
	
	RTC_WakeUpCmd(ENABLE);


	//�����жϵĴ�����ʽ�������ж�
	RTC_ITConfig(RTC_IT_WUT, ENABLE);
	
	
	RTC_ClearFlag(RTC_FLAG_WUTF);
	
	
	//RTC_AlarmCmd(RTC_Alarm_A,DISABLE);
	EXTI_ClearITPendingBit(EXTI_Line22);
	EXTI_InitStructure.EXTI_Line = EXTI_Line22;			//
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//RTC�ֲ�涨
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	//���ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	RTC_WriteBackupRegister(RTC_BKP_DR0, 0x9999);
	
}
void change_time(char *g_usart1_buf)
{
	
		char *p=NULL;
		uint8_t duty;
		if(strstr((const char *)g_usart1_buf,"DATE"))
		{
			p=strtok(g_usart1_buf,"-");
			p=strtok(NULL,"-");
			duty = atoi(p)-2000;
			RTC_DateStructure.RTC_Year = duty/10*16+duty%10;
			p=strtok(NULL,"-");
			duty = atoi(p);
			RTC_DateStructure.RTC_Month = duty/10*16+duty%10;
			p=strtok(NULL,"-");
			duty = atoi(p);
			RTC_DateStructure.RTC_Date = duty/10*16+duty%10;
			p=strtok(NULL,"-");
			duty = atoi(p);
			RTC_DateStructure.RTC_WeekDay = duty;
			RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);
			printf("set DATE 20%x-%x-%x  %x ok\r\n",RTC_DateStructure.RTC_Year,RTC_DateStructure.RTC_Month,RTC_DateStructure.RTC_Date,RTC_DateStructure.RTC_WeekDay);

	    }
		if(strstr((const char *)g_usart1_buf,"TIME"))
		{
			p=strtok(g_usart1_buf,"-");
			p=strtok(NULL,"-");
			duty = atoi(p);
			RTC_TimeStructure.RTC_Hours = duty/10*16+duty%10;
			if(duty>=12)
			{
				RTC_TimeStructure.RTC_H12  = RTC_H12_PM;
			}
			else
			{
				RTC_TimeStructure.RTC_H12  = RTC_H12_AM;
			}
			p=strtok(NULL,"-");
			duty = atoi(p);
			RTC_TimeStructure.RTC_Minutes = duty/10*16+duty%10;
			p=strtok(NULL,"-");
			duty = atoi(p);	
			RTC_TimeStructure.RTC_Seconds = duty/10*16+duty%10;
			RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);  
			printf("set TIME %x::%x::%x ok\r\n ",RTC_TimeStructure.RTC_Hours,RTC_TimeStructure.RTC_Minutes,RTC_TimeStructure.RTC_Seconds);
	    }
}
void  rtc_alarm_a (char *buf)
{

	char *p;
	int duty;
	
	RTC_AlarmCmd(RTC_Alarm_A,DISABLE);
	p=strtok(buf,"-");
	p=strtok(NULL,"-");
	duty = atoi(p);
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours = duty/10*16+duty%10;
	if(duty>=12)
	{
		RTC_AlarmStructure.RTC_AlarmTime.RTC_H12  = RTC_H12_PM;
	}
	else
	{
		RTC_AlarmStructure.RTC_AlarmTime.RTC_H12  = RTC_H12_AM;
	}
	p=strtok(NULL,"-");
	duty = atoi(p);

	RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes= duty/10*16+duty%10;
	p=strtok(NULL,"-");
	duty = atoi(p);

	RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = duty/10*16+duty%10;

	/* Set the alarm A Masks */
	//RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours = 0x14;
	//RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes =0x15;
	//RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds =0x40;
	//RTC_AlarmStructure.RTC_AlarmTime.RTC_H12= RTC_H12_PM;
	RTC_AlarmStructure.RTC_AlarmDateWeekDay = 0x31;
	RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
	RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;
	RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);
	RTC_ITConfig(RTC_IT_ALRA, ENABLE);
	RTC_AlarmCmd(RTC_Alarm_A, ENABLE);
	RTC_ClearFlag(RTC_FLAG_ALRAF);
	//printf("set ALARM %x::%x::%x ok\r\n ",RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours,RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes,RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds);

	EXTI_ClearITPendingBit(EXTI_Line17);
	EXTI_InitStructure.EXTI_Line = EXTI_Line17;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/* Enable the RTC Alarm Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void  RTC_Alarm_IRQHandler(void)
{
	OS_ERR err;
	if(RTC_GetITStatus(RTC_IT_ALRA) != RESET) 
	{ 
		RTC_GetTime(RTC_Format_BCD, &RTC_TimeStructure); 
		//printf("%x::%x::%x \r\n ",RTC_TimeStructure.RTC_Hours,RTC_TimeStructure.RTC_Minutes,RTC_TimeStructure.RTC_Seconds);	
		OSFlagPost(&g_flag_grp,0x04,OS_OPT_POST_FLAG_SET,&err);	
		/* Disable the RTC Clock */
		/* Clear RTC AlarmA Flags */
		RTC_ClearITPendingBit(RTC_IT_ALRA);
		/* Clear the EXTI line 17 */
		EXTI_ClearITPendingBit(EXTI_Line17);
	}


}
void  RTC_WKUP_IRQHandler(void)
{

	OS_ERR err;
	//����־λ
	if(RTC_GetITStatus(RTC_IT_WUT) == SET)
	{
		//�����¼���־��
		OSFlagPost(&g_flag_grp,0x02,OS_OPT_POST_FLAG_SET,&err);		
		
		//��ձ�־λ	

		RTC_ClearITPendingBit(RTC_IT_WUT);
		EXTI_ClearITPendingBit(EXTI_Line22);
	}
}

