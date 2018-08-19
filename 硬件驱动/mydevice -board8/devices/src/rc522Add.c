/********************
* FileName: 	rc522Add.h
* Description: 	
			��Ƶ���Ķ�ȡ��д��ӿ�����
* Author:		Dennis Chen
* CreateDate:	2018-7-11
* Copyright:	www.briup.com
* Update:	��������  ������  ��������
*	2018-7-11	����	��ӳ�ʼ���ӿ�����
*********************/

#include "basePeripheral.h"
#include "briupGPIO.h"
#include "rc522Add.h"
#include "rc522.h"
#include "mini12864.h"
#include "briupUSART.h"

#include <string.h>
#include <stdio.h>

int fputc(int ch,FILE *stream)
{
	putChar((uint8_t)ch);
	return ch;
}

//����������ݵĶ���
u16  KuaiN;//��ʾҪ���ʵĿ�
u8 oprationcard,bSendID;
u8 Read_Data[16],
	 PassWd[6]={0xff,0xff,0xff,0xff,0xff,0xff},
	 WriteData[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	 RevBuffer[30],
	 MLastSelectedSnr[4],
	 NewKey[16];		       
	 
// char cardID[4];//����
u8 cardID[4];//����
	 
u8 volatile flag;

u8 flag_com;   //�Ѷ������ı�־

double temp_money=0;//������32λ��Ч���֣�����

u8 administrator[4]={0x34,0xb2,0x1e,0xeb};//����Ա����
u8 datatemp[4];	 //��AT24C02�������Ŀ���
	 

//���ڷ���һ���ֽڣ�8λ����������
#define USART_FLAG_TXE   ((u16)0x0080)
	 
void UART1_SendByte(u16 Data)
{ 
   while (!(USART1->SR & USART_FLAG_TXE));
   USART1->DR = (Data & (u16)0x01FF);	    
}

 /*******************************************************************************
* ��  ��  :  ��ʼ�����ж���������ݵ�����
* ��  ��  :  ��
* ��  ��  :  ��
* ��  ��  :  ��
*******************************************************************************/
void InitAlldata(void)
{	
  baseLedSet( LED_BLACK);
	flag_com=0;//�Ѷ������ı�־
  KuaiN=0;
  oprationcard=0;
  bSendID=0;
}


 /*******************************************************************************
* ��  ��  :  �жϲ������ͣ����Ϳ��š�������д�����޸����� ��
* ��  ��  :  0xa0,0xa1,0xa2,0xa3
* ��  ��  :  ��
* ��  ��  :  ��
*******************************************************************************/
void command_choose(u8 command)
{
//   u8 ii;
	
	InitAlldata();			//��ʼ�����ж���������ݵ�����
	
  switch(command)
  {
    case 0xa0://���Ϳ���
							oprationcard=SENDID;
							break;
		
    case 0xa1://������
							oprationcard=READCARD;
// 							for(ii=0;ii<6;ii++)
// 							{
// 								PassWd[ii]=RevBuffer[ii+2];//RevBuffer[]����ĵ������ڰ˸����ݱ�ʾ����
// 							} 
							KuaiN=4;//��ʾҪ�����鼸�����4���ڶ��������ĵ�һ�����ݿ飩
							break;
			
    case 0xa2://д����
							oprationcard=WRITECARD;
// 							for(ii=0;ii<6;ii++)
// 							{
// 								PassWd[ii]=RevBuffer[ii+2];//RevBuffer[]����ĵ������ڰ˸����ݱ�ʾ����
// 							} 
							KuaiN=4;//��ʾҪ�����鼸�����4���ڶ��������ĵ�һ�����ݿ飩
// 							for(ii=0;ii<16;ii++)
// 							{
// 								WriteData[ii]=RevBuffer[ii+9];//Ҫд���16������
// 							}
							break;  
			
    case 0xa3://�޸�����
							oprationcard=KEYCARD; 
// 							for(ii=0;ii<6;ii++)
// 							{
// 								PassWd[ii]=RevBuffer[ii+2];//RevBuffer[]����ĵ������ڰ˸����ݱ�ʾ����
// 							} 
							KuaiN=7;//��ʾҪ�����鼸�����7���ڶ���������β������A�������
// 							for(ii=0;ii<6;ii++)
// 							{
// 								NewKey[ii]=RevBuffer[ii+9];
// 								NewKey[ii+10]=RevBuffer[ii+9];//RevBuffer[]����ĵ�ʮ����ʮ������ݱ�ʾ������
// 							}
							break;
			
    default:  break;                     
  }
}


 /*******************************************************************************
* ��  ��  :  ��Ѱ��������ײ��ѡ�������Ϳ��š�������д�����޸�������в���
             �ɹ���LED0����
* ��  ��  :  ��
* ��  ��  :  ��
* ��  ��  :  ��
*******************************************************************************/
void ctrlprocess(void)
{
  unsigned char ii;
  char status;
  
  PcdReset();//��λRC522
  status=PcdRequest(PICC_REQIDL,&RevBuffer[0]);//Ѱ��������δ��������״̬�Ŀ������ؿ�Ƭ���� 2�ֽ�
  if(status!=MI_OK) return ;
 
  status=PcdAnticoll(&RevBuffer[2]);//����ײ�����ؿ������к� 4�ֽ�
  if(status!=MI_OK) return ;
	
  memcpy(MLastSelectedSnr,&RevBuffer[2],4);//��&RevBuffer[2]�����ַ��ʼ����4���ֽڵ�ָ����ʼλ��MLastSelectedSnr
  status=PcdSelect(MLastSelectedSnr);//ѡ��
  if(status!=MI_OK) return ;
	
	
	
	//�޸���������
  if(oprationcard==KEYCARD)
  {
    oprationcard=0;    
    status=PcdAuthState(PICC_AUTHENT1A,KuaiN,PassWd,MLastSelectedSnr);//��֤A�ܳ�
    if(status!=MI_OK) return ;
		
    status=PcdWrite(KuaiN,&NewKey[0]);//�޸�����
    if(status!=MI_OK) return ;	
		
    PcdHalt();//���Ƭ��������״̬
	baseLedSet( LED_WHITE);

		flag_com=1;//�Ѷ������ı�־
  }
	
	//�������������
  else if(oprationcard==READCARD)
  {
    oprationcard=0;
    status=PcdAuthState(PICC_AUTHENT1A,KuaiN,PassWd,MLastSelectedSnr);//��֤A�ܳ�
    if(status!=MI_OK)  return ;
    
    status=PcdRead(KuaiN,Read_Data);//��M1��ĳһ���ȡ�������ݴ����Read_Data[]������
    if(status!=MI_OK)  return ;
    
		for(ii=0;ii<16;ii++)UART1_SendByte(Read_Data[ii]);//������������ͨ�����ڷ��͸�����	   
		
//     for(ii=0;ii<16;ii++)
// 			LCD_ShowNum(10+ii*8,180,Read_Data[ii],1,16);//��ʾ������16������
		
    PcdHalt();//���Ƭ��������״̬
	
	baseLedSet( LED_WHITE);

		flag_com=1;//�Ѷ������ı�־
  }
	
	//д�����������
  else if(oprationcard==WRITECARD)
  {
    oprationcard=0;
    status=PcdAuthState(PICC_AUTHENT1A,KuaiN,PassWd,MLastSelectedSnr);//��֤A�ܳ�
    if(status!=MI_OK) return ;

    status=PcdWrite(KuaiN,&WriteData[0]);//��WriteData[]�����е�����д��M1��ĳһ����
    if(status!=MI_OK) return ;
		
		for(ii=0;ii<16;ii++)UART1_SendByte(WriteData[ii]);//��д�����ڵ�����ͨ�����ڷ��͸�����	   

		PcdHalt();//���Ƭ��������״̬
		
	baseLedSet( LED_WHITE);

		flag_com=1;//�Ѷ������ı�־		
  } 
	
	//��ʾ�������������ѧ�š����ţ�
  else if(oprationcard==SENDID)
  {
    oprationcard=0;
		
    for(ii=0;ii<4;ii++)
    {
	  	cardID[ii]=MLastSelectedSnr[ii];//cardID[]�����4��2λ��16������
			
// 			UART1_SendByte(MLastSelectedSnr[ii]);//�����ţ�ID��ͨ�����ڷ��͵�����
				printf("ID=%d\n",MLastSelectedSnr[ii]);
			
// 			LCD_ShowNum(10+ii*8,150,MLastSelectedSnr[ii],3,16);//��ʾID��3λ10��������
    }
		
		PcdHalt();//���Ƭ��������״̬
		
		baseLedSet( LED_WHITE);

		flag_com=1;//�Ѷ������ı�־
		
		flag = 0x01;
  }  
	
}


 /*******************************************************************************
* ��  ��  :  ÿ�������ζ�ʱ���жϣ���50ms����Բ�����������ѡ���жϣ�
* ��  ��  :  ��
* ��  ��  :  ��
* ��  ��  :  ��
*******************************************************************************/
void RC522_work(void)
{  
	ctrlprocess();  //��Ѱ��������ײ��ѡ�������Ϳ��š�������д�����޸�������в���
}


//��10��n�η�
int Mult10(int n)
{  
  int sum = 10;  
  int m;  
  if(n==0) return 1;  
  for(m=1;m<n;m++) sum*=10;  
  return sum;
}


//�����ţ������cardID[]�����У�4��8λ��16��������
void Read_cardID(void)
{
	command_choose(0xa0);	//������	
	RC522_work();					//��  ��  :  ÿ�������ζ�ʱ���жϣ���50ms����Բ�����������ѡ���жϣ�
}


//�������������Read_Data[]�����У�	
//temp_money=Read_overage();
double Read_overage(void)
{
	u8 ii=0;
	double overage=0;
	
	command_choose(0xa1);	//������Ϣ	
	RC522_work();					//��  ��  :  ÿ�������ζ�ʱ���жϣ���50ms����Բ�����������ѡ���жϣ�
		
	for(ii=1;ii<16;ii++)
	{
		if(Read_Data[ii] != 0)
			overage=overage+Read_Data[ii]*Mult10(ii-1); //������������
	}
	overage=overage+Read_Data[0]/10.0;							//����С������
	
	return overage;
}


//д�����������WriteData[]�����У�	
//write_overage(temp_money);
void write_overage(double overage)
{
	u8 ii=0;
	u8 temp=0;
	
	command_choose(0xa2);	//д����Ϣ	
	for(ii=0;ii<16;ii++)
	{
		WriteData[ii]=0;//����
	}
	
	for(ii=15;ii>0;ii--)
	{
		temp=(u8)(overage/Mult10(ii-1));
		WriteData[ii]=temp;
		overage=overage-temp*Mult10(ii-1);
	}
	temp=(u8)(overage*10);
	WriteData[0]=temp;
	
	RC522_work();					//��  ��  :  ÿ�������ζ�ʱ���жϣ���50ms����Բ�����������ѡ���жϣ�
}

/***************************************
*�������ܣ���ʾ���Ŀ��ţ���ʮ��������ʾ
*������x��y ����
*		   p    ���ŵĵ�ַ
*	charcolor �ַ�����ɫ
*	bkcolor   ��������ɫ
***************************************/
void ShowID(u16 x,u16 y, u8 *p, u16 charColor, u16 bkColor)	
{
	u8 num[9];
	u8 i;

	for(i=0;i<4;i++)
	{
		num[i*2]=p[i]/16;
		num[i*2]>9?(num[i*2]+='7'):(num[i*2]+='0');
		num[i*2+1]=p[i]%16;
		num[i*2+1]>9?(num[i*2+1]+='7'):(num[i*2+1]+='0');
	}
	num[8]=0;
	
	putStr( "The Card ID is:");

 	for(i=0;i<9;i++)
	{
		putChar( num[i] + '0');
	}
}

