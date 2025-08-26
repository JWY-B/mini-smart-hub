/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-25 23:33:19
 * @LastEditTime: 2025-08-26 12:48:48
 * @FilePath: \智能家居中控系统\mini-smart-hub\Hardware\DHT11.c
 * @Description:温湿度传感器驱动
 */

#include "stm32f10x.h"
#include "DHT11.h"
#include "Delay.h"

/**
 * @description: 初始化DHT11
 * @return {无}
 */
void DHT11_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = DHT11_DATA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DHT11_PORT, &GPIO_InitStructure);
    GPIO_SetBits(DHT11_PORT, DHT11_DATA_PIN);
}

/**
 * @description: 设置DHT11引脚模式
 * @param {uint8_t} mode：模式，OUT：输出模式，IN：输入模式
 * @return {无}
 */
void DHT11_Mode(uint8_t mode)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    if (mode)
    {
        GPIO_InitStructure.GPIO_Pin = DHT11_DATA_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(DHT11_PORT, &GPIO_InitStructure);
    }
    else
    {
        GPIO_InitStructure.GPIO_Pin = DHT11_DATA_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(DHT11_PORT, &GPIO_InitStructure);
    }
}
/**
 * @description: 启动DHT11
 * @return {uint8_t} 0：启动成功，1：启动失败
 */
uint8_t DHT11_Start(void)
{

    uint8_t time = 0;
    DHT11_Mode(OUT);
    DHT11_LOW;
    delay_ms(20);
    DHT11_HIGH;

    delay_us(30);
    DHT11_Mode(IN);
    while (DHT11_READ_PIN == 0 && time < 100)
    {
        time++;
        delay_us(1);
    }
    if (time > 100)
    {
        return 1;
    }
    else
    {
        time = 0;
    }
    while (DHT11_READ_PIN == 1 && time < 100)
    {
        time++;
        delay_us(1);
    }
    if (time >= 100)
    {
        return 1;
    }
    return 0;
}

/**
 * @description: 读取DHT11Bit位
 * @return {uint8_t} Bit位
 */
uint8_t DHT11_Read_Bit(void)
{
    uint8_t time = 0;
    while (DHT11_READ_PIN == 1 && time < 100)
    {
        time++;
        delay_us(1);
    }
    time = 0;

    while (DHT11_READ_PIN == 0 && time < 100)
    {
        time++;
        delay_us(1);
    }
    delay_us(40);
    if (DHT11_READ_PIN == 1)
    {
        return 1;
    }
    return 0;
}
/**
 * @description: 读取DHT11字节
 * @return {uint8_t} 字节数据
 */
uint8_t DHT11_Read_Byte(void)
{
    uint8_t i, Byte;
    Byte = 0;
    for (i = 0; i < 8; i++)
    {
        Byte <<= 1;
        Byte |= DHT11_Read_Bit();
    }
    return Byte;
}

/**
 * @description: 读取DHT11温湿度数据
 * @param {uint8_t} *humidity:湿度指针
 * @param {uint8_t} *temperature:温度指针
 * @return {uint8_t} 0：读取成功，1：读取失败
 */
uint8_t DHT11_Read_Data(uint8_t *humidity, uint8_t *temperature)
{
    uint8_t i, j, data[5];
    if (DHT11_Start())
    {
        return 1;
    }
    for (i = 0; i < 5; i++)
    {
        data[i] = DHT11_Read_Byte();
    }
    if (data[0] + data[1] + data[2] + data[3] == data[4] && data[0]<=100 &&data[2] <=50)
    {
        *humidity = data[0];
        *temperature = data[2];
        return 0;
    }
    else
    {
        return 1;
    }
}