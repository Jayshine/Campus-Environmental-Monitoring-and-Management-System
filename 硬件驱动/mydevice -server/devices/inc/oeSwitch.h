/***************************************************************************
*FileName:		oeSwitch.h
*Description: ��翪�صĳ�ʼ�������ӿ�����
							ͨ����ѯ�ķ�ʽ���ع�翪��״̬
							ͨ���жϵķ�ʽ����翪��״̬
*Author:			yhs
*CreatDate:		2018-7-13
*Copyright		www.yanghs97@163.com
*UpDate:			�޸���		�޸�����
*2018-7-11		��Bɭ	 	��ӳ�ʼ������ʵ��
****************************************************************************/
#ifndef __OESWITCH_H__
#define	__OESWITCH_H__

#include <stm32f10x.h>

//��翪�صĳ�ʼ��
void oeSwitchInit(void);
	
//���ض��俪�صĵ�ǰ״̬
u8 currSwitchStat(void);

//���ط��俪�صĵ�ǰ״̬
u8 refSwitchStat(void);


#endif

