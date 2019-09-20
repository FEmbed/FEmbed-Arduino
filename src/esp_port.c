#if USE_ESPRESSIF8266

#include "FreeRTOS.h"

void delay(uint32_t ms)
{
    portTickType ticks = ms / portTICK_RATE_MS;
    vTaskDelay(ticks ? ticks : 1);
}

#endif