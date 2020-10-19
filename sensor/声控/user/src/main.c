#include "led.h"
#include "key.h"
#include "beep.h"
#include "usart1.h"
#include <string.h>
#include "hw_sr.h"
#include "hc_sr.h"
#include "systick.h"
#include "sk_sr.h"
/*******************************************************************************************************
**** �������ƣ�   main
**** �����:      Zhangxx    ���ڣ�2018��9��02��
**** �޸���:      Zhangxx    ���ڣ�2018��9��02��
**** ��  �ܣ�	    ����Ƿ�������
**** �汾��Ϣ:    V0.1
**** ˵  ����     
****���˼·��    �����������ģ���Ǹߵ�ƽ��LED1��������ǵ͵�ƽ����LED1��
****��ӯ�������  www.edu118.com   �ɲ����ߣ�18948782707
********************************************************************************************************/
int main()
{
	u8 data = 0;
	LED_Init();  
	KEY_Init();
	beep_init();
  USART1_Init(115200, 84, 0);
	Hw_SR_init();  								//�������IO��ʼ��
	HC_SR_init();                 //�������IO��ʼ��
	SK_SR_init();                 //����ģ��IO��ʼ��

	while(1)
	{ 
 
		data = SK_SR_input();
		if(data == 1)               //������������
		{
			  LED_ON(3);  					//��LED1
		}
		else
		{
			  LED_OFF(3);  						//��LED1
		}
	}
}








