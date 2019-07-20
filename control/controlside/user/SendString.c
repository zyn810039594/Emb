#include "SendString.h"
void SendDown(void)
{

    if (RCF == 1)
    {
        u8 Mode=0;
        RCF = 0;
        ModeFlag=(CL[3]-'0')+1;
        if(CL[1]=='1')
        {
            u8 AFlag, BFlag, CFlag, DFlag=0;
            int XPoint, YPoint=0;
            XPoint = (CL[5] - '0') * 100 + (CL[6] - '0') * 10 + (CL[7] - '0');
            YPoint = (CL[9] - '0') * 100 + (CL[10] - '0') * 10 + (CL[11] - '0');
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
                        Mode=3;
                    }
                    else if (DFlag == 0)
                    {
                        Mode=4;
                    }
                    else
                    {
                        if (AFlag == 1)
                        {
                            Mode=1;
                        }
                        else
                        {
                            Mode=2;
                        }
                    }
                }
                else
                {
                    if (CFlag == 1)
                    {
                        Mode=3;
                    }
                    else if (DFlag == 1)
                    {
                        Mode=4;
                    }
                    else
                    {
                        if (AFlag == 0)
                        {
                            Mode=1;
                        }
                        else
                        {
                            Mode=2;
                        }
                    }
                }
            }
            else if (ModeFlag == 2)
            {
                Mode=5;
            }
						
						
            
        }
				PrintFlag = 4;
				printf("$%1d:%c%c%c:%c%c%c:%c%c%c:%c%c%c:%c:%c%c%c:%c%c%c:%c%c%c:%c%c%c:%c%c%c:%c%c%c:%c%c%c:%c%c%c:%c%c%c:%c%c%c:%c%c%c:%c%%",Mode,CL[5], CL[6], CL[7],CL[9], CL[10], CL[11],CL[13], CL[14], CL[15],CL[17], CL[18], CL[19],CL[21],CL[23], CL[24], CL[25],CL[35], CL[36], CL[37],CL[39], CL[40], CL[41],CL[43], CL[44], CL[45],CL[47], CL[48], CL[49],CL[51], CL[52], CL[53],CL[55], CL[56], CL[57],CL[59], CL[60], CL[61],CL[63], CL[64], CL[65],CL[67], CL[68], CL[69],CL[71], CL[72], CL[73],CL[75]);

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
