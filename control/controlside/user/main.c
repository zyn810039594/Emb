#include "MainInclude.h"

int main(void)
{


    SysTick_Init();
    //SysTick_Delay_Ms(6000);
    //两路PWM初始化
    //GENERAL_TIM_Init();
    USART_Config();
    //BASIC_TIM_Init();
    IWDG_Config(IWDG_Prescaler_64, 1250);
    while (1)
    {
        IWDG_Feed();
        SendDown();
        SendUp();
    }



}
