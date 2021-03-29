#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "usart1.h"
#include  <stdio.h>
#include "systick.h"
#include "beep.h"
#include "timer.h"
#include "adc.h"
/*******************************************************************************************************
**** �������ƣ�   main
**** �����:      Zhangxx    ���ڣ�2018��9��02��
**** �޸���:      Zhangxx    ���ڣ�2018��9��02��
**** ��  �ܣ�	    �ƾ����
**** �汾��Ϣ:    V2
**** ˵  ����    
****���˼·��    ����ADC��ȡ����ģ������ת���������������ݹ�ʽ��ӡģ��������ӡ��ȡ�ĵ�ѹֵ
									�趨һ����ѹ��ֵ������һ���ĵ�ѹֵ������Լ���Ƿ񺬾ƾ�
****��ӯ�������  www.edu118.com   �ɲ����ߣ�18948782707
********************************************************************************************************/
int main(void)
{ 
	u16 ad_val=0;
	u16 temp;
	LED_Init();
	KEY_Init();
	beep_init();
	USART1_Init(115200);
	adc1_init();
  while(1)
	{	
		/*  PC2  ADC1_CH12  */
		Delay_ms(100);
		ad_val=get_adc_val();	
		printf("������ �� %d\r\n",ad_val);
		printf("��ѹֵ ��%.1f\r\n",(ad_val*3.3/4096) );
//		temp = (float)(ad_val * 100 / 4096);
//		printf("����ǿ�ȣ�%d%%\r\n", temp);
	}
}

