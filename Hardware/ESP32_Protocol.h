#ifndef ESP32_PROTOCOL_H
#define ESP32_PROTOCOL_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include <stdint.h>
#include <stdbool.h>
#define ESP32_PACKET_SIZE 7
typedef struct
{
    struct
    {
        uint8_t brightness;
    } light;

    struct
    {
        uint8_t mode;
        uint8_t value;
    } motor;
    struct
    {
        uint8_t mode;
        uint8_t value;
    } servo;
} ESP32Data_t;
extern ESP32Data_t esp32Data;
void ESP32_Protocol_Init(void);
bool ProcessESP32Byte(uint8_t byte);
ESP32Data_t GetESP32Data(void);

#endif // ESP32_PROTOCOL_H