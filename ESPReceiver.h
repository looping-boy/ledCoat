#ifndef ESP_RECEIVER_H
#define ESP_RECEIVER_H

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

typedef struct struct_message {
  char character[100];
  int integer;
  float floating_value;
  bool bool_value;
} struct_message;

struct_message incomingMessage;

void data_received(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingMessage, incomingData, sizeof(incomingMessage));

  // Handle incoming message
  something = incomingMessage.integer;
  currentStep = 0;
}

#endif 