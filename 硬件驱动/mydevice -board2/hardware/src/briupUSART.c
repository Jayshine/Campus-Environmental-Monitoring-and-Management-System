/***************************************************************************
*FileName:		briupUSART.h
*Description: ʵ�ֳ�ʼ��Dubug���� -> usart1 �ĺ����ӿ�
							ʵ�ִ��ڷ������ݣ�ch / str  /buf
							ʵ�ִ��ڽ������ݣ�ch / str
*Author:			yhs
*CreatDate:		2018-7-12
*Copyright		www.yanghs97@163.com
*UpDate:			�޸���		�޸�����
*2018-7-11		��Bɭ	 	��ӳ�ʼ������ʵ��
****************************************************************************/
#include "briupUSART.h"


//�������ڽ��յ�ѭ�����л�����
static volatile u8 Usart1Buf[256];
//�������ױ�Ǻ���β���
static volatile u16 u1Head,u1Tail;
//ͳ�����һ�ν��յ������ݳ���
static volatile u16 u1Count;

//��ʼ��usart1�ĺ����ӿ�
// pclk������ʱ��
// baud�� Ҫ���õĲ�����
void usart1Init(u8 pclk, u32 baud)
{
	NVIC_InitTypeDef nvicInit;
	
	double temp = (pclk * 1000000.0)/ (16*baud);
	//���㲨���ʷ�Ƶ���ӵ��������ֺ�С������
	u16 mant,frac;
	mant = (u16) temp;
	frac = (temp-mant) * 16;
	//������->���������ʷ�����
	mant = mant <<4 |(frac & 0x0f);
	
	//ʹ��USART1��ʱ��	ʹ��GPIOA��ʱ��
	RCC->APB2ENR |= 1<<14 | 1<<2;
	RCC->AHBENR |= 1<<0;
	
	//PA9->���츴����� PA10->��������
	GPIOA->CRH &= ~0x00000FF0;
	GPIOA->CRH |= 0x000008B0;
	GPIOA->ODR |= 1<<10;
	
	//���ô���
	USART1->BRR=mant;
	//ʹ�ܴ��ڵķ��ͺͽ���
	USART1->CR1 |= 1<<3 | 1<<2;
	//ʹ�ܴ���
	USART1->CR1 |=1<<13;
	//ʹ�ܴ��ڽ����ж�
	USART1->CR1 |= 1<<5;
	//ʹ�ܴ���DMA����
	USART1->CR3 |= 1<<7;
	
	//USART Tx��Ӧ��DMAͨ��
	DMA1_Channel4->CPAR = (u32)&USART1->DR;
	DMA1_Channel4->CMAR = 0;
	DMA1_Channel4->CNDTR = 0;
	DMA1_Channel4->CCR = 0;
	DMA1_Channel4->CCR |= 1<<12 | 1<<7 | 1<<4;
	
	//ע���ж����ȼ����жϱ��
	nvicInit.NVIC_IRQChannel = USART1_IRQn;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 3;
	nvicInit.NVIC_IRQChannelSubPriority = 3;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &nvicInit);
	
}

//���ͺ�������
void putChar( u8 ch)					//����1Byte����
{
	while(!(USART1->SR & (1<<7)));
	USART1->DR = ch;
	
}

//����String���� ��\0��
void putStr( char * str)			
{
	while( *str != '\0')
	{
		putChar( *str);
		str++;
	}
}

//����һ��Buffer
void putBuffer( u8 * buf, u16 len)		
{
	u16 i;
	for( i=0; i<len; i++)
	{
		putChar(*buf);
		buf++;
	}
}
//ͨ��DMA����һ������
void putDataDma( u8 * buf, u16 len)
{
	DMA1_Channel4->CCR &= ~0x01;
	DMA1_Channel4->CMAR = (u32) buf;
	DMA1_Channel4->CNDTR =len;
	DMA1_Channel4->CCR |= 0x01;
}

//���պ�������
u8 getChar( void)
{
	while(!(USART1->SR &(1<<5)));
	return USART1->DR;
}
u8 getStr( char * str)		//���ؽ��յ������ݳ���
{
	u8 len = 0;
	do
	{
		*str = getChar();
		str++;
		len++;
	}while(*(str-1) != '\0');
	return len;	//�����ַ����ĳ���
}

//ͨ��ѭ�����л�ȡһ������
// flag: 
//			0 ֱ�ӻ�ȡ������յ�������
//			1 �жϻ�ȡ��������һ֡Э�������ٷ���
u16 getBuffer( u8 *buf, u8 flag)
{
	u16 temp, i;
	temp = u1Count;
	if( u1Count == 0)
		return 0;
	if(!flag)		//flag ==0
	{
		u1Count = 0;
		for( i = 0;i < temp;i++)
		{
			*buf =Usart1Buf[u1Head];
			buf ++;
			u1Head ++;
			u1Head %= 256;
		}
		return temp;
	}
//	else				//��Э����ж�
//	{
//		
//	}
	return 0;
}

//============�жϷ�����===============
void USART1_IRQHandler(void)
{
	//�ж��Ƿ���յ�����
	if(USART1->SR & (1<<5))
	{
		Usart1Buf[u1Tail] = USART1->DR;
		u1Tail++;
		u1Tail %= 256;
		u1Count ++;
	}
}

