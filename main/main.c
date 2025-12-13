#include "../Src/App/EnviroSense/envirosense.h"
#include "../Src/Cfg.h"
#include "../Src/Hal/WiFi/wifi.h"
#include "../Src/Hal/MQTT/mqtt.h"
#include <stdio.h>                  // Standard input/output functions
#include <string.h>                 // For string handling (memcpy, strcmp, etc.)
#include <freertos/FreeRTOS.h>      // FreeRTOS base definitions
#include <driver/gpio.h>            // GPIO control

  
// static const char *TAG = "MAIN"; 
    // ====== Main application entry point ======
void app_main(void)
{		
	
    
	// Configure LED pin
	    gpio_reset_pin(LED_GPIO);
	    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
	    gpio_set_level(LED_GPIO, 0); // LED off initially

	    // Configure DHT pin
	    gpio_reset_pin(DHT_GPIO);
	    gpio_set_direction(DHT_GPIO, GPIO_MODE_INPUT);

       

    // Create task for DHT11 readings
    xTaskCreate(dht11_mqtt_task, "dht11_mqtt_task", 4096, NULL, 5, NULL);

	
}
