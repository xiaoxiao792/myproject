#include "rfid.h"
#include "string.h"

/*************************************************************************************
* ��������     RFID_Init
* �������� ��  ��ʼ���ܽ�
           SDA (CS)<----->PA6
           RST <----->PA7
 *************************************************************************************/
void RFID_Init(void)
{
  RCC->APB2ENR |=1<<2;  //ʹ��Bʱ��
	
	/*CS-----PA6*/ //������� 50MHZ
	GPIOA->CRL&=~(15<<6*4);
	GPIOA->CRL|=3<<(6*4);
	CS_H;
	
	/*RST-----PA7*/ //������� 50MHZ
	GPIOA->CRL&=~(15<<7*4);
	GPIOA->CRL|=3<<(7*4);
	RST_H;	
}

/*******************************************************************
* ��������     WriteRawRC()
* �������� ��  дRC632�Ĵ���
* ����˵��:   
	Address:�Ĵ�����ַ
	value:д���ֵ
*******************************************************************/
void WriteRawRC(u8 Address, u8 value)
{  
    u8 ucAddr;
	  //ѡ��rfid�ӻ�
		CS_L;
	  //����Ĵ����ĵ�ַ��ȡ����λ
    ucAddr = ((Address<<1)&0x7E);  //0111 1110
		//����Ҫд��ļĴ�����ַ
	  SPI_Read_Write_Byte(ucAddr);
	  //����д�������
		SPI_Read_Write_Byte(value);
		CS_H;
}
/*******************************************************************
* ��������     ReadRawRC()
* �������� ��  ��RC632�Ĵ���
* ����˵��:    Address:�Ĵ�����ַ
* ����ֵ˵���� ������ֵ
*******************************************************************/
u8 ReadRawRC(u8 Address)
{
		u8 ucAddr;
		u8 ucResult=0;
		CS_L;
		ucAddr = ((Address<<1)&0x7E)|0x80;
		SPI_Read_Write_Byte(ucAddr);
		ucResult=SPI_Read_Write_Byte(0);
		CS_H;
		return ucResult;
}
/*******************************************************************
* ��������     SetBitMask()
* �������� ��  ��RC522�Ĵ���λ
* ����˵��:    
	reg:�Ĵ�����ַ
	mask:��λ1
*******************************************************************/
void SetBitMask(u8 reg,u8 mask)  
{
    char   tmp = 0x0;
    tmp = ReadRawRC(reg);
    WriteRawRC(reg,tmp|mask);  //����ĳ��λλ1
}

/*******************************************************************
* ��������     ClearBitMask()
* �������� ��  ��RC522�Ĵ���λ
* ����˵��:    
	reg:�Ĵ�����ַ
	mask:��λ0

*******************************************************************/
void ClearBitMask(u8 reg,u8 mask)  
{
    char tmp = 0;
    tmp = ReadRawRC(reg);
    WriteRawRC(reg, tmp & ~mask);  //��ĳ��λ��0
} 





/*******************************************************************
* ��������     PcdAntennaOn()
* �������� ��  �������� 
*******************************************************************/
void PcdAntennaOn(void)
{
    u8   i;
    i = ReadRawRC(TxControlReg);
    if (!(i & 0x03))
    {
        SetBitMask(TxControlReg, 0x03);
    }
}

/*******************************************************************
* ��������     PcdAntennaOff()
* �������� ��  �ر����� 
*******************************************************************/
void PcdAntennaOff(void)
{
	ClearBitMask(TxControlReg, 0x03);
}






/*******************************************************************
* ��������     Reset_RC522()
* �������� ��   ��λRC522
*******************************************************************/
void Reset_RC522(void)
{
	RST_H;
  Delay_us(2);
	RST_L;
  Delay_us(2);
	RST_H;
  Delay_us(2);
  //��λ
  WriteRawRC(CommandReg,PCD_RESETPHASE);
  Delay_us(2);
  //���巢�ͽ��յĳ���ģʽ,��Mifare��ͨѶ��CRC��ʼֵ0x6363
	WriteRawRC(ModeReg,0x3D);  
  //������ʱ����װ��ֵ	
	WriteRawRC(TReloadRegL,30);           
	WriteRawRC(TReloadRegH,0);
	//�����ڲ���ʱ��������
	WriteRawRC(TModeReg,0x8D);
	WriteRawRC(TPrescalerReg,0x3E);
	//��������������������,//���Ʒ����ź�Ϊ100%ASK
	WriteRawRC(TxAutoReg,0x40); 

  //�ر�����
	PcdAntennaOff(); 
	//��������
	PcdAntennaOn();  
}    


/*******************************************************************
* ��������     PcdComMF522()
* �������� ��  ͨ��RC522��ISO14443��ͨѶ
* ����˵��:   
	Command :RC522������
	pIn :ͨ��RC522���͵���Ƭ������
	InLenByte :�������ݵ��ֽڳ���
	pOut :���յ��Ŀ�Ƭ��������
	*pOutLenBit :�������ݵ�λ����

*******************************************************************/
char PcdComMF522(u8   Command, 
                 u8 *pIn , 
                 u8   InLenByte,
                 u8 *pOut , 
                 u8 *pOutLenBit)
{
    char status = MI_ERR;
    u8 irqEn   = 0x00;
    u8 waitFor = 0x00;
    u8 lastBits;
    u8 n;
    u16 i;
    switch (Command)
    {
			  ////��֤��Կ
        case PCD_AUTHENT:    //Mifare��֤
													irqEn   = 0x12; //��������ж�����ErrIEn  ��������ж�IdleIEn
													waitFor = 0x10; //��֤Ѱ���ȴ�ʱ�� ��ѯ�����жϱ�־λ
													break;
				//���Ͳ���������
				case PCD_TRANSCEIVE:  //���շ��� ���ͽ���
													irqEn   = 0x77;  //����TxIEn RxIEn IdleIEn LoAlertIEn ErrIEn TimerIEn
													waitFor = 0x30;  //Ѱ���ȴ�ʱ�� ��ѯ�����жϱ�־λ�� �����жϱ�־λ
													break;
				default:	break;
    }
    //�ж����󴫵ݵ�ʹ�ܺͽ��ܿ���λ��IRqInv��λ�ܽ�IRQ��Status1Reg��IRqλ��ֵ�෴
    WriteRawRC(ComIEnReg,irqEn|0x80);
		//�������ж�λ��Set1��λ����ʱ��CommIRqReg������λ����
    ClearBitMask(ComIrqReg,0x80);	
		//����ֹͣ�����ִ�У�ȡ����ǰ���д��������
    WriteRawRC(CommandReg,PCD_IDLE);
		//��FIFO���棬��λFlushBuffer����ڲ�FIFO�Ķ���дָ���Լ�ErrReg��BufferOvfl��־λ�����
    SetBitMask(FIFOLevelReg,0x80);	 	
    
    for (i=0; i<InLenByte; i++)
    {
			//64�ֽ�FIFO������������������������д�뵽FIFO��
			WriteRawRC(FIFODataReg, pIn [i]);    
		}
		//���������֣�//д����
    WriteRawRC(CommandReg, Command);	  
 
    //�ж������Ƿ��Ƿ��ͻ��������
    if (Command == PCD_TRANSCEIVE)
    {
			 //StartSend��λ�������ݷ��� ��λ���շ�����ʹ��ʱ����Ч
		   SetBitMask(BitFramingReg,0x80);   //��ʼ����
		}	
    										 
    i = 600;//����ʱ��Ƶ�ʵ���������M1�����ȴ�ʱ��25ms
    do 
    {
			 //��ȡ�ж������־λ��//��ѯ�¼��ж�
        n = ReadRawRC(ComIrqReg);   
        i--;
    }
    while ((i!=0) && !(n&0x01) && !(n&waitFor)); //�˳�����i=0,��ʱ���жϣ���д��������
		//��������StartSendλ
    ClearBitMask(BitFramingReg,0x80);

    if (i!=0) //����δ���  
    {    
			  ////�������־�Ĵ���BufferOfI CollErr ParityErr ProtocolEr
        if(!(ReadRawRC(ErrorReg)&0x1B))
        {
            status = MI_OK;
            if(n & irqEn & 0x01) //�Ƿ�����ʱ���ж�
            {
   						status = MI_NOTAGERR;     
						}
						//��������Ƿ�Ϊ���ͽ�������
            if(Command == PCD_TRANSCEIVE)
            { 
							  //��FIFO�б�����ֽ���
               	n = ReadRawRC(FIFOLevelReg);
							  ////�����յ����ֽڵ���Чλ��
              	lastBits = ReadRawRC(ControlReg) & 0x07;
                if(lastBits)//��Ϊ0 
                {
									//N���ֽ�����ȥ1�����һ���ֽڣ�+���һλ��λ�� ��ȡ����������λ��
								  *pOutLenBit = (n-1)*8 + lastBits;   
								}
                else 
                {
									//�����յ����ֽ������ֽ���Ч
   								*pOutLenBit = n*8;   
								}
                if (n == 0)
                {
								   n = 1;    
								}
                if(n > MAXRLEN)  //FIFO�ĳ���
                {
   								n = MAXRLEN;   
								}
                for (i=0; i<n; i++)
                {
									 //��FIFO��ȡ����
								   pOut [i] = ReadRawRC(FIFODataReg);    
								}
             }
        }
        else
        {   status = MI_ERR;   }
        
    }
   
    //ֹͣ��ʱ��
    SetBitMask(ControlReg,0x80); 
    //ֹͣ��ǰ���д��������		
    WriteRawRC(CommandReg,PCD_IDLE); 
    return status;
}








/*******************************************************************
* ��������     PcdRequest()
* �������� ��   	Ѱ��
*����˵��: 
req_code:Ѱ����ʽ
                0x52 = Ѱ��Ӧ�������з���14443A��׼�Ŀ�
                0x26 = Ѱδ��������״̬�Ŀ�
pTagType����Ƭ���ʹ���
                0x4400 = Mifare_UltraLight
                0x0400 = Mifare_One(S50)
                0x0200 = Mifare_One(S70)
                0x0800 = Mifare_Pro(X)
                0x4403 = Mifare_DESFire
* ����ֵ˵�����ɹ�����MI_OK
*******************************************************************/               
char PcdRequest(u8 req_code,u8 *pTagType)
{
	char status;  
	u8 unLen;
	u8 ucComMF522Buf[MAXRLEN]; 
 ////����ָʾMIFARECyptol��Ԫ��ͨ�Լ����п�������ͨ�ű����ܵ����
	ClearBitMask(Status2Reg,0x08);
	//���巢�͵����һ���ֽڵ���λ
	WriteRawRC(BitFramingReg,0x07);
	//���������������Ĺܽ�//TX1,TX2������źŴ��ݾ����͵��Ƶ�13.56�������ز��ź�
	SetBitMask(TxControlReg,0x03);
  //��Ѱ����ʽ�浽����
	ucComMF522Buf[0] = req_code;
  //����Ѱ����ʽ�����ܷ��ص����ݼ��ֳ�
	status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,1,ucComMF522Buf,&unLen);
//Ѱ���ɹ����жϷ��ؿ����� 
	if ((status == MI_OK) && (unLen == 0x10))  
	{    
		*pTagType     = ucComMF522Buf[0];
		*(pTagType+1) = ucComMF522Buf[1];
	}
	else
	{   status = MI_ERR;   }
   
	return status;
}

/*******************************************************************
* ��������     PcdAnticoll()
* �������� ��   ����ײ
* ����˵����     pSnr :��Ƭ���кţ�4�ֽ�
* ����ֵ˵����   �ɹ�����MI_OK
*******************************************************************/
char PcdAnticoll(u8 *pSnr)
{
    char   status;
    u8   i,snr_check=0;
    u8   unLen;
    u8   ucComMF522Buf[MAXRLEN]; 
	  //������շ������ı�־λ
    ClearBitMask(Status2Reg,0x08);
	  //����Ĵ��� ֹͣ�շ�
    WriteRawRC(BitFramingReg,0x00);
	  //�����н��յ�λ�ڳ�ͻ�󽫱����
    ClearBitMask(CollReg,0x80);
    //������ײ����浽����
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x20;
    //���ͷ���ײ����
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,2,ucComMF522Buf,&unLen);
    //ͨ�ųɹ�
    if (status == MI_OK)
    {
    	 for (i=0; i<4; i++)
         {   
             *(pSnr+i)  = ucComMF522Buf[i];//���صĿ����кŴ浽����
             snr_check ^= ucComMF522Buf[i];
         }
         if (snr_check != ucComMF522Buf[i]) //У�鷵�ص������Ƿ���ȷ
         {
   				 status = MI_ERR;    
				 }
    }
    //�ָ��üĴ�����7��λ��Ҫ��ֻ�ڷ���ͻ��Ϊ0���������Ӧ����Ϊ,1
    SetBitMask(CollReg,0x80);
    return status;
}



/*******************************************************************
* ��������     PcdSelect()
* �������� ��   ѡ����Ƭ 
* ����˵����     pSnr:��Ƭ���кţ�4�ֽ�
* ����ֵ˵����   �ɹ�����MI_OK
*******************************************************************/
char PcdSelect(u8 *pSnr)
{
    char status;
    u8 i;
    u8 unLen;
    u8 ucComMF522Buf[MAXRLEN]; 
    //����ײ����浽����   
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x70;
    ucComMF522Buf[6] = 0;
	
    for (i=0; i<4; i++) //��֤���ź�
    {
    	ucComMF522Buf[i+2] = *(pSnr+i);
    	ucComMF522Buf[6]  ^= *(pSnr+i);
    }
		//CRCУ��
    CalulateCRC(ucComMF522Buf,7,&ucComMF522Buf[7]);
    //�����־λ
    ClearBitMask(Status2Reg,0x08);
		//���Ϳ��Ų�ѡ���ÿ�
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,9,ucComMF522Buf,&unLen);
    //�����Ƿ�ѡ��
    if ((status == MI_OK) && (unLen == 0x18))
    {   status = MI_OK;  }
    else
    {   status = MI_ERR;    }

    return status;
}
 


/*******************************************************************
* ��������     CalulateCRC()
* �������� ��  ��MF522����CRC16����
*******************************************************************/
void CalulateCRC(u8 *pIn ,u8 len,u8 *pOut )
{
    u8   i,n;
	  //����CRC�ж�����
    ClearBitMask(DivIrqReg,0x04);
	  //ȡ����ǰ����
    WriteRawRC(CommandReg,PCD_IDLE);
	  //���FIFO�������ı�־λ
    SetBitMask(FIFOLevelReg,0x80);
	  
    for (i=0; i<len; i++)
    {
			//д�����ݵ�FIFO
		  WriteRawRC(FIFODataReg, *(pIn +i));   
		}
		//��ʼCRCУ������  
    WriteRawRC(CommandReg, PCD_CALCCRC);
    i = 0xFF;
    do 
    {
			  //�ȴ�CRCУ�����
        n = ReadRawRC(DivIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x04));
		//��У������������
    pOut [0] = ReadRawRC(CRCResultRegL);
    pOut [1] = ReadRawRC(CRCResultRegM);
}


/*------------------------------------------------------��/д��--------------------------------------------------------------*/





/*******************************************************************
* ��������     PcdAuthState()
* �������� ��   ��֤��Ƭ����
*����˵��: auth_mode : ������֤ģʽ
                 0x60 = ��֤A��Կ
                 0x61 = ��֤B��Կ 
								addr �����ַ
								pKey ������
								pSnr ����Ƭ���кţ�4�ֽ�
* ����ֵ˵����   �ɹ�����MI_OK
*******************************************************************/             
char PcdAuthState(u8 auth_mode,u8 addr,u8 *pKey,u8 *pSnr)
{
    char status;
    u8 unLen;
		u8 ucComMF522Buf[MAXRLEN]; 
    //������浽����
    ucComMF522Buf[0] = auth_mode;
    //�����ַ�浽����
	  ucComMF522Buf[1] = addr;
	  //����������кŸ��Ƶ�������  
    memcpy(&ucComMF522Buf[2], pKey, 6); 
    memcpy(&ucComMF522Buf[8], pSnr, 4);
	  //������֤���������������
    status = PcdComMF522(PCD_AUTHENT,ucComMF522Buf,12,ucComMF522Buf,&unLen);
    //�ж�������֤�ɹ�����ʧ��
	  if((status != MI_OK) || (!(ReadRawRC(Status2Reg) & 0x08)))
    {
  		status = MI_ERR;   
		}
    return status;
}

/*******************************************************************
* ��������     PcdRead()
* �������� ��   ��ȡM1��һ������ 
*����˵��: addr �����ַ
           p  �����������ݣ�16�ֽ�
* ����ֵ˵����   �ɹ�����MI_OK
*******************************************************************/ 
char PcdRead(u8 addr,u8 *p )
{
    char status;
    u8 unLen;
    u8 i,ucComMF522Buf[MAXRLEN]; 
	  //����������浽����
    ucComMF522Buf[0] = PICC_READ;
	  //����ȡ�ĵ�ַ�浽����
    ucComMF522Buf[1] = addr;
	  //У��
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
    //���ն�ȡ��������
  	status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);
    //�ж��Ƿ���ܳɹ�   
  	if ((status == MI_OK) && (unLen == 0x90))
    {
        for (i=0; i<16; i++) //�ɹ��ͽ����ܵ������ݸ�P
        {
  				*(p +i) = ucComMF522Buf[i];   
				}
    }
    else
    {
   		status = MI_ERR;   
		}
    return status;
}

/*******************************************************************
* ��������     PcdWrite()
* �������� ��   д���ݵ�M1��һ��
*����˵��: addr �����ַ
           p  �����������ݣ�16�ֽ�
* ����ֵ˵����   �ɹ�����MI_OK
*******************************************************************/                  
char PcdWrite(u8   addr,u8 *p )
{
    char   status;
    u8   unLen;
    u8   i,ucComMF522Buf[MAXRLEN]; 
    //��д�������������
    ucComMF522Buf[0] = PICC_WRITE;
	  //��д�Ŀ��ַ�浽����
    ucComMF522Buf[1] = addr;
	  //У��
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
    //�����������
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);
    //�ж��Ƿ��ͳɹ�
    if((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {
  		status = MI_ERR;   
		}    
    if (status == MI_OK)   //����ͳɹ�
    {
        for (i=0; i<16; i++)  //�����ݴ浽������  
        {    
        	ucComMF522Buf[i] = *(p +i);   
        }
				//У��
        CalulateCRC(ucComMF522Buf,16,&ucComMF522Buf[16]);
        //�������ݵ���  
        status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,18,ucComMF522Buf,&unLen);
				//�ж��Ƿ��ͳɹ�
        if((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
        {
	  			status = MI_ERR;   
				}
    }
    
    return status;
}

 