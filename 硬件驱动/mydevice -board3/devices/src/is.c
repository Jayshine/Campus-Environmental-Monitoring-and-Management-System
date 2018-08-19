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
	//����GPIOCB��ʱ��
	RCC->APB2ENR |= 1<<3;
	//��������ʱ��
	RCC->APB2ENR |= 1<<0;
	
	//PB7��������
	GPIOB->CRL &= ~0xF0000000;
	GPIOB->CRL |= 0x80000000;
	GPIOB->ODR &= ~(1<<7);
	
	//�ⲿ�жϵĶ˿�����
	AFIO->EXTICR[1] |= 0x1000;
	
	//�ⲿ�жϵĴ���ģʽ��ʹ��
	EXTI->RTSR |= 1<<7;
	EXTI->FTSR &= ~(1<<7);
	EXTI->IMR |= 1<<7;
	
	//�ⲿ�ж���13��NVIC���ȼ�
	nvicInit.NVIC_IRQChannel = EXTI9_5_IRQn ;
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

