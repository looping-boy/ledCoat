/// @file    ArrayOfLedArrays.ino
/// @brief   Set up three LED strips, all running from an array of arrays
/// @example ArrayOfLedArrays.ino

// ArrayOfLedArrays - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers.  In this example, we're going to set up three NEOPIXEL strips on three
// different pins, each strip getting its own CRGB array to be played with, only this time they're going
// to be all parts of an array of arrays.

#include <FastLED.h>

#define NUM_STRIPS 4
#define SIZE_ANIM 1848
#define BRIGHTNESS 200

CRGB leds[NUM_STRIPS][500];
#include "I2SClocklessVirtualLedDriver.h"

// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip
void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, 2>(leds[1], 445);
  FastLED.addLeds<NEOPIXEL, 4>(leds[2], 477);
  FastLED.addLeds<NEOPIXEL, 5>(leds[3], 477);
  FastLED.addLeds<NEOPIXEL, 23>(leds[0], 445);
  // FastLED.addLeds<NEOPIXEL, 21>(leds[4], 70);
}

long time1,time2,time3;
void loop() {
  FastLED.setBrightness(BRIGHTNESS);
  rainbowCycle(1);
  //breathing();
}

void breathing() {
  for(uint16_t j=0; j<256; j++) {
    for(uint16_t i=300; i<400; i++) {
      for (int l = 3; l >= 0; l--) {
        leds[l][i] = CRGB(Wheel(((5 * 256 / SIZE_ANIM) + j) & 255));
      }
    }
    FastLED.show();
    //delay(1);
  }
}

void rainbowCycle(uint8_t wait) {
  for(uint16_t j=0; j<256; j++) { 
    // for(uint16_t i=0; i<70; i++) {
    //   leds[4][i] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
    // }
    time1=ESP.getCycleCount();
    uint16_t pwm1Index = 220;
    uint16_t pwm2Index = 0;
    uint16_t pwm3Index = 0;
    uint16_t pwm4Index = 0;
    for(uint16_t i=0; i<1848; i++) {
      if (i < 220) {
        leds[1][i] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
      } 
      else if (i == 220) {
        for (int k = 0; k < 33; k++) {
          leds[2][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
          i++;
        }
        i--;
        pwm2Index = 33;
      }
      else if (i == 253) {
        for (int k = pwm1Index; k < 32 + pwm1Index; k++) {
          leds[1][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
          i++;
        }
        i--;
        pwm1Index = 32 + pwm1Index;
      }
      else if (i == 285) {
        for (int k = pwm2Index; k < 32 + pwm2Index; k++) {
          leds[2][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
          i++;
        }
        i--;
        pwm2Index = 32 + pwm2Index;
      }
      else if (i == 317) {
        for (int k = pwm1Index; k < 31 + pwm1Index; k++) {
          leds[1][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
          i++;
        }
        i--;
        pwm1Index = 31 + pwm1Index;
      }
      else if (i == 348) {
        for (int k = pwm2Index; k < 30 + pwm2Index; k++) {
          leds[2][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
          i++;
        }
        i--;
        pwm2Index = 30 + pwm2Index;
      }
      else if (i == 378) {
        for (int k = pwm1Index; k < 162 + pwm1Index; k++) {
          leds[1][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
          i++;
        }
        leds[1][19 + pwm1Index] = CRGB(255,0,0);
        i--;
        pwm1Index = 162 + pwm1Index;
      }

      // BACK 
      else if (i == 540) {
        for (int k = pwm2Index; k < 33 + pwm2Index; k++) {
          leds[2][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
          i++;
        }
        pwm2Index = 33 + pwm2Index;
        for (int k = pwm3Index; k < 34 + pwm3Index; k++) {
          leds[3][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
          i++;
        }
        pwm3Index = 34 + pwm3Index; // 34 is weird I dunno why

        for (int l = 0; l < 3; l++) {
          for (int k = pwm2Index; k < 32 + pwm2Index; k++) {
            leds[2][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
            i++;
          }
          pwm2Index = 32 + pwm2Index;
          for (int k = pwm3Index; k < 32 + pwm3Index; k++) {
            leds[3][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
            i++;
          }
          pwm3Index = 32 + pwm3Index;
        }
        for (int l = 0; l < 4; l ++) {
          for (int k = pwm2Index; k < 31 + pwm2Index; k++) {
            leds[2][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
            i++;
          }
          pwm2Index = 31 + pwm2Index;
          for (int k = pwm3Index; k < 31 + pwm3Index; k++) {
            leds[3][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
            i++;
          }
          pwm3Index = 31 + pwm3Index;
        }
        for (int l = 0; l < 3; l ++) {
          for (int k = pwm2Index; k < 32 + pwm2Index; k++) {
            leds[2][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
            i++;
          }
          pwm2Index = 32 + pwm2Index;
          for (int k = pwm3Index; k < 32 + pwm3Index; k++) {
            leds[3][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
            i++;
          }
          pwm3Index = 32 + pwm3Index;
        }

        for (int k = pwm2Index; k < 33 + pwm2Index; k++) {
          leds[2][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
          i++;
        }
        pwm2Index = 33 + pwm2Index;
        for (int k = pwm3Index; k < 33 + pwm3Index; k++) {
          leds[3][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
          i++;
        }
        pwm3Index = 33 + pwm3Index; 
        i--;
      }
      // END BACK


      else if (i == 1305) {
        for (int k = pwm4Index; k < 165 + pwm4Index; k++) {
          leds[0][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
          i++;
        }
        i--;
        pwm4Index = 165 + pwm4Index;
      }
      else if (i == 1470) {
        for (int k = pwm3Index; k < 30 + pwm3Index; k++) {
          leds[3][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
          i++;
        }
        i--;
        pwm3Index = 30 + pwm3Index;
      }
      else if (i == 1500) {
        for (int k = pwm4Index; k < 31 + pwm4Index; k++) {
          leds[0][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
          i++;
        }
        i--;
        pwm4Index = 31 + pwm4Index;
      }
      else if (i == 1531) {
        for (int k = pwm3Index; k < 32 + pwm3Index; k++) {
          leds[3][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
          i++;
        }
        i--;
        pwm3Index = 32 + pwm3Index;
      }
      else if (i == 1563) {
        for (int k = pwm4Index; k < 32 + pwm4Index; k++) {
          leds[0][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
          i++;
        }
        i--;
        pwm4Index = 32 + pwm4Index;
      }
      else if (i == 1595) {
        for (int k = pwm3Index; k < 33 + pwm3Index; k++) {
          leds[3][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
          i++;
        }
        i--;
        pwm3Index = 33 + pwm3Index;
      }
      else if (i == 1628) {
        for (int k = pwm4Index; k < 220 + pwm4Index; k++) {
          leds[0][k] = CRGB(Wheel(((i * 256 / SIZE_ANIM) + j) & 255));
          i++;
        }
        i--;
        pwm4Index = 220 + pwm4Index;
        // time2=ESP.getCycleCount();
      } 
      else {
        Serial.printf("Value : %d\n", i);
      }
      
    }
    
    FastLED.show();
    // time3=ESP.getCycleCount();
    // Serial.printf("Calcul pixel fps:%.2f   showPixels fps:%.2f   Total fps:%.2f \n",(float)240000000/(time2-time1),(float)240000000/(time3-time2),(float)240000000/(time3-time1));
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos; // Reverse direction for smoother color transition
  if (WheelPos < 85) {
    // For the first third of the spectrum
    return rgbToUint32(255 - WheelPos * 3, WheelPos * 3, 0); // Red to Yellow
  } else if (WheelPos < 170) {
    // For the second third of the spectrum
    WheelPos -= 85;
    return rgbToUint32(0, 255 - WheelPos * 3, WheelPos * 3); // Yellow to Blue
  } else {
    // For the final third of the spectrum
    WheelPos -= 170;
    // Ensure smooth transition between full blue and full red
    return rgbToUint32(WheelPos * 3, 0, 255 - WheelPos * 3); // Blue to Red
  }
}

// uint32_t Wheel(byte value) {
//     //Serial.printf("Byte : %d", value);
//     // Ensure the input value is within the valid range
//     if (value > 255) {
//         value = 255;
//     }
    
//     // Calculate the red component based on the input value
//     uint8_t red = value;

//     // Return the RGB color as a 32-bit integer
//     return rgbToUint32(red, 0, 0);
// }

uint32_t rgbToUint32(uint8_t red, uint8_t green, uint8_t blue) {
    return ((uint32_t)red << 16) | ((uint32_t)green << 8) | blue;
}
