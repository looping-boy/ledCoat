// ColorTab.h
#ifndef ESP_SENDER_H
#define ESP_SENDER_H

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddresses[][6] = {
  // {0x64, 0xe8, 0x33, 0x86, 0x1d, 0xf4}, // WHITE
  // {0x64, 0xe8, 0x33, 0x85, 0x28, 0x3c}, // PURPLE
  // {0x64, 0xe8, 0x33, 0x85, 0xdb, 0x24},  // NEW
  // {0x64, 0xe8, 0x33, 0x85, 0x85, 0xd8},  // NEW Purple
  // {0x64, 0xe8, 0x33, 0x86, 0xf8, 0x0c},  // BLACK Broken pin
  // {0x64, 0xe8, 0x33, 0x86, 0xe9, 0x28},  // BLACK
  // {0x64, 0xe8, 0x33, 0x85, 0xc5, 0xbc},  // BLACK 2
  {0x64, 0xe8, 0x33, 0x86, 0xfe, 0x04},  // RED
  {0x64, 0xe8, 0x33, 0x85, 0xe0, 0x04},  // GREEN
  {0x64, 0xe8, 0x33, 0x50, 0x9f, 0x2c}  // GREEN
};

// Set the WiFi channel
#define WIFI_CHANNEL 3

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

void setupESP() {
  WiFi.mode(WIFI_STA); 

  // Set the WiFi channel
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(WIFI_CHANNEL, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(false);

  if (esp_now_init() != ESP_OK) {
    // Just failed bro
    return;
  }

  for (int i = 0; i < sizeof(broadcastAddresses) / sizeof(broadcastAddresses[0]); i++) {
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, broadcastAddresses[i], 6);
    peerInfo.channel = WIFI_CHANNEL;  
    peerInfo.encrypt = false;  
    peerInfo.ifidx = WIFI_IF_STA;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
      // Basically failed
      return;
    }
  }
}

void sendValue(uint8_t messageType, uint8_t value, uint16_t hue = 0) {
  Message message;

  message.message_type = messageType;

  switch (messageType) {
    case MESSAGE_TYPE_BRIGHTNESS:     // Brightness
    case MESSAGE_TYPE_BPM:            // BPM
    case MESSAGE_TYPE_PATTERN:        // Pattern
    case MESSAGE_TYPE_LIGHT_DEVICE:   // Define Light Device: Foot, Wrist, Coat, or HeadBand
    case MESSAGE_TWEAK_QUANTITY:      // Tweak Quantity
    case MESSAGE_TWEAK_BPM:           // Tweak BPM
    case MESSAGE_TWEAK_COLOR:         // Tweak Color
    case MESSAGE_TWEAK_PHASE:         // Tweak Phase
      message.value = value;
      message.hue = 0;                // Not used here
      break;
    case MESSAGE_TYPE_HUE:            // HSV Hue
      message.value = 0;              // Not used here
      message.hue = hue;              // 0 to 360
      break;
    default:
      return;
  }

  for (int i = 0; i < sizeof(broadcastAddresses) / sizeof(broadcastAddresses[0]); i++) {
    esp_now_send(broadcastAddresses[i], (uint8_t *) &message, sizeof(message));
  }
}

#endif
