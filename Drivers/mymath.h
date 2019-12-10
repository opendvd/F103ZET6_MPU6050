#ifndef _MYMATH_H
#define _MYMATH_H

#include "global.h"

#define ABS(a)      ((a)>=0 ? (a) : (-(a)))
#define MAX(a,b )   ((a)>=(b) ? (a) : (b))
#define MIN(a,b )   ((a)<(b) ? (a) : (b))  

u32 triangle_c(u32 a ,u32 b);
u16 sqrt32(u32 x);
u8 sqrt16(u16 x);
float arctan(float x);
float TAN(float x);
float SIN(float x);
float pow_double(float x,u16 n);
u32 pow_u32(u32 x,u16 n);



#endif



