#include "SendString.h"
void SendDown(void)
{

	static char ZBLast=0;
	static int YTLast=0;
	static int LTLast=100;
	static int MXLast=100;
	static int MYLast=100;
	static int MZLast=100;
	static int A1Last=100;
	static int A2Last=100;
	static int A3Last=100;
	static int A4Last=100;
	static int A5Last=100;
	static int B1Last=100;
	static int B2Last=100;
	static int B3Last=100;
	static int B4Last=100;
	static int B5Last=100;
	
	if (RCF == 1)
	{
		PrintFlag = 4;
		RCF = 0;
		ModeFlag=(CL[3]-'0')+1;
		if(ZBLast!=CL[21])
		{
			ZBLast=CL[21];
			printf("$ZB00%c%%",CL[21]);
		}
		if(CL[1]=='1')
		{
			u8 AFlag, BFlag, CFlag, DFlag=0;
			int XPoint, YPoint,ZPoint=0;
			int A1Point,A2Point,A3Point,A4Point,A5Point,B1Point,B2Point,B3Point,B4Point,B5Point;
			XPoint = (CL[5] - '0') * 100 + (CL[6] - '0') * 10 + (CL[7] - '0');
			YPoint = (CL[9] - '0') * 100 + (CL[10] - '0') * 10 + (CL[11] - '0');
			YPoint = (CL[13] - '0') * 100 + (CL[14] - '0') * 10 + (CL[15] - '0');
			if(((XPoint>104)||(XPoint<96))&&((YPoint>104)||(YPoint<96)))
			{
				if((((XPoint-MXLast)>3)||((XPoint-MXLast)<-3))||(((YPoint-MYLast)>3)||((YPoint-MYLast)<-3)))
				{
					MXLast=XPoint;
					MYLast=YPoint;
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
						printf("$MX%c%c%c%% ", CL[5], CL[6], CL[7]);
						printf("$MY%c%c%c%%", CL[9], CL[10], CL[11]);
					}
					else if (ModeFlag == 2)
					{
						printf("$MD005%%");
						printf("$MX%c%c%c%% ", CL[5], CL[6], CL[7]);
						printf("$MY%c%c%c%%", CL[9], CL[10], CL[11]);
					}
					if((ZPoint>104)||(ZPoint<96))
					{
						if(((ZPoint-MZLast)>3)||((ZPoint-MZLast)<-3))
						{
							MZLast=ZPoint;
							printf("$MZ%c%c%c%%", CL[13], CL[14], CL[15]);
						}
					}
				}
			}
			if(CL[21]=='1')
			{			
				A1Point=(CL[35] - '0') * 100 + (CL[36] - '0') * 10 + (CL[37] - '0');
				if(((A1Point-A1Last)>3)||((A1Point-A1Last)<-3))
				{
					A1Last=A1Point;
					printf("$03%c%c%c%%", CL[35], CL[36], CL[37]);
				}
				A2Point=(CL[39] - '0') * 100 + (CL[40] - '0') * 10 + (CL[41] - '0');
				if(((A2Point-A2Last)>3)||((A2Point-A2Last)<-3))
				{
					A2Last=A2Point;
					printf("$04%c%c%c%%", CL[39], CL[40], CL[41]);
				}
				
				A3Point=(CL[43] - '0') * 100 + (CL[44] - '0') * 10 + (CL[45] - '0');
				if(((A3Point-A3Last)>3)||((A3Point-A3Last)<-3))
				{
					A3Last=A3Point;
					printf("$05%c%c%c%%", CL[43], CL[44], CL[45]);
				}
				A4Point=(CL[47] - '0') * 100 + (CL[48] - '0') * 10 + (CL[49] - '0');
				if(((A4Point-A4Last)>3)||((A4Point-A4Last)<-3))
				{
					A4Last=A4Point;
					printf("$06%c%c%c%%", CL[47], CL[48], CL[49]);
				}
				A5Point=(CL[51] - '0') * 100 + (CL[52] - '0') * 10 + (CL[53] - '0');
				if(((A5Point-A5Last)>3)||((A5Point-A5Last)<-3))
				{
					A5Last=A5Point;
					printf("$BA%c%c%c%%", CL[51], CL[52], CL[53]);
				}
				B1Point=(CL[55] - '0') * 100 + (CL[56] - '0') * 10 + (CL[57] - '0');
				if(((B1Point-B1Last)>3)||((B1Point-B1Last)<-3))
				{
					B1Last=B1Point;
					printf("$07%c%c%c%%", CL[55], CL[56], CL[57]);
				}
				B2Point=(CL[59] - '0') * 100 + (CL[60] - '0') * 10 + (CL[61] - '0');
				if(((B2Point-B2Last)>3)||((B2Point-B2Last)<-3))
				{
					B2Last=B2Point;
					printf("$08%c%c%c%%", CL[59], CL[60], CL[61]);
				}
				B3Point=(CL[63] - '0') * 100 + (CL[64] - '0') * 10 + (CL[65] - '0');
				if(((B3Point-B3Last)>3)||((B3Point-B3Last)<-3))
				{
					B3Last=B3Point;
					printf("$09%c%c%c%%", CL[63], CL[64], CL[65]);
				}
				B4Point=(CL[67] - '0') * 100 + (CL[68] - '0') * 10 + (CL[69] - '0');
				if(((B4Point-B4Last)>3)||((B4Point-B4Last)<-3))
				{
					B4Last=B4Point;
					printf("$10%c%c%c%%", CL[67], CL[68], CL[69]);
				}
				B5Point=(CL[71] - '0') * 100 + (CL[72] - '0') * 10 + (CL[73] - '0');
				if(((B5Point-B5Last)>3)||((B5Point-B5Last)<-3))
				{
					B5Last=B5Point;
					printf("$BB%c%c%c%%", CL[71], CL[72], CL[73]);
				}
			}
			int YTPoint=(CL[17] - '0') * 100 + (CL[18] - '0') * 10 + (CL[19] - '0');
			if(((YTPoint-YTLast)>3)||((YTPoint-YTLast)<-3))
			{
				YTLast=YTPoint;
				printf("$YT%c%c%c%%", CL[17], CL[18], CL[19]);
			}
			int LTPoint=(CL[23] - '0') * 100 + (CL[24] - '0') * 10 + (CL[25] - '0');
			if(((LTPoint-LTLast)>3)||((LTPoint-LTLast)<-3))
			{
				LTLast=LTPoint;
				printf("$LT%c%c%c%%", CL[23], CL[24], CL[25]);
			}
			if(CL[75]=='1')
			{
				printf("$LF00%c%%",CL[75]);
			}
		} 
	}
}
void SendUp(void)
{
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