#include <FastLED.h>
#include <math.h>
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

void loop() {
  //readBatteryVoltage();
  if (!isForcedBrightness) {
    updateBrightness();
  }

  if (patternOld != pattern) {
    FastLED.clear();
    patternOld = pattern;
    animDone = false; 
    startAnimationTime = millis(); // Need if you need to stuck on BPM the start.
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
      animRightLine(currentTime, startAnimationTime);
      break;
    case ANIM_HORIZONTAL_LINE:
      animDownLine(currentTime, startAnimationTime);
      break;
    case ANIM_DIAGONAL_LINE:
      animDiagonalLine(currentTime, startAnimationTime);
      break;
    case ANIM_CIRCLE_LINE:
      animCircleLine(currentTime, startAnimationTime);
      break;
    case ANIM_CROSS_VERTICAL_LINE:
      animRightLine(currentTime, startAnimationTime);
      animDownLine(currentTime, startAnimationTime);
      break;
    case ANIM_CROSS_HORIZONTAL_LINE:
      animUpLine(currentTime, startAnimationTime);
      animLeftLine(currentTime, startAnimationTime);
      break;

    // SECOND LINE
    case ANIM_COLOR_FULL:
      animColorFull(currentTime, startAnimationTime);
      break;
    case ANIM_ALERT_COLOR_FULL:
      animAlertColorFull(currentTime, startAnimationTime);
      break;
    case ANIM_VERTICAL_RAINBOW:
      animVerticalRainbow(currentTime, startAnimationTime);  
      break;
    case ANIM_HORIZONTAL_RAINBOW:
      animHorizontalRainbow(currentTime, startAnimationTime);  
      break;
    case ANIM_DIAGONAL_RAINBOW:
      animDiagonalRainbow(currentTime, startAnimationTime);  
      break;
    case ANIM_CIRCLE_RAINBOW:
      animCircleRainbow(currentTime, startAnimationTime);  
      break;
    case ANIM_COLORFULL_RAIN:
      animColorfulRain(currentTime, startAnimationTime); 
      break;
    case ANIM_COLORFULL_SPARKLE:
      animColorfulSparkle();  
      break;

    // THIRD LINE
    case ANIM_GIF_CHECK_BLUE:
      animGifCheckBlue(currentTime, startAnimationTime);
      break;
    case ANIM_GIF_PONG:
      animGifPong(currentTime, startAnimationTime);
      break;
    case ANIM_GIF_WARNING:
      animGifWarning(currentTime, startAnimationTime);
      break;
    case ANIM_GIF_SPIRAL:
      animGifSpiral(currentTime, startAnimationTime);
      break;
    case ANIM_GIF_RAINBOW:
      animGifRainbow(currentTime, startAnimationTime);
      break;
    case ANIM_GIF_PSY:
      animGifPsy(currentTime, startAnimationTime);
      break;  
    default:
      FastLED.clear();  
      break;
  }
  FastLED.show();
}
