#include "dht.h"
#include "../../Cfg.h"


static const char *TAG = "dht11";     // Logging tag name
// ====== Microsecond delay function ======
static void dht_delay_us(uint32_t us)
{
    esp_rom_delay_us(us);  // Accurate microsecond delay using ROM function
}

// ====== Read data from DHT11 sensor with retries ======
esp_err_t dht11_read(uint8_t *temperature, uint8_t *humidity)
{
    uint8_t data[5] = {0};     // Buffer for DHT11 data
    int retry = 2;             // Try reading twice if it fails

    while (retry--) {
        // Start signal for DHT11
        gpio_set_direction(DHT_GPIO, GPIO_MODE_OUTPUT);  // Set as output
        gpio_set_level(DHT_GPIO, 0);                     // Pull low
        vTaskDelay(pdMS_TO_TICKS(20));                   // Hold for 20ms
        gpio_set_level(DHT_GPIO, 1);                     // Pull high
        dht_delay_us(50);                                // Wait 50µs
        gpio_set_direction(DHT_GPIO, GPIO_MODE_INPUT);   // Switch to input to read data

        // Wait for DHT11 response (low and high pulses)
        int timeout = 0;
        while (gpio_get_level(DHT_GPIO) == 1 && timeout++ < 100) dht_delay_us(1);
        timeout = 0;
        while (gpio_get_level(DHT_GPIO) == 0 && timeout++ < 100) dht_delay_us(1);
        timeout = 0;
        while (gpio_get_level(DHT_GPIO) == 1 && timeout++ < 100) dht_delay_us(1);

        // Read 40 bits of data (humidity, temperature, checksum)
        for (int i = 0; i < 40; i++) {
            timeout = 0;
            while (gpio_get_level(DHT_GPIO) == 0 && timeout++ < 200) dht_delay_us(1); // Wait for start of bit
            uint64_t start = esp_timer_get_time(); // Start measuring pulse length
            while (gpio_get_level(DHT_GPIO) == 1 && timeout++ < 200) dht_delay_us(1); // Wait for end of bit
            uint32_t duration = esp_timer_get_time() - start; // Measure pulse width

            // If pulse > 40µs, bit = 1, else bit = 0
            data[i / 8] <<= 1;
            if (duration > 40) data[i / 8] |= 1;
        }

        // Verify checksum
        if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
            *humidity = data[0];       // Integer part of humidity
            *temperature = data[2];    // Integer part of temperature
            return ESP_OK;             // Reading OK
        }

        // Retry if checksum fails
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    ESP_LOGE(TAG, "DHT11 checksum error after retries");
    return ESP_FAIL;  // Failed after retries
}
