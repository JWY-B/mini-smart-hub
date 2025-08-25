#include "XPT2046.h"
#include "stm32f10x.h"
#include "LCD.h"

/**
 * @description: 初始化触摸屏 GPIO
 * @return {无}
 */
void XPT2046_TouchInit(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOF, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    // PB1 推挽输出 (SCK)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_1);

    // PF9 PF11 推挽输出 (MOSI, CS)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_SetBits(GPIOF, GPIO_Pin_9 | GPIO_Pin_11);

    // PF10 上拉输入 (PENIRQ)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_SetBits(GPIOF, GPIO_Pin_10);

    // PB2 上拉输入 (MISO)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_2);
}

/**
 * @description: 发送一个字节并接收返回字节
 * @param {uint8_t} data:发送的字节
 * @return {rxData:接收的字节}
 */
uint8_t XPT2046_WriteByte(uint8_t data)
{
    uint8_t i, rxData = 0;

    for (i = 0; i < 8; i++)
    {
        // MOSI (PF9)
        if (data & 0x80)
            XPT2046_MOSI_HIGH();
        else
            XPT2046_MOSI_LOW();

        data <<= 1;

        XPT2046_CLK_HIGH();

        // 采样 MISO (PB2)
        rxData <<= 1;
        if (XPT2046_MISO_READ())
            rxData |= 0x01;

        // SCK 下降沿
        XPT2046_CLK_LOW();
    }

    return rxData;
}

/**
 * @description: 发送命令并读12位 ADC 数据
 * @param {uint8_t} cmd:命令字节
 * @return {12位触摸数据}
 */
uint16_t XPT2046_ReadADC(uint8_t cmd)
{
    uint16_t value;

    // CS 拉低 (PF11)
    XPT2046_CS_LOW();
    XPT2046_WriteByte(cmd);

    value = XPT2046_WriteByte(0x00) << 8; // 高8位
    value |= XPT2046_WriteByte(0x00);     // 低8位

    // CS 拉高
    XPT2046_CS_HIGH();

    value >>= 4; // 取高12位
    return value;
}

/**
 * @description: 读取一次坐标
 * @param {uint16_t} *x:x坐标
 * @param {uint16_t} *y:y坐标
 * @return {无}
 */
void XPT2046_GetRawXY(uint16_t *x, uint16_t *y)
{
    *x = XPT2046_ReadADC(CMD_X);
    *y = XPT2046_ReadADC(CMD_Y);
}

//
/**
 * @description: 多次采样平均，减少抖动
 * @param {uint16_t} *x:x坐标
 * @param {uint16_t} *y:y坐标
 * @return {1:成功}
 */
#define XPT2046_PEN_IS_DOWN() (!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_10)) // PENIRQ=0表示触摸

uint8_t XPT2046_GetAverageXY(uint16_t *x, uint16_t *y)
{
    if (!XPT2046_PEN_IS_DOWN())
        return 0; // 无触摸，直接返回

    uint16_t xbuf[9], ybuf[9];
    for (uint8_t i = 0; i < 9; i++)
    {
        xbuf[i] = XPT2046_ReadADC(CMD_X);
        ybuf[i] = XPT2046_ReadADC(CMD_Y);
    }

    // 简单选择排序（比冒泡更简洁）
    for (uint8_t i = 0; i < 8; i++)
    {
        uint8_t min = i;
        for (uint8_t j = i + 1; j < 9; j++)
        {
            if (xbuf[j] < xbuf[min])
                min = j;
        }
        if (min != i)
        {
            uint16_t t = xbuf[i];
            xbuf[i] = xbuf[min];
            xbuf[min] = t;
        }

        min = i;
        for (uint8_t j = i + 1; j < 9; j++)
        {
            if (ybuf[j] < ybuf[min])
                min = j;
        }
        if (min != i)
        {
            uint16_t t = ybuf[i];
            ybuf[i] = ybuf[min];
            ybuf[min] = t;
        }
    }

    uint32_t sumx = 0, sumy = 0;
    for (uint8_t i = 2; i < 7; i++)
    { // 取中间5个
        sumx += xbuf[i];
        sumy += ybuf[i];
    }

    // 得到滤波后的原始坐标
    uint16_t tx = sumx / 5;
    uint16_t ty = sumy / 5;

    // 坐标变换与校正
    *x = (ty * 0.26f - 50.0f) + 15;
    *y = 320 - (tx * 0.19f - 32.0f) + 5;

    return 1;
}

/**
 * @brief 返回是否有触摸，若有则给出坐标
 */
uint8_t XPT2046_Scan(uint16_t *x, uint16_t *y)
{
    return XPT2046_PEN_IS_DOWN() ? XPT2046_GetAverageXY(x, y) : 0;
}

/**
 * @brief 是否按下（无坐标）
 */
uint8_t XPT2046_IsPressed(void)
{
    return XPT2046_PEN_IS_DOWN();
}
