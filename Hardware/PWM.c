/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-25 17:39:13
 * @LastEditTime: 2025-08-26 11:32:15
 * @FilePath: \智能家居中控系统\mini-smart-hub\Hardware\PWM.c
 * @Description:PWM驱动
 */
#include "stm32f10x.h"
#include "PWM.h"

/**
 * @description: 初始化PWM
 * @return {无}
 */
void PWM_Init(void)
{
    // 1. 开时钟
    RCC_APB2PeriphClockCmd(PWM_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(PWM_TIM_CLK, ENABLE);

    // 2. 初始化 LCD_BL_GPIO
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = LCD_BL_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCD_BL_GPIO_PORT, &GPIO_InitStruct);

    // 3. 初始化 TIM2 PWM
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
    TIM_TimeBaseStruct.TIM_Period = 999;   // PWM周期
    TIM_TimeBaseStruct.TIM_Prescaler = 71; // 时钟分频 72MHz/72 = 1MHz
    TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(PWM_TIM, &TIM_TimeBaseStruct);

    // 4. LCD_Backlight_PWM模式配置
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 999; // 初始亮度100%
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(PWM_TIM, &TIM_OCInitStruct);

    // 2. 初始化 Motor_GPIO
    GPIO_InitStruct.GPIO_Pin = Motor_GPIO_PWM_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Motor_GPIO_PORT, &GPIO_InitStruct);
    // 5. Motor_PWM模式配置
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 0; // 初始占空比 0%，电机不转
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC3Init(PWM_TIM, &TIM_OCInitStruct);
    TIM_OC3PreloadConfig(PWM_TIM, TIM_OCPreload_Enable);

    GPIO_InitStruct.GPIO_Pin = Motor2_GPIO_PWM_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Motor2_GPIO_PORT, &GPIO_InitStruct);
    // 5. Motor_PWM模式配置
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 0; // 初始占空比 0%，电机不转
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC4Init(PWM_TIM, &TIM_OCInitStruct);
    TIM_OC4PreloadConfig(PWM_TIM, TIM_OCPreload_Enable);

    TIM_Cmd(PWM_TIM, ENABLE);
}
/**
 * @description: 设置LCD背光亮度
 * @param {uint8_t} brightness 0~100 (%)(亮度)
 * @return {无}
 */
void LCD_Backlight_SetBrightness(uint8_t brightness)
{
    if (brightness > 100)
        brightness = 100;
    uint16_t pulse = brightness * 999 / 100;
    TIM_SetCompare1(PWM_TIM, pulse);
    // TIM_SetCompare2
}

/**
 * @description: 设置电机转速
 * @param {uint8_t} speed 0~100 (%)(转速)
 * @return {无}
 */
void Motor_SetSpeed(uint8_t speed)
{
    if (speed > 100)
        speed = 100;
    uint16_t pulse = speed * 999 / 100; // 占空比计算
    TIM_SetCompare3(PWM_TIM, pulse);
}

void Motor_SetSpeed2(uint8_t speed)
{
    if (speed > 100)
        speed = 100;
    uint16_t pulse = speed * 999 / 100; // 占空比计算
    TIM_SetCompare4(PWM_TIM, pulse);
}
