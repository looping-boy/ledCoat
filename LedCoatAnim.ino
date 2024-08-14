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
  FastLED.setBrightness(MAX_BRIGHTNESS);
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

  // SETUP BLUE WATER ANIM
  for (int i = 0; i < NUM_VERTICAL_STRIPS; i++) {
    rainPosition[i] = 0;
  }
}


#define FULL 1
#define FULL_VERTICAL 2
#define FULL_HORIZONTAL 3
#define FULL_DIAGONAL 4
#define FULL_CIRCLE 5
#define FULL_TRIANGLE 6
#define FULL_ALARM 7

#define RAIN_CHOOSE_HUE 8
#define PULSE_CHOOSE_HUE_1 9
#define PULSE_CHOOSE_HUE_2 10
#define RAIN_COLORFULL 11
#define RAIN_COLORFULL_BEAT 12
#define LINE_HORIZONTAL_UP 13
#define LINE_HORIZONTAL_DOWN 14
#define LINE_HORIZONTAL_UP_DOWN 15
#define SPARKLE_WHITE 16
#define SPARKLE_COLOR 17
#define SPARKLE_COLOR_BEAT 18

#define GIF_PONG 19
#define GIF_SPIRAL 20
#define SPIRAL 21
#define WARNING 22

void loop() {
  //readBatteryVoltage();
  if (!isForcedBrightness) {
    updateBrightness();
  }

  if (patternOld != pattern) {
    FastLED.clear();
    patternOld = pattern;
    pulseDone = false; 
    startAnimationTime = millis();
  }

  unsigned long currentTime = millis();

  switch (pattern) {
    case 0:
      upLine(currentTime, startAnimationTime);
      break;
    case 1:
      myMatrixRain(currentTime, startAnimationTime);
      break;
    case 2:
      rainbowCycle(currentTime, startAnimationTime);
      break;
    case 3:
      colorfulSparkle();
      break;
    case 4:
      bigTempoPulse(currentTime, startAnimationTime);
      break;
  }

  
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


