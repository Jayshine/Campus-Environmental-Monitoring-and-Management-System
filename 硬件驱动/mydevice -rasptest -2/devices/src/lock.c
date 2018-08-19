/***************************************************************************
*FileName:		lock.c
*Description: ������ӿ�ʵ��
*Author:			yhs
*CreatDate:		2018-7-15
*Copyright		www.yanghs97@163.com
*UpDate:			�޸���		�޸�����
*2018-7-11		��Bɭ	 	��ӳ�ʼ������ʵ��
****************************************************************************/
#include "lock.h"
#include "briupDelay.h"

//��ʼ������� PB9 �ߵ�ƽ��Ч
void lockInit(void)
{
	//��ʼ��GPIOBʱ��
	RCC->APB2ENR |= 1<<3;
	
	//��PB9����Ϊͨ���������50MHz
	GPIOB->CRH &= 0xFFFFFF0F;
	GPIOB->CRH |= 0x00000030;
	
	//Ĭ��Ϊ�͵�ƽ
	GPIOB->ODR &= ~(1<<9);
}

//���ص���� key=1 ���� key=0 ����
void lock(u16 key)
{
	if(key==1)
	{
		GPIOB->ODR |= 1<<9;
		_delay_sec(2);
		GPIOB->ODR &= ~(1<<9);
	}	
	else
		GPIOB->ODR &= ~(1<<9);
}



