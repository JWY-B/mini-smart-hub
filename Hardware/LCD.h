/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-17 19:09:07
 * @LastEditTime: 2025-08-18 16:11:06
 * @FilePath: \mini-smart-hub\Hardware\LCD.h
 * @Description:
 */
#ifndef __LCD_H
#define __LCD_H

typedef struct
{
    volatile uint16_t LCD_TEG; // 控制寄存器
    volatile uint16_t LCD_RAM; // 数据寄存器
} LCD_TypeDef;

#define LCD_BASE ((uint32_t)(0x60000000 | 0x000007FE))
#define LCD ((LCD_TypeDef *)LCD_BASE)

#endif
