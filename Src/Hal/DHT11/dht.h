#ifndef DHT_H
#define DHT_H
#include <stdio.h>                  // Standard input/output functions
#include <string.h>                 // For string handling (memcpy, strcmp, etc.)
#include <freertos/FreeRTOS.h>      // FreeRTOS base definitions
#include <freertos/task.h>          // For task creation and delays
#include <esp_system.h>             // ESP32 system functions
#include <esp_log.h>                // Logging utilities
#include <driver/gpio.h>            // GPIO control
#include <esp_timer.h>              // High-resolution timer
#include "esp_rom_sys.h"            // For microsecond delay (esp_rom_delay_us)


esp_err_t dht11_read(uint8_t *temperature, uint8_t *humidity);



#endif