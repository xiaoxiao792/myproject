#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "usart1.h"
#include  <stdio.h>
#include "systick.h"
#include "beep.h"
#include "timer.h"
/*******************************************************************************************************
**** �������ƣ�   main
**** �����:      Zhangxx    ���ڣ�2018��11��09��
**** �޸���:      Zhangxx    ���ڣ�2018��11��09��
**** ��  �ܣ�	    PWM�������
**** �汾��Ϣ:    V0.1
**** ˵  ����     
****���˼·��    ����ռ�ձ��������
****��ӯ�������  www.edu118.com   �ɲ����ߣ�18948782707
********************************************************************************************************/
int main(void)
{
	u8 key=0;
	u16 ccr=80;
	u16 data=0;
	LED_Init();
	KEY_Init();
	beep_init();
	NVIC_SetPriorityGrouping(5);       //����Ϊ��5��
	USART1_Init(115200);
	TIM5_CH2_Init(8400-1,200,ccr);    //20msһ�����ڣ��ߵ�ƽռ����ʱ��0.5ms
  while(1)
	{	
		key = Key_Scan();
		if( key ==1 )
		{
			ccr+=1;
			if(ccr>195) //���ڽǶȱ�С
			{
				ccr=195;
			}
				printf("ccr=%d\r\n",ccr);
		}
		else if( key == 2)
		{
			ccr-=1;
			if(ccr<175)    //���ڽǶȱ�� 
			{
				ccr=175;
			}		
				printf("ccr=%d\r\n",ccr);
		}
		if( key )  
		{
			printf("ccr=%d\r\n",ccr);
			TIM5->CCR2 = ccr;     //д������Ƚ�ֵ	
		}
	}
}

