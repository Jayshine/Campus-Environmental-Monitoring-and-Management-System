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

#define FRAME_HEAD1   0xaa
#define FRAME_HEAD2   0xbb


//�����ڲ�У�麯��
static u8 cmdCheck( UserProt * cmd);

u8 heart[1]={0x00};

u8 addh=0xff,addl=0xff;

//Э����غ����ӿ�
// 1. �ϴ�����
// 2. �����ϲ�ָ��
u8 protocolSend(u8 type, u8 DevId, u8 len, u8 * buf)
{
	//����������Ҫͨ��ZigbeeЭ���װ
	//��ͨ��Zigbee�ӿڷ���
	//Ч����ߣ����ʡ�ڴ�
	u8 frame[50], i, check;
	check = BOARD_ID;
	check ^= DevId ^ type ^ len;
	frame[0] = FRAME_HEAD1;     //�û��Զ���
	frame[1] = FRAME_HEAD2;
	frame[2] = 0;        //zigbee֡����
	frame[3] = addh;     //�̵�ַH
	frame[4] = addl;     //�̵�ַL
	frame[5] = type;
	frame[6] = BOARD_ID;
	frame[7] = DevId;
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
	if( buf[0] != FRAME_HEAD2 || buf[1] != FRAME_HEAD1)
		return 2;           //zigbee֡ͷУ��ʧ��
	
	if( buf[6] != BOARD_ID && buf[6]!=0x00)
		return 3;           //���ݲ��Ǹ��ù��ܰ�
	
	//putBuffer(buf,len);
	memset( cmd, 0, sizeof( UserProt));
	memcpy( cmd, (buf + 5), len - 3);
	cmd->uCheck = buf[len - 3];
	cmd->uEnd   = buf[len - 2];
	
	if( cmdCheck( cmd))
		return 4;           //У��δͨ��
	
	if(cmd->uFrameType==0x03)	//����֡
	{
		protocolSend(0x03,0x00,0x01,heart);
		return 5;
	}
		
	
	
	return 0;
}

u8 protocolCon( UserProt * cmd)
{
	//�ж��Ƿ���յ�һ֡����
	u8 len, buf[50];
	len = zigbeeGetData( buf, 1);
	if( len == 0)
		return 1;           //��ʾδ���յ���Ч����
	putBuffer(buf,len);
	//�ж����ݺϷ���
	if( buf[0] != FRAME_HEAD2 || buf[1] != FRAME_HEAD1)
		return 2;           //zigbee֡ͷУ��ʧ��
	
	
	//putBuffer(buf,len);
	memset( cmd, 0, sizeof( UserProt));
	memcpy( cmd, (buf + 5), len - 3);
	cmd->uCheck = buf[len - 3];
	cmd->uEnd   = buf[len - 2];
	
	if( cmdCheck( cmd))
		return 4;           //У��δͨ��
	
	if(cmd->uFrameType==0x00)	//����֡
	{
		if(cmd->uBoardId==0x00)
		{
			addh=buf[3];
			addl=buf[4];
			protocolSend(0x00,0x00,0x01,(u8*)"0x00");	//����֡
			putChar(addh);
			putChar(addl);
		}
		return 6;	
	}
			
	return 0;		//�յ��ǿ���֡
}


//-----------------------------------�ڲ�������-----------------------
static u8 cmdCheck( UserProt * cmd)
{
	u8 check = cmd->uFrameType;
	u8 i, len, *cp = (u8 *)cmd;
	len = cmd->uDataLen + 4;
	cp++;
	for(i = 1;i < len;i ++)
	{
		check ^= *cp;
		cp ++;
	}
	if( check == cmd->uCheck)
		return 0;        //У��ɹ�
 	else 
		return 1;        //У��ʧ��
}



