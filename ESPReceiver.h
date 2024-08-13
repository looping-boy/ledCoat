#ifndef ESP_RECEIVER_H
#define ESP_RECEIVER_H

#include "Constant.h"
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

const uint8_t MESSAGE_TYPE_PATTERN = 2;
const uint8_t MESSAGE_TYPE_BPM = 1;

typedef struct Message {
  uint8_t message_type;  // 0: brightness, 1: bpm, 2: pattern, 3: define light device 4: RGBColor
  uint8_t value;          // For brightness, BPM, pattern, or define light device
  uint32_t color;     // For RGBColor (4 bytes)
} Message;

Message message;


void data_received(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&message, incomingData, sizeof(message));

Serial.print("Sending message_type: ");
Serial.println(message.message_type);
Serial.print("Sending value: ");
Serial.println(message.value);
Serial.print("Sending color: ");
Serial.println(message.color);
Serial.print("Sending len: ");
Serial.println(len);

  switch (message.message_type) {
    case 0:  // Brightness
      brightness = message.value;
      break;
    case MESSAGE_TYPE_BPM:  // BPM
      bpm = message.value;
      break;
    case MESSAGE_TYPE_PATTERN:  // Pattern
      pattern = message.value;
      break;
    case 3:  // Define light device
      // wont use for the coat code, because the ESP32S3 board is attached to the coat, so can't connect it to an WristBand or Feet or HeadBand.
      break;
    case 4:  // RGB Color
      color = message.color;
      break;
    default:
      // Handle unknown message type
      break;
  }
}

// void data_received(const uint8_t * mac, const uint8_t *incomingData, int len) {
//   memcpy(&incomingMessage, incomingData, sizeof(incomingMessage));

//   // Handle incoming message
//   pattern = incomingMessage.integer;
//   currentStep = 0;
// }



#endif 