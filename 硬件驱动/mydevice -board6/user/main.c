#include <stm32f10x.h>
#include <stdio.h>
#include "briupGPIO.h"
#include "basePeripheral.h"
#include "briupDelay.h"
#include "briupUSART.h"
#include "briupTim.h"
#include "servo.h"
#include "rc522.h"
#include "rc522Add.h"
#include "mini12864.h"
#include "briupZigbee.h"
#include "protocol.h"

//board1����Ӳ��
//����Ӳ��
//���
//RFID������
//��Ļ



 int main(void)
{	
	u8 len;
	UserProt cmd;
	extern u8 flag;
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2);
	//������ʼ��
	briupGPIOInit();
	usart1Init( 72, 57600);
	zigbeeInit( 36, 57600);
	_delay_init(72);
	//hardware��ʼ��
	timInit(72,1000);
	//device��ʼ��
	Servo_Init(20000,71);
	InitRc522();
	InitAlldata();
	Lcd_Init_IN();
	Clear_Screen_IN();
	
	flag=0;
//	baseLedSet(LED_CYAN);
//	while(protocolCon(&cmd)!=6)
//	{
//		_delay_ms(175);
//	}
//	_delay_ms(50);
	baseLedSet(LED_G);;
	
	showStrCn(0x01,0x21,(u8*)" forward");
	showStrCn(0x03,0x22,(u8*)"��ӭ����");
	
	//Read_cardID();
	
	while(1)
	{
		Clear_Screen_IN();
		showStrCn(0x01,0x21,(u8*)" forward");
		showStrCn(0x03,0x22,(u8*)"��ӭ����");
		showStrCn(0x05,0x27,(u8*)"��ˢ��");
		len = protocolRes(&cmd);
		if(len == 0)
		{
			if(cmd.uDevId == 0x01)		//���������Ϣ
			{
				if(cmd.uData[0] == 0x01) 
				{
					Servo_ON();
					_delay_sec(2);
					Servo_OFF();
				}
			}
			else if(cmd.uDevId == 0x03)		//RFIDȷ����Ϣ
			{
				if(cmd.uData[0] == 0x01)		//RFIDȷ�ϳɹ�
				{
					Clear_Screen_IN();
					showStrCn(0x03,0x22,(u8*)"��ӭ���� ���");
					Servo_ON();
					_delay_sec(2);
					Servo_OFF();
					showStrCn(0x01,0x21,(u8*)" forward");
					showStrCn(0x03,0x22,(u8*)"��ӭ����");
				}
				else if(cmd.uData[0] == 0x02)
				{
					Clear_Screen_IN();
					showStrCn(0x03,0x22,(u8*)"ʶ��ʧ�� ������ˢ��");
				}
				flag = 0x00;			//��λ������־
			}
		}
		if(!flag)
		{
			Read_cardID();
		}
		else if(flag == 0x01)
		{
			protocolSend(0x01,0x03,0x04,cardID);		//��������������֡
			flag = 0x02;											//��֤�����ظ�����
		}
			
			
		_delay_ms(1000);
		
	}
	
}

