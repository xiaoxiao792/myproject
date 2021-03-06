#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "includes.h"
#include "dth11.h"
#include "sr04.h"
#include "beep.h"
#include "flame.h"
#include "ir.h"
#include "oled.h"
#include "zymq.h"
#include "rtc.h"
#include "keyboard.h"
#include "mifare522.h"
#include "dog.h"
#include "mpu6050.h"
#include "myiic.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "stdio.h"
#include "stdlib.h"

//����1
OS_TCB Task1_TCB;
void task1(void *parg);
CPU_STK task1_stk[128];			//����1�������ջ����СΪ128�֣�Ҳ����512�ֽ�

//����2
OS_TCB Task2_TCB;
void task2(void *parg);
CPU_STK task2_stk[128];

//����3
OS_TCB Task3_TCB;
void task3(void *parg);
CPU_STK task3_stk[128];

//����4
OS_TCB Task4_TCB;
void task4(void *parg);
CPU_STK task4_stk[128];

//����5
OS_TCB Task5_TCB;
void task5(void *parg);
CPU_STK task5_stk[128];

//����6
OS_TCB Task6_TCB;
void task6(void *parg);
CPU_STK task6_stk[128];

//����7
OS_TCB Task7_TCB;
void task7(void *parg);
CPU_STK task7_stk[128];

//����8
OS_TCB Task8_TCB;
void task8(void *parg);
CPU_STK task8_stk[128];

//����9
OS_TCB Task9_TCB;
void task9(void *parg);
CPU_STK task9_stk[128];

//����10
OS_TCB Task10_TCB;
void task10(void *parg);
CPU_STK task10_stk[128];

//����11
OS_TCB Task11_TCB;
void task11(void *parg);
CPU_STK task11_stk[128];

//����12
OS_TCB Task12_TCB;
void task12(void *parg);
CPU_STK task12_stk[1024];

OS_Q	g_queue;							//��Ϣ���еĶ���
		
OS_MUTEX	g_mutex_oled;					//�������Ķ���
OS_MUTEX	g_mutex_usart3;					//�������Ķ���
		
OS_FLAG_GRP	g_flag_grp;						//�¼���־��Ķ���

static RTC_TimeTypeDef  	RTC_TimeStructure;
static RTC_DateTypeDef  	RTC_DateStructure;

volatile uint8_t *send_data[10];			//Ҫ���͵�����;
volatile uint32_t save_data[64*200];

volatile uint8_t id_count=0;

//������
int main(void)
{
	OS_ERR err;
	
	iwdg_init();								//���ڿ��Ź���ʼ��
	TIM2_init();								//���Ź��ж�����
	systick_init();  							//ʱ�ӳ�ʼ��

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);						//�жϷ�������
	usart_init(115200);  				 		//���ڳ�ʼ��
	usart3_init(9600);							//�������ڳ�ʼ��
	
	bluetooth_config();							//������ʼ��
	OLED_Init();								//��ʼ��OLED
	
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
	{ 
		printf("IWDG RESET OK#\r\n");
		RCC_ClearFlag();
	}

	//OS��ʼ�������ǵ�һ�����еĺ���,��ʼ�����ֵ�ȫ�ֱ����������ж�Ƕ�׼����������ȼ����洢��
	OSInit(&err);

	//��������1
	OSTaskCreate(	(OS_TCB *)&Task1_TCB,									//������ƿ飬��ͬ���߳�id
					(CPU_CHAR *)"Task1",									//��������֣����ֿ����Զ����
					(OS_TASK_PTR)task1,										//����������ͬ���̺߳���
					(void *)0,												//���ݲ�������ͬ���̵߳Ĵ��ݲ���
					(OS_PRIO)6,												//��������ȼ�6		
					(CPU_STK *)task1_stk,									//�����ջ����ַ
					(CPU_STK_SIZE)128/10,									//�����ջ�����λ���õ����λ�ã��������ټ���ʹ��
					(CPU_STK_SIZE)128,										//�����ջ��С			
					(OS_MSG_QTY)0,											//��ֹ������Ϣ����
					(OS_TICK)0,												//Ĭ��ʱ��Ƭ����																
					(void  *)0,												//����Ҫ�����û��洢��
					(OS_OPT)OS_OPT_TASK_NONE,								//û���κ�ѡ��
					&err													//���صĴ�����
				);

	//��������2
	OSTaskCreate(	(OS_TCB *)&Task2_TCB,
					(CPU_CHAR *)"Task2",
					(OS_TASK_PTR)task2,
					(void *)0,
					(OS_PRIO)6,
					(CPU_STK *)task2_stk,
					(CPU_STK_SIZE)128/10,
					(CPU_STK_SIZE)128,
					(OS_MSG_QTY)0,
					(OS_TICK)0,						
					(void  *)0,
					(OS_OPT)OS_OPT_TASK_NONE,
					&err
				);
	
	//��������3
	OSTaskCreate(	(OS_TCB *)&Task3_TCB,
					(CPU_CHAR *)"Task3",
					(OS_TASK_PTR)task3,
					(void *)0,
					(OS_PRIO)6,
					(CPU_STK *)task3_stk,
					(CPU_STK_SIZE)128/10,
					(CPU_STK_SIZE)128,
					(OS_MSG_QTY)0,
					(OS_TICK)0,			
					(void  *)0,
					(OS_OPT)OS_OPT_TASK_NONE,
					&err
				);
	
	//��������4
	OSTaskCreate(	(OS_TCB *)&Task4_TCB,
					(CPU_CHAR *)"Task4",
					(OS_TASK_PTR)task4,
					(void *)0,
					(OS_PRIO)6,
					(CPU_STK *)task4_stk,
					(CPU_STK_SIZE)128/10,
					(CPU_STK_SIZE)128,
					(OS_MSG_QTY)0,
					(OS_TICK)0,
					(void  *)0,
					(OS_OPT)OS_OPT_TASK_NONE,
					&err
				);
	
	//��������5
	OSTaskCreate(	(OS_TCB *)&Task5_TCB,
					(CPU_CHAR *)"Task5",
					(OS_TASK_PTR)task5,
					(void *)0,
					(OS_PRIO)6,
					(CPU_STK *)task5_stk,
					(CPU_STK_SIZE)128/10,
					(CPU_STK_SIZE)128,
					(OS_MSG_QTY)0,
					(OS_TICK)0,						
					(void  *)0,
					(OS_OPT)OS_OPT_TASK_NONE,
					&err
			);
	
	//��������6
	OSTaskCreate(	(OS_TCB *)&Task6_TCB,		
					(CPU_CHAR *)"Task6",					
					(OS_TASK_PTR)task6,						
					(void *)0,										
					(OS_PRIO)6,										
					(CPU_STK *)task6_stk,					
					(CPU_STK_SIZE)128/10,					
					(CPU_STK_SIZE)128,						
					(OS_MSG_QTY)0,								
					(OS_TICK)0,										
					(void  *)0,										
					(OS_OPT)OS_OPT_TASK_NONE,			
					&err													
				);
		
	//��������7
	OSTaskCreate(	(OS_TCB *)&Task7_TCB,	
					(CPU_CHAR *)"Task7",				
					(OS_TASK_PTR)task7,					
					(void *)0,									
					(OS_PRIO)6,									
					(CPU_STK *)task7_stk,				
					(CPU_STK_SIZE)128/10,				
					(CPU_STK_SIZE)128,					
					(OS_MSG_QTY)0,							
					(OS_TICK)0,									
					(void  *)0,									
					(OS_OPT)OS_OPT_TASK_NONE,		
					&err												
				);	
					
	//��������8
	OSTaskCreate(	(OS_TCB *)&Task8_TCB,	
					(CPU_CHAR *)"Task8",				
					(OS_TASK_PTR)task8,					
					(void *)0,									
					(OS_PRIO)6,									
					(CPU_STK *)task8_stk,				
					(CPU_STK_SIZE)128/10,				
					(CPU_STK_SIZE)128,					
					(OS_MSG_QTY)0,							
					(OS_TICK)0,									
					(void  *)0,									
					(OS_OPT)OS_OPT_TASK_NONE,		
					&err												
				);	
					
	//��������9
	OSTaskCreate(	(OS_TCB *)&Task9_TCB,	
					(CPU_CHAR *)"Task9",				
					(OS_TASK_PTR)task9,					
					(void *)0,									
					(OS_PRIO)6,									
					(CPU_STK *)task9_stk,				
					(CPU_STK_SIZE)128/10,				
					(CPU_STK_SIZE)128,					
					(OS_MSG_QTY)0,							
					(OS_TICK)0,									
					(void  *)0,									
					(OS_OPT)OS_OPT_TASK_NONE,		
					&err												
				);	
					
	//��������10
	OSTaskCreate(	(OS_TCB *)&Task10_TCB,
					(CPU_CHAR *)"Task10",				
					(OS_TASK_PTR)task10,				
					(void *)0,									
					(OS_PRIO)6,									
					(CPU_STK *)task10_stk,			
					(CPU_STK_SIZE)128/10,				
					(CPU_STK_SIZE)128,					
					(OS_MSG_QTY)0,							
					(OS_TICK)0,									
					(void  *)0,									
					(OS_OPT)OS_OPT_TASK_NONE,		
					&err												
				);
					
	//��������11
	OSTaskCreate(	(OS_TCB *)&Task11_TCB,
					(CPU_CHAR *)"Task11",				
					(OS_TASK_PTR)task11,				
					(void *)0,									
					(OS_PRIO)6,									
					(CPU_STK *)task11_stk,			
					(CPU_STK_SIZE)128/10,				
					(CPU_STK_SIZE)128,					
					(OS_MSG_QTY)0,							
					(OS_TICK)0,									
					(void  *)0,									
					(OS_OPT)OS_OPT_TASK_NONE,		
					&err												
				);	
					
	//��������12
	OSTaskCreate(	(OS_TCB *)&Task12_TCB,
					(CPU_CHAR *)"Task12",				
					(OS_TASK_PTR)task12,				
					(void *)0,									
					(OS_PRIO)6,									
					(CPU_STK *)task12_stk,			
					(CPU_STK_SIZE)1024/10,			
					(CPU_STK_SIZE)1024,					
					(OS_MSG_QTY)0,							
					(OS_TICK)0,									
					(void  *)0,									
					(OS_OPT)OS_OPT_TASK_NONE,		
					&err												
				);
					
	//�����¼���־�飬���б�־λ��ֵΪ0
	OSFlagCreate(&g_flag_grp,"g_flag_grp",0,&err);	
					
	//����������
	OSMutexCreate(&g_mutex_oled,"g_mutex_olde",&err);
	OSMutexCreate(&g_mutex_usart3,"g_mutex_usart3",&err);
	
	//������Ϣ����
	OSQCreate(&g_queue,"g_queue",16,&err);

	//����OS�������������
	OSStart(&err);
				
	printf("never run.......\r\n");
					
	while(1);
}
void task1(void *parg)//��ʾʱ��
{
	OS_ERR err;
	
	OS_FLAGS flags=0;
	uint8_t buf[16]={0};

	rtc_init();//��ʼ��rtcʱ��
	printf("task1 is create ok\r\n");

	while(1)
	{
				//һֱ�����ȴ��¼���־��bit0��1���ȴ��ɹ��󣬽�bit0��0
		flags=OSFlagPend(&g_flag_grp,0x02,0,OS_OPT_PEND_FLAG_SET_ANY + OS_OPT_PEND_FLAG_CONSUME+OS_OPT_PEND_BLOCKING,NULL,&err);
		if(err != OS_ERR_NONE)
		{
			printf("[task1][OSFlagPend]Error Code = %d\r\n",err);
			continue;
		}
			
		if(flags & 0x02)
		{
			//RTC_GetTime����ȡʱ��
			RTC_GetTime(RTC_Format_BCD, &RTC_TimeStructure); 
			//��ʽ���ַ���
			sprintf((char *)buf,"%02x:%02x:%02x",RTC_TimeStructure.RTC_Hours,RTC_TimeStructure.RTC_Minutes,RTC_TimeStructure.RTC_Seconds);
			//�����ȴ�������
			OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);			
						
			//oled��ʾʱ��;
			OLED_ShowString(32,6,buf);
			//�ͷŻ�����
			OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
		}
	}
}

void task2(void *parg)//���洫����
{
	OS_ERR err;
	uint32_t adc_val;
	uint32_t adc_vol;
	int i;
	uint32_t num=0;
	uint8_t buf[16];
	//�ǵ��޸�adc����
	adc_falame_init();
	
	EXIT9_init();
	
	//����ADC1�Ĺ���
	ADC_SoftwareStartConv(ADC1);
	
	printf("task2 is create ok\r\n");

	while(1)
	{
		num=0;
		for(i=0;i<1000;i++)
		{
			//�ȴ�ADC1ת������
			while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
			ADC_ClearFlag(ADC1,ADC_FLAG_EOC);
			
			//��ȡת�����
			adc_val = ADC_GetConversionValue(ADC1);
			
			//�����ֵת��Ϊ��ѹֵ
			adc_vol = adc_val * 3300 /4095;
			num+=adc_vol;
		
		}
		//printf("falame adc vol = %dmv\r\n",num/1000);
		
		if((num/1000)<=2000)
		{
			memset(buf,' ',16);
			
			//�����ȴ�������
			OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
			OLED_ShowString(0,4,buf);
			OLED_ShowCHinese(32,4,0);//��
			OLED_ShowCHinese(48,4,1);//��
			OLED_ShowCHinese(64,4,2);//Ԥ
			OLED_ShowCHinese(80,4,3);//��			

			//�ͷŻ�����
			OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
			memset(buf,'\0',16);
			sprintf((char *)buf,"F:YES");
		}
		else
		{
			memset(buf,'\0',16);
			sprintf((char *)buf,"F:NO");
		}
		send_data[1]=buf;
		delay_ms(1000);
	}

}
void task3(void *parg)//��ʪ��
{
	OS_ERR err;
	uint8_t data[5];
	int32_t rel;
	uint8_t buf[16];

	humiture_init();
	printf("task3 is create ok\r\n");

	while(1)
	{
		rel=humiture_get_distance(data);	
		if(rel<0)
		{
			//printf("��ȡʧ��,������Ϊ%d\r\n",rel);
		}
		else
		{
			//printf("ʪ��%d.%d,�¶�%d.%d\n",data[0],data[1],data[2],data[3]);
			sprintf((char *)buf,"T:%02d.%d,H:%02d.%d",data[2],data[3],data[0],data[1]);
			send_data[0]=buf;
			//�����ȴ�������
			OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);	
			
			OLED_ShowString(16,0,buf);		

			//�ͷŻ�����
			OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
		}
		delay_ms(6000);
	}
}
void task4(void *parg)//��ȼ��
{
	OS_ERR err;
	uint8_t buf[16];
	uint32_t adc_val;
	uint32_t adc_vol;
	int i;
	uint32_t num=0;
	
	//�ǵ��޸�adc����
	adc_zymq_init();
	
	EXIT7_init();
	
	//����ADC2�Ĺ���
	ADC_SoftwareStartConv(ADC2);
	
	printf("task4 is create ok\r\n");
	OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
	OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
	while(1)
	{
		num=0;
		for(i=0;i<1000;i++)
		{
			//�ȴ�ADC1ת������
			while(ADC_GetFlagStatus(ADC2,ADC_FLAG_EOC)==RESET);
			ADC_ClearFlag(ADC2,ADC_FLAG_EOC);
			
			//��ȡת�����
			adc_val = ADC_GetConversionValue(ADC2);
			
			//�����ֵת��Ϊ��ѹֵ
			adc_vol = adc_val * 3300 /4095;
			num+=adc_vol;
		}
		//printf("zymq adc vol = %dmv\r\n",num/1000);
		sprintf((char *)buf,"C:%03d",num/1000*100/3300);
		if(num/1000>=3000)
		{
			OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
			OLED_ShowCHinese(24,4,4);//��
			OLED_ShowCHinese(40,4,5);//Ȼ
			OLED_ShowCHinese(56,4,6);//��
			OLED_ShowCHinese(72,4,2);//Ԥ
			OLED_ShowCHinese(88,4,3);//��	
			OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
		}
		send_data[2]=buf;
		strcat((char *)send_data[2],"%");
		OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
		OLED_ShowChar(72,2,',');
		OLED_ShowString(80,2,buf);
				
		OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
		
		delay_ms(1000);
	}
}
void task5(void *parg)//���շ��͵���Ϣ
{
	//����CPU״̬����
	CPU_SR_ALLOC();
	OS_ERR err;
	int8_t i,j;
	OS_MSG_SIZE msg_size;
	//int32_t i;
	char *p=NULL;
	int32_t id=0;
	int8_t num=0;
	u8 buf[16];
	u8 save_buf[64];
	memset(buf,' ',16);
	printf("task5 is create ok\r\n");

	while(1)
	{
		p=OSQPend(&g_queue,0,OS_OPT_PEND_BLOCKING,&msg_size,NULL,&err);
		printf("p=%s\r\n",p);
		if(p && msg_size)
		{
			if(strstr((const char *)p,"DATE"))
			{
				change_time(p);
				//�����ȴ�������
				OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);	
				OLED_ShowString(0,4,buf);
				OLED_ShowString(32,4,"set data");

				//�ͷŻ�����
				OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
				//�����ȴ�������
				OSMutexPend(&g_mutex_usart3,0,OS_OPT_PEND_BLOCKING,NULL,&err);
				usart3_send_str("set data ok\r\n");
				OSMutexPost(&g_mutex_usart3,OS_OPT_POST_NONE,&err);
			}
			else if(strstr((const char *)p,"TIME"))
			{
				change_time(p);
					//�����ȴ�������
				OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);	
				OLED_ShowString(0,4,buf);
				OLED_ShowString(32,4,"set time \0");

				//�ͷŻ�����
				OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
				OSMutexPend(&g_mutex_usart3,0,OS_OPT_PEND_BLOCKING,NULL,&err);
				usart3_send_str("set time ok\r\n");
				OSMutexPost(&g_mutex_usart3,OS_OPT_POST_NONE,&err);
			}
			else if(strstr((const char *)p,"ALARM"))
			{
				rtc_alarm_a(p);
							//�����ȴ�������
				OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);	
				OLED_ShowString(0,4,buf);
				OLED_ShowString(32,4,"set alarm ");

				//�ͷŻ�����
				OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
				OSMutexPend(&g_mutex_usart3,0,OS_OPT_PEND_BLOCKING,NULL,&err);
				usart3_send_str("set alarm ok\r\n");
				OSMutexPost(&g_mutex_usart3,OS_OPT_POST_NONE,&err);
			}
			else if(strstr((const char *)p,"QUERY"))
			{

				OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);	
				OLED_ShowString(0,4,buf);
				OLED_ShowString(32,4,"query ok");

				//�ͷŻ�����
				OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
				OSMutexPend(&g_mutex_usart3,0,OS_OPT_PEND_BLOCKING,NULL,&err);
				for(i=0;i<4;i++)
				{
					strcat((char *)send_data[i],"\n\r");
					usart3_send_str((char *)send_data[i]);
				}
				OSMutexPost(&g_mutex_usart3,OS_OPT_POST_NONE,&err);
			}
			else if(strstr((const char *)p,"DISTANCE"))
			{
				memset((char *)save_data,'\0',64*200);
				p=strtok(p,"-");
				p=strtok(NULL,"-");
				//printf("p=%d\r\n",atoi(p));
				for(i=0;i<2*200;i++)
				{
					save_data[i] = *(volatile uint32_t *)(0x08020000+i*4);
					if(save_data[i]==0xffffffff)
					{
						break;
					}
				}
				printf("save_data[0]==%d\r\n",save_data[0]);
				save_data[0]=atoi(p);
				//printf("read flash addr at 0x08010000,data is 0x%x\r\n",d);
;
				//���д����������FLASH
				FLASH_Unlock();
				//�����ٽ�������ǰ��ʹ�ù��ж�
				OS_CRITICAL_ENTER();
				
				if(FLASH_COMPLETE!=FLASH_EraseSector(FLASH_Sector_5,VoltageRange_3))
				{
					printf("FLASH_EraseSector fail\r\n");
					while(1);								
				}
				for(i=0;save_data[i]!=0xffffffff;i++)
				{
					//������4�׵�ַ(0x08010000)д������(0x12345678)
					if(FLASH_COMPLETE!=FLASH_ProgramWord(0x08020000+4*i,save_data[i]))
					{
						printf("FLASH_ProgramWord fail\r\n");
						while(1);	
					
					}
				}
				//�˳��ٽ���,�������ж�
				OS_CRITICAL_EXIT(); 
				//���д����������FLASH
				FLASH_Lock();
; 
				OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);	
				OLED_ShowString(0,4,buf);
				OLED_ShowString(32,4,"set D");

				//�ͷŻ�����
				OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
				OSMutexPend(&g_mutex_usart3,0,OS_OPT_PEND_BLOCKING,NULL,&err);
				usart3_send_str("set D ok\r\n");
				OSMutexPost(&g_mutex_usart3,OS_OPT_POST_NONE,&err);
				
			}
			else if(strstr((const char *)p,"ID"))
			{
				memset((char *)save_data,'\0',64*200);
				p=strtok(p,"-");
				p=strtok(NULL,"-");
				///printf("p=%s\r\n",p);
				for(i=0;p[i]!='#';i++)
				{
					if(p[i]>='0'&&p[i]<='9')
					{
						num=(p[i]-'0');
					}
					else if(p[i]>='a'&&p[i]<='z')
					{
						num=(p[i]-'a')+10;
					}
					else
					{
						num=(p[i]-'A')+10;
					}
					printf("num=%d\r\n",num);
					id|=num<<4*(5-i);
				}
				//printf("id=0x%x\r\n",id);
				for(i=0;i<2*200;i++)
				{
					save_data[i] = *(volatile uint32_t *)(0x08020000+i*4);
					if(save_data[i]==0xffffffff)
					{
						break;
					}
				}
				//printf("save_data[1]==%x\r\n",save_data[1]);
				save_data[1]=id;
				//���д����������FLASH
				FLASH_Unlock();
				//�����ٽ�������ǰ��ʹ�ù��ж�
				OS_CRITICAL_ENTER();
				
				if(FLASH_COMPLETE!=FLASH_EraseSector(FLASH_Sector_5,VoltageRange_3))
				{
					printf("FLASH_EraseSector fail\r\n");
					while(1);								
				}
				for(i=0;save_data[i]!=0xffffffff;i++)
				{
					//������4�׵�ַ(0x08010000)д������(0x12345678)
					if(FLASH_COMPLETE!=FLASH_ProgramWord(0x08020000+4*i,save_data[i]))
					{
						printf("FLASH_ProgramWord fail\r\n");
						while(1);	
					
					}
				}	
				//�˳��ٽ���,�������ж�
				OS_CRITICAL_EXIT() ;
				//���д����������FLASH
				FLASH_Lock();
				OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);	
				OLED_ShowString(0,4,buf);
				OLED_ShowString(32,4,"set id");

				//�ͷŻ�����
				OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
				OSMutexPend(&g_mutex_usart3,0,OS_OPT_PEND_BLOCKING,NULL,&err);
				usart3_send_str("set ID ok\r\n");
				OSMutexPost(&g_mutex_usart3,OS_OPT_POST_NONE,&err);
			}
			else if(strstr((const char *)p,"SHOW"))
			{
				
				for(j=0;j<100;j++)
				{

					for(i=0;i<64;)
					{
						*(uint32_t *)&save_buf[i] = *(volatile uint32_t *)(0x08020008+i+j*64);
						i+=4;
					}
					if(!strstr((const char *)save_buf,"\n"))
					{
						break;
					}
					OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
					OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
					OSMutexPend(&g_mutex_usart3,0,OS_OPT_PEND_BLOCKING,NULL,&err);
					usart3_send_str((char *)save_buf);
					OSMutexPost(&g_mutex_usart3,OS_OPT_POST_NONE,&err);
					printf("buf=%s\r\n",save_buf);
				}
				OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
				OLED_ShowString(0,4,buf);
				OLED_ShowString(32,4,"show ok");

				//�ͷŻ�����
				OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);


			}
			else if(strstr((const char *)p,"CLEAR"))
			{
				memset((char *)save_data,'\0',64*200);

				save_data[0] = *(volatile uint32_t *)(0x08020000);
				save_data[1] = *(volatile uint32_t *)(0x08020000+4);
				//���д����������FLASH
				FLASH_Unlock();
				//�����ٽ�������ǰ��ʹ�ù��ж�
				OS_CRITICAL_ENTER();
				
				if(FLASH_COMPLETE!=FLASH_EraseSector(FLASH_Sector_5,VoltageRange_3))
				{
					printf("FLASH_EraseSector fail\r\n");
					while(1);								
				}
				//������4�׵�ַ(0x08010000)д������(0x12345678)
				if(FLASH_COMPLETE!=FLASH_ProgramWord(0x08020000,save_data[0]))
				{
					printf("FLASH_ProgramWord fail\r\n");
					while(1);	
				
				}
				
				//������4 0x08010000 д������(0xAABBCCDD)
				if(FLASH_COMPLETE!=FLASH_ProgramWord(0x08020004,save_data[1]))
				{
					printf("FLASH_ProgramWord fail\r\n");
					while(1);	
				
				}	
	
				//�˳��ٽ���,�������ж�
				OS_CRITICAL_EXIT() ;
				//���д����������FLASH
				FLASH_Lock();
				OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);	
				OLED_ShowString(0,4,buf);
				OLED_ShowString(32,4,"clear ok");

				//�ͷŻ�����
				OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
				OSMutexPend(&g_mutex_usart3,0,OS_OPT_PEND_BLOCKING,NULL,&err);
				usart3_send_str("clear ok\r\n");
				OSMutexPost(&g_mutex_usart3,OS_OPT_POST_NONE,&err);
				id_count=0;
			}
			memset(p,0,msg_size);

		}
	}
}
void task6(void *parg)//����
{
	OS_ERR err;
	
	OS_FLAGS flags=0;
	
	int32_t ret=0;
	uint8_t data[4];
	uint32_t compare3=100;
	u8 buf[16];
	memset(buf,' ',16);
	printf("task6 is create ok\r\n");
	infrared_init();

	TIM1_PWM_init();//��ʼ��TM1���PWM


	while(1)
	{

		//һֱ�����ȴ��¼���־��bit0/bit1��1���ȴ��ɹ��󣬽�bit0/bit1��0
		flags=OSFlagPend(&g_flag_grp,0x01,0,OS_OPT_PEND_FLAG_SET_ANY + OS_OPT_PEND_FLAG_CONSUME+OS_OPT_PEND_BLOCKING,NULL,&err);
				
		if(err != OS_ERR_NONE)
		{
			printf("[task1][OSFlagPend]Error Code = %d\r\n",err);
			
			continue;
		}
		if(flags & 0x01)
		{

				ret=infrared_get_distance(data);	
				if(ret ==0)
				{
						printf("%x,%x,%x,%x\n\r",data[0],data[1],data[2],data[3]);
						OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
						OLED_ShowString(0,4,buf);
						OLED_ShowCHinese(32,4,7);//��
						OLED_ShowCHinese(48,4,8);//��
						OLED_ShowCHinese(64,4,9);//��
						OLED_ShowCHinese(80,4,10);//��

						OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
					if(data[2]==0x07)
					{
						
						compare3+=5;
						if(compare3>100)
						{
							compare3=100;
						}
						printf("compare3=%d\n\r",compare3);
						TIM_SetCompare3(TIM1, compare3);
					}
					else if(data[2]==0x15)
					{
						//printf("%x,%x,%x,%x\n\r",data[0],data[1],data[2],data[3]);
						compare3-=5;
						if(compare3<1)
						{
							compare3=0;
						}
						printf("compare3=%d\n\r",compare3);
						TIM_SetCompare3(TIM1, compare3);
					}
				}

		
		}

		
	}
}
void task7(void *parg)//������ģ��
{
	uint8_t buf[16];
	int32_t d=0;
	uint32_t max_d=0;
	OS_ERR err;

	printf("task7 is create ok\r\n");
	//������ģ���ʼ��
	sr04_init();
	OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);

	OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
	while(1)
	{
		d = sr04_get_distance();
		if(d < 0)
		{
			//printf("sr04 get distance fail,error code = %d\r\n",d);
		
		}
		else
		{
			//printf("sr04 get distance %dmm\r\n",d);
			max_d=*(volatile uint32_t *)(0x08020000);
			if(d<max_d)
			{
				OSFlagPost(&g_flag_grp,0x10,OS_OPT_POST_FLAG_SET,&err);	
			}
			else
			{
				OSFlagPost(&g_flag_grp,0x20,OS_OPT_POST_FLAG_SET,&err);	
			}
			sprintf((char *)buf,"D:%04dmm",d);
			send_data[3]=buf;
			//�����ȴ�������
			OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
			OLED_ShowString(4,2,buf);		

			//�ͷŻ�����
			OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
		
		}
		delay_ms(1000);
	}
}
void task8(void *parg)//��Ĥ����
{

	OS_ERR err;
	int8_t i;
	u8 buf[16]={0};
	u8 clear[17];
	int32_t count=0;
	char save_buf[64];
	printf("task8 is create ok\r\n");
	keyboard_init();//��ʼ����Ĥ����
	memset(clear,'\0',17);
	memset(clear,' ',16);
	while(1)
	{
		for(i=0;i<4;i++)
		{
			switch(i)
			{
				case 0:PDout(4)=0;break;
				case 1:PDout(14)=0;break;
				case 2:PDout(0)=0;break;
				case 3:PEout(7)=0;break;
			}


			if(PEin(9)==0)
			{
					delay_ms(50);
					
					if(PEin(9) == 0)
					{
						OSFlagPost(&g_flag_grp,0x08,OS_OPT_POST_FLAG_SET,&err);
						//�ȴ������ͷ�
						while(PEin(9) == 0)
						{
							delay_ms(1);
						}

						switch(i)
						{
							case 0:
								//printf("D\r\n");
								buf[count++]='D';
								OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
								OLED_ShowString(0,4,clear);
								OLED_ShowString(40,4,buf);
								OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
								break;
							case 1:
								//printf("#\r\n");
								//printf("buf==%s\r\n",buf);
								RTC_GetDate(RTC_Format_BCD,&RTC_DateStructure);
								// ��ȡʱ��
								RTC_GetTime(RTC_Format_BCD, &RTC_TimeStructure);
								id_count++;
								if(!strcmp((char *)buf,"123456"))
								{
									PFout(9)=0;
									OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
									OLED_ShowString(0,4,clear);
									OLED_ShowCHinese(32,4,16);//��
									OLED_ShowCHinese(48,4,17);//��
									OLED_ShowCHinese(64,4,18);//��
									OLED_ShowCHinese(80,4,19);//ȷ
									OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
									sprintf((char *)save_buf,"[%03d]20%02x/%02x/%02x Week:%x %02x:%02x:%02x password  1\r\n", \
											id_count,\
											RTC_DateStructure.RTC_Year, RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Date,RTC_DateStructure.RTC_WeekDay,\
											RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds);
									//printf("save_buf==%s\r\n",save_buf);
								}
								else
								{
									OSFlagPost(&g_flag_grp,0x40,OS_OPT_POST_FLAG_SET,&err);
									PFout(9)=1;
									OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
									OLED_ShowString(0,4,clear);
									OLED_ShowCHinese(32,4,16);//��
									OLED_ShowCHinese(48,4,17);//��
									OLED_ShowCHinese(64,4,20);//��
									OLED_ShowCHinese(80,4,21);//��
									OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
									sprintf((char *)save_buf,"[%03d]20%02x/%02x/%02x Week:%x %02x:%02x:%02x password  0\r\n", \
											id_count,\
											RTC_DateStructure.RTC_Year, RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Date,RTC_DateStructure.RTC_WeekDay,\
											RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds);
									//printf("save_buf==%s\r\n",save_buf);
								}
								if(id_count<=100)
								{
										//���д����������FLASH
									FLASH_Unlock();
									for(i=0;i<64;)
									{
										if(FLASH_COMPLETE!=FLASH_ProgramWord(0x08020000+8+i+(id_count-1)*64,*(uint32_t *)&save_buf[i]))
										{
											printf("FLASH_ProgramWord fail\r\n");
											while(1);					
										}
										i+=4;
									}
									//���д����������FLASH
									FLASH_Lock();
								}
								count=0;
								memset(buf,'\0',16);
								break;
							case 2:
								//printf("0\r\n");
								buf[count++]='0';
								OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
								OLED_ShowString(0,4,clear);
								OLED_ShowString(40,4,buf);
								OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
								break;
							case 3:
								//printf("*\r\n");
								buf[count++]='*';
								OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
								OLED_ShowString(0,4,clear);
								OLED_ShowString(40,4,buf);
								OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
								break;
						}
					}
			
			}
			if(PEin(11)==0)
			{
				delay_ms(50);
					
					if(PEin(11) == 0)
					{
						//printf("flag group bit0 set ok,key1 happend\r\n");
						OSFlagPost(&g_flag_grp,0x08,OS_OPT_POST_FLAG_SET,&err);
						//�ȴ������ͷ�
						while(PEin(11) == 0)
						{
							delay_ms(1);
						}
						switch(i)
						{
							case 0:
								//printf("C\r\n");
								buf[count++]='C';
								OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
								OLED_ShowString(0,4,clear);
								OLED_ShowString(40,4,buf);
								OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
								break;
							case 1:
								//printf("9\r\n");
								buf[count++]='9';
								OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
								OLED_ShowString(0,4,clear);
								OLED_ShowString(40,4,buf);
								OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
								break;
							case 2:
								//printf("8\r\n");
								buf[count++]='8';
								OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
								OLED_ShowString(0,4,clear);
								OLED_ShowString(40,4,buf);
								OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
								break;
							case 3:
								//printf("7\r\n");
								buf[count++]='7';
								OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
								OLED_ShowString(0,4,clear);
								OLED_ShowString(40,4,buf);
								OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
								break;
						}
							


					}
			
			}
			if(PEin(15)==0)
			{
				delay_ms(50);
					
					if(PEin(15) == 0)
					{
						//printf("flag group bit0 set ok,key1 happend\r\n");
						OSFlagPost(&g_flag_grp,0x08,OS_OPT_POST_FLAG_SET,&err);	
						//�ȴ������ͷ�
						while(PEin(15) == 0)
						{
							delay_ms(1);
						}
			
						switch(i)
						{
							case 0:
								//printf("B\r\n");
								buf[count++]='B';
								OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
								OLED_ShowString(0,4,clear);
								OLED_ShowString(40,4,buf);
								OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
								break;
							case 1:
								//printf("6\r\n");
								buf[count++]='6';
								OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
								OLED_ShowString(0,4,clear);
								OLED_ShowString(40,4,buf);
								OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
								break;
							case 2:
								//printf("5\r\n");
								buf[count++]='5';
								OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
								OLED_ShowString(0,4,clear);
								OLED_ShowString(40,4,buf);
								OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
								break;
							case 3:
								//printf("4\r\n");
								buf[count++]='4';
								OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
								OLED_ShowString(0,4,clear);
								OLED_ShowString(40,4,buf);
								OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
								break;
						}
						

					}
			}
			if(PDin(9)==0)
			{
				delay_ms(50);
					
					if(PDin(9)== 0)
					{
						//printf("flag group bit0 set ok,key1 happend\r\n");
						
						//�ȴ������ͷ�
						while(PDin(9)== 0)
						{
							delay_ms(1);
						}
						OSFlagPost(&g_flag_grp,0x08,OS_OPT_POST_FLAG_SET,&err);	
						switch(i)
						{
							case 0:
								//printf("A\r\n");
								buf[count++]='A';
								OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
								OLED_ShowString(0,4,clear);
								OLED_ShowString(40,4,buf);
								OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
								break;
							case 1:
								//printf("3\r\n");
								buf[count++]='3';
								OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
								OLED_ShowString(0,4,clear);
								OLED_ShowString(40,4,buf);
								OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
								break;
							case 2:
								//printf("2\r\n");
								buf[count++]='2';
								OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
								OLED_ShowString(0,4,clear);
								OLED_ShowString(40,4,buf);
								OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
								break;
							case 3:
								//printf("1\r\n");
								buf[count++]='1';
								OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
								OLED_ShowString(0,4,clear);
								OLED_ShowString(40,4,buf);
								OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
								break;
						}

					}
			}
			switch(i)
			{
				case 0:PDout(4)=1;break;
				case 1:PDout(14)=1;break;
				case 2:PDout(0)=1;break;
				case 3:PEout(7)=1;break;
			}
		}
		delay_ms(1);
	
	}
}
void task9(void *parg)//RFIDģ��
{
	char buf[64];
	int8_t i,j;

#if 0
	//���д����������FLASH
	FLASH_Unlock();


	if(FLASH_COMPLETE!=FLASH_EraseSector(FLASH_Sector_5,VoltageRange_3))
	{
		printf("FLASH_EraseSector fail\r\n");
		while(1);								
	}

	//������4�׵�ַ(0x08010000)д������(0x12345678)
	if(FLASH_COMPLETE!=FLASH_ProgramWord(0x08020000,100))
	{
		printf("FLASH_ProgramWord fail\r\n");
		while(1);	
	
	}

	//������4 0x08010000 д������(0xAABBCCDD)
	if(FLASH_COMPLETE!=FLASH_ProgramWord(0x08020004,0x77de41))
	{
		printf("FLASH_ProgramWord fail\r\n");
		while(1);	
	
	}	
	
	//���д����������FLASH
	FLASH_Lock();
#endif
	printf("task9 is create ok\r\n");
	uart2_init(9600);

	for(j=0;j<100;j++)
	{
		for(i=0;i<64;)
		{
			*(uint32_t *)&buf[i] = *(volatile uint32_t *)(0x08020000+8+i+j*64);
			i+=4;
		}
		if(!strstr((const char *)buf,"\n"))
			break;
		else
		{
			id_count++;
		}
		//printf("buf=%s\r\n",buf);
	}

	while(1)
	{

		
		//printf("Ѱ��\r\n");
		mifare522Request();
		delay_ms(1000);
		
	}
}
void task10(void *parg)//������ģ��
{

	OS_ERR err;
	OS_FLAGS flags=0;
	int32_t i;
	beep_init();//��ʼ��������
	printf("task10 is create ok\r\n");


	while(1)
	{
		flags=OSFlagPend(&g_flag_grp,0x04|0x08|0x40|0x80|0x100,0,OS_OPT_PEND_FLAG_SET_ANY + OS_OPT_PEND_FLAG_CONSUME+OS_OPT_PEND_BLOCKING,NULL,&err);
		
		
		if(err != OS_ERR_NONE)
		{
			printf("[task1][OSFlagPend]Error Code = %d\r\n",err);
			
			continue;
		}	
		if(flags & 0x04)
		{

			for(i=0;i<6;i++)
			{
				PFout(8)=1;
				delay_ms(80);
				PFout(8)=0;
				delay_ms(80);
				PFout(8)=1;
				delay_ms(80);
				PFout(8)=0;
				delay_ms(500);
				
			}
		
		}
		else if(flags & 0x08)
		{

			PFout(8)=1;
			delay_ms(100);
			PFout(8)=0;

		}
		else if(flags & 0x40)
		{

			PFout(8)=1;
			delay_ms(1000);
			PFout(8)=0;

		}
		else if(flags & 0x80)
		{

			PFout(8)=1;


		}
		else if(flags & 0x100)
		{

			PFout(8)=0;
	
		}
	}
}
void task11(void *parg)//LEDģ��
{

	OS_ERR err;
	OS_FLAGS flags=0;
	int32_t i;
	LED_Init();			//��ʼ��LED
	printf("task11 is create ok\r\n");


	while(1)
	{
		flags=OSFlagPend(&g_flag_grp,0x10|0x20,0,OS_OPT_PEND_FLAG_SET_ANY + OS_OPT_PEND_FLAG_CONSUME+OS_OPT_PEND_BLOCKING,NULL,&err);
		
		
		if(err != OS_ERR_NONE)
		{
			printf("[task1][OSFlagPend]Error Code = %d\r\n",err);
			
			continue;
		}
		if(flags & 0x10)
		{
			for(i=0;i<5;i++)
			{
				PEout(14)=0;
				delay_ms(100);
				PEout(14)=1;
				delay_ms(100);
			}

		}
		else if(flags & 0x20)
		{
			PEout(14)=1;
		}
	}
}
void task12(void *parg)//cpu6050ģ��
{
	uint8_t res;
	float pitch,roll,yaw; 		//ŷ����
	
	OS_ERR err;
	u8 clear[17];
	printf("task12 is create ok\r\n");
	MPU_Init();					//��ʼ��MPU6050

	mpu_dmp_init();
	memset(clear,'\0',17);
	memset(clear,' ',16);
	while(1)
	{
		res=mpu_dmp_get_data(&pitch,&roll,&yaw);

		//printf("res=%d\r\n",res);
		if(res==0)
		{ 

			//printf("pitch=%f,roll=%f,yaw=%f\r\n",pitch,roll,yaw);
			if(((pitch)>15||(pitch)<(-15))||(roll>15||roll<(-15)))
			{
				//printf("pitch=%f,roll=%f,yaw=%f\r\n",pitch,roll,yaw);
				OSFlagPost(&g_flag_grp,0x08,OS_OPT_POST_FLAG_SET,&err);	

				OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
				OLED_ShowString(0,4,clear);
				OLED_ShowCHinese(32,4,22);//λ
				OLED_ShowCHinese(48,4,23);//��
				OLED_ShowCHinese(64,4,2);//Ԥ
				OLED_ShowCHinese(80,4,3);//��		
				OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
			}
			delay_ms(50);
		}
		else
		{
			delay_ms(100);
		}
	}
}
