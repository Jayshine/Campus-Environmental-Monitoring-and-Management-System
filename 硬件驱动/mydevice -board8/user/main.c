#include <stm32f10x.h>
#include "briupGPIO.h"
#include "basePeripheral.h"
#include "briupDelay.h"
#include "briupUSART.h"
#include "briupTim.h"
#include "briupI2C.h"
#include "figure.h"
#include "lock.h"
#include "keyboard.h"
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
	extern u8 cardID[4];
	extern u8 volatile flag;
	u8 len;
	UserProt cmd;
	//NVIC�жϷ�������
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2);
	//������ʼ��
	briupGPIOInit();
	usart1Init( 72, 57600);
	zigbeeInit( 36, 57600);
	_delay_init(72);
	//hardware��ʼ��
	//timInit(72,1000);
	IIC_Init();
	usart3Init(72,57600);
	//device��ʼ��
	InitRc522();
	InitAlldata();
	Lcd_GPIO_Iint_IN();
	Lcd_Init_IN();
	Clear_Screen_IN();
	keyboardInit();
	lockInit();
	figureInit();
	
	flag=0x00;
	
//	baseLedSet(LED_CYAN);
//	while(protocolCon(&cmd)!=6)
//	{
//		_delay_ms(205);
//	}
//	
//	_delay_ms(50);
	
	baseLedSet(LED_G);
		
	
	while(1)
	{
		Clear_Screen_IN();
		showStrCn(0x01,0x21,(u8*)" forward");
		showStrCn(0x03,0x22,(u8*)"��ӭ����");
		showStrCn(0x05,0x27,(u8*)"��ˢ��");
		len = protocolRes(&cmd);
		if(len == 0)
		{
			switch(cmd.uDevId)
			{
				case 0x01 :
					lock(0x01);
					break;
				case 0x02 :
					if(cmd.uData[0]==0x00)			//ָ��ʶ�����
					{
						addFigure();			//ָ��¼��
					}
					else if(cmd.uData[0]==0x01)		//ָ��ʶ��
					{
						u8 che=checkFigure();
						if(che == 1)			//ʶ��ɹ�
						{
							lock(0x01);
							baseLedSet(LED_G);
						}
						else if(che == 0)		//ʶ��ʧ��
						{
							baseLedSet(LED_G);
						}
					}
					break;
				case 0x04 :
					if(cmd.uData[0]==0x01)		//RFID �˶Գɹ�
					{
						Clear_Screen_IN();
						showStrCn(0x03,0x15,"��ӭ���� ���");
						lock(0x01);
					}
					if(cmd.uData[0]==0x02)		//RFID �˶�ʧ��
					{
						Clear_Screen_IN();
						showStrCn(0x03,0x10,"ʶ��ʧ�� ������ˢ��");

					}
					flag=0x00;
					break;
				case 0x05:
					//�������
					break;
			}
			
		}
		
		
		if(flag==0x00)		//û������ʱһֱ����
		{
			Read_cardID();
		}
		else if(flag==0x01)
		{
			protocolSend(0x01,0x04,0x04,cardID);
			flag=0x02;
		}
		_delay_ms(500);
	}
	

	
}

