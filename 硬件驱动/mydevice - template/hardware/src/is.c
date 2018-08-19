/***************************************************************************
*FileName:		is.h
*Description: ������⴫������ʼ���ӿ�ʵ��
*Author:			yhs
*CreatDate:		2018-7-11
*Copyright		www.yanghs97@163.com
*UpDate:			�޸���		�޸�����
*2018-7-11		��Bɭ	 	��ӳ�ʼ������ʵ��
****************************************************************************/
#include "is.h"
#include "briupDelay.h"
#include "briupUSART.h"
//��ʼ��������⴫���������ӿ�
void is_Init(void)
{
	NVIC_InitTypeDef nvicInit;
	//����GPIOC��ʱ��
	RCC->APB2ENR |= 1<<4;
	//��������ʱ��
	RCC->APB2ENR |= 1<<0;
	
	//PC13��������
	GPIOC->CRH &= ~0x00F00000;
	GPIOC->CRH |= 0x00800000;
	GPIOC->ODR &= ~(1<<13);
	
	//�ⲿ�жϵĶ˿�����
	AFIO->EXTICR[3] |= 0x0020;
	
	//�ⲿ�жϵĴ���ģʽ��ʹ��
	EXTI->RTSR |= 1<<13;
	EXTI->FTSR &= ~(1<<13);
	EXTI->IMR |= 1<<13;
	
	//�ⲿ�ж���13��NVIC���ȼ�
	nvicInit.NVIC_IRQChannel = EXTI15_10_IRQn ;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 1;
	nvicInit.NVIC_IRQChannelSubPriority = 1;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &nvicInit);
}

//����������⴫�����ĵ�ǰ״̬
u8 havehuman(void)
{
	if( GPIOC->IDR & (1<<13))
		return '1';
	else
		return '0';
}


//==================�ⲿ�жϷ�����=============
void EXTI15_10_IRQHandler(void)
{
	_delay_ms(10);
	//��Ӧ������жϱ�־
	if( GPIOC->IDR & 1<<13)
	{
		EXTI->PR |= 1<<13;
		putDataDma("EXTI13\r\n", 8);
	}
}

