/********************************************************
*FileName:     briupZigbee.c
*Destription:  
*              Zigbee Usart2��ʼ���Ľӿ�ʵ��
*              ͨ��DMA��������
*              ͨ��Usart2�жϵķ�ʽ��������
*Author:      
*CreateDate:   2018-7-15
*Copyright     
*Update:       �޸���    �޸�����
*  2018-7-15     	       ʵ�ֳ�ʼ������
********************************************************/

#include "briupZigbee.h"

//����ѭ������
static volatile u8 zbBuffer[256];
static volatile u16 zbHead, zbTail;
static volatile u16 zbCount=0;


//Zigbee���ڵĳ�ʼ��
void zigbeeInit( u8 pclk, u32 baud)
{
	
	NVIC_InitTypeDef nvicInit;
	
	
	double div= (pclk * 1000000) / (16*baud);
	u16 mant = (u16)div;
	u16 frac = (div - mant) * 16;
	mant = mant << 4 |(frac & 0x0f);
	
	//1. RCC ����GPIOA������ʱ��
	RCC->APB2ENR |= 1<<2;
	RCC->APB1ENR |= 1<<17;       //USART2ʱ��ʹ��
	RCC->AHBENR  |= 0x01;        //DMAʱ��ʹ��
	
	//2. ����PA2 PA3�Ĺ���ģʽ
	//  PA2 -> U2.Tx  PA3 -> U2.Rx
	GPIOA->CRL &= ~0x0000FF00;
	GPIOA->CRL |=  0x00008B00;
	GPIOA->ODR |=  1<<3;
	
	//3.  ����Usart2
	//  ���ô��ڲ�����
	USART2->BRR = mant;
	//����USART2�Ľ���ʹ�ܡ�����ʹ�ܡ�����ʹ�ܺͽ����ж�ʹ�ܣ�DMA����ʹ��
	USART2->CR1 |= 1<<13 | 1<<5 | 1<<3 | 1<<2;	
	USART2->CR3 |= 1<<7;
	
	//��ʼ��DMA  U2. Tx -> DMAͨ��1 7
	DMA1_Channel7->CCR   = 0;
	//ͨ�������ַ
	DMA1_Channel7->CPAR  = (u32) &USART2->DR;
	DMA1_Channel7->CMAR  = 0;
	DMA1_Channel7->CNDTR = 0;
	DMA1_Channel7->CCR   |= 1<<13 | 1<<7 | 1<<4;
	
	nvicInit.NVIC_IRQChannel                   = USART2_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 2;
	nvicInit.NVIC_IRQChannelSubPriority        = 3;
	nvicInit.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init( &nvicInit);
	
}

//ͨ��DMA����һ��buf����
void zigbeeSendBuf( u8 * buf, u16 len)
{
	DMA1_Channel7->CCR   &= ~0x01;
	DMA1_Channel7->CMAR  = (u32) buf;
	DMA1_Channel7->CNDTR = len;
	DMA1_Channel7->CCR   |= 0x01;
}


//��ȡzigbee������
u16 zigbeeGetData( u8 * buf, u8 flag)
{
	u16 temp, i, ck;
	temp = zbCount;
	if( zbCount == 0)
		return 0;

	if(!flag)
	{
		zbCount = 0;
		for( i = 0;i < temp;i ++)
		{
			*buf = zbBuffer[zbHead];
			buf ++;
			zbHead ++;
			zbHead %= 256;
		}
		return temp;
	}
//  ��Э����ж�
	else
	{
		for(i = zbHead; ;i ++)
		{
			i %= 256;
			if( zbBuffer[i] == 0xee && zbBuffer[i + 1] == 0xff)
			{
				ck = 1;
				break;
			}
			if( i == zbTail)
				break;
		}
		if( ck == 0)
			return 0;
		temp = zbCount;
		zbCount = 0;
		for( i = 0; i < temp; i ++)
		{
			*buf = zbBuffer[zbHead];
			buf ++;
			zbHead ++;
			zbHead %= 256;
		}
		return temp;
	}
}


//----------------------------�жϷ�����------------------------------

void USART2_IRQHandler(void)
{
	if( USART2->SR & (1<<5))
	{
		zbBuffer[zbTail] = USART2->DR;
		zbTail ++;
		zbCount ++;
		zbTail %= 256;
	}
}
	



