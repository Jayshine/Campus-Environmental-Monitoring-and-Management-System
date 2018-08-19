/***************************************************************************
*FileName:		oeSwitch.c
*Description: ��翪�صĳ�ʼ�������ӿ�ʵ��
							ͨ����ѯ�ķ�ʽ���ع�翪��״̬
							ͨ���жϵķ�ʽ����翪��״̬
*Author:			yhs
*CreatDate:		2018-7-13
*Copyright		www.yanghs97@163.com
*UpDate:			�޸���		�޸�����
*2018-7-11		��Bɭ	 	��ӳ�ʼ������ʵ��
****************************************************************************/
#include "oeSwitch.h"
#include "briupUsart.h"
#include "briupDelay.h"
#include "warn.h"
#include "briupZigbee.h"
#include "protocol.h"

volatile u8 flag;

//��翪�صĳ�ʼ���ӿ�
void oeSwitchInit(void)
{
	NVIC_InitTypeDef nvicInit;
	
	//��ʼ����翪��IO����
	RCC->APB2ENR |= 1<<3;	//PBʱ��
	RCC->APB2ENR |= 1<<0;	//AFIOʱ��
	
	//PB0 PB1 ��������
	GPIOB->CRL &= ~0x000000FF;
	GPIOB->CRL |=  0x00000088;
	GPIOB->ODR |= 1<<1 | 1<<0;
	
	//�ⲿ�ж��ߵĶ˿�����
	AFIO->EXTICR[0] |= 0x0011;
	
	//�ⲿ�жϵĴ���ģʽ��ʹ��
	EXTI->RTSR &= ~(1<<1 | 1<<0);
	EXTI->FTSR |= 1<<1 | 1<<0;
	EXTI->IMR |= 1<<1 | 1<<0;
	
	//�ⲿ�ж���0��NVIC���ȼ�
	nvicInit.NVIC_IRQChannel = EXTI0_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 1;
	nvicInit.NVIC_IRQChannelSubPriority = 1;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &nvicInit);
	
	//�ⲿ�ж���1��NVIC���ȼ�
	nvicInit.NVIC_IRQChannel = EXTI1_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 1;
	nvicInit.NVIC_IRQChannelSubPriority = 2;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &nvicInit);
}

//���ض��俪�صĵ�ǰ״̬
u8 currSwitchStat(void)
{
	if( GPIOB->IDR & (1<<1))
		return 1;
	else
		return 0;
}

//���ط��俪�صĵ�ǰ״̬
u8 refSwitchStat(void)
{
	if( GPIOB->IDR & (1<<0))
		return 1;
	else
		return 0;
}

//=======================�ⲿ�жϷ�����==========
void EXTI0_IRQHandler(void)
{
	_delay_ms(10);
	//��Ӧ������жϱ�־
	if( !(GPIOB->IDR & 0x01))
	{
		u8 buf[1]={0x01};
		protocolSend(0x01,0x04,0x01,buf);
		flag = 0x01;
	}
	EXTI->PR |= 1<<0;
}

void EXTI1_IRQHandler(void)
{
	_delay_ms(10);
	//��Ӧ������жϱ�־
	if( !(GPIOB->IDR & 0x02))
	{
		u8 buf[1]={0x01};
		protocolSend(0x01,0x03,0x01,buf);
		flag = 0x01;
	}
	EXTI->PR |= 1<<1;
}

