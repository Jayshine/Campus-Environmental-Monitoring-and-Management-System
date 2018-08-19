/***************************************************************************
*FileName:		briupDelay.c
*Description: ͨ��SysTick��ʱ��ʵ����ʱ����
							������ʱ�ĳ�ʼ�������ӿ�
							��us ΢����ʱ����ms ������ʱ����sec ����ʱ
*Author:			yhs
*CreatDate:		2018-7-12
*Copyright		www.yanghs97@163.com
*UpDate:			�޸���		�޸�����
*2018-7-11		��Bɭ	 	��ӳ�ʼ������ʵ��
****************************************************************************/
#include "briupDelay.h"

//΢��ͺ����Ӧ�ļ�������
static u16 frac_us,frac_ms;

//��ʱ�����ĳ�ʼ���ӿ�
//Input: pclk->оƬ����ʱ�ӣ�MHz��
void _delay_init(u32 pclk)
{
		//���ö�ʱ��
	SysTick->CTRL = 0;
	frac_us=pclk/8;
	frac_ms=frac_us*1000;

}

//��ʱ����
void _delay_us(u32 us)
{
	volatile u32 temp = 0;
	//�رն�ʱ��
	SysTick->CTRL &= ~(1<<0);
	//������װ��ֵ
	SysTick->LOAD=us;
	//��յ�ǰ����ֵ
	SysTick->VAL = 0;
	//�򿪶�ʱ��
	SysTick->CTRL |= 1<<0;
	
	do
	{
		temp=SysTick->CTRL;
	}while(!(temp & (1<<16)) && (temp & 0x01));
	//�ر�SysTick��ʱ��
	SysTick->CTRL &= ~0x01;
}	

void _delay_ms(u32 ms)
{
	volatile u32 temp = 0;
	if( ms > 1800)
		ms = 1800;
	ms *= frac_ms;
	//�رն�ʱ��
	SysTick->CTRL &= ~(1<<0);
	//������װ��ֵ
	SysTick->LOAD=ms;
	//��յ�ǰ����ֵ
	SysTick->VAL = 0;
	//�򿪶�ʱ��
	SysTick->CTRL |= 1<<0;
	
	do
	{
		temp=SysTick->CTRL;
	}while(!(temp & (1<<16)) && (temp & 0x01));
	//�ر�SysTick��ʱ��
	SysTick->CTRL &= ~0x01;
}

//�����sec������λС��
// N sec -> N*1000ms
void _delay_sec(double sec)
{
	u32 count = sec * 1000.0;
	while(count>1800)
	{
		_delay_ms(1800);
		count -= 1800;
	}
	_delay_ms(count);
}

