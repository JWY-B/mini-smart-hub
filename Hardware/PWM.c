/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-25 17:39:13
 * @LastEditTime: 2025-08-25 23:44:40
 * @FilePath: \mini-smart-hub\Hardware\PWM.c
 * @Description:PWM����
 */
#include "stm32f10x.h"
#include "PWM.h"

/**
 * @description: ��ʼ��LCD����PWM
 * @return {��}
 */
void LCD_Backlight_PWM_Init(void)
{
    // 1. ��ʱ��
    RCC_APB2PeriphClockCmd(LCD_BL_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(LCD_BL_TIM_CLK, ENABLE);

    // 2. ��ʼ�� GPIO
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = LCD_BL_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; // ��������
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCD_BL_GPIO_PORT, &GPIO_InitStruct);

    // 3. ��ʼ�� TIM2 PWM
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
    TIM_TimeBaseStruct.TIM_Period = 999;   // PWM����
    TIM_TimeBaseStruct.TIM_Prescaler = 71; // ʱ�ӷ�Ƶ 72MHz/72 = 1MHz
    TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(LCD_BL_TIM, &TIM_TimeBaseStruct);

    // 4. PWM ģʽ����
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 1000; // ��ʼ����100%
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(LCD_BL_TIM, &TIM_OCInitStruct);

    TIM_Cmd(LCD_BL_TIM, ENABLE);
}
/**
 * @description: ����LCD��������
 * @param {uint8_t} brightness 0~100 (%)(����)
 * @return {��}
 */
void LCD_Backlight_SetBrightness(uint8_t brightness)
{
    if (brightness > 100)
        brightness = 100;
    uint16_t pulse = brightness * 999 / 100; // ��Ӧ TIM_Period = 999
    TIM_SetCompare1(LCD_BL_TIM, pulse);
}
