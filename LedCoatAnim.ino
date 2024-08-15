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


#define ANIM_STATIC_FULL 0
#define ANIM_ALERT_FULL 1
#define ANIM_VERTICAL_LINE 2
#define ANIM_HORIZONTAL_LINE 3
#define ANIM_DIAGONAL_LINE 4
#define ANIM_CIRCLE_LINE 5
#define ANIM_CROSS_VERTICAL_LINE 6
#define ANIM_CROSS_HORIZONTAL_LINE 7

#define ANIM_COLOR_FULL 8
#define ANIM_ALERT_COLOR_FULL 9
#define ANIM_VERTICAL_RAINBOW 10
#define ANIM_HORIZONTAL_RAINBOW 11
#define ANIM_DIAGONAL_RAINBOW 12
#define ANIM_CIRCLE_RAINBOW 13
#define ANIM_COLORFULL_RAIN 14
#define ANIM_COLORFULL_SPARKLE 15

#define ANIM_COLOR_PULSE 16
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
    case ANIM_COLOR_PULSE:
      //colorPulse(currentTime);  
      break;
    default:
      FastLED.clear();  
      break;
  }
  FastLED.show();

}

    //   break;
    // default:
    //   fullGradientVertical(currentTime, startAnimationTime);
    //   leftLine(currentTime, startAnimationTime);
    //   upLine(currentTime, startAnimationTime);
    //   bigTempoPulse(currentTime, startAnimationTime);
    //   colorfulSparkle();
    //   rainbowCycle(currentTime, startAnimationTime);
    //   myMatrixRain(currentTime, startAnimationTime);
    //   break;


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


