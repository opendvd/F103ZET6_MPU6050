/********************************************************************************************************
**                                 Copyright (c)          MEI14
**                                                 All Rights Reserved
**  
**                                 Email:729527658@qq.com   QQ:729527658
**-------------------------------------------------------------------------------------------------------
**  MCU        : STM32F103ZE (STMicroelectronics)
**  Compiler   : Keil uVision 5.10
**  Module Name: ADC functions
**  Module Date: 2015年4月3日 21:35:25
**  Module Auth: 
**  Description: 采样电压不大于3.3V
                12位ADC是一种逐次逼近型模拟数字转换器。它有多达18个通道，可测量16个外部和2个内部
                信号源。各通道的A/D转换可以单次、连续、扫描或间断模式执行。ADC的结果可以左对齐或右
                对齐方式存储在16位数据寄存器中。ADC的输入时钟不得超过14MHz，它是由PCLK2经分频产生。
								RCC控制器为ADC时钟提供一个
                专用的可编程预分频器
**  Version    : V1.0
**  Notes      : 
**-------------------------------------------------------------------------------------------------------
**  Version    : 
**  Modified By: 
**  Date       : 
**  Content    : 
**  Others     :温度传感器和通道ADC1_IN16相连接，内部参照电压V REFINT 和ADC1_IN17相连接。可以按注入
                或规则通道对这两个内部通道进行转换。
								注意： 温度传感器和 V REFINT 只能出现在主 ADC1 中。
**  Notes      : 
********************************************************************************************************/
/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "adc.h"
/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/

/*----------------------------------------  F U N C T I O N S  ----------------------------------------*/
/********************************************************************************************************
Function Name: ADC_Config
Author       : 
Date         : 
Description  : ADC通用配置，以下使用了PA1作为模拟通道X的模拟输入管脚
Inputs       : None
Outputs      : None
Notes        : 
Revision     : 
********************************************************************************************************/
void ADC_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef  ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA ,ENABLE);
  RCC_ADCCLKConfig(RCC_PCLK2_Div2);//ADC分频系数为2

	/**************GPIO口配置*******************/
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;//模拟输入
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;//配置PA1管脚 
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	/***************ADC配置********************/
	ADC_DeInit(ADC1);
	ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;//独立模式(共10种ADC采集模式)【比如：同步模式-双ADC模式（主ADC，从ADC）】
	ADC_InitStructure.ADC_ScanConvMode       = ENABLE;//开启扫描模式 | 开启单通道模式为DISABLE
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//开启连续扫描模式 | 单次转换为DISABLE
	ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;//ADC外部触发关闭,由软件触发
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;//数据对齐方式为右对齐
	ADC_InitStructure.ADC_NbrOfChannel       = 1;//开启通道数为1，取值范围为1~16
	
	ADC_Init(ADC1,&ADC_InitStructure);//ADC初始化
	/*设置完以后使能ADC转换，执行复位较准，最后执行AD较准*/
	ADC_Cmd(ADC1,ENABLE);//使能ADC
  ADC_ResetCalibration(ADC1);//开启复位较准
	while(ADC_GetResetCalibrationStatus(ADC1));//等待复位较准结束
	ADC_StartCalibration(ADC1);//开启AD较准
	while(ADC_GetCalibrationStatus(ADC1));//等待AD较准结束

}
/********************************************************************************************************
Function Name: Get_AdcValue
Author       : 
Date         : 
Description  : 获取ADC值
Inputs       : ADCx,通道channel(ADC1、ADC2、ADC3)
Outputs      : ADC_GetConversionValue(返回最近一次的ADC转换结果)
Notes        : 
Revision     : 
********************************************************************************************************/
u16 Get_AdcValue(ADC_TypeDef* ADCx,u8 channel)
{
		/*进行ADC通道配置，ADC采样通道为10，采样顺序为1（Rank）,采样时间为41.5个周期*/
	ADC_RegularChannelConfig(ADCx,channel,1,ADC_SampleTime_41Cycles5);
  //ADC_RegularChannelConfig(ADCx,ADC_Channel_x,Rank,ADC_SampleTime_-------);//ADC_Channel_0~ADC_Channel_17、ADC_Channel_TempSensor、ADC_Channel_Vrefint
	ADC_SoftwareStartConvCmd(ADCx,ENABLE);//使能ADC1转换
	while(!(ADC_GetFlagStatus(ADCx,ADC_FLAG_EOC)));//等待转换结束
	
	return ADC_GetConversionValue(ADCx);//返回最近一次的ADC转换结果
}

/********************************************************************************************************
Function Name: Get_Adc_Average,得到多次采集后的平均值
Author       : 
Date         : 
Description  : 
Inputs       : ADCx,channel,times
Outputs      : 采集多次后的平均值
Notes        : 
Revision     : 
********************************************************************************************************/
u16 Get_Adc_Average(ADC_TypeDef* ADCx,u8 channel,u8 times)
{
	u32 value_temp = 0;
	u8 i = 0;
	for(;i<times;i++)
	{
		value_temp += Get_AdcValue(ADCx,channel);
		delay_ms(2);
	}
	
	return value_temp /times;
}
