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
	//����GPIOB��ʱ��
	RCC->APB2ENR |= 1<<3;
	
	//ʹ��PB6��PB5��PB4�������50MHzģʽ
	GPIOB->CRL &= 0xF000FFFF;
	GPIOB->CRL |= 0x03330000;
	
	//Ĭ�Ϲرշ��ȣ��̵���
	GPIOB->ODR |= 1<<4| 1<<5 | 1<<6;
	
}

//���Ʒ��� key:1-�� 0-��
void fan(u16 key)
{
	if(key == 1)
		GPIOB->ODR &= ~(1<<6);
	else
		GPIOB->ODR |= 1<<6;
}

//���Ƽ̵���1 key:1-�� 0-��
void relay1(u16 key)
{
	if(key == 1)
		GPIOB->ODR &= ~(1<<5);
	else
		GPIOB->ODR |= 1<<5;
}

//���Ƽ̵���2 key:1-�� 0-��
void relay2(u16 key)
{
	if(key == 1)
		GPIOB->ODR &= ~(1<<4);
	else
		GPIOB->ODR |= 1<<4;
}


