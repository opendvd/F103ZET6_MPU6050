/********************************************************************************************************
**                                 Copyright (c)          MEI14
**                                                 All Rights Reserved
**  
**                                 Email:729527658@qq.com   QQ:729527658
**-------------------------------------------------------------------------------------------------------
**  MCU        : STM32F103ZE (STMicroelectronics)
**  Compiler   : Keil uVision 5.10
**  Module Name: USART functions
**  Module Date: 2015年3月27日 21:10:00
**  Module Auth: 
**  Description: UART：通用异步收发器；USART：通用同步异步收发器；
                 一般而言，单片机中，名称为UART的接口一般只能用于异步串行通讯，
						     而名称为USART的接口既可以用于同步串行通讯，也能用于异步串行通讯。
**  Version    : V1.0
**  Notes      : 
**-------------------------------------------------------------------------------------------------------
**  Version    : 
**  Modified By: 
**  Date       : 
**  Content    : 
**  Notes      : 
********************************************************************************************************/

/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "usart.h"
/*----------------------------------------  F U N C T I O N S  ----------------------------------------*/
/********************************************************************************************************
Function Name: UART_Init
Author       : 
Date         : 
Description  : 使用USART2，其他USART类似（注意RCC_APBxPeriphClockCmd不一样）
Inputs       : 波特率
Outputs      : None
Notes        : 
Revision     : 
********************************************************************************************************/
void UART_Init(u32 bound)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	USART_InitTypeDef  USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;//RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//配置为浮空输入或上拉输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化

	USART_InitStructure.USART_BaudRate = bound;//波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8位字长
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//停止位为1位
	USART_Init(USART2,&USART_InitStructure);//初始化
	
  USART_Cmd(USART2,ENABLE);//串口使能
	
	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);//使能串口2的DMA，开启DMA传输
}




















