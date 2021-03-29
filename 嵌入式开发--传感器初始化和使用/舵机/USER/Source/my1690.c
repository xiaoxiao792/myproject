#include "my1690.h"

/*  此模块串口波特率为9600 */

void send_cmd(u8 cmd)  
{
		while( !(USART2->SR & (1 << 7)))
		{
			/* 等待发送完成 */
		}
		USART2->DR = cmd;
}
/*********************************************************************************
* 【函 数 名】： void send_3dat_cmd(u8 cmd,u8 dat)
* 【功    能】： 除了起始和结束标志外，发三位长度的数据 
*send_3dat_cmd(0x11,0x12);	  // 播放
*send_3dat_cmd(0x12,0x11);    //暂停
* send_3dat_cmd(0x13,0x10);    // 下一曲
* send_3dat_cmd(0x14,0x17);   //上一曲
*send_3dat_cmd(0x15,0x16);	  //音量加
*send_3dat_cmd(0x16,0x15);	  //音量减
* send_3dat_cmd(0x1A,0x19);	  //快进
*send_3dat_cmd(0x1B,0x18);	    //快退
* send_3dat_cmd(0x1C,0x1F);	   //播放/暂停						
**********************************************************************************/
void send_3dat_cmd(u8 cmd,u8 jy)
{
	send_cmd(0x7E);		 //发送“开始命令”到SBUF
	send_cmd(0x03);		 //发送“命令长度”到SBUF
	send_cmd(cmd);		 //发送“命令”到SBUF
	send_cmd(jy);	     //  发送校验码到SBUF
	send_cmd(0xEF);		 //发送“结束指令”到SBUF
}
/*********************************************************************************
* 【函 数 名】： void send_4dat_cmd(u8 cmd,u8 cs,u8 jy ) 
* 【功    能】： 除了起始和结束标志外，发四位长度的数据 	
*  send_4dat_cmd(0x32,0x00,0x36 ) ;	      //设置EQ
*  send_4dat_cmd(0x34,0x01,0x31 ) ;	      //文件切换
*  send_4dat_cmd(0x35,0x01,0x30 ) ;	  //设备切换					
**********************************************************************************/
  void send_4dat_cmd(u8 cmd,u8 cs,u8 jy ) 
{
	send_cmd(0x7E);		 //发送“开始命令”到SBUF
	send_cmd(0x04);		 //发送“命令长度”到SBUF
	send_cmd(cmd);		 //发送“插播指令”到SBUF
	send_cmd(cs);		 //	发送参数 到SBUF
	send_cmd(jy);		 //  发送校验码到SBUF
	send_cmd(0xEF);		 //发送“结束指令”到SBUF
} 
/*********************************************************************************
* 【函 数 名】： void send_5dat_cmd(u8 cmd,u8 cs,u8 gq,u8 jy ) 
* 【功    能】： 除了起始和结束标志外，发四位长度的数据 
* send_5dat_cmd(0x43,0x00,0x03,0x45);      //插播功能
* send_5dat_cmd(0x44,0x01,0x06,0x46) ;     //插播指定文件夹的歌曲播放，本指令为文件夹01的第6首歌曲						
**********************************************************************************/
  void send_5dat_cmd(u8 cmd,u8 cs,u8 gq,u8 jy ) 
{
	send_cmd(0x7E);		 //发送“开始命令”到SBUF
	send_cmd(0x05);		 //发送“命令长度”到SBUF
	send_cmd(cmd);		 //发送“插播指令”到SBUF
	send_cmd(cs);		     //发送参数 到SBUF	
	send_cmd(gq);		 //发送第几首歌曲到SBUF
	send_cmd(jy);		     //发送校验码到SBUF
	send_cmd(0xEF);		 //发送“结束指令”到SBUF
} 								