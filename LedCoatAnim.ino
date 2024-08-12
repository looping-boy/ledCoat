#include <FastLED.h>
#include "Constant.h"
#include "ESPReceiver.h"
#include "LedMap.h"
#include "LogicAnims.h"
#include "GifAnims.h"
#include "BoardFunctions.h"

void setup() {
  Serial.begin(115200);

  pinMode(SHUT_DOWN_PIN, OUTPUT);
  digitalWrite(SHUT_DOWN_PIN, LOW);

  FastLED.addLeds<NEOPIXEL, D7>(leds[1], 451);
  FastLED.addLeds<NEOPIXEL, D8>(leds[2], 477);
  FastLED.addLeds<NEOPIXEL, D9>(leds[3], 477);
  FastLED.addLeds<NEOPIXEL, D10>(leds[0], 451);
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
  //readBatteryVoltage();
  updateBrightness();

  switch (pattern) {
    case 0:
      allWhiteStep(CRGB::Blue);
      break;
    case 1:
      allWhiteStep(CRGB::Red);
      break;
    case 2:
      allWhiteStep(CRGB::Yellow);
      break;
    case 3:
      allWhiteStep(CRGB::Purple);
      break;
    case 4:
      allWhiteStep(CRGB::Green);
      break;
  }
  
  FastLED.show();

}


  // rainbowCycle(1);
  // horizontalLignRainbowCycle(1);
  // verticalRainbowCycle(1);
  // breathing();
  // breathingSmall();
  // printNiantCat();
  // circleRainbowCycle(5);
  // printLooping2();
  // displayGif(1);
  // animateGif();
  // batteryLevel();
  // psyAnim();
  // pongAnim();
  // spiralAnim();
  // diagonalRainbowCycle(1);
  // warningAnim();
  // warningAnim();
  // checkBlueAnim();
  // blink();
  // explosion(5);
  // circleRainbowCycle(5);


