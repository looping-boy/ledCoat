#ifndef GIF_ANIMS_H
#define GIF_ANIMS_H

#include "ConvertedPictures.h"
#include "ConvertedGifs.h"
#include "Squeletons.h"

#define NOT_EXISTANT_PWM 7

// --------------------------------------------------------------------------------------------------------------------------------------
// LINE OF PATTERN 3 --------------------------------------------------------------------------------------------------------------------

void printLooping() {
  time1 = ESP.getCycleCount();
  for (uint16_t i = 0; i < 72; i++) {
    if (ledMappingVertical[i].isGoingUp) {
      for (int k = 0; k < ledMappingVertical[i].numbersOfLeds; k++) {
        if (k * 72 + i < 2448) {
          leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm] = CRGB(looping[k * 72 + i]);
        }
      }
    } else {
      for (int k = ledMappingVertical[i].numbersOfLeds - 1; k >= 0; k--) {
        if (34 - ledMappingVertical[i].numbersOfLeds + k >= 0) {
          leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm] = CRGB(looping[(34 - ledMappingVertical[i].numbersOfLeds + k) * 72 + i]);
        }
      }
    }
  }
  FastLED.show();
  time3 = ESP.getCycleCount();
  Serial.printf("Calcul pixel Total fps:%.2f \n", (float)240000000 / (time3 - time1));
  //delay(1000);
}

void printLooping2() {
  time1 = ESP.getCycleCount();
  uint8_t height = 37;
  uint8_t width = 72;
  uint8_t gifHeight = 34;
  uint8_t offset = (height - gifHeight) * 72;

  for (uint16_t i = 0; i < 2448; i++) {
    if (ledMapping[i].pwmChannel != 7) {
      leds[ledMapping[i].pwmChannel][ledMapping[i].indexInPwm] = CRGB(looping[i]);
    }
  }
  FastLED.show();
  time3 = ESP.getCycleCount();
  Serial.printf("Calcul pixel Total fps:%.2f \n", (float)240000000 / (time3 - time1));
}

void displayGif(uint8_t wait) {

  uint8_t height = 37;
  uint8_t width = 72;
  uint8_t gifHeight = 34;
  uint8_t offset = (height - gifHeight) * 72;

  for (uint16_t f = 0; f < 14; f++) {
    time1 = ESP.getCycleCount();
    for (uint16_t i = 0; i < 2448; i++) {
      if (ledMapping[i].pwmChannel != 7) {
        leds[ledMapping[i].pwmChannel][ledMapping[i].indexInPwm] = CRGB(looping2[f][i]);
      }
    }
    FastLED.show();
    delay(75);
    time3 = ESP.getCycleCount();
    Serial.printf("Calcul pixel Total fps:%.2f \n", (float)240000000 / (time3 - time1));
  }
}

void batteryLevel() {
  for (uint16_t f = 0; f < 12; f++) {
    time1 = ESP.getCycleCount();
    for (uint16_t i = 0; i < 2664; i++) {
      if (ledMapping[i].pwmChannel != 7) {
        leds[ledMapping[i].pwmChannel][ledMapping[i].indexInPwm] = CRGB(lowBatteryLevel[f][i]);
      }
    }
    FastLED.show();
    delay(300);
    time3 = ESP.getCycleCount();
    Serial.printf("Calcul pixel Total fps:%.2f \n", (float)240000000 / (time3 - time1));
  }
}


// GIF PATTERNS --------------------------------------------------------------------------

void animGifCheckBlue(long currentTime, long startAnimationTime) {
  float barCycleTime = (60000 / bpm) * (tweakBPM / 4);
  uint8_t frame = (uint8_t)((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 40) / barCycleTime);
  if (frame < 40) {
    for (uint16_t i = 0; i < 2664; i++) {
      if (ledMapping[i].pwmChannel != NOT_EXISTANT_PWM) {
        leds[ledMapping[i].pwmChannel][ledMapping[i].indexInPwm] = CRGB(checkBlue[frame][i]);
      }
    }
  }
}

void animGifPong(long currentTime, long startAnimationTime) {
  float barCycleTime = (60000 / bpm) * (tweakBPM / 4);
  uint8_t frame = (uint8_t)((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 19) / barCycleTime);
  if (frame < 19) {
    for (uint16_t i = 0; i < 2664; i++) {
      if (ledMapping[i].pwmChannel != NOT_EXISTANT_PWM) {
        leds[ledMapping[i].pwmChannel][ledMapping[i].indexInPwm] = CRGB(pong[frame][i]);
      }
    }
  }
}

void animGifWarning(long currentTime, long startAnimationTime) {
  float barCycleTime = (60000 / bpm) * (tweakBPM / 4);
  uint8_t frame = (uint8_t)((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 7) / barCycleTime);
  if (frame < 7) {
    for (uint16_t i = 0; i < 2664; i++) {
      if (ledMapping[i].pwmChannel != NOT_EXISTANT_PWM) {
        leds[ledMapping[i].pwmChannel][ledMapping[i].indexInPwm] = CRGB(warning[frame][i]);
      }
    }
  }
}

void animGifSpiral(long currentTime, long startAnimationTime) {
  float barCycleTime = (60000 / bpm) * (tweakBPM / 4);
  uint8_t frame = (uint8_t)((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 15) / barCycleTime);
  if (frame < 15) {
    for (uint16_t i = 0; i < 2664; i++) {
      if (ledMapping[i].pwmChannel != NOT_EXISTANT_PWM) {
        leds[ledMapping[i].pwmChannel][ledMapping[i].indexInPwm] = CRGB(spiral[frame][i]);
      }
    }
  }
}

void animGifRainbow(long currentTime, long startAnimationTime) {
  float barCycleTime = (60000 / bpm) * (tweakBPM / 4);
  uint8_t frame = (uint8_t)((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 20) / barCycleTime);
  if (frame < 20) {
    for (uint16_t i = 0; i < 2664; i++) {
      if (ledMapping[i].pwmChannel != NOT_EXISTANT_PWM) {
        leds[ledMapping[i].pwmChannel][ledMapping[i].indexInPwm] = CRGB(movingRainbow[frame][i]);
      }
    }
  }
}

void animGifPsy(long currentTime, long startAnimationTime) {
  float barCycleTime = (60000 / bpm) * (tweakBPM / 4);
  uint8_t frame = (uint8_t)((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 20) / barCycleTime);
  if (frame < 20) {
    for (uint16_t i = 0; i < 2664; i++) {
      if (ledMapping[i].pwmChannel != NOT_EXISTANT_PWM) {
        leds[ledMapping[i].pwmChannel][ledMapping[i].indexInPwm] = CRGB(psy[frame][i]);
      }
    }
  }
}

#endif
