/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-16 18:13:19
 * @LastEditTime: 2025-08-18 14:46:39
 * @FilePath: \mini-smart-hub\User\main.c
 * @Description:
 */
#include "stm32f10x.h" // Device header
#include "LCD.h"
#include "Serial.h"
int main(void)
{
	Serial_Init();						//´®¿Ú³õÊ¼»¯
	
	while (1)
	{
		printf("11");
	}
}