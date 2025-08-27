/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-24 18:09:10
 * @LastEditTime: 2025-08-27 10:29:50
 * @FilePath: \mini-smart-hub\System\TIM3.c
 * @Description:
 */
#include "stm32f10x.h"
#include "LCD.h"
#include "Delay.h"
void TIM3_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 999;   // ARR = 999
    TIM_TimeBaseStructure.TIM_Prescaler = 71; // PSC = 71
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM3, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); // 开启GPIOA的时钟
                                                          // 使用各个外设前必须开启时钟，否则对外设的操作无效
    /*GPIO初始化*/
    GPIO_InitTypeDef GPIO_InitStructure; // 定义结构体变量

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // GPIO模式，赋值为推挽输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;         // GPIO引脚，赋值为第0号引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // GPIO速度，赋值为50MHz

    GPIO_Init(GPIOE, &GPIO_InitStructure); // 将赋值后的构体变量传递给GPIO_Init函数
                                           // 函数内部会自动根据结构体的参数配置相应寄存器
}
void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        // lv_tick_inc(1);
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}
