#ifndef _SendString_h_
#define _SendString_h_

#include "stm32f10x.h"
#include "bsp_usart.h"	

void SendDown(void);
void SendUp(void);

extern vu8 ModeFlag;
extern vu8 RCF;

extern vu8 PT;
extern vu8 WAP1;
extern vu8 WAP2;
extern vu8 WAC1;
extern vu8 WAC2;
extern vu8 HT1;
extern vu8 HT2;
extern vu8 HT3;
extern vu8 HT4;
extern vu16 DE;
extern vu8 CT;
extern vu16 YA;
extern vu16 PI;
extern vu16 RO;
extern vu16 DP;
extern vu16 WT;
extern __IO char CL[80];

#endif // !1



