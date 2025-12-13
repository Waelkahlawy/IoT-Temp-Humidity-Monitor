#ifndef MQTT_H
#define MQTT_H
#include <stdio.h>                  // Standard input/output functions
#include <string.h>                 // For string handling (memcpy, strcmp, etc.)
#include <freertos/FreeRTOS.h>      // FreeRTOS base definitions
#include <freertos/task.h>          // For task creation and delays
#include <esp_system.h>             // ESP32 system functions
#include <esp_wifi.h>               // Wi-Fi driver
#include <esp_event.h>              // Event loop for Wi-Fi and system
#include <esp_log.h>                // Logging utilities
#include <nvs_flash.h>              // Non-volatile storage for Wi-Fi credentials
#include <driver/gpio.h>            // GPIO control
#include <esp_netif.h>              // Network interface setup
#include <mqtt_client.h>            // MQTT client
#include <esp_timer.h>              // High-resolution timer
#include "esp_rom_sys.h"            // For microsecond delay (esp_rom_delay_us)

 void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
 void mqtt_app_start(void);


#endif