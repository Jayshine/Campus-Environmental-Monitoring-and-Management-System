/***************************************************************************
*FileName:		lock.h
*Description: ������ӿ�����
*Author:			yhs
*CreatDate:		2018-7-15
*Copyright		www.yanghs97@163.com
*UpDate:			�޸���		�޸�����
*2018-7-11		��Bɭ	 	��ӳ�ʼ������ʵ��
****************************************************************************/
#ifndef __LOCK_H_
#define __LOCK_H_
#include <stm32f10x.h>

//��ʼ�������
void lockInit(void);

//���ص����
void lock(u16 key);

#endif

