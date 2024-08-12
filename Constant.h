#ifndef CONSTANT_H
#define CONSTANT_H

// STRIP
#define NUM_STRIPS 4
#define SIZE_ANIM 1856
#define MAX_BRIGHTNESS 255
#define BRIGHTNESS 20
#define POT_PIN D0  
#define BATTERY_PIN D1 
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

int currentStep = 0;
int something = 0;

uint8_t bpm = 120;

long time1,time2,time3;


#endif 