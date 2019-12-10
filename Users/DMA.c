/********************************************************************************************************
**                                 Copyright (c)          MEI14
**                                                 All Rights Reserved
**  
**                                 Email:729527658@qq.com   QQ:729527658
**-------------------------------------------------------------------------------------------------------
**  MCU        : STM32F407VG (STMicroelectronics)
**  Compiler   : Keil uVision 5.10
**  Module Name: common functions
**  Module Date: 2015年4月1日 11:11:16
**  Module Auth: 
**  Description: 实现：使用DMA1将内存中缓冲区的数据输出到USART
**  Version    : V1.0
**  Notes      : 
**-------------------------------------------------------------------------------------------------------
**  Version    : 
**  Modified By: 
**  Date       : 
**  Content    : STM32F1 最多有DMA1，DMA2，两个DMA控制器。【DMA1有7个通道，DMA2有5个通道】
                 STM32F4 最多有 2 个 DMA 控制器（DMA1 和 DMA2） ，共 16 个数据流（每个控制器 8 个） ，每
                 一个 DMA 控制器都用于管理一个或多个外设的存储器访问请求。每个数据流总共可以有多达 8
                  个通道（或称请求） 。每个数据流通道都有一个仲裁器，用于处理 DMA 请求间的优先级。
**  Notes      : 
********************************************************************************************************/
/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "dma.h"
/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/

/*----------------------------------------  F U N C T I O N S  ----------------------------------------*/


void DMA_Config()
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_DeInit(DMA1_Channel7);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&(USART2->DR));//外设基地址（usart的DR数据寄存器）
	DMA_InitStructure.DMA_MemoryBaseAddr     = (u32)(dma_butter);//内存基地址，即数组名的首地址
	DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;//DMA传输方向
	DMA_InitStructure.DMA_BufferSize         = 1000;//DMA传输数目(最大为65536)
	DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;//外设地址不增加
	DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;//内存地址自动加1
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//外设数据宽度16字节
	DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;//内存数据宽度16字节
	DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;//开启循环模式
	DMA_InitStructure.DMA_Priority           = DMA_Priority_High;//设置DMA优先级为最高
	/*
	** 循环模式：比如我们要从内存中采集 64 个字节发送到串口，如果设置为重复采集，
	** 那么它会在 64 个字节采集完成之后继续从内存的第一个地址采集，如此循环
	*/
	DMA_Init(DMA1_Channel7,&DMA_InitStructure);//初始化DMA通道4
	DMA_Cmd(DMA1_Channel7,ENABLE);//使能DMA
	
}















