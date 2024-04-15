/// @file    ArrayOfLedArrays.ino
/// @brief   Set up three LED strips, all running from an array of arrays
/// @example ArrayOfLedArrays.ino

// ArrayOfLedArrays - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers.  In this example, we're going to set up three NEOPIXEL strips on three
// different pins, each strip getting its own CRGB array to be played with, only this time they're going
// to be all parts of an array of arrays.

#include <FastLED.h>

#define NUM_STRIPS 4
#define SIZE_ANIM 1856
#define BRIGHTNESS 20

CRGB leds[NUM_STRIPS][500];
#include "I2SClocklessVirtualLedDriver.h"

typedef struct {
    int pwmChannel;
    int numbersOfLeds;
    int indexInPwm;
    int indexTotal;
    bool isGoingUp;
} LedInfo;

LedInfo ledMappingVertical[72] = {
    {1, 17, 0, 0, false}, 
    {1, 19, 17, 17, true}, 
    {1, 21, 36, 36, false}, 
    {1, 23, 57, 57, true},
    {1, 25, 80, 80, false}, 
    {1, 27, 105, 105, true}, 
    {1, 28, 132, 132, false}, 
    {1, 30, 160, 160, true},
    {1, 33, 190, 190, false}, 

    {2, 33, 0, 223, false}, 
    {1, 32, 223, 256, true}, 
    {2, 32, 33, 288, true},
    {1, 31, 255, 320, false}, 
    {2, 30, 65, 351, false},

    {1, 20, 286, 381, true}, 
    {1, 17, 306, 401, false},
    {1, 16, 323, 418, true}, 
    {1, 16, 339, 434, false}, 
    {1, 15, 355, 450, true}, 
    {1, 14, 370, 465, false},
    {1, 15, 384, 479, true}, 
    {1, 16, 399, 494, false}, 
    {1, 17, 415, 510, true}, 
    {1, 19, 432, 527, false}, // END 1 to 451

    {2, 33, 95, 546, true}, 
    {3, 33, 0, 579, true}, 
    {2, 32, 128, 612, false}, 
    {3, 32, 33, 644, false},
    {2, 32, 160, 676, true}, 
    {3, 32, 65, 708, true}, 
    {2, 32, 192, 740, false}, 
    {3, 32, 97, 772, false},

    {2, 31, 224, 804, true}, 
    {3, 31, 129, 835, true}, 
    {2, 31, 255, 866, false}, 
    {3, 31, 160, 897, false},
    {2, 31, 286, 928, true}, 
    {3, 31, 191, 959, true}, 
    {2, 31, 317, 990, false}, 
    {3, 31, 222, 1021, false},

    {2, 32, 348, 1052, true}, 
    {3, 32, 253, 1084, true}, 
    {2, 32, 380, 1116, false}, 
    {3, 32, 285, 1148, false},
    {2, 32, 412, 1180, true}, 
    {3, 32, 317, 1212, true}, 
    {2, 33, 444, 1244, false}, // END OF 2
    {3, 33, 349, 1277, false},

    {0, 19, 0, 1310, true}, 
    {0, 17, 19, 1329, false}, 
    {0, 16, 36, 1346, true}, 
    {0, 15, 52, 1362, false},
    {0, 14, 67, 1377, true}, 
    {0, 15, 81, 1391, false}, 
    {0, 16, 96, 1406, true}, 
    {0, 16, 112, 1422, false},
    {0, 17, 128, 1438, true}, 
    {0, 20, 145, 1455, false}, 

    {3, 30, 382, 1475, true}, 
    {0, 31, 165, 1505, true},
    {3, 32, 412, 1536, false}, 
    {0, 32, 196, 1568, false}, 
    {3, 33, 444, 1600, true}, 

    {0, 33, 228, 1633, true},
    {0, 30, 261, 1666, false}, 
    {0, 28, 291, 1696, true}, 
    {0, 27, 319, 1724, false}, 
    {0, 25, 346, 1751, true},
    {0, 23, 371, 1776, false}, 
    {0, 21, 394, 1799, true}, 
    {0, 19, 415, 1820, false}, 
    {0, 17, 434, 1839, true} // TOTAL 1856
};

// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip
void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, 2>(leds[1], 451);
  FastLED.addLeds<NEOPIXEL, 4>(leds[2], 477);
  FastLED.addLeds<NEOPIXEL, 5>(leds[3], 477);
  FastLED.addLeds<NEOPIXEL, 23>(leds[0], 451);
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
    int l = 0; 
    for(uint16_t i=0; i<72; i++) {
      if (!ledMappingVertical[i].isGoingUp) {
        for (int k = 0; k < ledMappingVertical[i].numbersOfLeds; k++) {
          leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm] = CRGB(Wheel((((ledMappingVertical[i].indexTotal + k) * 256 / SIZE_ANIM) + j) & 255));
        }
      } else {
        for (int k = ledMappingVertical[i].numbersOfLeds - 1; k >= 0 ; k--) {
          leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm] = CRGB(Wheel((((ledMappingVertical[i].indexTotal - k + ledMappingVertical[i].numbersOfLeds - 1) * 256 / SIZE_ANIM) + j) & 255));
        }
      }
    }
    FastLED.show();
    time3=ESP.getCycleCount();
    Serial.printf("Calcul pixel Total fps:%.2f \n",(float)240000000/(time3-time1));
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
