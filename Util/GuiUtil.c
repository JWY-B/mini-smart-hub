/*
 * @Author: jwy 2660243285@qq.com
 * @Date: 2025-08-27 20:16:43
 * @LastEditTime: 2025-08-27 20:18:02
 * @FilePath: \mini-smart-hub\Util\GuiUtil.c
 * @Description:
 */
#include "Global.h"
#include "GuiUtil.h"
uint8_t get_motor_dropdown_index(MotorMessage_t motor_msg)
{
    if (motor_msg.mode == MOTOR_MODE_AUTO)
        return 0; // 下拉列表第 0 项 = Auto

    // 手动模式，value 对应下拉列表 1~4 项
    switch (motor_msg.value)
    {
    case 25:
        return 1;
    case 50:
        return 2;
    case 75:
        return 3;
    case 100:
        return 4;
    default:
        return 1; // 如果 value 不在范围内，默认选第 1 项
    }
}