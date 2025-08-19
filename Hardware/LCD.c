/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-17 19:08:54
 * @LastEditTime: 2025-08-20 00:01:43
 * @FilePath: \mini-smart-hub\Hardware\LCD.c
 * @Description:
 */
#include "stm32f10x.h" // Device header
#include "LCD.h"
#include "Delay.h"
void LCD_WR_REG(uint16_t regval)
{
    LCD->LCD_REG = regval; // 写寄存器
}

void LCD_WR_DATA(uint16_t data)
{
    LCD->LCD_RAM = data; // 写数据
}
void LCD_Init(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |
                               RCC_APB2Periph_GPIOD |
                               RCC_APB2Periph_GPIOE |
                               RCC_APB2Periph_GPIOG,
                           ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_12;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef ReadWriteTimingStruct, WriteTimingStruct;
    ReadWriteTimingStruct.FSMC_AddressSetupTime = 26;
    ReadWriteTimingStruct.FSMC_AddressHoldTime = 7;
    ReadWriteTimingStruct.FSMC_DataSetupTime = 32;
    ReadWriteTimingStruct.FSMC_BusTurnAroundDuration = 1;
    ReadWriteTimingStruct.FSMC_CLKDivision = 0;
    ReadWriteTimingStruct.FSMC_DataLatency = 0;
    ReadWriteTimingStruct.FSMC_AccessMode = FSMC_AccessMode_A;

    WriteTimingStruct.FSMC_AddressSetupTime = 1; // ASET ≈ 14ns
    WriteTimingStruct.FSMC_AddressHoldTime = 1;  // AHOLD ≈ 14ns
    WriteTimingStruct.FSMC_DataSetupTime = 6;    // DSET ≈ 83ns
    WriteTimingStruct.FSMC_BusTurnAroundDuration = 1;
    WriteTimingStruct.FSMC_CLKDivision = 0;
    WriteTimingStruct.FSMC_DataLatency = 0;
    WriteTimingStruct.FSMC_AccessMode = FSMC_AccessMode_A;

    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;                     //  这里我们使用NE4 ，也就对应BTCR[6],[7]。
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;   // 不复用数据地址
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;              // FSMC_MemoryType_SRAM;  //SRAM
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;     // 存储器数据宽度为16bit
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable; // FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable; //  存储器写使能
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // 读写使用不同的时序
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &ReadWriteTimingStruct; // 读写时序
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &WriteTimingStruct;         // 写时序

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); // 初始化FSMC配置

    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE); // 使能BANK1

    // 退出睡眠
    LCD_WR_REG(0x11);
    Delay_ms(120);

    // 命令解锁
    LCD_WR_REG(0xF0);
    LCD_WR_DATA(0xC3);
    LCD_WR_REG(0xF0);
    LCD_WR_DATA(0x96);

    // 内存访问控制
    LCD_WR_REG(0x36);
    LCD_WR_DATA(0x48); // 屏幕方向，RGB顺序

    // 像素格式
    LCD_WR_REG(0x3A);
    LCD_WR_DATA(0x55); // 16bit/pixel

    // 显示反转设置
    LCD_WR_REG(0xB4);
    LCD_WR_DATA(0x01); // 1-dot inversion

    // 门驱动时序控制
    LCD_WR_REG(0xB7);
    LCD_WR_DATA(0xC6);

    // 电源设置
    LCD_WR_REG(0xC0);
    LCD_WR_DATA(0x80);
    LCD_WR_DATA(0x64); // VGH=15V, VGL=-10V

    LCD_WR_REG(0xC1);
    LCD_WR_DATA(0x13); // Vop=4.5V

    LCD_WR_REG(0xC2);
    LCD_WR_DATA(0xA7);

    LCD_WR_REG(0xC5);
    LCD_WR_DATA(0x08);

    // 电压设置
    LCD_WR_REG(0xE8);
    LCD_WR_DATA(0x40);
    LCD_WR_DATA(0x8A);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x29);
    LCD_WR_DATA(0x19);
    LCD_WR_DATA(0xA5);
    LCD_WR_DATA(0x33);

    // 正极性Gamma
    LCD_WR_REG(0xE0);
    LCD_WR_DATA(0xF0);
    LCD_WR_DATA(0x06);
    LCD_WR_DATA(0x0B);
    LCD_WR_DATA(0x07);
    LCD_WR_DATA(0x06);
    LCD_WR_DATA(0x05);
    LCD_WR_DATA(0x2E);
    LCD_WR_DATA(0x33);
    LCD_WR_DATA(0x47);
    LCD_WR_DATA(0x3A);
    LCD_WR_DATA(0x17);
    LCD_WR_DATA(0x16);
    LCD_WR_DATA(0x2E);
    LCD_WR_DATA(0x31);

    // 负极性Gamma
    LCD_WR_REG(0xE1);
    LCD_WR_DATA(0xF0);
    LCD_WR_DATA(0x09);
    LCD_WR_DATA(0x0D);
    LCD_WR_DATA(0x09);
    LCD_WR_DATA(0x08);
    LCD_WR_DATA(0x23);
    LCD_WR_DATA(0x2E);
    LCD_WR_DATA(0x33);
    LCD_WR_DATA(0x46);
    LCD_WR_DATA(0x38);
    LCD_WR_DATA(0x13);
    LCD_WR_DATA(0x13);
    LCD_WR_DATA(0x2C);
    LCD_WR_DATA(0x32);

    // 命令锁回去
    LCD_WR_REG(0xF0);
    LCD_WR_DATA(0x3C);
    LCD_WR_REG(0xF0);
    LCD_WR_DATA(0x69);

    // TE 信号
    LCD_WR_REG(0x35);
    LCD_WR_DATA(0x00);

    // 显示反色（可选，不要就注释掉）
    LCD_WR_REG(0x21);

    // 设置窗口大小 320x480
    LCD_WR_REG(0x2A); // column addr set
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x01);
    LCD_WR_DATA(0x3F); // 319

    LCD_WR_REG(0x2B); // row addr set
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x01);
    LCD_WR_DATA(0xDF); // 479

    // 开显示
    LCD_WR_REG(0x29);
    Delay_ms(50);

    // 写内存使能
    LCD_WR_REG(0x2C);
}


uint16_t LCD_RD_DATA(void)
{
    volatile uint16_t data;
    data = LCD->LCD_RAM; // 读数据
    return data;
}

void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{
    LCD->LCD_REG = LCD_Reg;      // 写寄存器
    LCD->LCD_RAM = LCD_RegValue; // 写数据
}

uint16_t LCD_ReadReg(uint16_t LCD_Reg)
{
    LCD_WR_REG(LCD_Reg); // 写寄存器
    Delay_us(5);
    return LCD_RD_DATA(); // 读数据
}

void LCD_WriteRAM_Prepare(void)
{
    LCD->LCD_REG = lcddev.wramcmd;
}

uint16_t LCD_WriteRAM(uint16_t RGB_Code)
{
    LCD->LCD_RAM = RGB_Code; // 写GRAM
}