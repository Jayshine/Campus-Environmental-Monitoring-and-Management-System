/***************************************************************************
*FileName:		basePeripheral.c
*Description: LED�Ʋ����ӿڡ�
							�����������ӿ�ʵ��
*Author:			yhs
*CreatDate:		2018-7-11
*Copyright		www.yanghs97@163.com
*UpDate:			�޸���		�޸�����
*2018-7-11		��Bɭ	 	��ӳ�ʼ������ʵ��
****************************************************************************/

#include "basePeripheral.h"

//����LED�ƵĽӿڲ���
void baseLedSet(u8 led)
{
	if(led>7)
		return;
	switch( led)
	{
		case 0:
			GPIOA->ODR |= (1<<8 | 1<<11 | 1<<12);
			break;
		case LED_R:
			GPIOA->ODR |= (1<<11 | 1<<12);
			GPIOA->ODR &= ~(1<<8);
			break;
		case LED_G:
			GPIOA->ODR |= (1<<8 | 1<<12);
			GPIOA->ODR &= ~(1<<11);
			break;
		case LED_B:
			GPIOA->ODR |= (1<<8 | 1<<11);
			GPIOA->ODR &= ~(1<<12);
			break;
		case LED_YELLOW:
			GPIOA->ODR |= (1<<12);
			GPIOA->ODR &= ~(1<<8 | 1<<11);
			break;
		case LED_PURPLE:
			GPIOA->ODR |= (1<<11);
			GPIOA->ODR &= ~(1<<8 | 1<<12);
			break;
		case LED_CYAN:
			GPIOA->ODR |= (1<<8);
			GPIOA->ODR &= ~(1<<11 | 1<<12);
			break;
		case LED_WHITE:
			GPIOA->ODR &= ~(1<<8 | 1<<11 | 1<<12);
			break;
	}
}


//����BEEP�ӿڲ���
void baseBeepSet(u8 set)
{
	if(set !=0)
		GPIOA->ODR |= 1<<15;
	else
		GPIOA->ODR &= ~(1<<15);
}
