#ifndef   DELAY_H
#define   DELAY_H

/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "global.h"
/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/

/*----------------------------------------  F U N C T I O N S  ----------------------------------------*/
static u8  fac_us;//us延时倍乘数
static u16 fac_ms;//ms延时倍乘数

extern void SysTick_init(void);
extern void delay_us(u32 n_us);
extern void delay_ms(u32 n_ms);
#endif

