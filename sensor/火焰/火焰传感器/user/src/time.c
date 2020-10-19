#include "stm32f4xx.h"
#include "led.h"

//1s定时
void time7_init(void)
{
	//	1.	模块时钟使能--TIME7
	RCC->APB1ENR |=0X01<<5;
	//2.	设置预分频和自动重装载值
	TIM7->PSC =9999;   //10000   84*10^6 /10000 = 8400
	TIM7->ARR =8399;   //定时时间1s = 计数值* 时钟脉冲   x = 1s/时钟脉冲  = 1s * 8400
	//3.	设置UG会产生更新事件
	
	//4.	设置UG位，产生软件更新
	TIM7->EGR |=0X01;
	//5.	清更新标志
	TIM7->SR &=~(0X01);
	//开定时中断
	TIM7->DIER |=0X01;
	NVIC_SetPriority(TIM7_IRQn,NVIC_EncodePriority(7-2,1,1));
	//在NVIC中使能串口中断
	NVIC_EnableIRQ(TIM7_IRQn);
	
	//6.	开定时器
	TIM7->CR1 |=0X01<<0;
}

void TIM7_IRQHandler(void)
{
	static int cnt=0;
	
	TIM7->SR &=~(0X01);  //清标志
	LED_Triggle(2);
	
	
	cnt++;
	if(cnt>1000)
	{
		cnt=0;
		//步进电机停止转动
	//	motor_stop();
		//关闭定时器
		TIM7->CR1 &=0;	
	}
}

