/***************************************************************************
*FileName:		briupDelay.h
*Description: ͨ��SysTick��ʱ��ʵ����ʱ����
							������ʱ�ĳ�ʼ�������ӿ�
							��us ΢����ʱ����ms ������ʱ����sec ����ʱ
*Author:			yhs
*CreatDate:		2018-7-12
*Copyright		www.yanghs97@163.com
*UpDate:			�޸���		�޸�����
*2018-7-11		��Bɭ	 	��ӳ�ʼ����������
****************************************************************************/
#ifndef __DELAY_H__
#define __DELAY_H__

#include <stm32f10x.h>

//��ʱ�����ĳ�ʼ���ӿ�
//Input: pclk->оƬ����ʱ��
void _delay_init(u32 pclk);

//��ʱ����
void _delay_us(u32 us);
void _delay_ms(u32 ms);
void _delay_sec(double sec);

#endif
