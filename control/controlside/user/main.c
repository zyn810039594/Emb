#include "stm32f10x.h"
#include "bsp_GeneralTim.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "bsp_Timbase.h"
#include "bsp_iwdg.h"


extern u8 PrintFlag;
vu8 HighMes = 0;

vu8 PT = 0;
vu8 WAP1 = 0;
vu8 WAP2 = 0;
vu8 WAC1 = 0;
vu8 WAC2 = 0;
vu8 HT1 = 0;
vu8 HT2 = 0;
vu8 HT3 = 0;
vu8 HT4 = 0;
vu16 DE = 0;
vu8 CT = 0;
vu16 YA = 0;
vu16 PI = 0;
vu16 RO = 0;
vu16 DP = 0;
vu16 WT = 0;
u8 ModeFlag = 1; //Mode 0:Stop Mode 1:Normal(Round) Mode 2:Strict


float dDS = 0;

u16 dDX1 = 0;
u16 dDX2 = 0;

int DXNum = 100;
int DZNum = 100;

extern u8 Rev1[10];

extern vu8 RCF;

extern __IO char CL[80];

extern u8 AFlag, BFlag, CFlag, DFlag;
extern u8 XPoint, YPoint;

int main(void)
{


	SysTick_Init();
	SysTick_Delay_Ms(6000);
	//两路PWM初始化
	GENERAL_TIM_Init();
	USART_Config();
	//BASIC_TIM_Init();
	IWDG_Config(IWDG_Prescaler_64, 625);
	while (1)
	{
        
		if (RCF == 1)
		{
			RCF = 0;
			PrintFlag = 4;
			XPoint = (CL[7] - '0') * 100 + (CL[8] - '0') * 10 + (CL[9] - '0');
			YPoint = (CL[11] - '0') * 100 + (CL[12] - '0') * 10 + (CL[13] - '0');
			AFlag = (XPoint > YPoint);
			BFlag = ((XPoint + YPoint) > 200);
			CFlag = (XPoint > 100);
			DFlag = (YPoint > 100);
			if (ModeFlag == 1)
			{
				if (BFlag == 1)
				{
					if (CFlag == 0)
					{
						printf("$MD003%%");
					}
					else if (DFlag == 0)
					{
						printf("$MD004%%");
					}
					else
					{
						if (AFlag == 1)
						{
							printf("$MD001%%");
						}
						else
						{
							printf("$MD002%%");
						}
					}
				}
				else
				{
					if (CFlag == 1)
					{
						printf("$MD003%%");
					}
					else if (DFlag == 1)
					{
						printf("$MD004%%");
					}
					else
					{
						if (AFlag == 0)
						{
							printf("$MD001%%");
						}
						else
						{
							printf("$MD002%%");
						}
					}
				}
				printf("$MX%03d%%", XPoint);
				printf("$MY%03d%%", YPoint);
				printf("$MZ%c%c%c%%", CL[15], CL[16], CL[17]);
			}
			else if (ModeFlag == 2)
			{
				printf("$MD005%%");
				printf("$MX%03d%% ", XPoint);
				printf("$MY%03d%%", YPoint);
				printf("$MZ%c%c%c%%", CL[15], CL[16], CL[17]);
			}
                    
			printf("$HA%c%c%c%%", CL[37], CL[38], CL[39]);
			printf("$YA%c%c%c%%", CL[41], CL[42], CL[43]);
			printf("$WA%c%c%c%%", CL[45], CL[46], CL[47]);
			printf("$GA%c%c%c%%", CL[49], CL[50], CL[51]);
			printf("$BA%c%c%c%%", CL[53], CL[54], CL[55]);
			printf("$HB%c%c%c%%", CL[57], CL[58], CL[59]);
			printf("$YB%c%c%c%%", CL[61], CL[62], CL[63]);
			printf("$WB%c%c%c%%", CL[65], CL[66], CL[67]);
			printf("$GB%c%c%c%%", CL[69], CL[70], CL[71]);
			printf("$BB%c%c%c%%", CL[73], CL[74], CL[75]);
			printf("$YT%c%c%c%%", CL[19], CL[20], CL[21]);
			printf("$ZB%c%c%c%%", '0', '0', CL[23]);
			printf("$LF%c%c%c%%", '0', '0', CL[77]);
			printf("$LT%c%c%c%%", CL[25], CL[26], CL[27]);
			//                        DZNum=(CL[29]-'0')*100+(CL[30]-'0')*10+(CL[31]-'0');
			//                        dDS=DP;
			//                        DXNum=(CL[33]-'0')*100+(CL[34]-'0')*10+(CL[35]-'0');
			//                        dDX1=DE;
			//                        dDX2=YA;
			if((DXNum != 100)&&(DXNum != 300))
			{
				PrintFlag = 4;
				if (DXNum > 200)
				{
					if (DE > dDX2)
					{
						printf("$MD004%%");
						printf("$MX%3d%%", 400 - DXNum);
						printf("$MY100%%");
					}
					else if (DE < dDX2)
					{
						printf("$MD001%%");
						printf("$MX%3d%%", DXNum - 200);
						printf("$MY100%%");
					}
					else
					{
						printf("$MD001%%");
						printf("$MX100%%");
						printf("$MY100%%");
					}
				}
				else
				{
					if (DE > dDX1)
					{
						printf("$MD004%%");
						printf("$MX%3d%%", 200 - DXNum);
						printf("$MY100%%");
					}
					else if (DE < dDX1)
					{
						printf("$MD001%%");
						printf("$MX%3d%%", DXNum);
						printf("$MY100%%");
					}
					else
					{
						printf("$MD001%%");
						printf("$MX100%%");
						printf("$MY100%%");
					}
				}
			}
			if (DZNum != 100)
			{
				PrintFlag = 4;
				if (DP > dDS)
				{
					printf("$MZ%3d%%", 200 - DZNum);
				}
				else if (DP < dDS)
				{
					printf("$MZ%3d%%", DZNum);
				}
				else
				{
					printf("$MZ100%%");
				}
			}
                    
		}
		PrintFlag = 5;
		if (WAP1 == 1)
		{
			printf("$!P001%%");
			WAP1 = 0;
		}
		if (WAP2 == 1)
		{
			printf("$!P002%%");
			WAP2 = 0;
		}
		if (WAC1 == 1)
		{
			printf("$!C001%%");
			WAC1 = 0;
		}
		if (WAC2 == 1)
		{
			printf("$!C002%%");
			WAC2 = 0;
		}
		if (HT1 == 1)
		{
			printf("$!H001%%");
			HT1 = 0;
		}
		if (HT2 == 1)
		{
			printf("$!H002%%");
			HT2 = 0;
		}
		if (HT3 == 1)
		{
			printf("$!H003%%");
			HT3 = 0;
		}
		if (HT4 == 1)
		{
			printf("$!H004%%");
			HT4 = 0;
		}
		printf("$DP%05d $WT%04d $PT%03d $CT%03d $YA%03d $PI%03d $RO%03d $DE%03d\r\n", DP, WT, PT, CT, YA, PI, RO, DE);

	}

}
