#include <stm32f10x.h>
#include <stdio.h>
#include "briupGPIO.h"
#include "basePeripheral.h"
#include "briupDelay.h"
#include "briupUSART.h"
#include "briupI2C.h"
#include "briupUsart3.h"
#include "sht20.h"
#include "veml6070.h"
#include "CO2.h"
#include "BH1750.h"
#include "briupZigbee.h"
#include "protocol.h"

//board2����Ӳ��
//����Ӳ��
//������̼������		ȱʧ
//��ʪ�ȴ�����
//�����ߴ�����
//����ǿ�ȴ�����		ȱʧ

//Э����� �����floatת���Ƿ�ɹ���

int fputc(int ch, FILE* stream)
{
    putChar((uint8_t)ch);
    return ch;
}

 int main(void)
{
	float Tem,Hum,Li;
	u16 tem,hum,li;
	u16 Result;
	u8 VH,VL;
	u8 buf[30];
	UserProt cmd;
	
	//NVIC�жϷ�������
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2);
	//������ʼ��
	briupGPIOInit();
	usart1Init( 72, 57600);
	zigbeeInit( 36, 57600);
	_delay_init(72);
	//hardware��ʼ��
	IIC_Init();
	usart3Init(36,9600);
	//device��ʼ��
	VEML6070Init();
	BH1750_Init();
	
//	baseLedSet(LED_CYAN);
//	while(protocolCon(&cmd)!=6)
//	{
//		_delay_ms(115);
//	}
//	_delay_ms(50);
	baseLedSet(LED_G);
	
	
	while(1)
	{
			//protocolRes(&cmd);	//���տ���֡������֡
			baseLedSet(LED_G);
			_delay_sec(9);
			CO2_Measure(&VH, &VL);		//CO2 ����
			_delay_ms(50);
			buf[0] = VH;
			buf[1] = VL;
			SHT20_Measure(&Tem, &Hum);	//��ʪ��	������ �¶ȱ�����λС����ʪ�ȱ�����λС��
			_delay_ms(50);
			tem = (u16)(Tem*1000);
			hum = (u16)(Hum*100);
			VH = (u8)(tem>>8);
			VL = (u8)tem;
			buf[2] = VH;
			buf[3] = VL;
			VH = (u8)(hum>>8);
			VL = (u8)hum;
			buf[4] = VH;
			buf[5] = VL;
			BH1750_Measure(&Li);			//��ǿ	������ ����һλС��
			_delay_ms(50);
			li = (u16)(Li*10);
			VH = (u8)(li>>8);
			VL = (u8)li;
			buf[6] = VH;
			buf[7] = VL;	
			VEML6070Measure(&Result);		//������		���� ǿ�ȵȼ�
			_delay_ms(50);
			VH = Result>>8;
			VL = Result;
			buf[8] = VH;
			buf[9] = VL;
			protocolSend(0x01,0x05,0x0a,buf);	//�������ݣ�˳��Ϊ�������˳��
			baseLedSet(LED_B);
			_delay_ms(500);
	}
	
}

