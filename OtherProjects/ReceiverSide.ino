#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

// Set the WiFi channel
#define WIFI_CHANNEL 3

typedef struct struct_message {
  char character[100];
  int integer;
  float floating_value;
  bool bool_value;
} struct_message;

struct_message incomingMessage;

void data_received(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingMessage, incomingData, sizeof(incomingMessage));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(incomingMessage.character);
  Serial.print("Int: ");
  Serial.println(incomingMessage.integer);
  Serial.print("Float: ");
  Serial.println(incomingMessage.floating_value);
  Serial.print("Bool: ");
  Serial.println(incomingMessage.bool_value);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  
  // Set the WiFi channel
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(WIFI_CHANNEL, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(false);
  
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_recv_cb(data_received);
}
 
void loop() {
  // Nothing to do here, everything is handled in the callback
}
