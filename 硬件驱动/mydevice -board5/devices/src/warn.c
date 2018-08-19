/***************************************************************************
*FileName:		warn.c
*Description: ������PB9��������PB8 ��ʼ���ӿ�ʵ��
*Author:			yhs
*CreatDate:		2018-7-15
*Copyright		www.yanghs97@163.com
*UpDate:			�޸���		�޸�����
*2018-7-11		��Bɭ	 	��ӳ�ʼ������ʵ��
****************************************************************************/
#include "warn.h"
#include "briupDelay.h"

//��ʼ�������Ʊ������ӿ�
void warnInit(void)
{
	//����GPIOB��ʱ��
	RCC->APB2ENR |= 1<<3 | 1<<0;
	
	//��PB8��PB9���ó��������50MHzģʽ
	GPIOB->CRH &= 0xFFFFFF00;
	GPIOB->CRH |= 0x00000033;
	
	//Ĭ�Ϲرձ����ƺͱ�����
	GPIOB->ODR &= ~(1<<9|1<<8); 
}

//����������
void warnLed(void)
{
	GPIOB->ODR |= 1<<9;
	
}
//�رձ�����
void closeWarnLed(void)
{
	GPIOB->ODR &= ~(1<<9);
}
	
//����������
void warn(void)
{
	GPIOB->ODR |= 1<<8;
}

//�رձ�����
void closeWarn(void)
{
		GPIOB->ODR &= ~(1<<8);
}


