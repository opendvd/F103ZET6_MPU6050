/********************************************************************************************************
**                                 Copyright (c)          MEI14
**                                                 All Rights Reserved
**  
**                                 Email:729527658@qq.com   QQ:729527658
**-------------------------------------------------------------------------------------------------------
**  MCU        : STM32F103ZE (STMicroelectronics)
**  Compiler   : Keil uVision 5.10
**  Module Name: Delay Fuction
**  Module Date: 2015年3月26日 09:54:56
**  Module Auth: 
**  Description: 
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
#include "delay.h"
/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/
//u32 TimingDelay = 0;
/*----------------------------------------  F U N C T I O N S  ----------------------------------------*/
/*************************************************
Cortex-M3内核包含了一个SysTick定时器，利用SysTick来延时，既不用中断，也不占用系统定时器
下面有两种方式延时：不用中断（直接对寄存器进行操作）；
                    中断（直接调用库函数,很简单）。
**************************************************/

/********************************************************************************************************
Function Name: delay_init
Author       : 
Date         : 
Description  : 初始化将计算出1us,1ms需要多少个SysTick时钟周期
Inputs       : None
Outputs      : None
Notes        : 一般情况直接使用第二种初始化即可，
               如果使用了us/os就使用第一种初始化（时钟摘取法：在us/os情况下还想使用SysTick来延时）；
Revision     : 
********************************************************************************************************/
/*
void delay_init()
{
	#ifdef OS_CRITICAL_METHOD    //如果OS_CRITICAL_METHOD定义了,说明使用ucosII了.
	u32 reload;
	#endif
	
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//选择外部时钟HCLK/8
	fac_us=SystemCoreClock/8000000;	//为系统时钟的1/8  
	 
  #ifdef OS_CRITICAL_METHOD 	//如果OS_CRITICAL_METHOD定义了,说明使用ucosII了.
	reload=SystemCoreClock/8000000;		//每秒钟的计数次数 单位为K	   
	reload*=1000000/OS_TICKS_PER_SEC;//根据OS_TICKS_PER_SEC设定溢出时间
							//reload为24位寄存器,最大值:16777216,在72M下,约合1.86s左右	
	fac_ms=1000/OS_TICKS_PER_SEC;//代表ucos可以延时的最少单位	   
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//开启SYSTICK中断
	SysTick->LOAD=reload; 	//每1/OS_TICKS_PER_SEC秒中断一次	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//开启SYSTICK    
#else
	fac_ms=(u16)fac_us*1000;//非ucos下,代表每个ms需要的systick时钟数   
#endif
}				
*/
void SysTick_init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us=SystemCoreClock/8000000;	//为系统时钟的1/8  
	fac_ms=(u16)fac_us*1000;//非ucos下,代表每个ms需要的systick时钟数  
}

/*如果使用中断方式延时，需要取消下面注释*/

//void SysTick_init()
//{
//	SysTick_Config(SystemCoreClock/1000);//配置为1ms中断一次，计时的基础单位
//}

/********************************************************************************************************
Function Name: delay_us(u32 n_us)；
               delay_ms(u32 n_ms)
Author       : 
Date         : 
Description  : 先把延时数换算为systick的时钟数，然后写入LOAD寄存器，
               然后清空当前计数器VAL的内容，最后开启倒数功能
Inputs       : n_us：要延时的微妙数
               n_ms: 要延时的毫秒数
Outputs      : None
Notes        : 
Revision     : 
********************************************************************************************************/
void delay_us(u32 n_us)
{
	u32 temp;
	SysTick ->LOAD = n_us*fac_us;
	SysTick ->VAL  = 0x00;//clear counter
	SysTick ->CTRL|=SysTick_CTRL_CLKSOURCE_Msk;//start count backwards
	do
	{
		temp = SysTick->CTRL;
	}
	while(temp & 0x01 &&! (temp&(1<<16)));//wait time arrive
	SysTick ->CTRL&=~SysTick_CTRL_CLKSOURCE_Msk;//shutdown the counter
	SysTick ->VAL  = 0x00;//clear counter
}
void delay_ms(u32 n_ms)
{
	u32 temp;
	SysTick ->LOAD = n_ms*fac_ms;
	SysTick ->VAL  = 0x00;//clear counter
	SysTick ->CTRL|=SysTick_CTRL_CLKSOURCE_Msk;//start count backwards
	do
	{
		temp = SysTick->CTRL;
	}
	while(temp & 0x01 &&! (temp&(1<<16)));//wait time arrive
	SysTick ->CTRL&=~SysTick_CTRL_CLKSOURCE_Msk;//shutdown the counter
	SysTick ->VAL  = 0x00;//clear counter
}

/*中断方式延时函数*/

//void delay_ms(u32 ms)
//{
//   TimingDelay = ms;
//	while(TimingDelay != 0) ;       
//}
