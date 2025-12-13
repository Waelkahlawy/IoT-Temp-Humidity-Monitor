#ifndef CFG_H
#define CFG_H


// ====== Wi-Fi and MQTT configuration ======
#define WIFI_SSID       "WAEL"    // Your Wi-Fi SSID
#define WIFI_PASSWORD   "Null@987897"         // Your Wi-Fi password
#define MQTT_BROKER_IP  "192.168.1.2"    // Local MQTT broker IP address
#define MQTT_BROKER_URI "mqtt://192.168.1.2"  
// ====== GPIO pin configuration ======
#define LED_GPIO        GPIO_NUM_2         // Onboard LED (GPIO 2)
#define DHT_GPIO        GPIO_NUM_4         // DHT11 data pin (GPIO 4)

// ====== MQTT topics ======
#define TEMP_TOPIC      "local/temperature"   // Temperature topic
#define HUMIDITY_TOPIC  "local/humidity"      // Humidity topic
#define LED_TOPIC       "local/led"        // LED control topic




#endif