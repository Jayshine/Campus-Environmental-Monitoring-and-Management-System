/********************************************************
*FileName:     protocol.c
*Destription:  �û�Э���װģ��ʵ��
*Author:      
*CreateDate:   2018-7-15
*Copyright     
*Update:       �޸���    �޸�����
*  2018-7-15     	       ʵ�ֳ�ʼ������
********************************************************/
#include "protocol.h"
#include "briupZigbee.h"
#include "briupUsart.h"   //������
#include "briupDelay.h"

#define FRAME_HEAD1   0xaa
#define FRAME_HEAD2   0xbb

//�����ڲ�У�麯��
static u8 cmdCheck( UserProt * cmd);

//Э����غ����ӿ�
// 1. �ϴ�����
// 2. �����ϲ�ָ��
u8 protocolSend(u8 type, u8 devId, u8 len, u8 * buf)
{
	//����������Ҫͨ��ZigbeeЭ���װ
	//��ͨ��Zigbee�ӿڷ���
	//Ч����ߣ����ʡ�ڴ�
	u8 frame[50], i, check;
	check = BOARD_ID;
	check ^= devId ^ type ^ len;
	frame[0] = FRAME_HEAD2;     //�û��Զ���
	frame[1] = FRAME_HEAD1;
	frame[2] = 0;        //zigbee֡����
	frame[3] = 0xff;     //�̵�ַH
	frame[4] = 0xff;     //�̵�ַL
	frame[5] = 0x05;
	frame[6] = type;
	frame[7] = devId;
	frame[8] = len;
	for(i = 0; i < len;i ++)
	{
		frame[9 + i] = *buf;
		check ^= *buf;
		buf ++;
	}
	frame[9 + i] = check;
	frame[10 + i] = 0xee;
	frame[11 + i] = 0xff;
	zigbeeSendBuf( frame, 12 + i);
	putBuffer((u8*)"okkkkk",6);
	return 0;
}

//���ղ�����һ֡����
// return 0 �������ղ�����һ֡����
u8 protocolRes( UserProt * cmd)
{
	//�ж��Ƿ���յ�һ֡����
	u8 len, buf[50];
	len = zigbeeGetData( buf, 1);
	if( len == 0)
		return 1;           //��ʾδ���յ���Ч����
	putBuffer(buf,len);
	
	//�ж����ݺϷ���
	if( buf[0] != FRAME_HEAD1 || buf[1] != FRAME_HEAD2)
		return 2;           //zigbee֡ͷУ��ʧ��
	
//	if( buf[5] != BOARD_ID)
//		return 3;           //���ݲ��Ǹ��ù��ܰ�
	
	//cmd->uBoardId = 5;
	
	memset( cmd, 0, sizeof( UserProt));
	memcpy( cmd, (buf + 5), len - 3);
	cmd->uCheck = buf[len - 3];
	cmd->uEnd   = buf[len - 2];
	
//	if( cmdCheck( cmd))
//		return 4;           //У��δͨ��
	
	return 0;
}

void analysis(UserProt * cmd)
{
	u8 buf[1]={0x01};
	u8 buf1[20] = {0xbb, 0xaa, 0x00, 0xff, 0xff,\
									0x05, 0x02, 0x01, 0x01, \
									0x01,\
									0xee, 0xff};
	switch(cmd->uBoardId)
	{
		case 0x03: putBuffer((u8*)"board3",6); putBuffer(cmd->uData,cmd->uDataLen);break;
		case 0x05: _delay_ms(100); 
							
							zigbeeSendBuf( buf1, 12);
	//baseLedSet(LED_R);
	_delay_sec(1.5);
		
		
		//protocolSend(0x02,0x01,0x01,buf); _delay_ms(100);putBuffer((u8*)"board5",6);
									break;
				
	}
}

//-----------------------------------�ڲ�������-----------------------
static u8 cmdCheck( UserProt * cmd)
{
	u8 check = cmd->uBoardId;
	u8 i, len, *cp = (u8 *)cmd;
	len = cmd->uDataLen + 4;
	for(i = 0;i < len-1;i ++)
	{// check ^= *cp++
		cp ++;
		check ^= *cp;
	}
	if( check == cmd->uCheck)
		return 0;        //У��ɹ�
 	else 
		return 1;        //У��ʧ��
}



