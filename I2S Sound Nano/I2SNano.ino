#include <driver/i2s.h>
#include "progmem.h" // Include your PROGMEM-like data header

#define I2S_NUM           ((i2s_port_t)0) // I2S port number

void setup() {
  Serial.begin(115200);
  delay(1000); // Ensure Serial is initialized

  // I2S configuration
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX), // Master, TX only
    .sample_rate = 22100,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ALL_RIGHT,
    .communication_format = I2S_COMM_FORMAT_I2S_MSB,
    .intr_alloc_flags = 0, // Default interrupt priority
    .dma_buf_count = 8,
    .dma_buf_len = 64,
    .use_apll = false
  };

  // I2S pin configuration
  i2s_pin_config_t pin_config = {
    .bck_io_num = 7,    // Bit Clock (BCK)
    .ws_io_num = 8,     // Word Select (LCK)
    .data_out_num = 9,  // Data Out (DIN)
    .data_in_num = I2S_PIN_NO_CHANGE
  };

  // Install and start I2S driver
  esp_err_t err;
  err = i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
  if (err != ESP_OK) {
    Serial.printf("Failed to install I2S driver: %d\n", err);
    return;
  }

  err = i2s_set_pin(I2S_NUM, &pin_config);
  if (err != ESP_OK) {
    Serial.printf("Failed to set I2S pins: %d\n", err);
    return;
  }

  Serial.println("I2S driver installed and pins set");
}

void loop() {
  // Example: send data from PROGMEM-like array
  size_t bytes_written;

  esp_err_t err = i2s_write(I2S_NUM, StarWars30_raw, StarWars30_raw_len, &bytes_written, portMAX_DELAY);
  // if (err != ESP_OK) {
  //   Serial.printf("Failed to write I2S data: %d\n", err);
  // } else {
  //   Serial.printf("Bytes written: %d\n", bytes_written);
  // }

  // delay(100);
}
