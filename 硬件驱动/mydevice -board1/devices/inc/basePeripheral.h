/***************************************************************************
*FileName:		basePeripheral.h
*Description: ��ɫLED�Ƶ���ɫ�궨��
							LED�Ʋ����ӿ�
							�����������ӿ�����
*Author:			yhs
*CreatDate:		2018-7-11
*Copyright		www.yanghs97@163.com
*UpDate:			�޸���		�޸�����
*2018-7-11		��Bɭ	 	��ӳ�ʼ����������
****************************************************************************/
#ifndef __BASEPERIPH_H__
#define __BASEPERIPH_H__

#include <stm32f10x.h>

//R G B
#define LED_R				1
#define LED_G				2
#define LED_B				3
#define LED_YELLOW	4
#define LED_PURPLE	5
#define LED_CYAN		6
#define LED_WHITE		7
#define LED_BLACK		0

//����LED�ƵĲ����ӿ�
void baseLedSet(u8 led);

//����BEEP�Ĳ����ӿ�
void baseBeepSet(u8 set);

#endif

