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
#define BRIGHTNESS 255

CRGB leds[NUM_STRIPS][500];
#include "I2SClocklessVirtualLedDriver.h"
#include "GifAnimations.h"
#include "ConvertedGifs.h"
#include "Squeletons.h"

typedef struct {
    uint8_t pwmChannel;
    uint8_t numbersOfLeds;
    uint16_t indexInPwm;
    uint16_t indexTotal;
    uint8_t offset;
    bool isGoingUp;
} LedInfo;

LedInfo ledMappingVertical[72] = {
    {1, 17, 0, 0, 5, false}, 
    {1, 19, 17, 17, 5, true}, 
    {1, 21, 36, 36, 5, false}, 
    {1, 23, 57, 57, 5, true},
    {1, 25, 80, 80, 5, false}, 
    {1, 27, 105, 105, 5, true}, 
    {1, 28, 132, 132, 4, false}, 
    {1, 30, 160, 160, 4, true},
    {1, 33, 190, 190, 4, false}, 

    {2, 33, 0, 223, 4, false}, 
    {1, 32, 223, 256, 3, true}, 
    {2, 32, 33, 288, 3, true},
    {1, 31, 255, 320, 3, false}, 
    {2, 30, 65, 351, 3, false},

    {1, 20, 286, 381, 2, true}, 
    {1, 17, 306, 401, 2, false},
    {1, 16, 323, 418, 2, true}, 
    {1, 16, 339, 434, 2, false}, 
    {1, 15, 355, 450, 2, true}, 
    {1, 14, 370, 465, 1, false},
    {1, 15, 384, 479, 1, true}, 
    {1, 16, 399, 494, 1, false}, 
    {1, 17, 415, 510, 1, true}, 
    {1, 19, 432, 527, 1, false}, // END 1 to 451

    {2, 33, 95, 546, 1, true}, 
    {3, 33, 0, 579, 1, true}, 
    {2, 32, 128, 612, 0, false}, 
    {3, 32, 33, 644, 0, false},
    {2, 32, 160, 676, 0, true}, 
    {3, 32, 65, 708, 0, true}, 
    {2, 32, 192, 740, 0, false}, 
    {3, 32, 97, 772, 0,false},

    {2, 31, 224, 804, 0, true}, 
    {3, 31, 129, 835, 0, true}, 
    {2, 31, 255, 866, 0, false}, 
    {3, 31, 160, 897, 0, false},
    {2, 31, 286, 928, 0, true}, 
    {3, 31, 191, 959, 0, true}, 
    {2, 31, 317, 990, 0, false}, 
    {3, 31, 222, 1021, 0, false},

    {2, 32, 348, 1052, 0, true}, 
    {3, 32, 253, 1084, 0, true}, 
    {2, 32, 380, 1116, 0, false}, 
    {3, 32, 285, 1148, 0, false},
    {2, 32, 412, 1180, 0, true}, 
    {3, 32, 317, 1212, 0, true}, 
    {2, 33, 444, 1244, 1, false}, // END OF 2
    {3, 33, 349, 1277, 1, false},

    {0, 19, 0, 1310, 1, true}, 
    {0, 17, 19, 1329, 1, false}, 
    {0, 16, 36, 1346, 1, true}, 
    {0, 15, 52, 1362, 1, false},
    {0, 14, 67, 1377, 1, true}, 
    {0, 15, 81, 1391, 2, false}, 
    {0, 16, 96, 1406, 2, true}, 
    {0, 16, 112, 1422, 2, false},
    {0, 17, 128, 1438, 2, true}, 
    {0, 20, 145, 1455, 3, false}, 

    {3, 30, 382, 1475, 3, true}, 
    {0, 31, 165, 1505, 3, true},
    {3, 32, 412, 1536, 3, false}, 
    {0, 32, 196, 1568, 3, false}, 
    {3, 33, 444, 1600, 4, true}, 

    {0, 33, 228, 1633, 4, true},
    {0, 30, 261, 1666, 4, false}, 
    {0, 28, 291, 1696, 4, true}, 
    {0, 27, 319, 1724, 5, false}, 
    {0, 25, 346, 1751, 5, true},
    {0, 23, 371, 1776, 5, false}, 
    {0, 21, 394, 1799, 5, true}, 
    {0, 19, 415, 1820, 5, false}, 
    {0, 17, 434, 1839, 5, true} // TOTAL 1856
};



// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip
void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, 2>(leds[1], 451);
  FastLED.addLeds<NEOPIXEL, 4>(leds[2], 477);
  FastLED.addLeds<NEOPIXEL, 5>(leds[3], 477);
  FastLED.addLeds<NEOPIXEL, 23>(leds[0], 451);
  pinMode(18, OUTPUT);

  // FastLED.addLeds<NEOPIXEL, 21>(leds[4], 70);
}

long time1,time2,time3;
void loop() {
  FastLED.setBrightness(BRIGHTNESS);
  //rainbowCycle(1);
  //horizontalLignRainbowCycle(1);
  // upLign(1);
  //verticalRainbowCycle(1);
  
  // breathing();
  breathingSmall();
  //printNiantCat();
  // circleRainbowCycle(5);
  //printLooping2();
  // displayGif(1);
  // animateGif();
  // batteryLevel();
  //psyAnim();
  // pongAnim();
  // spiralAnim();
  //diagonalRainbowCycle(1);
  // warningAnim();
  // warningAnim();
  //checkBlueAnim();
  // blink();
  // explosion(5);
  // circleRainbowCycle(5);
}

void breathingSmall() {
  for(uint16_t j=0; j<256; j++) {
    for(uint16_t i=0; i<288; i++) {
        leds[1][i] = CRGB(Wheel(((5 * 256 / 288) + j) & 255));
    }
    FastLED.show();
  }
  tone(18, 500); // Send 1KHz sound signal...
  delay(500);        // ...for 1 sec
  noTone(18);     // Stop sound...
  delay(500); 
}

void explosion(uint8_t loop) {
  for(uint8_t l=0; l < loop; l++) {

    //for(uint16_t j=0; j < 256; j++) {
      for (int i = 0; i < 40; i+=2) {
        for (int j = 0; j < 2; j++) {
          for (int k = 0; k < 200; k++) {
            leds[ledMappingCylinder[i + j][k].pwmChannel][ledMappingCylinder[i + j][k].indexInPwm] = CRGB(Wheel((((i) * 256 / 72) + l*(256/loop)) & 255));
          }
        }
        FastLED.show();
        float logValue = log(i+1);
        int roundedLog = round(logValue) * 4;
        //int delayTime = roundedLog * 100;
        delay(roundedLog);
        //delay(i);
      }

      for (int i = 0; i < 40; i += 4) {
        for (int j = 0; j < 4; j++) {
          for (int k = 0; k < 200; k++) {
            leds[ledMappingCylinder[i + j][k].pwmChannel][ledMappingCylinder[i + j][k].indexInPwm] = CRGB(0x00000000);
          }
        }
        FastLED.show();
      }
  }
}

void blink() {
  for(uint16_t j=0; j<20; j++) {
    if (j % 2 == 0) {
      for(uint16_t i=0; i<477; i++) {
        for (int l = 3; l >= 0; l--) {
          leds[l][i] = CRGB(Wheel(((5 * 256 / SIZE_ANIM) + j*(256/20)) & 255));
        }
      }
    } else {
      for(uint16_t i=0; i<477; i++) {
        for (int l = 3; l >= 0; l--) {
          leds[l][i] = CRGB(0x00000000);
        }
      }
    }
    FastLED.show();
    delay(100);
  }
}

void breathing() {
  for(uint16_t j=0; j<256; j++) {
    for(uint16_t i=0; i<477; i++) {
      for (int l = 3; l >= 0; l--) {
        leds[l][i] = CRGB(Wheel(((5 * 256 / SIZE_ANIM) + j) & 255));
      }
    }
    FastLED.show();
  }
}

void verticalRainbowCycle(uint8_t wait) {
  for(uint16_t j=0; j<256; j++) {
    for (int i = 0; i < 72; i++) {
        for (int k = 0; k < 72; k++) {
            leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CRGB(Wheel((((i) * 256 / 72) + j) & 255));
        }
    }
    FastLED.show();
    delay(wait);
  }
}

void horizontalLignRainbowCycle(uint8_t wait) {
  for(uint16_t j=0; j<37; j++) {
    for (int i = 0; i < 72; i++) {
      if (j == i) {
        for (int k = 0; k < 72; k++) {
            leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CRGB(Wheel((((i) * 256 / 72) + j*(256/37)) & 255));
        }
      } else {
        for (int k = 0; k < 72; k++) {
            leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CRGB(0x00000000);
        }
      }
        
    }
    FastLED.show();
    delay(wait);
  }
}

void upLign(uint8_t wait) {
  for(uint16_t j = 37; j>0; j--) {
    for (int i = 0; i < 72; i++) {
      if (j == i) {
        for (int k = 0; k < 72; k++) {
            leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CRGB(Wheel((( 256 - i * 256 / 72) + (256 - j*(256/37))) & 255));
        }
      } else {
        for (int k = 0; k < 72; k++) {
            leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CRGB(0x00000000);
        }
      }
    }
    FastLED.show();
    delay(wait);
  }
}

void diagonalRainbowCycle(uint8_t wait) {
  for(uint16_t j=0; j<256; j++) {
    for (int i = 0; i < 72; i++) {
        for (int k = 0; k < 140; k++) {
            leds[ledMappingDiagonal[i][k].pwmChannel][ledMappingDiagonal[i][k].indexInPwm] = CRGB(Wheel((((i) * 256 / 72) + j) & 255));
        }
    }
    FastLED.show();
    delay(wait);
  }
}

void circleRainbowCycle(uint8_t loop) {
  for(uint8_t l=0; l < loop; l++) {
    for(uint16_t j=0; j < 256; j++) {
      for (int i = 0; i < 40; i++) {
        for (int k = 0; k < 200; k++) {
            leds[ledMappingCylinder[i][k].pwmChannel][ledMappingCylinder[i][k].indexInPwm] = CRGB(Wheel((((i) * 256 / 72) + j) & 255));
        }
      }
      FastLED.show();
      delay(1);
    }
  }
}

void rainbowCycle(uint8_t wait) {
  for(uint16_t j=0; j<256; j++) { 
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

void printNiantCat() {
    time1=ESP.getCycleCount();
    for(uint16_t i=0; i<72; i++) {
      if (ledMappingVertical[i].isGoingUp) {
        for (int k = 0; k < ledMappingVertical[i].numbersOfLeds; k++) {
          if (k*62+i < 1550) {
            leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm] = CRGB(niantCat[k*62+i]);
          }
        }
      } else {
        for (int k = ledMappingVertical[i].numbersOfLeds - 1; k >= 0 ; k--) {
          if (24-ledMappingVertical[i].numbersOfLeds+k >= 0) {
            leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm] = CRGB(niantCat[(24-ledMappingVertical[i].numbersOfLeds+k)*62+i]);
          }        
        }
      }
    }
    FastLED.show();
    time3=ESP.getCycleCount();
    Serial.printf("Calcul pixel Total fps:%.2f \n",(float)240000000/(time3-time1));
    //delay(1000);
}

void printLooping() {
    time1=ESP.getCycleCount();
    for(uint16_t i=0; i<72; i++) {
      if (ledMappingVertical[i].isGoingUp) {
        for (int k = 0; k < ledMappingVertical[i].numbersOfLeds; k++) {
          if (k*72+i < 2448) {
            leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm] = CRGB(looping[k*72+i]);
          }
        }
      } else {
        for (int k = ledMappingVertical[i].numbersOfLeds - 1; k >= 0 ; k--) {
          if (34-ledMappingVertical[i].numbersOfLeds+k >= 0) {
            leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm] = CRGB(looping[(34-ledMappingVertical[i].numbersOfLeds+k)*72+i]);
          }        
        }
      }
    }
    FastLED.show();
    time3=ESP.getCycleCount();
    Serial.printf("Calcul pixel Total fps:%.2f \n",(float)240000000/(time3-time1));
    //delay(1000);
}

void printLooping2() {
    time1=ESP.getCycleCount();
    uint8_t height = 37;
    uint8_t width = 72;
    uint8_t gifHeight = 34;
    uint8_t offset = (height-gifHeight) * 72;
    
    for(uint16_t i = 0; i < 2448; i++) {
      if (ledMapping[i].pwmChannel != 7) {
        leds[ledMapping[i].pwmChannel][ledMapping[i].indexInPwm] = CRGB(looping[i]);
      }
    }
    FastLED.show();
    time3=ESP.getCycleCount();
    Serial.printf("Calcul pixel Total fps:%.2f \n",(float)240000000/(time3-time1));
}

void displayGif(uint8_t wait) {
    
    uint8_t height = 37;
    uint8_t width = 72;
    uint8_t gifHeight = 34;
    uint8_t offset = (height-gifHeight) * 72;
    
    for (uint16_t f = 0; f < 14; f++) {
      time1=ESP.getCycleCount();
      for(uint16_t i = 0; i < 2448; i++) {
        if (ledMapping[i].pwmChannel != 7) {
          leds[ledMapping[i].pwmChannel][ledMapping[i].indexInPwm] = CRGB(looping2[f][i]);
        }
      }
      FastLED.show();
      delay(75);
      time3=ESP.getCycleCount();
      Serial.printf("Calcul pixel Total fps:%.2f \n",(float)240000000/(time3-time1));
    }
    
    
}

void animateGif() {
  // int total = sizeof(movingRainbow);
  // uint16_t frameSize = sizeof(movingRainbow[0]);
  // uint8_t numberOfFrame = total / frameSize;
    for (uint16_t f = 0; f < 20; f++) {
      time1=ESP.getCycleCount();
      for(uint16_t i = 0; i < 2664; i++) {
        if (ledMapping[i].pwmChannel != 7) {
          leds[ledMapping[i].pwmChannel][ledMapping[i].indexInPwm] = CRGB(movingRainbow[f][i]);
        }
      }
      FastLED.show();
      delay(25);
      time3=ESP.getCycleCount();
      Serial.printf("Calcul pixel Total fps:%.2f \n",(float)240000000/(time3-time1));
    }       
}

void batteryLevel() {
    for (uint16_t f = 0; f < 12; f++) {
      time1=ESP.getCycleCount();
      for(uint16_t i = 0; i < 2664; i++) {
        if (ledMapping[i].pwmChannel != 7) {
          leds[ledMapping[i].pwmChannel][ledMapping[i].indexInPwm] = CRGB(lowBatteryLevel[f][i]);
        }
      }
      FastLED.show();
      delay(300);
      time3=ESP.getCycleCount();
      Serial.printf("Calcul pixel Total fps:%.2f \n",(float)240000000/(time3-time1));
    }       
}

void psyAnim() {
    for (uint16_t f = 0; f < 20; f++) {
      time1=ESP.getCycleCount();
      for(uint16_t i = 0; i < 2664; i++) {
        if (ledMapping[i].pwmChannel != 7) {
          leds[ledMapping[i].pwmChannel][ledMapping[i].indexInPwm] = CRGB(psy[f][i]);
        }
      }
      FastLED.show();
      delay(25);
      time3=ESP.getCycleCount();
      Serial.printf("Calcul pixel Total fps:%.2f \n",(float)240000000/(time3-time1));
    }       
}

void pongAnim() {
    for (uint16_t f = 0; f < 19; f++) {
      time1=ESP.getCycleCount();
      for(uint16_t i = 0; i < 2664; i++) {
        if (ledMapping[i].pwmChannel != 7) {
          leds[ledMapping[i].pwmChannel][ledMapping[i].indexInPwm] = CRGB(pong[f][i]);
        }
      }
      FastLED.show();
      delay(25);
      time3=ESP.getCycleCount();
      Serial.printf("Calcul pixel Total fps:%.2f \n",(float)240000000/(time3-time1));
    }       
}

void spiralAnim() {
    for (uint16_t f = 0; f < 15; f++) {
      time1=ESP.getCycleCount();
      for(uint16_t i = 0; i < 2664; i++) {
        if (ledMapping[i].pwmChannel != 7) {
          leds[ledMapping[i].pwmChannel][ledMapping[i].indexInPwm] = CRGB(spiral[f][i]);
        }
      }
      FastLED.show();
      delay(25);
      time3=ESP.getCycleCount();
      Serial.printf("Calcul pixel Total fps:%.2f \n",(float)240000000/(time3-time1));
    }       
}

void warningAnim() {
    for (uint16_t f = 0; f < 7; f++) {
      time1=ESP.getCycleCount();
      for(uint16_t i = 0; i < 2664; i++) {
        if (ledMapping[i].pwmChannel != 7) {
          leds[ledMapping[i].pwmChannel][ledMapping[i].indexInPwm] = CRGB(warning[f][i]);
        }
      }
      FastLED.show();
      delay(25);
      time3=ESP.getCycleCount();
      Serial.printf("Calcul pixel Total fps:%.2f \n",(float)240000000/(time3-time1));
    }       
}

void checkBlueAnim() {
    for (uint16_t f = 0; f < 40; f++) {
      time1=ESP.getCycleCount();
      for(uint16_t i = 0; i < 2664; i++) {
        if (ledMapping[i].pwmChannel != 7) {
          leds[ledMapping[i].pwmChannel][ledMapping[i].indexInPwm] = CRGB(checkBlue[f][i]);
        }
      }
      FastLED.show();
      delay(25);
      time3=ESP.getCycleCount();
      Serial.printf("Calcul pixel Total fps:%.2f \n",(float)240000000/(time3-time1));
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
