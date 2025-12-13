#include "mqtt.h"
#include "../../Cfg.h"
#include "../WiFi/wifi.h"


static const char *TAG = "mqtt";     // Logging tag name

// ====== Global variables ======
 esp_mqtt_client_handle_t mqtt_client = NULL;  // MQTT client handle
 bool led_state = false;             // Current LED state



// ====== MQTT event handler ======
 void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t) event_data;
    esp_mqtt_client_handle_t client = event->client;

    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "✅ Connected to MQTT broker");
            esp_mqtt_client_subscribe(client, LED_TOPIC, 1); // Subscribe to LED topic
            break;

        case MQTT_EVENT_DATA: {
            char topic[128] = {0};
            char payload[128] = {0};
            memcpy(topic, event->topic, event->topic_len);    // Copy topic string
            memcpy(payload, event->data, event->data_len);    // Copy payload string
            topic[event->topic_len] = '\0';
            payload[event->data_len] = '\0';
            ESP_LOGI(TAG, "📩 %s => %s", topic, payload);     // Log received message

            // If LED topic message received
            if (strcmp(topic, LED_TOPIC) == 0) {
                bool new_state = led_state; // Default: no change

                // Parse payload text
                if (strcasecmp(payload, "ON") == 0) {
                    new_state = true;
                } else if (strcasecmp(payload, "OFF") == 0) {
                    new_state = false;
                }

                // Only change if state differs
                if (new_state != led_state) {
                    gpio_set_level(LED_GPIO, new_state ? 1 : 0); // Set LED level
                    led_state = new_state;
                    // Publish confirmation message (ON/OFF)
                    esp_mqtt_client_publish(client, LED_TOPIC, led_state ? "ON" : "OFF", 0, 1, true);
                    ESP_LOGI(TAG, "LED state updated to: %s", led_state ? "ON" : "OFF");
                }
                // If same state, do nothing → prevents MQTT feedback loop
            }
            break;
        }

        case MQTT_EVENT_ERROR:
            ESP_LOGE(TAG, "MQTT connection error"); // Connection error
            break;

        default:
            break;
    }
}

// ====== Initialize Wi-Fi in station mode ======

// ====== Start MQTT client ======
void mqtt_app_start(void)
{
    static char broker_uri[64];
    snprintf(broker_uri, sizeof(broker_uri), "mqtt://%s:1883", MQTT_BROKER_IP); // Format broker URI

     esp_mqtt_client_config_t mqtt_cfg = {
		.broker.address.uri = MQTT_BROKER_URI,
        // .broker.address.uri = broker_uri,                 // Broker URI
        .credentials.client_id = "esp32_dht11_local",     // MQTT client ID
        .network.disable_auto_reconnect = false,          // Auto reconnect enabled
    };

    mqtt_client = esp_mqtt_client_init(&mqtt_cfg); // Initialize MQTT client
    if (!mqtt_client) {
        ESP_LOGE(TAG, "MQTT init failed");
        return;
    }

    // Register MQTT event callback
    esp_mqtt_client_register_event(mqtt_client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(mqtt_client); // Start client
}
