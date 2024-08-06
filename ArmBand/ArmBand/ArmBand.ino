#include <FastLED.h>
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

#define NUM_STRIPS 4
#define SIZE_ANIM 144
#define MAX_BRIGHTNESS 20
#define POT_PIN D0  
#define BATTERY_PIN D1  
#define shutdownPin D9 
#define MOTOR_PIN D10
#define WIFI_CHANNEL 3

CRGB leds[NUM_STRIPS][72];
unsigned long lastPotReadTime = 0;
const unsigned long potReadInterval = 100;

int something = 0; // Current animation state
int currentStep = 0; // Current step in the animation

void setup() {
  Serial.begin(115200);

  // ------------- SHUTDOWN ---------------
  pinMode(shutdownPin, OUTPUT);
  digitalWrite(shutdownPin, LOW);

  // ------------- MOTOR ---------------
  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, LOW);

  // ------------- NEOPIXEL ---------------  
  FastLED.addLeds<NEOPIXEL, D8>(leds[1], SIZE_ANIM);
  updateBrightness();

  // ------------- ESP NOW ---------------
  WiFi.mode(WIFI_STA);
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(WIFI_CHANNEL, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(false);
  
  if (esp_now_init() != ESP_OK) {
    return;
  }
  
  esp_now_register_recv_cb(data_received);
}

void loop() {
  //updateBrightness();
  readBatteryVoltage();
  
  switch (something) {
    case 0:
      breathingSmallStep();
      break;
    case 1:
      allWhiteStep();
      break;
    case 2:
      allRedStep();
      break;
    case 4:
      FastLED.setBrightness(250);
      break;
  }
  
  FastLED.show();
}

void updateBrightness() {
  int potValue = analogRead(POT_PIN);
  int brightness = mapPotValueToBrightness(potValue);
  FastLED.setBrightness(brightness);
}

void readBatteryVoltage() {
  int batteryValue = analogRead(BATTERY_PIN);
  if (batteryValue < 2000) {
    digitalWrite(MOTOR_PIN, HIGH);
    delay(1000);
    digitalWrite(MOTOR_PIN, LOW);
    delay(500);
    digitalWrite(MOTOR_PIN, HIGH);
    delay(1000);
    digitalWrite(MOTOR_PIN, LOW);
    delay(500);
    digitalWrite(shutdownPin, LOW);
    digitalWrite(shutdownPin, HIGH);
    delay(5000);
    digitalWrite(shutdownPin, LOW);
  }
}

int mapPotValueToBrightness(int potValue) {
  float scale = (float)potValue / 3145.0; // Scale to range 0.0 to 1.0
  float expBrightness = pow(scale, 2.5) * MAX_BRIGHTNESS + 1; 
  return constrain((int)expBrightness, 0, MAX_BRIGHTNESS);
}

void breathingSmallStep() {
  static uint16_t j = 0;
  for(uint16_t i = 0; i < SIZE_ANIM; i++) {
    leds[1][i] = CRGB(Wheel(((5 * 256 / SIZE_ANIM) + j) & 255));
  }
  j++;
  if (j >= 256) j = 0;
}

void allWhiteStep() {
  for(uint16_t i = 0; i < SIZE_ANIM; i++) {
    leds[1][i] = CRGB(0xFFFFFFFF);
  }
}

void allRedStep() {
  for(uint16_t i = 0; i < SIZE_ANIM; i++) {
    leds[1][i] = CRGB(0xFFFF0000);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos; 
  if (WheelPos < 85) {
    return rgbToUint32(255 - WheelPos * 3, WheelPos * 3, 0); // Red to Yellow
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return rgbToUint32(0, 255 - WheelPos * 3, WheelPos * 3); // Yellow to Blue
  } else {
    WheelPos -= 170;
    return rgbToUint32(WheelPos * 3, 0, 255 - WheelPos * 3); // Blue to Red
  }
}

uint32_t rgbToUint32(uint8_t red, uint8_t green, uint8_t blue) {
  return ((uint32_t)red << 16) | ((uint32_t)green << 8) | blue;
}

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
  currentStep = 0; // Reset the animation step when a new message is received
}
