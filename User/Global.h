
#ifndef __GLOBAL_H
#define __GLOBAL_H

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

typedef struct
{
    uint8_t temperature;
    uint8_t humidity;
} DHT11_Data_t;

extern DHT11_Data_t dht11_data;
extern SemaphoreHandle_t dht11_mutex;

#endif