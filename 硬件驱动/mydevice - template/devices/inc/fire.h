/***************************************************************************
*FileName:		fire.h
*Description: ����PB6�����PB0������PB1��������ʼ���ӿ�����
							ͨ����ѯ��ʽʵ��
							ͨ���жϷ�ʽʵ��
*Author:			yhs
*CreatDate:		2018-7-15
*Copyright		www.yanghs97@163.com
*UpDate:			�޸���		�޸�����
*2018-7-11		��Bɭ	 	��ӳ�ʼ������ʵ��
****************************************************************************/
#ifndef	__FIRE_H_
#define	__FIRE_H_
#include <stm32f10x.h>

//��ʼ��������⡢���鴫��������
void fireInit(void);

//��ȡ��������״̬
u8 fogStat(void);
//��ȡ��⴫����״̬
u8 fireStat(void);
//��ȡ���鴫����״̬
u8 CH4Stat(void);
//�������
void fogMonitor(void);
//��ػ��
void fireMonitor(void);
//��ؼ���
void CH4Monitor(void);


#endif

