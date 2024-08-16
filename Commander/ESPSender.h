// ColorTab.h
#ifndef ESP_SENDER_H
#define ESP_SENDER_H

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddresses[][6] = {
  {0x64, 0xe8, 0x33, 0x50, 0x9f, 0x2c},  // COAT
  // {0x64, 0xe8, 0x33, 0x86, 0x1d, 0xf4},  // WHITE
  //{0x64, 0xe8, 0x33, 0x85, 0x85, 0xd8},  // PURPLE (feet right now)
  //{0x64, 0xe8, 0x33, 0x86, 0xe9, 0x28},  // BLACK (feet right now)
  {0x64, 0xe8, 0x33, 0x85, 0xc5, 0xbc},  // BLACK (headbandRightNow)
  {0x64, 0xe8, 0x33, 0x86, 0xfe, 0x04},  // RED (arm)
  {0x64, 0xe8, 0x33, 0x85, 0xe0, 0x04},  // GREEN (arm)
};

enum LightDevice {
  COAT,
  WHITE,
  PURPLE_FEET,
  BLACK_FEET,
  BLACK_HEADBAND,
  RED_ARM,
  GREEN_ARM,
  DEVICE_COUNT  // Used to get the number of devices
};

// Set the WiFi channel
#define WIFI_CHANNEL 3

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

void sendValue(uint8_t messageType, uint8_t value) {
  Message message;

  message.message_type = messageType;

  switch (messageType) {
    case MESSAGE_TYPE_BRIGHTNESS:     // Brightness
    case MESSAGE_TYPE_HUE:            // Send HSV hue
    case MESSAGE_TYPE_BPM:            // BPM
    case MESSAGE_TYPE_PATTERN:        // Pattern
    case MESSAGE_TYPE_LIGHT_DEVICE:   // Define Light Device: Foot, Wrist, Coat, or HeadBand
    case MESSAGE_TWEAK_QUANTITY:      // Tweak Quantity
    case MESSAGE_TWEAK_BPM:           // Tweak BPM
    case MESSAGE_TWEAK_COLOR:         // Tweak Color
    case MESSAGE_TWEAK_PHASE:         // Tweak Phase
    case MESSAGE_TYPE_FORCE_BRIGHTNESS:
      message.value = value;    // Not used here
      break;   
    default:
      return;
  }

  for (int i = 0; i < sizeof(broadcastAddresses) / sizeof(broadcastAddresses[0]); i++) {
    esp_now_send(broadcastAddresses[i], (uint8_t *) &message, sizeof(message));
  }
}

void sendValueToDevice(LightDevice device, uint8_t value) {
  if (device >= DEVICE_COUNT) {
    return;
  }

  Message message;
  message.message_type = MESSAGE_TYPE_LIGHT_DEVICE;
  message.value = value;

  esp_now_send(broadcastAddresses[device], (uint8_t *) &message, sizeof(message));
}

#endif
