/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_usart.h"
#include "bsp_Timbase.h"
#include "bsp_iwdg.h"
#include <string.h>

extern u8 PrintFlag;
extern vu8 HighMes;

extern __IO uint16_t ADC_ConvertedValue;
uint32_t time;
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

extern int DXNum;
extern int DZNum;

extern float dDS;
extern u16 dDX1;
extern u16 dDX2;

__IO char Rev1[80]= {0};

vu8 Rev3[10]= {0};
vu8 Rev4[10]= {0};
vu8 MXN[3];
vu8 MXF=0;
vu8 MYN[3];
vu8 MYF=0;
vu8 MZN[3];
vu8 MZF=0;
vu8 HAN[3];
vu8 HAF=0;
vu8 YAN[3];
vu8	YAF=0;
vu8 WAN[3];
vu8 WAF=0;
vu8 GAN[3];
vu8 GAF=0;
vu8 BAN[3];
vu8 BAF=0;
vu8 HBN[3];
vu8 HBF=0;
vu8 YBN[3];
vu8	YBF=0;
vu8 WBN[3];
vu8 WBF=0;
vu8 GBN[3];
vu8 GBF=0;
vu8 BBN[3];
vu8 BBF=0;
vu8 LTN[3];
vu8 LTF=0;
vu8 YTN[3];
vu8 YTF=0;
vu8 LFN[3];
vu8 LFF=0;
vu8 ZBN[3];
vu8 ZBF=0;
vu8 KZN[3];
vu8 KZF=0;
vu8 KPN[3];
vu8 KPF=0;
vu8 SCN[5];
vu8 SCF=0;
vu8 RCF=0;

__IO char CL[80]={0};

u8 AFlag,BFlag,CFlag,DFlag;
u8 XPoint,YPoint;

extern u8 ModeFlag;//Mode 0:Stop Mode 1:Normal(Round) Mode 2:Strict
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{

}


void USART1_IRQHandler(void)
{
    u8 Rev;

    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
    {
        Rev = USART_ReceiveData(USART1);

    }
}
void USART2_IRQHandler(void)
{
    u8 Rev;
    static u8 Rev2Start;
    static u8 Pos2;
    static u8 Dpos;
    static u8 Tflag;
    static u8 Rev2[20]= {0};
    if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
    {
        Rev = USART_ReceiveData(USART2);
        if(Rev=='T')
        {
            Rev2Start=1;
        }

        if(Rev2Start==1)
        {
            if(Rev=='=')
            {
                switch (Tflag)
                {
                case 0:
                {
                    Tflag=1;
                    break;
                }
                case 1:
                {
                    Dpos=Pos2;
                    Tflag=0;
                    break;
                }
                }
            }


            else if(Rev=='\r'&&Tflag==0)
            {
                Rev2Start=0;
                WT=0;
                DP=0;
                for(int i=0; i<=Pos2; ++i)
                {
                    if(i<Dpos)
                    {
                        WT*=10;
                        WT+=Rev2[i];
                    }
                    else
                    {
                        DP*=10;
                        DP+=Rev2[i];
                    }
                }
                Pos2=0;
                Dpos=0;
            }
            if((Rev>='0')&&(Rev<='9'))
            {
                Rev2[Pos2]=Rev-'0';
                ++Pos2;
                if(Pos2==20)
                {
                    Pos2=0;
                    Rev2Start=0;
                }
            }


        }

        else
        {
            Pos2=0;
        }
    }



}
void USART3_IRQHandler(void)
{
    u8 Rev;
    static u8 Rev3Start;
    static u8 Rev3Warn;
    static u8 Pos3=0;
    if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)
    {
        Rev = USART_ReceiveData(USART3);
        if(Rev=='!')
        {
            Rev3Warn=1;
        }
        else if(Rev=='$')
        {
            Rev3Start=1;
        }
        if(Rev3Start==1)
        {
            Rev3[Pos3]=Rev;
            ++Pos3;
            if(Pos3==6)
            {
                Pos3=0;
                Rev3Start=0;
                for(int i=3; i<6; ++i)
                {
                    Rev3[i]-=48;
                }
                if(Rev3[1]=='D'&&Rev3[2]=='E')
                {
                    DE=Rev3[3]*100+Rev3[4]*10+Rev3[5];
                }
                else if(Rev3[1]=='T'&&Rev3[2]=='E')
                {
                    CT=Rev3[3]*100+Rev3[4]*10+Rev3[5];
                }
                else if(Rev3[1]=='Y'&&Rev3[2]=='A')
                {
                    YA=Rev3[3]*100+Rev3[4]*10+Rev3[5];
                }
                else if(Rev3[1]=='P'&&Rev3[2]=='I')
                {
                    PI=Rev3[3]*100+Rev3[4]*10+Rev3[5];
                }
                else if(Rev3[1]=='R'&&Rev3[2]=='O')
                {
                    RO=Rev3[3]*100+Rev3[4]*10+Rev3[5];
                }
            }
        }
        else if(Rev3Warn==1)
        {
            Rev3[Pos3]=Rev;
            ++Pos3;
            if(Pos3==2)
            {
                Pos3=0;
                Rev3Warn=0;
                if(Rev3[1]=='8')
                {
                    WAC1=1;
                }
                else if(Rev3[1]=='9')
                {
                    WAC2=1;
                }
                else
                {
                    if(Rev3[1]=='1')
                    {
                        HT1=1;
                    }
                    if(Rev3[1]=='2')
                    {
                        HT2=1;
                    }
                    if(Rev3[1]=='3')
                    {
                        HT3=1;
                    }
                    if(Rev3[1]=='4')
                    {
                        HT4=1;
                    }
                }
            }

        }
        else
        {
            Pos3=0;
        }
    }
}
void UART4_IRQHandler(void)
{
    u8 Rev;
    static u8 Rev4Start;
    static u8 Pos4=0;
    static u8 WaterFlag=0;
    if(USART_GetITStatus(UART4,USART_IT_RXNE)!=RESET)
    {
        Rev=USART_ReceiveData(UART4);
        if(WaterFlag==1)
        {
            WaterFlag=0;
            if(Rev=='1')
            {
                WAP1=1;
            }
            else if(Rev=='2')
            {
                WAP2=1;
            }
        }
        if(Rev=='!')
        {
            WaterFlag=1;
        }
        else if(Rev=='$')
        {
            Rev4Start=1;
        }
        if(Rev4Start==1)
        {
            Rev4[Pos4]=Rev;
            ++Pos4;

            if(Pos4==6)
            {
                Pos4=0;
                Rev4Start=0;
                if(Rev4[1]=='T'&&Rev4[2]=='M')
                {
                    PT=(Rev4[4]-'0')*10+(Rev4[5]-'0');
                }
            }
        }
        else
        {
            Pos4=0;
        }
    }
}
void UART5_IRQHandler(void)
{
    u8 Rev;
    static u8 Rev5Start;
    static u8 Pos5=0;
    if(USART_GetITStatus(UART5,USART_IT_RXNE)!=RESET)
    {
        Rev=USART_ReceiveData(UART5);
        if(Rev=='$')
        {
            Rev5Start=1;
        }
        if(Rev5Start==1)
        {
            Rev1[Pos5]=Rev;
            ++Pos5;
            if(Rev=='%')
            {
								
								if(Pos5==79)
								{
									RCF=1;
									Rev1[79]=0;
									strcpy(CL,Rev1);
								}
								
                Pos5=0;
                Rev5Start=0;
            }
						if(Pos5==80)
						{
								Pos5=0;
                Rev5Start=0;
						}
        }
        else
        {
            Pos5=0;
        }
    }
}
void  BASIC_TIM_IRQHandler (void)
{
    if ( TIM_GetITStatus( BASIC_TIM, TIM_IT_Update) != RESET )
    {
        ++time;
        IWDG_Feed();
        if((time%20)==0)
        {
            if(LineFlag==2)
            {
                if(RCF==1)
                {
                    RCF=0;
										PrintFlag=4;
                        XPoint=(CL[7]-'0')*100+(CL[8]-'0')*10+(CL[9]-'0');
                        YPoint=(CL[11]-'0')*100+(CL[12]-'0')*10+(CL[13]-'0');
                        AFlag=(XPoint>YPoint);
                        BFlag=((XPoint+YPoint)>200);
                        CFlag=(XPoint>100);
                        DFlag=(YPoint>100);
                        if(ModeFlag==1)
                        {
                            if(BFlag==1)
                            {
                                if(CFlag==0)
                                {
                                    printf("$MD003%%");
                                }
                                else if(DFlag==0)
                                {
                                    printf("$MD004%%");
                                }
                                else
                                {
                                    if(AFlag==1)
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
                                if(CFlag==1)
                                {
                                    printf("$MD003%%");
                                }
                                else if(DFlag==1)
                                {
                                    printf("$MD004%%");
                                }
                                else
                                {
                                    if(AFlag==0)
                                    {
                                        printf("$MD001%%");
                                    }
                                    else
                                    {
                                        printf("$MD002%%");
                                    }
                                }
                            }
                            printf("$MX%03d%%",XPoint);
                            printf("$MY%03d%%",YPoint);
														printf("$MZ%c%c%c%%",CL[15],CL[16],CL[17]);
                        }
                        else if(ModeFlag==2)
                        {
                            printf("$MD005%%");
                            printf("$MX%03d%% ",XPoint);
                            printf("$MY%03d%%",YPoint);
														printf("$MZ%c%c%c%%",CL[15],CL[16],CL[17]);
                        }
                    
                        PrintFlag=4;
                        printf("$HA%c%c%c%%",CL[37],CL[38],CL[39]);
                        printf("$YA%c%c%c%%",CL[41],CL[42],CL[43]);
                        printf("$WA%c%c%c%%",CL[45],CL[46],CL[47]);
                        printf("$GA%c%c%c%%",CL[49],CL[50],CL[51]);
                        printf("$BA%c%c%c%%",CL[53],CL[54],CL[55]);
                        printf("$HB%c%c%c%%",CL[57],CL[58],CL[59]);
                        printf("$YB%c%c%c%%",CL[61],CL[62],CL[63]);
                        printf("$WB%c%c%c%%",CL[65],CL[66],CL[67]);
                        printf("$GB%c%c%c%%",CL[69],CL[70],CL[71]);
                        printf("$BB%c%c%c%%",CL[73],CL[74],CL[75]);
                        printf("$YT%c%c%c%%",CL[19],CL[20],CL[21]);
                        printf("$ZB%c%c%c%%",'0','0',CL[23]);
                        printf("$LF%c%c%c%%",'0','0',CL[77]);
                        printf("$LT%c%c%c%%",CL[25],CL[26],CL[27]);
//                        DZNum=(CL[29]-'0')*100+(CL[30]-'0')*10+(CL[31]-'0');
//                        dDS=DP;
//                        DXNum=(CL[33]-'0')*100+(CL[34]-'0')*10+(CL[35]-'0');
//                        dDX1=DE;
//                        dDX2=YA;
                    
                }
            }
        }
        if((time%100)==0)
        {
            

        }
        if(time==600)
        {
            time=0;
            PrintFlag=5;
            if(WAP1==1)
            {
                printf("$!P001%%");
                WAP1=0;
            }
            if(WAP2==1)
            {
                printf("$!P002%%");
                WAP2=0;
            }
            if(WAC1==1)
            {
                printf("$!C001%%");
                WAC1=0;
            }
            if(WAC2==1)
            {
                printf("$!C002%%");
                WAC2=0;
            }
            if(HT1==1)
            {
                printf("$!H001%%");
                HT1=0;
            }
            if(HT2==1)
            {
                printf("$!H002%%");
                HT2=0;
            }
            if(HT3==1)
            {
                printf("$!H003%%");
                HT3=0;
            }
            if(HT4==1)
            {
                printf("$!H004%%");
                HT4=0;
            }
            printf("$DP%05d $WT%04d $PT%03d $CT%03d $YA%03d $PI%03d $RO%03d $DE%03d\r\n",DP,WT,PT,CT,YA,PI,RO,DE);
        }
        TIM_ClearITPendingBit(BASIC_TIM, TIM_FLAG_Update);
    }
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
