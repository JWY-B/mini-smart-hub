/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-25 17:39:13
 * @LastEditTime: 2025-08-26 11:32:15
 * @FilePath: \���ܼҾ��п�ϵͳ\mini-smart-hub\Hardware\PWM.c
 * @Description:PWM����
 */
#include "stm32f10x.h"
#include "PWM.h"

/**
 * @description: ��ʼ��PWM
 * @return {��}
 */
void PWM_Init(void)
{
    // 1. ��ʱ��
    RCC_APB2PeriphClockCmd(PWM_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(PWM_TIM_CLK, ENABLE);

    // 2. ��ʼ�� LCD_BL_GPIO
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
    TIM_TimeBaseInit(PWM_TIM, &TIM_TimeBaseStruct);

    // 4. LCD_Backlight_PWMģʽ����
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 999; // ��ʼ����100%
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(PWM_TIM, &TIM_OCInitStruct);

    // 2. ��ʼ�� Motor_GPIO
    GPIO_InitStruct.GPIO_Pin = Motor_GPIO_PWM_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; // ��������
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Motor_GPIO_PORT, &GPIO_InitStruct);
    // 5. Motor_PWMģʽ����
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 0; // ��ʼռ�ձ� 0%�������ת
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC3Init(PWM_TIM, &TIM_OCInitStruct);
    TIM_OC3PreloadConfig(PWM_TIM, TIM_OCPreload_Enable);

    GPIO_InitStruct.GPIO_Pin = Motor2_GPIO_PWM_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; // ��������
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Motor2_GPIO_PORT, &GPIO_InitStruct);
    // 5. Motor_PWMģʽ����
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 0; // ��ʼռ�ձ� 0%�������ת
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC4Init(PWM_TIM, &TIM_OCInitStruct);
    TIM_OC4PreloadConfig(PWM_TIM, TIM_OCPreload_Enable);

    TIM_Cmd(PWM_TIM, ENABLE);
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
    uint16_t pulse = brightness * 999 / 100;
    TIM_SetCompare1(PWM_TIM, pulse);
    // TIM_SetCompare2
}

/**
 * @description: ���õ��ת��
 * @param {uint8_t} speed 0~100 (%)(ת��)
 * @return {��}
 */
void Motor_SetSpeed(uint8_t speed)
{
    if (speed > 100)
        speed = 100;
    uint16_t pulse = speed * 999 / 100; // ռ�ձȼ���
    TIM_SetCompare3(PWM_TIM, pulse);
}

void Motor_SetSpeed2(uint8_t speed)
{
    if (speed > 100)
        speed = 100;
    uint16_t pulse = speed * 999 / 100; // ռ�ձȼ���
    TIM_SetCompare4(PWM_TIM, pulse);
}
