#include <FastLED.h>
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <Preferences.h>
#include <math.h>
#include "Constant.h"
#include "ESPReceiver.h"
#include "LogicAnims.h"

unsigned long lastPotReadTime = 0;
const unsigned long potReadInterval = 100;

int something = 0;    // Current animation state
int currentStep = 0;  // Current step in the animation

void setup() {
  Serial.begin(115200);

  // ------------- SHUTDOWN ---------------
  pinMode(SHUTDOWN_PIN, OUTPUT);
  digitalWrite(SHUTDOWN_PIN, LOW);

  // ------------- MOTOR ---------------
  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, LOW);

  // ------------- NEOPIXEL ---------------
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds[1], SIZE_ANIM);
  FastLED.setBrightness(MAX_BRIGHTNESS);
  updateBrightness();

  // ------------- SHARED PREFERENCE ---------------
  preferences.begin("my-app", true);  // Open in read-only mode
  lightDevice = preferences.getInt("lightDevice", 0);  // Retrieve the value, with a default of 0 if not found
  preferences.end();
  whichLightDevice();

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

void whichLightDevice() {
  switch(lightDevice) {
    case LIGHT_DEVICE_WRIST:
      totalLine = 6;
      totalColumn = 24;
      break;
    case LIGHT_DEVICE_FEET:
      totalLine = 1;
      totalColumn = 100;
      break;
    case LIGHT_DEVICE_HEADBAND:
      totalLine = 2;
      totalColumn = 72;
      break;
    default :
      break;
  }
}

void loop() {
  //seeIfNeedToShutdown((uint16_t) analogRead(BATTERY_PIN));

  if (!isForcedBrightness) {
    updateBrightness();
  }

  if (patternOld != pattern) {
    FastLED.clear();
    patternOld = pattern;
    animDone = false;
    startAnimationTime = millis();  // Need if you need to stuck on BPM the start.
  }

  unsigned long currentTime = millis();

  FastLED.clear();
  switch (pattern) {
    // FIRST LINE
    case ANIM_STATIC_FULL:
      animFullStatic();
      break;
    case ANIM_ALERT_FULL:
      animAlertFull(currentTime);
      break;
    case ANIM_VERTICAL_LINE:
      animLeftLine(currentTime, startAnimationTime);
      break;
    case ANIM_HORIZONTAL_LINE:
      animHorizontalRainbow(currentTime, startAnimationTime);
      break;
    default:
      FastLED.clear();
      break;
  }
  FastLED.show();
}

void allRedBatteryLowAnim() {
  CRGB red = CRGB(255, 0, 0);
  for (uint16_t i = 0; i < 144; i++) {
    leds[1][i] = red;
  }
  FastLED.show();
}

void allBlackBatteryLowAnim() {
  CRGB red = CRGB(0, 0, 0);
  for (uint16_t i = 0; i < 144; i++) {
    leds[1][i] = red;
  }
  FastLED.show();
}

void updateBrightness() {
  int potValue = analogRead(POT_PIN);
  brightness = mapPotValueToBrightness(potValue);
}

int mapPotValueToBrightness(int potValue) {
  float scale = (float)potValue / 3000.0; 
  float expBrightness = 10 + pow(scale, 2.5) * (MAX_BRIGHTNESS - 10);
  return constrain((int)expBrightness, 10, MAX_BRIGHTNESS - 1);
}

void seeIfNeedToShutdown(uint16_t batteryValue) {
  if (batteryValue < 2000) {
    allRedBatteryLowAnim();
    digitalWrite(MOTOR_PIN, HIGH);
    delay(1000);
    allBlackBatteryLowAnim();
    digitalWrite(MOTOR_PIN, LOW);
    delay(500);
    allRedBatteryLowAnim();
    digitalWrite(MOTOR_PIN, HIGH);
    delay(1000);
    allBlackBatteryLowAnim();
    digitalWrite(MOTOR_PIN, LOW);
    delay(500);
    digitalWrite(SHUTDOWN_PIN, LOW);
    digitalWrite(SHUTDOWN_PIN, HIGH);
    delay(5000);
    digitalWrite(SHUTDOWN_PIN, LOW);
  }
}
