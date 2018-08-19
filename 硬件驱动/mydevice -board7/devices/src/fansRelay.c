/***************************************************************************
*FileName:		fansRelay.c
*Description: ���Ⱥͼ̵����ӿ�ʵ��
*Author:			yhs
*CreatDate:		2018-7-15
*Copyright		www.yanghs97@163.com
*UpDate:			�޸���		�޸�����
*2018-7-11		��Bɭ	 	��ӳ�ʼ������ʵ��
****************************************************************************/
#include "fansRelay.h"

//��ʼ�����Ⱥͼ̵���  ���ȣ�PA6 �̵���1��PA5 �̵���2��PA4
void fanRelayInit(void)
{
	//����GPIOA��ʱ��
	RCC->APB2ENR |= 1<<2;
	
	//ʹ��PA6��PA5��PA4�������50MHzģʽ
	GPIOA->CRL &= 0xF000FFFF;
	GPIOA->CRL |= 0x03330000;
	
	//Ĭ�Ϲرշ��ȣ��̵���
	GPIOA->ODR &= ~(1<<4| 1<<5 | 1<<6);
	
}

//���Ʒ��� key:1-�� 0-��
void fan(u8 key)
{
	if(key == 0)
		GPIOA->ODR &= ~(1<<6);
	else
		GPIOA->ODR |= 1<<6;
}

//���Ƽ̵���1 key:1-�� 0-��
void relay1(u8 key)
{
	if(key == 0)
		GPIOA->ODR &= ~(1<<5);
	else
		GPIOA->ODR |= 1<<5;
}

//���Ƽ̵���2 key:1-�� 0-��
void relay2(u8 key)
{
	if(key == 0)
		GPIOA->ODR &= ~(1<<4);
	else
		GPIOA->ODR |= 1<<4;
}


