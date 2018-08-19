/********************************************************
*FileName:     protocol.h
*Destription:  �û�Э���װģ��
*Author:      
*CreateDate:   2018-7-15
*Copyright     
*Update:       �޸���    �޸�����
*  2018-7-15     	       ��ӳ�ʼ������
********************************************************/
#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <stm32f10x.h>
#include <string.h>
#include <stdlib.h>

//������Id��
#define BOARD_ID     0x02


//���û��Զ���Э���װ�ɽṹ������
typedef struct
{
	u8 uFrameType;
	u8 uBoardId;
	u8 uDevId;
	u8 uDataLen;
	u8 uData[30];
	u8 uCheck;
	u8 uEnd;
}UserProt;

//Э����غ����ӿ�
// 1. �ϴ�����
// 2. �����ϲ�ָ��
u8 protocolSend(u8 type, u8 DevId, u8 len, u8 * buf);

u8 protocolRes( UserProt * cmd);

u8 protocolCon( UserProt * cmd);




#endif
