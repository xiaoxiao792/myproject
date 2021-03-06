#include "sys.h"
#include "usart.h"	
#include "delay.h"
#include "includes.h"					//ucos ʹ��	  

static GPIO_InitTypeDef		GPIO_InitStructure;
static USART_InitTypeDef	USART_InitStructure;
static NVIC_InitTypeDef		NVIC_InitStructure;
static volatile uint8_t  	g_usart1_recv_buf[128]={0};
static volatile uint32_t 	g_usart1_recv_cnt = 0;
static volatile uint32_t 	g_usart1_event=0;
extern OS_Q	g_queue;
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  

#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}

 
//��ʼ��IO ����1 
//baud:������
void usart_init(u32 baud)
{
   //GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = baud;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
	USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);
	

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

	
}


void USART1_IRQHandler(void)                	//����1�жϷ������
{
	uint8_t d;
  
	OS_ERR err;

	//�����ж�
	OSIntEnter();    

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		//���մ�������
		d=USART_ReceiveData(USART1);	
		
		g_usart1_recv_buf[g_usart1_recv_cnt] = d;
		
		//��¼���ٸ�����
		g_usart1_recv_cnt++;
		
		//��⵽'#'������յ���������ʱ����������
		if(d=='#' || g_usart1_recv_cnt>=(sizeof g_usart1_recv_buf))
		{
			g_usart1_event = 1;
		
		}
		//��մ��ڽ����жϱ�־λ
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	} 
	
	//�˳��ж�
	OSIntExit();    

		//������Ϣ
	if(g_usart1_event)
	{
	
		OSQPost(&g_queue,(void *)g_usart1_recv_buf,g_usart1_recv_cnt,OS_OPT_POST_FIFO,&err);
	
		g_usart1_recv_cnt=0;
		
		g_usart1_event=0;
	}	
} 
void usart3_init(uint32_t baud)
{
	//ʹ�ܴ���3Ӳ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 
	
	//ʹ�ܶ˿�B��Ӳ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	//����PB10 PB11Ϊ���ù���ģʽ
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;	//��10 11������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;		//���ù���ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_High_Speed;	//���Ÿ��ٹ������յ�ָ������������ȱ�㣺���ĸ�
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;	//�����������������
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;	//����Ҫ����������
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//��PB10��PB11���ӵ�����1Ӳ��
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);		

	//���ô���3�������ʣ�У��λ������λ��ֹͣλ
	USART_InitStructure.USART_BaudRate = baud;						//������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//����λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;				//��У��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//ȡ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�ܹ��շ�����
	USART_Init(USART3,&USART_InitStructure);
	
	
	//���ô���3���жϴ�����ʽ���������ֽڴ����ж�
	USART_ITConfig(USART3,USART_IT_RXNE , ENABLE);
	
	
	//ʹ�ܴ���3����	
	USART_Cmd(USART3, ENABLE);
	
	
	//����NVIC������3
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;		//����1���жϺ�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ� 0x2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//��Ӧ���ȼ� 0x2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//NVICʹ�ܴ���1�ж�����ͨ��
	NVIC_Init(&NVIC_InitStructure);	
}
void usart3_send_str(char *str)
{
	char *p = str;
	
	while(p && (*p!='\0'))
	{
	
		USART_SendData(USART3,*p);
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET)
		{
			delay_ms(1);
		}
		p++;
	}
}
void bluetooth_config(void)
{
	
	usart3_send_str("AT\r\n");
	delay_ms(500);	
	

	usart3_send_str("AT+NAMECWJ\r\n");
	delay_ms(500);

}
void  USART3_IRQHandler(void)
{
	uint8_t d;
	
	OS_ERR err;
	//�����ж�
	OSIntEnter();    

	//����־λ
	if(USART_GetITStatus(USART3,USART_IT_RXNE) == SET)
	{
		
		//��������
		d = USART_ReceiveData(USART3);
				
		//���͵�����1->PC
		USART_SendData(USART1,d);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
		
		g_usart1_recv_buf[g_usart1_recv_cnt] = d;
		
		//��¼���ٸ�����
		g_usart1_recv_cnt++;
		
		//��⵽'#'������յ���������ʱ����������
		if(d=='#' || g_usart1_recv_cnt>=(sizeof g_usart1_recv_buf))
		{
			g_usart1_event = 1;
		
		}			
		//��ձ�־λ	
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	}
	//�˳��ж�
	OSIntExit();
	
		//������Ϣ
	if(g_usart1_event)
	{
	
		OSQPost(&g_queue,(void *)g_usart1_recv_buf,g_usart1_recv_cnt,OS_OPT_POST_FIFO,&err);
	
		g_usart1_recv_cnt=0;
		
		g_usart1_event=0;
	}

}

 



