#ifndef __PWM_H
#define __PWM_H

#define LCD_BL_GPIO_PORT GPIOA
#define LCD_BL_GPIO_PIN GPIO_Pin_0
#define LCD_BL_GPIO_CLK RCC_APB2Periph_GPIOA
#define LCD_BL_TIM TIM2
#define LCD_BL_TIM_CLK RCC_APB1Periph_TIM2

void LCD_Backlight_PWM_Init(void);
void LCD_Backlight_SetBrightness(uint8_t brightness);

#endif
