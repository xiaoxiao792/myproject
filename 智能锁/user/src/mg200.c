#include "mg200.h"
#include "string.h"
#include "usart.h"
#include "stdio.h"

u8 Send_Buff[7];   //�������ݻ�����
u8 Recv_Buff[8];   //�������ݻ�����
u8 RecvCount = 0;   //���ݽ����±�
u8 RecvFlag = 0;    //������ɱ�־λ
/***************************************************************
�������ܣ�ָ��ģ���ʼ������
����������
	Bound��������
Ӳ���ӿڣ�
		USART2_TX-----PA2
		USART2_RX-----PA3
		FING_PWR ----- PB9 ------�ߵ�ƽָ��ģ�鹤��
		FING_DETECT----PC13 ------ ��Ӧ�ϵ��źţ���ָ����ָ�ƴ�����ʱ����ߵ�ƽ��
***************************************************************/
void MG200_USART2_Init(u32 bps)
{
 	u32 pri;
	//�˿�ʱ��ʹ��
	RCC->APB2ENR |= 1 << 2;//A
	RCC->APB2ENR |= 1 << 3;//B
	RCC->APB2ENR |= 1 << 4;//C	
 
	//FING_PWR-----PB9--ָ��ģ�鹩������
	GPIOB->CRH &= ~(0XF << (4 * (9 - 8)));
	GPIOB->CRH |=  (3 << (4 * (9 - 8)));		//ͨ������50M
	GPIOB->ODR |= 1 << 9;      //һֱ��ģ�鹩��
	
	//FING_DETECT----PC13----��Ӧ�ϵ��ź�
	GPIOC->CRH &= ~(0XF << (4 * (13 - 8)));
	GPIOC->CRH |=  (3 << (4 * (13 - 8)));		//ͨ������50M
	
	//PA2  PA3 
	//�˿�ģʽ����
	GPIOA->CRL &= ~(0XF << (4 * 2));
	GPIOA->CRL |=  (0XB << (4 * 2));		//��������50M
	
	GPIOA->CRL &= ~(0XF << (4 * 3));
	GPIOA->CRL |=  (0X4 << (4 * 3));		//��������
	
	/*����2����������*/
	//����1ģ��ʱ��ʹ��
	RCC->APB1ENR |= 1 << 17;
	//CR1
	USART2->CR1 &= ~(1<<12);        //8λ�ֳ�
	USART2->CR1 |= (1<<3);          //����ʹ��
	USART2->CR1 |= (1<<2);          //����ʹ��
	USART2->CR1 |= (1<<5);          //�����ж�ʹ��
	USART2->CR1 |= (1<<4);          //�����ж�ʹ��	
	//CR2
	USART2->CR2 &= ~(3<<12);        //1��ֹͣλ
	//BRR
	USART2->BRR = 36000000 / bps;

  /*NVIC����������*/
	//���ȼ�����  ��ռ2λ��Ӧ ��λ  д�����5
	//����������
	//�������ȼ�����ֵ
	 pri = NVIC_EncodePriority(5,1,2);
	//���þ����ж�Դ���ȼ�
	NVIC_SetPriority(USART2_IRQn,pri);
	//ʹ��NVIC��Ӧͨ��
	NVIC_EnableIRQ(USART2_IRQn);	

	//����ʹ��
	USART2->CR1 |= (1<<13); 

}
/*************************����2�жϷ�����********************************************/
void USART2_IRQHandler()
{
	if(USART2->SR & (1<<5))  //�ж��Ƿ��ǽ����ж�
	{
		Recv_Buff[RecvCount] = USART2->DR; //��������
		RecvCount++;   //�±�����
	}
	if(USART2->SR & (1<<4))  //�ж��Ƿ��ǿ����ж�
	{
		USART2->SR;     //���־λ
		USART2->DR;
		RecvFlag = 1;    //���ձ�־λ��1		
	}
}
/*****************************************************************************************
�������ܣ����������
����������
	Command��Ҫ���͵�����
	Data��Ҫ���͵�����
*****************************************************************************************/
void MG200_Send_Data(u8 Command,u8 Data)
{
	u8 i = 0,Checksum = 0;
	memset(Send_Buff,0,7);  //����
	Send_Buff[0] = 0x6C;    //��ʼ��
	Send_Buff[1] = 0x63;    //���͵�ַ
	Send_Buff[2] = 0x62;    //���յ�ַ
	Send_Buff[3] = Command;   //����
	Send_Buff[4] = Data;      //����
	Send_Buff[5] = 0;          //����
	for(i = 1; i <6 ;i++)
	{
		Checksum = Checksum + Send_Buff[i];
	}
	Send_Buff[6] = Checksum;   //У���
	for(i = 0;i < 7; i++)
	{
		//�ȴ�֮ǰ�ķ������
   	while(!(USART2->SR & (1<<6)));
   	//��Ҫ���͵����ݸ����ݼĴ���
	  USART2->DR = Send_Buff[i];		
	}
}
/********************************************************************************************
�������ܣ����յ�������
����������
command������
parameter������
��������ֵ��
�������ݰ����󷵻�-1,���ݰ�������ȷ���ش�����
********************************************************************************************/
int MG200_Recv_Check(u8 command,u8 *parameter)
{
	u8 i;
	u8 result,checksum = 0;
	if(Recv_Buff[0] != 0x6c)		return -1;   //�����ʼ��
	if(Recv_Buff[1] != 0x62)		return -1;   //���ָ��ģ���ַ
	if(Recv_Buff[2] != 0x63)		return -1;   //�������MCU��ַ
	if(Recv_Buff[3] != command)	    return -1;   //���Ŀ��ָ��
	result = Recv_Buff[4];           //����Ӧ����
	if(parameter != NULL)
	{
			*parameter = Recv_Buff[5];  //�ж��Ƿ��в���
	}		
	for(i=1;i<6;i++)
	{
		checksum = checksum + Recv_Buff[i];   //У���
	}
	if(Recv_Buff[7] != checksum)	 return -1;//���У���
	memset(Recv_Buff,0,8);      //����
	RecvCount = 0;
	RecvFlag = 0;
	return result;
}
/***********************************************************************************************
�������ܣ�ע���û�
����������
	ID:ע���ID��(ȡֵ��ΧΪ1~100������û�IDΪ100,���д0����ע��ɹ���ID��ϵͳ��������)
��������ֵ��
	0��ע��ɹ�
	1��ע��ʧ��
***********************************************************************************************/
u8 ReqEnroll(u8 ID)
{
	u8 result = 0;   //���շ���ֵ
	MG200_Send_Data(ReqEnroll_Command,ID);
	while(RecvFlag == 0);   //ѭ���ȴ�������ɱ�־λ��1
	result = MG200_Recv_Check(ReqEnroll_Command,0x00);
	switch(result)
	{
		case 0x00: printf("   success       \r\n");    break;
		case 0x83: printf("  ID  error      \r\n");    break;
		case 0x91: printf("  �û���������   \r\n");    break;
		case 0x93: printf("  ��ID�Ѿ�ע��� \r\n");    break;
		case 0x94: printf("  ָ����ȡ��<3   \r\n");    break;
		default:   printf("  ���ݰ�����     \r\n");    break;
	}
	printf("result: %x\r\n",result);
	if(!result)  return result;  //ע��ɹ�
	else         return 1;  //ע��ʧ��
}
/*********************************************************************************************
�������ܣ�ץȡָ��ͼ�����ȡ������
����������
	num:Ҫ���ݵĴ���
��������ֵ��
	0���ɹ�
	1��ʧ��
����˵����
���ص�Ԫ MCU ��ʹ�ø�ע���û�ָ��ǰ������ִ�� 3~5 �Σ�ִ�д����ɸ����û�
�����ƣ� 0x51 ָ���ȡҪע���û�ָ�Ƶ�������
*********************************************************************************************/
u8 ReqCaptureAndExtract(u8 parameter)
{
	u8 result = 0;   //���շ���ֵ
	MG200_Send_Data(ReqCaptureAndExtract_Command,parameter);
	while(RecvFlag == 0);   //ѭ���ȴ�������ɱ�־λ��1
	result = MG200_Recv_Check(ReqCaptureAndExtract_Command,0x00);	
	switch(result)
	{
		case 0x00:printf("		syccess     	\r\n");break;
		case 0xB1:printf("		ָ�ƹ�С		\r\n");break;
		case 0xB2:printf("		��ָ��			\r\n");break;
		case 0xC0:printf("		������ȡ����	\r\n");break;
		default:printf("		�������ݰ�����	\r\n");break;
	}
	if(!result)  return 0;  //�ɹ�
	else         return 1;  //ʧ��	
}

/********************************************************************************************
�������ܣ�ɾ��ָ��ID�û�
����������
	ID��Ҫɾ����ID��
��������ֵ��
	0��ɾ���ɹ�
	1��ɾ��ʧ��
********************************************************************************************/
u8 ReqEraseOne(u8 ID)
{
	u8 result = 0;   //���շ���ֵ
	MG200_Send_Data(ReqEraseOne_Command,0x00);
	while(RecvFlag == 0);   //ѭ���ȴ�������ɱ�־λ��1
	result = MG200_Recv_Check(ReqEraseOne_Command,0x00);	
	switch(result)
	{
		case 0x00: printf("   success       \r\n");    break;
		case 0x83: printf("  ��������       \r\n");    break;
		case 0x90: printf("  δע������û� \r\n");    break;
		case 0xFF: printf("  д�����       \r\n");    break;
		default:   printf("  ���ݰ�����     \r\n");    break;
	}
	if(!result)  return 0;  //�ɹ�
	else         return 1;  //ʧ��
}


/********************************************************************************************
�������ܣ�ɾ�������û�
��������ֵ��
	0��ɾ���ɹ�
	1��ɾ��ʧ��
********************************************************************************************/
u8 ReqEraseAll(void)
{
	u8 result = 0;   //���շ���ֵ
	MG200_Send_Data(ReqEraseAll_Command,0x00);
	while(RecvFlag == 0);   //ѭ���ȴ�������ɱ�־λ��1
	result = MG200_Recv_Check(ReqEraseAll_Command,0x00);	
	switch(result)
	{
		case 0x00: printf("   success       \r\n");    break;
		case 0x90: printf("  ɾ��ʧ��       \r\n");    break;
		default:   printf("  ���ݰ�����     \r\n");    break;
	}
	if(!result)  return 0;  //�ɹ�
	else         return 1;  //ʧ��
}

/********************************************************************************************
�������ܣ���ȡ��ע���û�����
��������ֵ��
	�ɹ���������ע�������
	ʧ�ܣ�1
********************************************************************************************/
u8 ReqGetUserNum(void)
{
	u8 result = 0,parameter = 0;   //���շ���ֵ
	MG200_Send_Data(ReqGetUserNum_Command,0x00);
	while(RecvFlag == 0);   //ѭ���ȴ�������ɱ�־λ��1
	result = MG200_Recv_Check(ReqGetUserNum_Command,&parameter);	
	switch(result)
	{
		case 0x00: printf("   success       \r\n");    break;
		default:   printf("  ���ݰ�����     \r\n");    break;
	}
	if(!result)  return parameter;  //�ɹ�
	else         return 1;  //ʧ��
}


/********************************************************************************************
�������ܣ�1�� N �ȶԶԱ��û�ָ��
��������ֵ��
	�ɹ������ضԱȳɹ���ID��
	ʧ�ܣ�1
********************************************************************************************/
u8 ReqMatch1N(void)
{
	u8 result = 0,parameter = 0;   //���շ���ֵ
	MG200_Send_Data(ReqMatch1N_Command,0x00);
	while(RecvFlag == 0);   //ѭ���ȴ�������ɱ�־λ��1
	result = MG200_Recv_Check(ReqMatch1N_Command,&parameter);	
	switch(result)
	{
		case 0x00: printf("   success       \r\n");    break;
		case 0x92: printf("   �ȶ�ʧ��      \r\n");    break;
		default:   printf("  ���ݰ�����     \r\n");    break;
	}
	if(!result)  return result;  //�ɹ�
	else         return -1;  //ʧ��
}




















