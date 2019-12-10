#ifndef   _ADC_H
#define   _ADC_H
/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "global.h"
/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/

void ADC_Config(void);
u16 Get_Adc_Average(ADC_TypeDef* ADCx,u8 channel,u8 times);

#endif

