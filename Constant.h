#ifndef CONSTANT_H
#define CONSTANT_H

// STRIP
#define NUM_STRIPS 4
#define SIZE_ANIM 1856
#define MAX_BRIGHTNESS 255
#define POT_PIN D0  
#define BATTERY_PIN D1

uint8_t brightness = 20;
uint8_t originalBrightness = 20;
uint32_t color = 255; // Blue
CRGB leds[NUM_STRIPS][500];

// SHUTDOWN
#define SHUT_DOWN_PIN D3

// ESP NOW
#define WIFI_CHANNEL 3

// ANIMS
#define FULL 1
#define FULL_VERTICAL 2
#define FULL_HORIZONTAL 3
#define FULL_DIAGONAL 4
#define FULL_CIRCLE 5
#define FULL_TRIANGLE 6
#define FULL_ALARM 7

#define RAIN 8
#define LINE_HORIZONTAL 8
#define SPARKLE 8

#define GIF_PONG 9
#define GIF_SPIRAL 9
#define SPIRAL 9
#define WARNING 9

uint8_t pattern = 1;
uint8_t patternOld = 0;
uint8_t bpm = 120;
bool pulseDone = false; 
long bpmUpdateTime = 0;
long startAnimationTime = millis();
uint16_t hue = 200;


// SETUP BLUE WATER ANIM
#define NUM_VERTICAL_STRIPS 72
#define MAX_LEDS_PER_STRIP 100 // Adjust this to the maximum number of LEDs per strip
long rainPosition[NUM_VERTICAL_STRIPS];



long time1,time2,time3; // For TIME LOGS


#endif 