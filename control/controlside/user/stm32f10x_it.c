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

u8 ModeFlag=1;//Mode 0:Stop Mode 1:Normal(Round) Mode 2:Strict
extern __IO uint16_t ADC_ConvertedValue;
//uint32_t time;
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

__IO char Rev1[80]= {0};

vu8 Rev3[10]= {0};
vu8 Rev4[10]= {0};

vu8 RCF=0;

__IO char CL[80]= {0};


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
	char USART2Start=0;
	char USART2End=0;
	char Start2=0;
	if(USART_GetITStatus(USART2,USART_IT_IDLE)!=RESET)
	{
		USART_ReceiveData(USART2);
		USART2->DR;
		for(char i=0;i<40;i++)
		{
			if(USART2DMACache[i]=='T')
			{
				USART2Start=i;
				Start2=1;
			}
			else if(USART2DMACache[i]=='\n'&&Start2==1)
			{
				USART2End=1;
				break;
			}
		}
		if(USART2End==1)
		{
			if(USART2DMACache[USART2Start+4]=='.')
			{
				WT=(USART2DMACache[USART2Start+2]-'0')*1000+(USART2DMACache[USART2Start+3]-'0')*100+(USART2DMACache[USART2Start+5]-'0')*10+(USART2DMACache[USART2Start+6]-'0');
				if(USART2DMACache[USART2Start+9]=='-')
				{
					DP=0;
				}
				else
				{
					if(USART2DMACache[USART2Start+10]=='.')
					{
						DP=(USART2DMACache[USART2Start+9]-'0')*100+(USART2DMACache[USART2Start+11]-'0')*10+(USART2DMACache[USART2Start+12]-'0');
						if(USART2DMACache[USART2Start+14]=='\n')
						{
							USART2RecComplete=1;
						}
					}
					else if(USART2DMACache[USART2Start+11]=='.')
					{
						DP=(USART2DMACache[USART2Start+9]-'0')*1000+(USART2DMACache[USART2Start+10]-'0')*100+(USART2DMACache[USART2Start+12]-'0')*10+(USART2DMACache[USART2Start+13]-'0');
						if(USART2DMACache[USART2Start+15]=='\n')
						{
							USART2RecComplete=1;
						}
					}
					else if(USART2DMACache[USART2Start+12]=='.')
					{
						DP=(USART2DMACache[USART2Start+9]-'0')*10000+(USART2DMACache[USART2Start+10]-'0')*1000+(USART2DMACache[USART2Start+11]-'0')*100+(USART2DMACache[USART2Start+13]-'0')*10+(USART2DMACache[USART2Start+14]-'0');
						if(USART2DMACache[USART2Start+16]=='\n')
						{
							USART2RecComplete=1;
						}
					}
				}
			}
			else if(USART2DMACache[USART2Start+3]=='.')
			{
				WT=(USART2DMACache[USART2Start+2]-'0')*100+(USART2DMACache[USART2Start+4]-'0')*10+(USART2DMACache[USART2Start+5]-'0');
				if(USART2DMACache[USART2Start+8]=='-')
				{
					DP=0;
				}
				else
				{
					if(USART2DMACache[USART2Start+9]=='.')
					{
						DP=(USART2DMACache[USART2Start+8]-'0')*100+(USART2DMACache[USART2Start+10]-'0')*10+(USART2DMACache[USART2Start+11]-'0');
						if(USART2DMACache[USART2Start+13]=='\n')
						{
							USART2RecComplete=1;
						}
					}
					else if(USART2DMACache[USART2Start+10]=='.')
					{
						DP=(USART2DMACache[USART2Start+8]-'0')*1000+(USART2DMACache[USART2Start+9]-'0')*100+(USART2DMACache[USART2Start+11]-'0')*10+(USART2DMACache[USART2Start+12]-'0');
						if(USART2DMACache[USART2Start+14]=='\n')
						{
							USART2RecComplete=1;
						}
					}
					else if(USART2DMACache[USART2Start+11]=='.')
					{
						DP=(USART2DMACache[USART2Start+8]-'0')*10000+(USART2DMACache[USART2Start+9]-'0')*1000+(USART2DMACache[USART2Start+10]-'0')*100+(USART2DMACache[USART2Start+12]-'0')*10+(USART2DMACache[USART2Start+13]-'0');
						if(USART2DMACache[USART2Start+15]=='\n')
						{
							USART2RecComplete=1;
						}
					}
				}
			}
		}
		DMA_Cmd(DMA1_Channel6,DISABLE);
		DMA1_Channel6->CNDTR=40;
		DMA_Cmd(DMA1_Channel6,ENABLE);
		USART_ClearITPendingBit(USART2,USART_IT_IDLE);
		
	}
//    u8 Rev;
//    static u8 Rev2Start;
//    static u8 Pos2;
//    static u8 Dpos;
//    static u8 Tflag;
//    static u8 Rev2[20]= {0};
//    if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
//    {
//        Rev = USART_ReceiveData(USART2);
//        if(Rev=='T')
//        {
//            Rev2Start=1;
//        }

//        if(Rev2Start==1)
//        {
//            if(Rev=='=')
//            {
//                switch (Tflag)
//                {
//                case 0:
//                {
//                    Tflag=1;
//                    break;
//                }
//                case 1:
//                {
//                    Dpos=Pos2;
//                    Tflag=0;
//                    break;
//                }
//                }
//            }


//            else if(Rev=='\r'&&Tflag==0)
//            {
//                Rev2Start=0;
//                WT=0;
//                DP=0;
//                for(int i=0; i<=Pos2; ++i)
//                {
//                    if(i<Dpos)
//                    {
//                        WT*=10;
//                        WT+=Rev2[i];
//                    }
//                    else
//                    {
//                        DP*=10;
//                        DP+=Rev2[i];
//                    }
//                }
//                Pos2=0;
//                Dpos=0;
//            }
//            if((Rev>='0')&&(Rev<='9'))
//            {
//                Rev2[Pos2]=Rev-'0';
//                ++Pos2;
//                if(Pos2==20)
//                {
//                    Pos2=0;
//                    Rev2Start=0;
//                }
//            }


//        }

//        else
//        {
//            Pos2=0;
//        }
//    }



}
void USART3_IRQHandler(void)
{
	char USART3Start=0;
	char USART3End=0;
	char Start3=0;
	if(USART_GetITStatus(USART3,USART_IT_IDLE)!=RESET)
	{
		for(char i=0;i<70;i++)
		{
			if(USART3DMACache[i]=='$')
			{
				USART3Start=i+1;
				Start3=1;
			}
			else if(USART3DMACache[i]=='%'&&Start3==1)
			{
				USART3End=i;
				break;
			}
		}
		if((USART3End-USART3Start)==31)
		{
			WAC1=USART3DMACache[USART3Start]-'0';
			WAC2=USART3DMACache[USART3Start+2]-'0';
			HT1=USART3DMACache[USART3Start+4]-'0';
			HT2=USART3DMACache[USART3Start+6]-'0';
			HT3=USART3DMACache[USART3Start+8]-'0';
			HT4=USART3DMACache[USART3Start+10]-'0';
			DE=(USART3DMACache[USART3Start+12]-'0')*100+(USART3DMACache[USART3Start+13]-'0')*10+(USART3DMACache[USART3Start+14]-'0');
			CT=(USART3DMACache[USART3Start+16]-'0')*100+(USART3DMACache[USART3Start+17]-'0')*10+(USART3DMACache[USART3Start+18]-'0');
			YA=(USART3DMACache[USART3Start+20]-'0')*100+(USART3DMACache[USART3Start+21]-'0')*10+(USART3DMACache[USART3Start+22]-'0');
			PI=(USART3DMACache[USART3Start+24]-'0')*100+(USART3DMACache[USART3Start+25]-'0')*10+(USART3DMACache[USART3Start+26]-'0');
			RO=(USART3DMACache[USART3Start+28]-'0')*100+(USART3DMACache[USART3Start+29]-'0')*10+(USART3DMACache[USART3Start+30]-'0');

			USART3RecComplete=1;

		}
		DMA_Cmd(DMA1_Channel3,DISABLE);
		DMA1_Channel3->CNDTR=70;
		DMA_Cmd(DMA1_Channel3,ENABLE);
		USART_ClearITPendingBit(USART3,USART_IT_IDLE);
		USART_ReceiveData(USART3);
	}
}
void UART4_IRQHandler(void)
{
	char UART4Start=0;
	char UART4End=0;
	char Start4=0;
	if(USART_GetITStatus(UART4,USART_IT_IDLE)!=RESET)
	{
		for(char i=0;i<20;i++)
		{
			if(UART4DMACache[i]=='$')
			{
				UART4Start=i+1;
				Start4=1;
			}
			else if(UART4DMACache[i]=='%'&&Start4==1)
			{
				UART4End=i;
				break;
			}
		}
		if(UART4End-UART4Start==7)
		{
			WAP1=UART4DMACache[UART4Start]-'0';
			WAP2=UART4DMACache[UART4Start+2]-'0';
			PT=(UART4DMACache[UART4Start+5]-'0')*10+(UART4DMACache[UART4Start+6]-'0');
			
			UART4RecComplete=1;

		}
		DMA_Cmd(DMA2_Channel3,DISABLE);
		DMA2_Channel3->CNDTR=20;
		DMA_Cmd(DMA2_Channel3,ENABLE);
		USART_ClearITPendingBit(UART4,USART_IT_IDLE);
		USART_ReceiveData(UART4);
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

                if(Pos5==77)
                {
                    RCF=1;
                    Rev1[77]=0;
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
