/***************************************************************************
*FileName:		fansRelay.h
*Description: ���Ⱥͼ̵����ӿ�����
							ͨ����ѯ��ʽʵ��
							ͨ���жϷ�ʽʵ��
*Author:			yhs
*CreatDate:		2018-7-15
*Copyright		www.yanghs97@163.com
*UpDate:			�޸���		�޸�����
*2018-7-11		��Bɭ	 	��ӳ�ʼ������ʵ��
****************************************************************************/
#ifndef	__FANSRELAY_H_
#define __FANSRELAY_H_
#include <stm32f10x.h>

//��ʼ�����Ⱥͼ̵���
void fanRelayInit(void);

//���Ʒ��� key:1-�� 0-��
void fan(u16 key);

//���Ƽ̵���1 key:1-�� 0-��
void relay1(u16 key);

//���Ƽ̵���2 key:1-�� 0-��
void relay2(u16 key);

#endif

