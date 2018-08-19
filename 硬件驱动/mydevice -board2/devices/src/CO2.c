/***************************************************************************
*FileName:		CO2.c
*Description: CO2�������Ľӿ�ʵ��
*Author:			yhs
*CreatDate:		2018-7-18
*Copyright		www.yanghs97@163.com
*UpDate:			�޸���		�޸�����
*2018-7-11		��Bɭ	 	��ӳ�ʼ������ʵ��
****************************************************************************/
#include "CO2.h"
#include "briupUsart3.h"
#include "briupDelay.h"

//extern volatile u8 UsartR_Finished;
//extern u8 Usart3Buffer[15];
unsigned char CO2_R_COM[7]={0X42,0X4D,0XE3,0X00,0X00,0X01,0X72};

void CO2_Measure(u8* CO2_Value_H, u8* CO2_Value_L)
{
	u8 len,buf[50];
	U3putBuffer(CO2_R_COM,7);//���ͻ�ȡ����ָ��
	
	do
	{
		len=usart3GetBuffer(buf);
		_delay_ms(50);
	}while(len==0);
	*CO2_Value_H = buf[4];
	*CO2_Value_L = buf[5];
	
//	while(!UsartR_Finished);
//	*CO2_Value_H = Usart3Buffer[4];
//	*CO2_Value_L = Usart3Buffer[5];
	
}

//void CO2_Init()
//{
//	usart3Init(36,9600);
//}

