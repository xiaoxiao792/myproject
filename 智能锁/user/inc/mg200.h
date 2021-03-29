#ifndef _MG200_H
#define _MG200_H
#include "stm32f10x.h"  

//指令集
#define ReqEnroll_Command  						           0x7F   //注册用户
#define ReqCaptureAndExtract_Command 			       0x51   //抓取指纹图像特征点
#define ReqEraseOne_Command                      0x73   //删除指定用户
#define ReqEraseAll_Command                      0x54   //删除所有用户
#define ReqGetUserNum_Command                    0x55   //获取已注册的用户数量
#define ReqMatch1N_Command                       0x71   //指纹对比 

//寄存器地址
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