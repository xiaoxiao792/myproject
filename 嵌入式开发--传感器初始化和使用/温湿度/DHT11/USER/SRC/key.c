#include "key.h"

/*
�������ܣ�key��ʼ��
��������ֵ����
�����βΣ���
��ע��KEY1 -- PA0  û�а����ǵ͵�ƽ�������Ǹߵ�ƽ
			KEY2 -- PE2  û�а����Ǹߵ�ƽ�������ǵ͵�ƽ
			KEY3 -- PE3  û�а����Ǹߵ�ƽ�������ǵ͵�ƽ
			KEY4 -- PE4  û�а����Ǹߵ�ƽ�������ǵ͵�ƽ
*/
void KEY_Init(void)
{
	 RCC->AHB1ENR |= 1 << 0;  //ʹ��GPIOAʱ��
	 RCC->AHB1ENR |= 1 << 4;  //ʹ��GPIOEʱ��
	 
	/* ����PA0 */
	 GPIOA->MODER &= ~(3 << (0 * 2));   //����ģʽ
	 GPIOA->PUPDR &= ~(3 << (0 * 2)); //��������
	/* ����PE2 */
	 GPIOE->MODER &= ~(3 << (2 * 2));   //����ģʽ
	 GPIOE->PUPDR &= ~(3 << (2 * 2)); //��������
	
	/* ����PE3 */
	 GPIOE->MODER &= ~(3 << (3 * 2));   //����ģʽ
	 GPIOE->PUPDR &= ~(3 << (3 * 2)); //��������
	
	/* ����PE4 */
	 GPIOE->MODER &= ~(3 << (4 * 2));   //����ģʽ
	 GPIOE->PUPDR &= ~(3 << (4 * 2)); //��������
}

/*
�������ܣ�keyɨ��
��������ֵ�����ذ���ֵ
�����βΣ���
��ע��return 1 : key1����  return 2 : key2����
      return 3 : key3����  return 4 : key4����
      return 0 : û�а�������
*/
u8 key_Scan(void)
{
	 static u8 flag = 1;
	 u8 key = 0;
	 
	 if((KEY1 || KEY2 || KEY3 || KEY4) && flag == 1)
	 {
		  delay(50000);  //��ʱ10ms
		  if(KEY1)
			{
				 flag = 0;
				 key = 1;
			}
			else if(KEY2)
			{
				flag = 0;
				key = 2;
			}
		  else if(KEY3)
			{
				flag = 0;
				key = 3;
			}
			else if(KEY4)
			{
				flag = 0;
				key = 4;
			}
	 }
	 else if(!KEY1 && !KEY2  && !KEY3 && !KEY4)  //����û�а���
	 {
		  flag = 1;     //Ϊ��һ�ΰ���������׼��
		  key = 0;
	 }
	  return key;
}


void delay(u32 t)
{
	while(t--);
}





