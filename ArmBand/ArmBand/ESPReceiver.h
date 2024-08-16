#ifndef ESP_RECEIVER_H
#define ESP_RECEIVER_H

#include "Constant.h"
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

const uint8_t MESSAGE_TYPE_BRIGHTNESS = 0;
const uint8_t MESSAGE_TYPE_HUE = 1;
const uint8_t MESSAGE_TYPE_BPM = 2;
const uint8_t MESSAGE_TYPE_PATTERN = 3;
const uint8_t MESSAGE_TYPE_LIGHT_DEVICE = 4;
const uint8_t MESSAGE_TYPE_FORCE_BRIGHTNESS = 5; 

const uint8_t MESSAGE_TWEAK_QUANTITY = 6;
const uint8_t MESSAGE_TWEAK_BPM = 7;    
const uint8_t MESSAGE_TWEAK_COLOR = 8;     
const uint8_t MESSAGE_TWEAK_PHASE = 9;    

typedef struct Message {
  uint8_t message_type;   
  uint8_t value;          
} Message;

Message message;

void data_received(const uint8_t *mac, const uint8_t *incomingData, int len) {
    memcpy(&message, incomingData, sizeof(message));

    switch (message.message_type) {
        case MESSAGE_TYPE_BRIGHTNESS:
            brightness = message.value;
            break;
        case MESSAGE_TYPE_HUE:
            hue = message.value;
            break;
        case MESSAGE_TYPE_BPM:
            bpm = message.value;
            break;
        case MESSAGE_TYPE_PATTERN:
            pattern = message.value;
            break;
        case MESSAGE_TYPE_LIGHT_DEVICE:
            // preferences.begin("my-app", false);  // Namespace "my-app", RW mode
            // preferences.putInt("lightDevice", message.value);  
            // preferences.end(); 
            lightDevice = message.value;
            whichLightDevice(); 
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
        case MESSAGE_TYPE_FORCE_BRIGHTNESS: 
            isForcedBrightness = (message.value == 1) ? true : false;
            break;
        default:
            break;
    }
}

#endif 