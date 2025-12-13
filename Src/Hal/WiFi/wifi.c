#include "wifi.h"
#include "../../Cfg.h"

  static const char *TAG = "WiFi";     // Logging tag name




// ====== Wi-Fi event handler ======
 void wifi_event_handler(void* arg, esp_event_base_t event_base,
                              int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect(); // Start connecting when Wi-Fi starts
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        ESP_LOGW(TAG, "Wi-Fi disconnected. Reconnecting...");
        esp_wifi_connect(); // Auto reconnect on disconnection
        
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "Wi-Fi connected, IP: " IPSTR, IP2STR(&event->ip_info.ip)); // Log IP address
    }
}

void wifi_init_sta(void)
{
    
    esp_netif_init();                       // Initialize network interface
    esp_event_loop_create_default();        // Create default event loop
    esp_netif_create_default_wifi_sta();    // Create default Wi-Fi station

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT(); // Default config
    esp_wifi_init(&cfg);                                // Initialize Wi-Fi driver

    // Register event handlers
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL);

    // Configure Wi-Fi credentials
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASSWORD,
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
        },
    };

    esp_wifi_set_mode(WIFI_MODE_STA);          // Station mode (client)
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config); // Apply Wi-Fi settings
    esp_wifi_start();                          // Start Wi-Fi
}
