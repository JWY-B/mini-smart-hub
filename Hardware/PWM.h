/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-25 17:40:58
 * @LastEditTime: 2025-08-26 11:32:31
 * @FilePath: \智能家居中控系统\mini-smart-hub\Hardware\PWM.h
 * @Description:
 */
#ifndef __PWM_H
#define __PWM_H

#define LCD_BL_GPIO_PORT GPIOA
#define LCD_BL_GPIO_PIN GPIO_Pin_0
#define PWM_GPIO_CLK RCC_APB2Periph_GPIOA

#define PWM_TIM TIM2
#define PWM_TIM_CLK RCC_APB1Periph_TIM2

void PWM_Init(void);
void LCD_Backlight_SetBrightness(uint8_t brightness);

#define Motor_GPIO_PORT GPIOA
#define Motor_GPIO_PWM_PIN GPIO_Pin_2

#define Motor2_GPIO_PORT GPIOA
#define Motor2_GPIO_PWM_PIN GPIO_Pin_3

void Motor_SetSpeed(uint8_t speed);
void Motor_SetSpeed2(uint8_t speed);
#endif
