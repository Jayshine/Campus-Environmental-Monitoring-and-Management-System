/***************************************************************************
*FileName:		fire.c
*Description: ����PB6�����PB0������PB1�������ӿ�ʵ��
							ͨ����ѯ��ʽʵ��
							ͨ���жϷ�ʽʵ��
*Author:			yhs
*CreatDate:		2018-7-15
*Copyright		www.yanghs97@163.com
*UpDate:			�޸���		�޸�����
*2018-7-11		��Bɭ	 	��ӳ�ʼ������ʵ��
****************************************************************************/
#include "fire.h"
#include "briupDelay.h"
#include "briupUSART.h"
#include "briupZigbee.h"
#include "basePeripheral.h"
#include "briupGPIO.h"
#include "protocol.h"

volatile u8 statFlag;

//��ʼ���𾯴�������ؽӿ�
void fireInit(void)
{
	NVIC_InitTypeDef nvicInit;
	//����GPIOB��ʱ��
	RCC->APB2ENR |= 1<<3;
	//��������ʱ��
	RCC->APB2ENR |= 1<<0;
	
	//ʹ��PB0��PB1��PB6�������� PB7��������
	GPIOB->CRL &= 0X00FFFF00;
	GPIOB->CRL |= 0X88000088;
	GPIOB->ODR |= (1<<6)|(1<<1)|(1<<0);
	GPIOB->ODR &= ~(1<<7);
	
	//�ⲿ�жϵĶ˿�����
	AFIO->EXTICR[0] |= 0x0011;
	AFIO->EXTICR[1] |= 0x1100;
	
	//�ⲿ�жϵĴ���ģʽ��ʹ��
	EXTI->RTSR &= ~(1<<0 | 1<<1 | 1<<6 | 1<<7);
	EXTI->FTSR |= 1<<0 | 1<<1 | 1<<6 | 1<<7;
	EXTI->IMR |= 1<<0 | 1<<1 | 1<<6 | 1<<7;
	
	//�ⲿ�ж���0��1��6��7��NVIC���ȼ�
	nvicInit.NVIC_IRQChannel = EXTI0_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 1;
	nvicInit.NVIC_IRQChannelSubPriority = 2;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInit);
	
	nvicInit.NVIC_IRQChannel = EXTI1_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 1;
	nvicInit.NVIC_IRQChannelSubPriority = 2;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInit);
	
	nvicInit.NVIC_IRQChannel = EXTI9_5_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 1;
	nvicInit.NVIC_IRQChannelSubPriority = 2;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInit);
	
}

//��ȡ��������״̬
u8 fogStat(void)
{
	_delay_ms(10);
	if(!(GPIOB->IDR & (1<<6)))
		return '1';
	else
		return '0';
}
//��ȡ��⴫����״̬
u8 fireStat(void)
{
	if(!(GPIOB->IDR & (1<<0)))
		return '1';
	else
		return '0';
}
//��ȡ���鴫����״̬
u8 CH4Stat(void)
{
	{
	if(!(GPIOB->IDR & (1<<1)))
		return '1';
	else
		return '0';
}
}
//��ȡ���⴫����״̬
u8 infrared(void)
{
	if( GPIOB->IDR & (1<<7))
		return '1';
	else
		return '0';
}

//=========�ⲿ�жϷ�����
//��������
void EXTI9_5_IRQHandler(void)
{
	_delay_ms(100);
	//��Ӧ������жϱ�־
	if( !(GPIOB->IDR & 1<<6))
	{	
		if(!(statFlag & 0x01)) statFlag |= 1<<0;
	}
	EXTI->PR |= 1<<6;
//	if( GPIOB->IDR & 1<<7)
//	{
//		EXTI->PR |= 1<<7;
//		if(!(statFlag & 1<<4)) statFlag |= 1<<4;
//	}
//	
}
//��⴫����
void EXTI0_IRQHandler(void)
{
	
	_delay_ms(100);
	//��Ӧ������жϱ�־
	if( !(GPIOB->IDR & 1<<0))
	{					
		if(!(statFlag & 1<<6)) statFlag |= 1<<6;
	}
	EXTI->PR |= 1<<0;
}
//���鴫����
void EXTI1_IRQHandler(void)
{
	_delay_ms(100);
	//��Ӧ������жϱ�־
	if( !(GPIOB->IDR & 1<<1))
	{
		if(!(statFlag & 1<<2)) statFlag |= 1<<2;
	}
	EXTI->PR |= 1<<1;
}

