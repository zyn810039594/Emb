#ifndef __BSP_USART_H
#define	__BSP_USART_H


#include "stm32f10x.h"
#include <stdio.h>

extern vu8 PrintFlag;
// 串口1-USART1 无
#define  DEBUG_USARTx_CON                   USART1
#define  DEBUG_USART_CLK_CON                RCC_APB2Periph_USART1
#define  DEBUG_USART_APBxClkCmd_CON         RCC_APB2PeriphClockCmd
#define  DEBUG_USART_BAUDRATE_CON           115200

// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK_CON           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd_CON    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT_CON       GPIOA   
#define  DEBUG_USART_TX_GPIO_PIN_CON        GPIO_Pin_9
#define  DEBUG_USART_RX_GPIO_PORT_CON       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN_CON        GPIO_Pin_10

#define  DEBUG_USART_IRQ_CON                USART1_IRQn
#define  DEBUG_USART_IRQHandler_CON         USART1_IRQHandler


// 串口2-USART2 水深
#define  DEBUG_USARTx_SON                   USART2
#define  DEBUG_USART_CLK_SON                RCC_APB1Periph_USART2
#define  DEBUG_USART_APBxClkCmd_SON         RCC_APB1PeriphClockCmd
#define  DEBUG_USART_BAUDRATE_SON           115200

//// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK_SON           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd_SON    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT_SON       GPIOA   
#define  DEBUG_USART_TX_GPIO_PIN_SON        GPIO_Pin_2
#define  DEBUG_USART_RX_GPIO_PORT_SON       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN_SON        GPIO_Pin_3

#define  DEBUG_USART_IRQ_SON                USART2_IRQn
#define  DEBUG_USART_IRQHandler_SON         USART2_IRQHandler

// 串口3-USART3 与arduino通信
#define  DEBUG_USARTx_ARD                   USART3
#define  DEBUG_USART_CLK_ARD                RCC_APB1Periph_USART3
#define  DEBUG_USART_APBxClkCmd_ARD         RCC_APB1PeriphClockCmd
#define  DEBUG_USART_BAUDRATE_ARD           9600

//// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK_ARD           (RCC_APB2Periph_GPIOB)
#define  DEBUG_USART_GPIO_APBxClkCmd_ARD    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT_ARD       GPIOB   
#define  DEBUG_USART_TX_GPIO_PIN_ARD        GPIO_Pin_10
#define  DEBUG_USART_RX_GPIO_PORT_ARD       GPIOB
#define  DEBUG_USART_RX_GPIO_PIN_ARD        GPIO_Pin_11

#define  DEBUG_USART_IRQ_ARD                USART3_IRQn
#define  DEBUG_USART_IRQHandler_ARD         USART3_IRQHandler

// 串口4-UART4 2560
#define  DEBUG_USARTx_SE1                   UART4
#define  DEBUG_USART_CLK_SE1                RCC_APB1Periph_UART4
#define  DEBUG_USART_APBxClkCmd_SE1         RCC_APB1PeriphClockCmd
#define  DEBUG_USART_BAUDRATE_SE1           9600

//// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK_SE1           (RCC_APB2Periph_GPIOC)
#define  DEBUG_USART_GPIO_APBxClkCmd_SE1    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT_SE1       GPIOC   
#define  DEBUG_USART_TX_GPIO_PIN_SE1        GPIO_Pin_10
#define  DEBUG_USART_RX_GPIO_PORT_SE1       GPIOC
#define  DEBUG_USART_RX_GPIO_PIN_SE1        GPIO_Pin_11

#define  DEBUG_USART_IRQ_SE1                UART4_IRQn
#define  DEBUG_USART_IRQHandler_SE1         UART4_IRQHandler


// 串口5-UART5 上下位通信
#define  DEBUG_USARTx_SE2                   UART5
#define  DEBUG_USART_CLK_SE2                RCC_APB1Periph_UART5
#define  DEBUG_USART_APBxClkCmd_SE2         RCC_APB1PeriphClockCmd
#define  DEBUG_USART_BAUDRATE_SE2           115200

//// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK_SE2           (RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD)
#define  DEBUG_USART_GPIO_APBxClkCmd_SE2    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT_SE2       GPIOC   
#define  DEBUG_USART_TX_GPIO_PIN_SE2        GPIO_Pin_12
#define  DEBUG_USART_RX_GPIO_PORT_SE2       GPIOD
#define  DEBUG_USART_RX_GPIO_PIN_SE2        GPIO_Pin_2

#define  DEBUG_USART_IRQ_SE2               UART5_IRQn
#define  DEBUG_USART_IRQHandler_SE2         UART5_IRQHandler

void USART_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);

#endif /* __USART_H */
