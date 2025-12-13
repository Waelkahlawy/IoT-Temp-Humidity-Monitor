#ifndef WIFI_H
#define WIFI_H
#include <stdio.h>                  // Standard input/output functions
#include <string.h>                 // For string handling (memcpy, strcmp, etc.)
#include <freertos/FreeRTOS.h>      // FreeRTOS base definitions
#include <freertos/task.h>          // For task creation and delays
#include <esp_system.h>             // ESP32 system functions
#include <esp_wifi.h>               // Wi-Fi driver
#include <esp_event.h>              // Event loop for Wi-Fi and system
#include <esp_log.h>                // Logging utilities
#include <nvs_flash.h>              // Non-volatile storage for Wi-Fi credentials
#include <esp_netif.h>              // Network interface setup

#include <esp_timer.h>              // High-resolution timer
#include "esp_rom_sys.h"            // For microsecond delay (esp_rom_delay_us)


 void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

 void wifi_init_sta(void);
                             


#endif