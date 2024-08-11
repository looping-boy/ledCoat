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

// void data_sent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//   Serial.print("\r\nStatus of Last Message Sent:\t");
//   Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
// }

typedef struct struct_message {
  char character[100];
  int integer;
  float floating_value;
  bool bool_value;
} struct_message;

struct_message message;

void setupESP() {
  WiFi.mode(WIFI_STA); 

  // Set the WiFi channel
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(WIFI_CHANNEL, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(false);
  //esp_wifi_set_antenna(WIFI_ANT_EXTERNAL);

  if (esp_now_init() != ESP_OK) {
    // Serial.println("ESP-NOW initialization failed");
    return;
  }

  // esp_now_register_send_cb(data_sent);

  for (int i = 0; i < sizeof(broadcastAddresses) / sizeof(broadcastAddresses[0]); i++) {
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, broadcastAddresses[i], 6);
    peerInfo.channel = WIFI_CHANNEL;  
    peerInfo.encrypt = false;  
    peerInfo.ifidx = WIFI_IF_STA;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
      // Serial.println("Failed to add peer");
      return;
    }
  }
}

void sendValue(int value) {
  // Populate message with default values
  //strcpy(message.character, "Welcome to Microcontrollerslab! This is test example.");
  message.integer = random(1, 10);
  message.floating_value = 5.6;
  message.bool_value = true;

  // Set integer based on the input value
  switch (value) {
    case 1:
      message.integer = 1;
      break;
    case 2:
      message.integer = 2;
      break;
    case 3:
      message.integer = 0;
      break;
    case 4:
      message.integer = 4;
      break;
    default:
      return;
  }
  //56ms pour 3 adresses
  unsigned long startTime, endTime;
  startTime = micros();
  // Send message to all broadcast addresses
  for (int i = 0; i < sizeof(broadcastAddresses) / sizeof(broadcastAddresses[0]); i++) {
    
    esp_err_t outcome = esp_now_send(broadcastAddresses[i], (uint8_t *) &message, sizeof(message));
    endTime = micros();

    // if (outcome == ESP_OK) {
    //   Serial.print("Message sent successfully to address ");
    // } else {
    //   Serial.print("Error sending the message to address ");
    // }

    // char buffer[32];
    // snprintf(buffer, sizeof(buffer), "%d", endTime - startTime);
    // const char* resultString = buffer;

    // sprite.fillRect(M_20 + M_20 + M_20 + M_20 + M_20 + M_20 + M_20 + M_20 + M_20 + M_20 , M_20 , M_20 + M_20 + M_20 + M_20, M_20 + M_20, TFT_BLACK);
    // sprite.drawString(resultString, M_20 + M_20 + M_20 + M_20 + M_20 + M_20 + M_20 + M_20 + M_20 + M_20 , M_20 , 2);
    // sprite.pushSprite(0, 0);

  }
}

#endif
