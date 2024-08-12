#ifndef LOGIC_ANIMS_H
#define LOGIC_ANIMS_H

#include "Squeletons.h"

uint32_t Wheel(byte WheelPos);
uint32_t rgbToUint32(uint8_t red, uint8_t green, uint8_t blue);

void breathingSmall() {
  for(uint16_t j=0; j<256; j++) {
    for(uint16_t i=0; i<200; i++) {
        leds[1][i] = CRGB(Wheel(((5 * 256 / 200) + j) & 255));
    }
  }
}

void allWhiteStep(CRGB color) {
    for(uint16_t i=0; i<200; i++) {
        leds[1][i] = color;
        leds[0][i] = color;
    }
    for(uint16_t i=0; i<200; i++) {
        leds[2][i] = color;
        leds[3][i] = color;
    }
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
    //FastLED.show();
    //delay(wait);
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

uint32_t rgbToUint32(uint8_t red, uint8_t green, uint8_t blue) {
    return ((uint32_t)red << 16) | ((uint32_t)green << 8) | blue;
}

#endif 