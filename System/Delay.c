/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-17 23:11:03
 * @LastEditTime: 2025-08-27 10:43:07
 * @FilePath: \mini-smart-hub\System\Delay.c
 * @Description:
 */
#include "stm32f10x.h"
#include "Delay.h"
#include "FreeRTOS.h"
#include "task.h"
/**
 * @brief  微秒级延时
 * @param  xus 延时时长，范围：0~233015
 * @retval 无
 */

// nus为要延时的us数.
void delay_us(u32 nus)
{
	u32 ticks;
	u32 told, tnow, tcnt = 0;
	u32 reload = SysTick->LOAD;				   // LOAD的值
	ticks = nus * (SystemCoreClock / 1000000); // 需要的节拍数
	tcnt = 0;
	vTaskSuspendAll();	 // 阻止OS调度，防止打断us延时
	told = SysTick->VAL; // 刚进入时的计数器值
	while (1)
	{
		tnow = SysTick->VAL;
		if (tnow != told)
		{
			if (tnow < told)
				tcnt += told - tnow; // 这里注意一下SYSTICK是一个递减的计数器就可以了.
			else
				tcnt += reload - tnow + told;
			told = tnow;
			if (tcnt >= ticks)
				break; // 时间超过/等于要延迟的时间,则退出.
		}
	};
	xTaskResumeAll(); // 恢复OS调度
}

/**
 * @brief  毫秒级延时
 * @param  xms 延时时长，范围：0~4294967295
 * @retval 无
 */
void delay_ms(uint32_t ms)
{
#if (IN_FREERTOS == 1)
	// FreeRTOS 环境下用调度延时
	vTaskDelay(pdMS_TO_TICKS(ms));
#else
	// 裸机环境下用 us 延时凑出来
	while (ms--)
		delay_us(1000);
#endif
}

/**
 * @brief  秒级延时
 * @param  xs 延时时长，范围：0~4294967295
 * @retval 无
 */
void delay_s(uint32_t xs)
{
	while (xs--)
	{
		delay_ms(1000);
	}
}
