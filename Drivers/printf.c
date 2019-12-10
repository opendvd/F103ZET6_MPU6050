/********************************************************************************************************
**                                 Copyright (c)          MEI14
**                                                 All Rights Reserved
**  
**                                 Email:729527658@qq.com   QQ:729527658
**-------------------------------------------------------------------------------------------------------
**  MCU        : STM32F103ZE (STMicroelectronics)
**  Compiler   : Keil uVision 5.10
**  Module Name: fun_printf functions
**  Module Date: 2015年3月26日 10:51:48
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
#include "printf.h"
/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/

/*----------------------------------------  F U N C T I O N S  ----------------------------------------*/
void fun_usartSend(USART_TypeDef *com ,u8 data)
{
  while(USART_GetFlagStatus(com, USART_FLAG_TC) == RESET);
  //{}
  USART_SendData(com, (u8) data);
}

int fun_printf(USART_TypeDef* com, char * plog,...)
{
    int nret = 0;
    va_list args;
    char data[30];
    char *p;
    if (plog == NULL) {
      return nret;
    }	
    va_start(args, plog);
    nret = vsprintf(data,plog,args);
    p = data;
    while(*p)
    {
      fun_usartSend(com, *p++);
    }
    va_end(args);
    return nret;
}


u8 fun_usartRec(USART_TypeDef *com)
{
  while(USART_GetFlagStatus(com, USART_FLAG_RXNE) == RESET)
  {}
  return USART_ReceiveData(com);
}


u8 fun_spiSwap(SPI_TypeDef* spix,u8 data)
{
  /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(spix, SPI_I2S_FLAG_TXE) == RESET)      //?????????
  {

  }			  
  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(spix, data);                                    //????SPI1??????

  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(spix, SPI_I2S_FLAG_RXNE) == RESET)   //??????????
  {

  }	  						    
  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(spix);                  
}



//===========================================  End Of File  ===========================================//
