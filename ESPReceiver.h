#ifndef ESP_RECEIVER_H
#define ESP_RECEIVER_H

#include "Constant.h"
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

const uint8_t MESSAGE_TYPE_BRIGHTNESS = 0;
const uint8_t MESSAGE_TYPE_BPM = 1;
const uint8_t MESSAGE_TYPE_PATTERN = 2;
const uint8_t MESSAGE_TYPE_LIGHT_DEVICE = 3;
const uint8_t MESSAGE_TYPE_HUE = 4;

const uint8_t MESSAGE_TWEAK_QUANTITY = 5;
const uint8_t MESSAGE_TWEAK_BPM = 6;    
const uint8_t MESSAGE_TWEAK_COLOR = 7;     
const uint8_t MESSAGE_TWEAK_PHASE = 8;    

typedef struct Message {
  uint8_t message_type;  // 0: brightness, 1: bpm, 2: pattern, 3: define light device 4: RGBColor
  uint8_t value;          // For brightness, BPM, pattern, or define light device
  uint16_t hue;     // For RGBColor (4 bytes)
} Message;

Message message;

void data_received(const uint8_t *mac, const uint8_t *incomingData, int len) {
    memcpy(&message, incomingData, sizeof(message));

    switch (message.message_type) {
        case MESSAGE_TYPE_BRIGHTNESS:
            brightness = message.value;
            break;
        case MESSAGE_TYPE_BPM:
            bpm = message.value;
            break;
        case MESSAGE_TYPE_PATTERN:
            pattern = message.value;
            break;
        case MESSAGE_TYPE_LIGHT_DEVICE:
            // This won't be used for the coat code, because the ESP32S3 board is attached to the coat, so it can't connect to a WristBand or Feet or HeadBand.
            break;
        case MESSAGE_TYPE_HUE:
            hue = message.hue;
            break;
        case MESSAGE_TWEAK_QUANTITY:
            tweakQuantity = message.value;
            break;
        case MESSAGE_TWEAK_BPM:
            tweakBPM = message.value;
            break;
        case MESSAGE_TWEAK_COLOR:  
            tweakColor = message.value;
            break;
        case MESSAGE_TWEAK_PHASE: 
            tweakPhase = message.value;
            break;
        default:
            break;
    }
}

#endif 