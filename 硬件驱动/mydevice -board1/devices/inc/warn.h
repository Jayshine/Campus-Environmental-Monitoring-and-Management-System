/***************************************************************************
*FileName:		warn.h
*Description: ������PB9��������PB8 ��ʼ���ӿ�����
*Author:			yhs
*CreatDate:		2018-7-15
*Copyright		www.yanghs97@163.com
*UpDate:			�޸���		�޸�����
*2018-7-11		��Bɭ	 	��ӳ�ʼ������ʵ��
****************************************************************************/
#ifndef __WARN_H_
#define __WARN_H_
#include <stm32f10x.h>

//��ʼ�������Ʊ������ӿ�
void warnInit(void);

//����������
void warnLed(void);
	
//����������
void warn(void);

#endif

