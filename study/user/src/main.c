#include "stm32f10x.h"
#include "key.h"
#include "oled.h"
#include "font.h"
#include "systick.h"
#include "iic.h"
#include "MPR121.h"
#include "string.h"
#include "voice.h"
#include "spi.h"
#include "rfid.h"
#include "stdio.h"
#include "motor.h"
#include "usart.h"

void Interface_one();
void Interface_two();
void Interface_three();
void Interface_four();
void Interface_five();

u8 Identificate_Card(u8 *pTagType,u8 *pSnr);                                //Ѱ��--����ײ--ѡ��
u8 ReadCardData(u8 auth_mode,u8 addr,u8 *Src_Key,u8 *data,u8 *pSnr);        //��ָ��������

char *pwd = "123456";
u8 CardId[4];  				//����
u8 CardType[2];//������
unsigned char RFID[16];			//���RFID 
u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff}; //������-��ʼ����--��������

int main()
{
	u8 key = 0;
	Key_Init();
	OLED_Init();
	IIC_Init();
	MPR_Init();
	VOICE_Init();
	SPI_2_Init();
	RFID_Init();
	lock_init();
	usart1_init(115200);
	
	while(1)
	{
		switch(key)
		{
			case 0:Interface_one();key++;break;
			case 1:Interface_two();key++;break;
			case 2:Interface_three();key++;break;
			case 3:Interface_four();key++;break;
			case 4:Interface_five();key=0;break;
		}
	}
	return 0;
}

void Interface_one(){
	oled_Dis_hzstr16(1,40,"������");
	oled_Dis_hzstr16(4,24,"��Ա");
	oled_Dis_ch16(4,56,':');
	oled_Dis_hzstr16(4,72,"���ı�");
	while(1){
		if(Key_Scan()){
			OLED_clear();
			break;
		}
	}
}

void Interface_two(){
	u8 ls = 3;
	while(1)
	{
		oled_Dis_pic(3,ls,(u8 *)pic_car,20,20);  //3
		if(ls >= 132)
		{
			ls = 3;
		}
		Delay_ms(10);
		OLED_clear();
		ls++;
		if(Key_Scan()){
			break;
		}
	}
}

void Interface_three(){
	u8 pwdnum;
	char pwdsum[80];
	u8 i = 0;
	CC:
	oled_Dis_hzstr16(1,0,"����������");
	oled_Dis_ch16(1,80,':');
	while(1){
		if(Key_Scan()){
			OLED_clear();
			goto BB;
		}
		if(!(GPIOB->IDR&(1<<3)))
		{
			pwdnum=MPR_GetKey();
			if(pwdnum){
				pwdsum[i] = pwdnum;
				oled_Dis_ch16(3,i*8,'*');
				if(i==5){
					pwdsum[i+1]='\0';
					break;
				}
				i++;
			}
		}
	}
	if(strcmp(pwdsum,pwd)==0){
		OLED_clear();
		oled_Dis_hzstr16(1,24,"������ȷ");
		oled_Dis_ch16(1,88,'!');
		
		open_lock(5);
		Send_Data(24);
		Delay_ms(500);
	}else{
		OLED_clear();
		oled_Dis_hzstr16(1,24,"�������");
		oled_Dis_ch16(1,88,'!');
		Send_Data(16);
		Delay_ms(500);
		i=0;
		OLED_clear();
		goto CC;
	}
  BB:
	OLED_clear();

}

void Interface_four(){
	u8 card_id[4];  				//����
	unsigned char CT[2];//������
	//NVIC_SetPriorityGrouping(7-2);
	u8 print_id[80];
	u8 print_cardtype[80];

	while(1)
	{
		if(PcdRequest(PICC_REQALL,CT) == MI_OK)   //Ѱ���ɹ�
		{
		  if(PcdAnticoll(card_id)==MI_OK)/*����ײ�ɹ�*/
		  {
				if(PcdSelect(card_id)==MI_OK)//ѡ���ɹ�
				{
					sprintf(print_cardtype,"0x%02X %02X",CT[0],CT[1]);
					sprintf(print_id,"0x%02X %02X %02X %02X",card_id[0],card_id[1],card_id[2],card_id[3]);
					
					oled_Dis_hzstr16(0,0,"������");
					oled_Dis_ch16(0,48,':');
					oled_Dis_str16(2,0,print_cardtype);
					oled_Dis_hzstr16(4,0,"����");
					oled_Dis_ch16(4,32,':');
					oled_Dis_str16(6,0,print_id);
					
					Delay_ms(1000);
					OLED_clear();
				}
			}			
		}else{
			oled_Dis_hzstr16(0,8,"����ÿ�Ƭ����");
			oled_Dis_hzstr16(2,16,"����");
			oled_Dis_str16(2,48,"10CM");
			oled_Dis_hzstr16(2,80,"����");
			
			Delay_ms(100);
			OLED_clear();
		}
		if(Key_Scan()){
			break;
		}
	}

}

void Interface_five(){
	u8 readDataBuf[16];	
	//NVIC_SetPriorityGrouping(7-2);
	u8 print_info[80];

	while(1)
	{
		oled_Dis_hzstr16(0,0,"��");
		oled_Dis_str16(0,16,"info:");
		Delay_ms(500);
		if(ReadCardData(PICC_AUTHENT1A,1,KEY,readDataBuf,CardId)==MI_OK){
			sprintf(print_info,"0x%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",readDataBuf[0],readDataBuf[1],readDataBuf[2],readDataBuf[3],readDataBuf[4],readDataBuf[5],readDataBuf[6],readDataBuf[7],readDataBuf[8],readDataBuf[9],readDataBuf[10],readDataBuf[11],readDataBuf[12],readDataBuf[13],readDataBuf[14],readDataBuf[15]);
			oled_Dis_str16(0,0,print_info);
			Delay_ms(500);
			OLED_clear();
		}
		if(Key_Scan()){
			OLED_clear();
			break;
		}
	}
}

u8 Identificate_Card(u8 *pTagType,u8 *pSnr)
{
  u8 status=MI_ERR;
	u8 STA=0;
   if(PcdRequest(PICC_REQALL,pTagType)==MI_OK)//Ѱ���ɹ�
   {
      STA |=0x01;
      if(PcdAnticoll(pSnr)==MI_OK)/*����ײ�ɹ�*/
      {
				STA |=0x02;
		
        if(PcdSelect(pSnr)==MI_OK)//ѡ���ɹ�
        {
					STA |=0x04;
        }
      }
   }
	 
	 
	 if(STA==0x07)
		 status=MI_OK;
	 
  return status;
}

u8 ReadCardData(u8 auth_mode,u8 addr,u8 *Src_Key,u8 *data,u8 *pSnr)
{
  int status;
	
  /*1. Ѱ��--����ײ--ѡ��*/
  status=Identificate_Card(CardType,pSnr);  
  /*2. ��֤������*/
  if(status==MI_OK)
  {
    status=PcdAuthState(auth_mode,addr/4*4+3,KEY,pSnr);   //��֤��Ƭ���� �ββ�������֤��ʽ�����ַ�����룬�����к�
  }
  /*3. ��������*/
  if(status==MI_OK)
  {
    status=PcdRead(addr,data); //�ӵ�addr���������ֵ��
  }
  return status;
}


