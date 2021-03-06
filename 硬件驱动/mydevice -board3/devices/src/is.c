/***************************************************************************
*FileName:		is.h
*Description: 人体红外传感器初始化接口实现
*Author:			yhs
*CreatDate:		2018-7-11
*Copyright		www.yanghs97@163.com
*UpDate:			修改人		修改内容
*2018-7-11		杨淏森	 	添加初始化函数实现
****************************************************************************/
#include "is.h"
#include "briupDelay.h"
#include "briupUSART.h"
//初始化人体红外传感器函数接口
void is_Init(void)
{
	NVIC_InitTypeDef nvicInit;
	//开启GPIOCB的时钟
	RCC->APB2ENR |= 1<<3;
	//开启复用时钟
	RCC->APB2ENR |= 1<<0;
	
	//PB7下拉输入
	GPIOB->CRL &= ~0xF0000000;
	GPIOB->CRL |= 0x80000000;
	GPIOB->ODR &= ~(1<<7);
	
	//外部中断的端口设置
	AFIO->EXTICR[1] |= 0x1000;
	
	//外部中断的触发模式与使能
	EXTI->RTSR |= 1<<7;
	EXTI->FTSR &= ~(1<<7);
	EXTI->IMR |= 1<<7;
	
	//外部中断线13的NVIC优先级
	nvicInit.NVIC_IRQChannel = EXTI9_5_IRQn ;
	nvicInit.NVIC_IRQChannelPreemptionPriority = 1;
	nvicInit.NVIC_IRQChannelSubPriority = 1;
	nvicInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &nvicInit);
}

//返回人体红外传感器的当前状态
u8 havehuman(void)
{
	if( GPIOC->IDR & (1<<13))
		return '1';
	else
		return '0';
}


//==================外部中断服务函数=============
void EXTI15_10_IRQHandler(void)
{
	_delay_ms(10);
	//响应并清除中断标志
	if( GPIOC->IDR & 1<<13)
	{
		EXTI->PR |= 1<<13;
		putDataDma("EXTI13\r\n", 8);
	}
}

