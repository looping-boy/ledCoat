#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xA0, 0xA3, 0xB3, 0xAA, 0x65, 0x6C};

// Set the WiFi channel
#define WIFI_CHANNEL 3

typedef struct struct_message {
  char character[100];
  int integer;
  float floating_value;
  bool bool_value;
} struct_message;

struct_message message;

void data_sent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nStatus of Last Message Sent:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
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

  esp_now_register_send_cb(data_sent);
  
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = WIFI_CHANNEL;  
  peerInfo.encrypt = false;  
  peerInfo.ifidx = WIFI_IF_STA;
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  strcpy(message.character, "Welcome to Microcontrollerslab! This is test example.");
  message.integer = random(1, 10);
  message.floating_value = 5.6;
  message.bool_value = true;
  
  esp_err_t outcome = esp_now_send(broadcastAddress, (uint8_t *) &message, sizeof(message));
   
  if (outcome == ESP_OK) {
    Serial.println("Message sent successfully!");
  } else {
    Serial.println("Error sending the message");
  }
  delay(2000);
}
