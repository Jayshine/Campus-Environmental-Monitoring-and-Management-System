/********************************************************
*FileName:     briupZigbee.h
*Destription:  
*              Zigbee Usart2��ʼ���Ľӿ�
*              ͨ��DMA��������
*              ͨ��Usart2�жϵķ�ʽ��������
*Author:      
*CreateDate:   2018-7-15
*Copyright     
*Update:       �޸���    �޸�����
*  2018-7-15     	       ��ʼ����������
********************************************************/
#ifndef __BRIUPZIGBEE_H__
#define __BRIUPZIGBEE_H__

#include <stm32f10x.h>

//Zigbee���ڵĳ�ʼ��
void zigbeeInit( u8 pclk, u32 baud);

//ͨ��DMA����һ��buf����
void zigbeeSendBuf( u8 * buf, u16 len);

//��ȡzigbee������
u16 zigbeeGetData( u8 * buf, u8 flag);



#endif






