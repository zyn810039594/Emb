/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
#include "cmsis_os.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_uart4_rx;
extern DMA_HandleTypeDef hdma_uart5_tx;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim6;

/* USER CODE BEGIN EV */
extern u8 SystemBegin;
//串口1RX口
extern volatile u8 U1_RX_Len;
extern volatile u8 U1_RX_EndFlag;
extern u8 U1_RX_Buffer[70];
extern char U1_RX_BufferSize;
extern u8* U1_RX_Position;
//串口2RX口
extern volatile u8 U2_RX_Len;
extern volatile u8 U2_RX_EndFlag;
extern u8 U2_RX_Buffer[12];
extern char U2_RX_BufferSize;
extern u8* U2_RX_Position;
//串口3RX口
extern volatile u8 U3_RX_Len;
extern volatile u8 U3_RX_EndFlag;
extern u8 U3_RX_Buffer[50];
extern char U3_RX_BufferSize;
extern u8* U3_RX_Position;
//串口4RX口
extern volatile u8 U4_RX_Len;
extern volatile u8 U4_RX_EndFlag;
extern u8 U4_RX_Buffer[40];
extern char U4_RX_BufferSize;
extern u8* U4_RX_Position;
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 stream1 global interrupt.
  */
void DMA1_Stream1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream1_IRQn 0 */

  /* USER CODE END DMA1_Stream1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart3_rx);
  /* USER CODE BEGIN DMA1_Stream1_IRQn 1 */

  /* USER CODE END DMA1_Stream1_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream2 global interrupt.
  */
void DMA1_Stream2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream2_IRQn 0 */

  /* USER CODE END DMA1_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_uart4_rx);
  /* USER CODE BEGIN DMA1_Stream2_IRQn 1 */

  /* USER CODE END DMA1_Stream2_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream3 global interrupt.
  */
void DMA1_Stream3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream3_IRQn 0 */

  /* USER CODE END DMA1_Stream3_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart3_tx);
  /* USER CODE BEGIN DMA1_Stream3_IRQn 1 */

  /* USER CODE END DMA1_Stream3_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream5 global interrupt.
  */
void DMA1_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream5_IRQn 0 */

  /* USER CODE END DMA1_Stream5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* USER CODE BEGIN DMA1_Stream5_IRQn 1 */

  /* USER CODE END DMA1_Stream5_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream6 global interrupt.
  */
void DMA1_Stream6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream6_IRQn 0 */

  /* USER CODE END DMA1_Stream6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_tx);
  /* USER CODE BEGIN DMA1_Stream6_IRQn 1 */

  /* USER CODE END DMA1_Stream6_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
	uint32_t tmp_flag = 0;
	uint32_t temp;
	tmp_flag = __HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE);
	if ((tmp_flag != RESET))
	{ 
		__HAL_UART_CLEAR_IDLEFLAG(&huart1); 
		temp = huart1.Instance->SR; 
		temp = huart1.Instance->DR; 
		HAL_UART_DMAStop(&huart1); 
		temp  = __HAL_DMA_GET_COUNTER(&hdma_usart1_rx); 
		U1_RX_Len =  U1_RX_BufferSize - temp; 
		if (U1_RX_Len >= 30)
		{
			if ((U1_RX_Buffer[(U1_RX_Len - 1)] == '%')&&(U1_RX_Buffer[U1_RX_Len - 30] == '$'))
			{
				U1_RX_EndFlag = 1; 
				U1_RX_Position = &U1_RX_Buffer[U1_RX_Len - 30];
			}
			else
			{
				HAL_UART_Receive_DMA(&huart1, U1_RX_Buffer, U1_RX_BufferSize);
			}
		}
		else
		{
			HAL_UART_Receive_DMA(&huart1, U1_RX_Buffer, U1_RX_BufferSize);
		}
	}
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
	uint32_t tmp_flag = 0;
	uint32_t temp;
	tmp_flag = __HAL_UART_GET_FLAG(&huart2, UART_FLAG_IDLE);
	if ((tmp_flag != RESET))
	{ 
		__HAL_UART_CLEAR_IDLEFLAG(&huart2); 
		temp = huart2.Instance->SR; 
		temp = huart2.Instance->DR; 
		HAL_UART_DMAStop(&huart2); 
		temp  = __HAL_DMA_GET_COUNTER(&hdma_usart2_rx); 
		U2_RX_Len =  U2_RX_BufferSize- temp; 
		if (U2_RX_Len >= 5)
		{
			if ((U2_RX_Buffer[(U2_RX_Len - 1)] == '%')&&(U2_RX_Buffer[U2_RX_Len - 5] == '$'))
			{
				U2_RX_EndFlag = 1; 
				U2_RX_Position = &U2_RX_Buffer[U2_RX_Len - 5];
			}
			else
			{
				HAL_UART_Receive_DMA(&huart2, U2_RX_Buffer, U2_RX_BufferSize);
			}
		}
		else
		{
			HAL_UART_Receive_DMA(&huart2, U2_RX_Buffer, U2_RX_BufferSize);
		}
	}
  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */
	uint32_t tmp_flag = 0;
	uint32_t temp;
	tmp_flag = __HAL_UART_GET_FLAG(&huart3, UART_FLAG_IDLE);
	if ((tmp_flag != RESET))
	{ 
		__HAL_UART_CLEAR_IDLEFLAG(&huart3); 
		temp = huart3.Instance->SR; 
		temp = huart3.Instance->DR; 
		HAL_UART_DMAStop(&huart3); 
		temp  = __HAL_DMA_GET_COUNTER(&hdma_usart3_rx); 
		U3_RX_Len =  U3_RX_BufferSize - temp; 
		if (U3_RX_Len >= 23)
		{
			if ((U3_RX_Buffer[(U3_RX_Len - 1)] == '%')&&(U3_RX_Buffer[U3_RX_Len - 23] == '$'))
			{
				U3_RX_EndFlag = 1; 
				U3_RX_Position = &U3_RX_Buffer[U3_RX_Len - 23];
			}
			else
			{
				HAL_UART_Receive_DMA(&huart3, U3_RX_Buffer, U3_RX_BufferSize);
			}
		}
		else
		{
			HAL_UART_Receive_DMA(&huart3, U3_RX_Buffer, U3_RX_BufferSize);
		}
	}
  /* USER CODE END USART3_IRQn 0 */
  HAL_UART_IRQHandler(&huart3);
  /* USER CODE BEGIN USART3_IRQn 1 */

  /* USER CODE END USART3_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream7 global interrupt.
  */
void DMA1_Stream7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream7_IRQn 0 */

  /* USER CODE END DMA1_Stream7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_uart5_tx);
  /* USER CODE BEGIN DMA1_Stream7_IRQn 1 */

  /* USER CODE END DMA1_Stream7_IRQn 1 */
}

/**
  * @brief This function handles UART4 global interrupt.
  */
void UART4_IRQHandler(void)
{
  /* USER CODE BEGIN UART4_IRQn 0 */
	uint32_t tmp_flag = 0;
	uint32_t temp;
	tmp_flag = __HAL_UART_GET_FLAG(&huart4, UART_FLAG_IDLE);
	if ((tmp_flag != RESET))
	{ 
		__HAL_UART_CLEAR_IDLEFLAG(&huart4); 
		temp = huart4.Instance->SR; 
		temp = huart4.Instance->DR; 
		HAL_UART_DMAStop(&huart4); 
		temp  = __HAL_DMA_GET_COUNTER(&hdma_uart4_rx); 
		U4_RX_Len =  U4_RX_BufferSize - temp; 
		if (U4_RX_Len >= 14)
		{
			for (int i = 0; i < 40; ++i)
			{
				if (U4_RX_Buffer[i] == 'T')
				{
					for (int j = i; j < 40; ++j)
					{
						if (U4_RX_Buffer[j] == '\n')
						{
							U4_RX_Position = &U4_RX_Buffer[i];
							U4_RX_EndFlag = 1; 
							break;
						}
					}
					break;
				}
			}
			if (U4_RX_EndFlag == 0)
			{
				HAL_UART_Receive_DMA(&huart4, U4_RX_Buffer, U4_RX_BufferSize);
			}
		}
		else
		{
			HAL_UART_Receive_DMA(&huart4, U4_RX_Buffer, U4_RX_BufferSize);
		}
	}
  /* USER CODE END UART4_IRQn 0 */
  HAL_UART_IRQHandler(&huart4);
  /* USER CODE BEGIN UART4_IRQn 1 */

  /* USER CODE END UART4_IRQn 1 */
}

/**
  * @brief This function handles UART5 global interrupt.
  */
void UART5_IRQHandler(void)
{
  /* USER CODE BEGIN UART5_IRQn 0 */

  /* USER CODE END UART5_IRQn 0 */
  HAL_UART_IRQHandler(&huart5);
  /* USER CODE BEGIN UART5_IRQn 1 */

  /* USER CODE END UART5_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global interrupt, DAC1 and DAC2 underrun error interrupts.
  */
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */

  /* USER CODE END TIM6_DAC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream0 global interrupt.
  */
void DMA2_Stream0_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream0_IRQn 0 */

  /* USER CODE END DMA2_Stream0_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA2_Stream0_IRQn 1 */

  /* USER CODE END DMA2_Stream0_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream5 global interrupt.
  */
void DMA2_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream5_IRQn 0 */

  /* USER CODE END DMA2_Stream5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* USER CODE BEGIN DMA2_Stream5_IRQn 1 */

  /* USER CODE END DMA2_Stream5_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
