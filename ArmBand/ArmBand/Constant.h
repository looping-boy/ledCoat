#ifndef CONSTANT_H
#define CONSTANT_H

// STRIP
#define NUM_STRIPS 4
#define SIZE_ANIM 144
#define MAX_BRIGHTNESS 255

uint8_t brightness = 20;
uint8_t originalBrightness = 20;
CRGB leds[NUM_STRIPS][100];

// ESP NOW
#define WIFI_CHANNEL 3

// PATTERNS 
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

#define ANIM_GIF_CHECK_BLUE 16
#define ANIM_GIF_PONG 17
#define ANIM_GIF_WARNING 18
#define ANIM_GIF_SPIRAL 19
#define ANIM_GIF_RAINBOW 20
#define ANIM_GIF_PSY 21

uint8_t pattern = ANIM_HORIZONTAL_LINE;
uint8_t patternOld = 0;
uint8_t bpm = 120;
bool animDone = false; 
long bpmUpdateTime = 0;
long startAnimationTime = millis();
uint8_t hue = 200;

// SETUP BLUE WATER ANIM
#define NUM_VERTICAL_STRIPS 72
#define MAX_LEDS_PER_STRIP 100 // Adjust this to the maximum number of LEDs per strip
long rainPosition[NUM_VERTICAL_STRIPS];

uint8_t tweakQuantity = 16;   // just go until 128
uint8_t tweakBPM = 16;       // just go until 128
uint8_t tweakColor = 16;     // just go until 128
uint8_t tweakPhase = 1;      // From 1 to 8 only
bool isForcedBrightness = false;
uint8_t forcedBrightness = 0;

long time1,time2,time3; // For TIME LOGS

// FOR WRIST, HEADBAND, FEET :

Preferences preferences;
uint8_t lightDevice = 0;

#define LIGHT_DEVICE_WRIST 0 // Total 144, 6 x 23
#define LIGHT_DEVICE_FEET 1  // Total 
#define LIGHT_DEVICE_HEADBAND 2 // Total , 2 x

uint8_t totalLine = 2;
uint8_t totalColumn = 24;

#define NUM_STRIPS 4
#define POT_PIN D0
#define BATTERY_PIN D1
#define SHUTDOWN_PIN D9
#define MOTOR_PIN D10
#define LED_PIN D8

#endif 