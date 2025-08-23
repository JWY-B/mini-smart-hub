#include "XPT2046.h"
#include "stm32f10x.h"

// 初始化触摸屏 GPIO
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

// 发送一个字节并接收返回字节
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

// 发送命令并读12位 ADC 数据
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

//===================== 高层功能函数 =====================//

// 读取一次坐标 (不做平均)
void XPT2046_GetRawXY(uint16_t *x, uint16_t *y)
{
    *x = XPT2046_ReadADC(CMD_X);
    *y = XPT2046_ReadADC(CMD_Y);
}

// 多次采样平均，减少抖动
uint8_t XPT2046_GetAverageXY(uint16_t *x, uint16_t *y)
{
    uint16_t xbuf[5], ybuf[5];
    uint32_t sumx = 0, sumy = 0;
    uint8_t i;

    // 检查 PENIRQ (PF10) 是否触摸
    if (XPT2046_PEN_READ())
        return 0; // 高电平 = 未按下

    for (i = 0; i < 5; i++)
    {
        xbuf[i] = XPT2046_ReadADC(CMD_X);
        ybuf[i] = XPT2046_ReadADC(CMD_Y);
        delay_us(200); // 两次采样间隔
    }

    for (i = 0; i < 5; i++)
    {
        sumx += xbuf[i];
        sumy += ybuf[i];
    }

    *x = sumx / 5;
    *y = sumy / 5;

    return 1; // 成功获取
}

//===================== 对外接口 =====================//

// 返回是否有触摸，x,y 为触摸点坐标
uint8_t XPT2046_Scan(uint16_t *x, uint16_t *y)
{
    // PENIRQ = 0 表示触摸
    if (!GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_10))
    {
        return XPT2046_GetAverageXY(x, y);
    }
    return 0; // 没有触摸
}
