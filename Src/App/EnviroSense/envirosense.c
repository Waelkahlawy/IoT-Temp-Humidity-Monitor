#include "envirosense.h"

#include "../../Cfg.h"
#include "../../Hal/DHT11/dht.h"
#include "../../Hal/MQTT/mqtt.h"
#include "../../Hal/WiFi/wifi.h"
#include <mqtt_client.h>            

extern esp_mqtt_client_handle_t mqtt_client ;  // MQTT client handle

static const char *TAG = "envirosense";     // Logging tag name


// ====== Task: read DHT11 and send data via MQTT ======
void dht11_mqtt_task(void *pvParameters)
{
	  // Initialize non-volatile storage
    esp_err_t ret = nvs_flash_init();
     if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        ret= nvs_flash_init();
    }
        ESP_LOGI(TAG, "Connecting Wi-Fi...");
    wifi_init_sta();  // Initialize Wi-Fi

    vTaskDelay(pdMS_TO_TICKS(7000)); // Wait for connection before MQTT
    mqtt_app_start();                // Start MQTT client


    uint8_t temp = 0, hum = 0;
    char temp_str[10], hum_str[10];

    while (1) {
        if (!mqtt_client) {
            ESP_LOGW(TAG, "MQTT not ready yet...");
            vTaskDelay(pdMS_TO_TICKS(2000));  // Wait before retrying
            continue;
        }

        if (dht11_read(&temp, &hum) == ESP_OK) { // Successfully read DHT11
            snprintf(temp_str, sizeof(temp_str), "%d", temp);
            snprintf(hum_str, sizeof(hum_str), "%d", hum);
            ESP_LOGI(TAG, "Temperature:  %s  | Humidity:  %s%%", temp_str, hum_str);
            esp_mqtt_client_publish(mqtt_client, TEMP_TOPIC, temp_str, 0, 1, false); // Publish temperature
            esp_mqtt_client_publish(mqtt_client, HUMIDITY_TOPIC, hum_str, 0, 1, false); // Publish humidity
        } else {
            ESP_LOGW(TAG, "Failed to read DHT11 — skipping publish");
        }

        vTaskDelay(pdMS_TO_TICKS(3000)); // Wait 3 seconds before next reading
    }
}

