#ifndef GIF_ANIMS_H
#define GIF_ANIMS_H

#include "ConvertedPictures.h"
#include "ConvertedGifs.h"
#include "Squeletons.h"

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

#endif 
