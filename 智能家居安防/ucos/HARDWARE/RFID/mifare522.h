#ifndef __MIFARE522_H
#define __MIFARE522_H
#include "sys.h"
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "string.h"


//������Ҫ����9600
//���ݸ�ʽ   1 ����ʼλ��8 ������λ������żУ��λ��1 ��ֹͣλ
//


#define STX 0x20	// ��ʼ��
#define ETX 0x03	// ��ֹ��
#define ACK 0x06	// Ӧ��
#define NAK 0x15	// ��Ӧ��	 


//��ȡ�豸������
extern u8 readCmd[];

//�������
extern u8 requestCmd[];

//����ײ
extern u8 piccAnticollCmd[];

#define USART2_REC_LEN  			200  	//�����������ֽ��� 200
	  	
extern u8  USART2_RX_BUF[USART2_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART2_RX_STA;         		    //����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart2_init(u32 bound);


void mifare522ReadDevice(void);
void mifare522Request(void);
void mifare522ReadID(void);


u8 CalBCC(u8 *buf, int n);
void USART2_SendByte(u8 Data);
void print3RX(u8 * data,u16 nub);




#endif
