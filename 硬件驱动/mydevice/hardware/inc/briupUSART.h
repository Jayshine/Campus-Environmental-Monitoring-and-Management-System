/***************************************************************************
*FileName:		bruipUSART.h
*Description: ������ʼ��Dubug���� -> usart1 �ĺ����ӿ�
							�������ڷ������ݣ�ch / str  /buf
							�������ڽ������ݣ�ch / str
*Author:			yhs
*CreatDate:		2018-7-12
*Copyright		www.yanghs97@163.com
*UpDate:			�޸���		�޸�����
*2018-7-11		��Bɭ	 	��ӳ�ʼ������ʵ��
****************************************************************************/
#ifndef __USART1_H_
#define __USART1_H_

#include <stm32f10x.h>

//��ʼ��usart1�ĺ����ӿ�
// pclk������ʱ��
// baud�� Ҫ���õĲ�����
void usart1Init(u8 pclk, u32 baud);

//���ͺ�������
void putChar( u8 ch);
void putStr( char * str);
void putBuffer( u8 * buf,u16 length);

//���պ�������
u8 getChar( void);
u8 getStr(char * str);

//ͨ��ѭ�����л�ȡһ������
// flag: 
//			0 ֱ�ӻ�ȡ������յ�������
//			1 �жϻ�ȡ��������һ֡Э�������ٷ���
u16 getBuffer( u8 *buf, u8 flag);

//ͨ��DMA����һ������
void putDataDma( u8 * buf, u16 len);


#endif



