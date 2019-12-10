#ifndef   _PRINTF_H
#define   _PRINTF_H
/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "global.h"
#include "stdio.h"//系统文件，使用标准输入输出就必须包含这两个头文件
#include "stdarg.h"//系统文件
/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/

/*----------------------------------------    M A C R O S  ----------------------------------------*/
/* Internal Variable */

/* External Variable */

/* Internal Function */

/* External Function */
void   fun_usartSend(USART_TypeDef *com ,u8 data);
u8     fun_usartRec(USART_TypeDef *com);
u8 fun_spiSwap(SPI_TypeDef* spix,u8 data);
int fun_printf(USART_TypeDef* com, char * plog,...);
#endif

