#ifndef _MG200_H
#define _MG200_H
#include "stm32f10x.h"  

//ָ�
#define ReqEnroll_Command  						           0x7F   //ע���û�
#define ReqCaptureAndExtract_Command 			       0x51   //ץȡָ��ͼ��������
#define ReqEraseOne_Command                      0x73   //ɾ��ָ���û�
#define ReqEraseAll_Command                      0x54   //ɾ�������û�
#define ReqGetUserNum_Command                    0x55   //��ȡ��ע����û�����
#define ReqMatch1N_Command                       0x71   //ָ�ƶԱ� 

//�Ĵ�����ַ
#define Send_Add  0x63
#define Recv_Add  0x62

void MG200_USART2_Init(u32 bps);
void MG200_Send_Data(u8 Command,u8 Data);
int MG200_Recv_Check(u8 command,u8 *parameter);
u8 ReqEnroll(u8 ID);
u8 ReqCaptureAndExtract(u8 parameter);
u8 ReqEraseOne(u8 ID);
u8 ReqEraseAll(void);
u8 ReqGetUserNum(void);
u8 ReqMatch1N(void);

#endif