#ifndef __BSP_GENERALTIME_H
#define __BSP_GENERALTIME_H


#include "stm32f10x.h"

// 我们这里默认使用TIM3

#define            GENERAL_TIM                   TIM3
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM3
#define            GENERAL_TIM_Period            19999
#define            GENERAL_TIM_Prescaler         71
// TIM3 输出比较通道1
#define            GENERAL_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH1_PORT          GPIOA
#define            GENERAL_TIM_CH1_PIN           GPIO_Pin_6

// TIM3 输出比较通道2
#define            GENERAL_TIM_CH2_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH2_PORT          GPIOA
#define            GENERAL_TIM_CH2_PIN           GPIO_Pin_7


/**************************函数声明********************************/

void GENERAL_TIM_Init(void);

#endif	/* __BSP_GENERALTIME_H */


