#include "stm32f4xx.h"
#include "led.h"


/****************** ΢����ʱ���� ******************
SysCLK�� ϵͳʱ��
us��     ��Ҫ��ʱ��΢����
����168M�����£�������ֵΪ798915us
Cortexϵͳ��ʱ��ʱ�ӣ�����ϵͳ����ʱ��(HCLK) 8��Ƶ
����168/8=21M
���ݹ�ʽ��LOAD - 1 =��24 * us)->  LOAD��ֵ���ܴ���16777216-1��
us-->��16777215/21=798915��
***************************************************/
void Delay_us(u8 SysClk,u32 us)
{
	u32 tmp;
	//1.ѡ��ʱ��ʱ��Դ
	SysTick->CTRL &=~(0x01<<2);//AHBʱ��8��Ƶ����ΪSysTickʱ��
	//2.ȷ����ʱ����ʱʱ��,���ݶ�ʱʱ�������ʱ��ֵ�����ѳ�ʼֵд��LOAD�Ĵ���
	SysTick->LOAD=us*(SysClk/8);
	//3.��VAL�Ĵ�������д�����ԶԼ���ֵ��������
	SysTick->VAL=0; //�����Ĵ�������
	//4.������ʱ��
	SysTick->CTRL |=1<<0;   //ʹ��systick
	//5.�ȴ�ʱ�����
	//while(!(SysTick->CTRL&(1<<16)));//����ѯCTRL.16�Ƿ�Ϊ1��
	do
	{
		tmp=SysTick->CTRL;   //��ȡ����&״̬�Ĵ�����ֵ
	}while(!(tmp &(1<<16)));  //�ȴ�ʱ�䵽��
	//6.�رն�ʱ��
	SysTick->CTRL &=~(1<<0);   //ʧ��systick

}
/****************** ������ʱ���� ******************
SysCLK�� ϵͳʱ��
ms��     ��Ҫ��ʱ�ĺ�����
����168M�����£�������ֵΪ798ms
***************************************************/
void Delay_ms(u8 SysCLK, u16 ms)
{
	u32 temp;
	
	SysTick->CTRL &= ~(1 << 2);                //AHBʱ��8��Ƶ����ΪSysTickʱ��
	SysTick->LOAD = ms * 1000 * (SysCLK / 8);  //����ʱ����ֵд�����ؼĴ���
	SysTick->VAL = 0;                          //�Ѽ����Ĵ�������
	SysTick->CTRL |= 1 << 0;                   //ʹ��SysTick
	//�ȴ�ʱ�䵽��
	while(!(SysTick->CTRL&(1<<16)));//����ѯCTRL.16�Ƿ�Ϊ1��
	SysTick->CTRL &= ~(1 << 0);                //�ر�SysTick

}




/****************** SysTick�жϳ�ʼ������ ******************
SysCLK�� ϵͳʱ��
ms��     ms�������һ���ж�
State��  SysTick״̬λ��1������0���ر�
***********************************************************/
void systick_interrupt_init(u8 SysClk,u16 ms,u8 state)
{
//	1.	ѡ���ⲿʱ��Դsysclk/8
	SysTick->CTRL &=~(0x01<<2);
//2.	����load�Ĵ���-----�趨������ֵ
	SysTick->LOAD=ms*1000*SysClk/8;
//3.	��VALд����------VAL�ᱻ����?��װ��
	SysTick->VAL=0;
//���ж�
//	SysTick->CTRL |=0x01<<1; //������0ʱ�����ж�
	
//		NVIC_SetPriorityGrouping(7-2);                      //�������ȼ�����
 //  NVIC_SetPriority(SysTick_IRQn ,NVIC_EncodePriority(7-2,3,3));   //�����ж�Դ���ȼ�
	//ϵͳ�жϣ�  
	
	//������Ҫ�����Ƿ�Ҫ������ʱ��
	if(state==1)
		SysTick->CTRL |=0x01<<0; //	����SYSTICK
  else 
		SysTick->CTRL &= ~( 0x01 << 0 ); // �ر�SYSTICK

}










