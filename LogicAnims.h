#ifndef LOGIC_ANIMS_H
#define LOGIC_ANIMS_H

#include "Squeletons.h"

CHSV Wheel(byte WheelPos);
CHSV rgbToCHSV(uint8_t red, uint8_t green, uint8_t blue);
void fadeToBlackByIndex(CRGB* leds, int num_leds, uint8_t fadeBy);

// --------------------------------------------------------------------------------------------------------------------------------------
// LINE OF PATTERN 1 --------------------------------------------------------------------------------------------------------------------

void animFullStatic() {
  CHSV colorValue = CHSV(hue, 255, brightness);
  for (uint16_t i = 0; i < 451; i++) {
    leds[0][i] = colorValue;
    leds[1][i] = colorValue;
  }
  for (uint16_t i = 0; i < 477; i++) {
    leds[2][i] = colorValue;
    leds[3][i] = colorValue;
  }
  // Because static
  animDone = true;
}

void animAlertFull(long currentTime) {
  float barCycleTime = (60000 / bpm) * (tweakBPM / 4);
  float phase = (float)(currentTime % (uint32_t)barCycleTime) / barCycleTime;
  uint8_t j = (uint8_t)((sin(phase * 2 * 3.14159265359) + 1) * (brightness / 2));

  CHSV colorValue = CHSV(hue, 255, j);
  
  for (uint16_t i = 0; i < 451; i++) {
    leds[0][i] = colorValue;
    leds[1][i] = colorValue;
  }
  for (uint16_t i = 0; i < 477; i++) {
    leds[2][i] = colorValue;
    leds[3][i] = colorValue;
  }
}

void animDownLine(long currentTime, long startAnimationTime) {
  float barCycleTime = (60000 / bpm) * (tweakBPM / 16) * tweakPhase;
  
  // Iterate over two phases
  for (int phase = 0; phase < tweakPhase; phase++) {
    uint8_t pos = (uint8_t)(((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 37) / barCycleTime) + (phase * (37 / tweakPhase))) % 37;

    for (int i = 0; i < 72; i++) {
      if (pos == i) {
        for (int k = 0; k < 72; k++) {
          if (pos > 15 && random(1, 38 - pos) == 1) {
            uint8_t pulseBrightness = (uint8_t) brightness * 1.5;
            leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CHSV(((256 - i * 256 / 72) + (256 - pos * (256 / 37))) & 255, 255, pulseBrightness);
          } else {
            leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CHSV(((256 - i * 256 / 72) + (256 - pos * (256 / 37))) & 255, 255, brightness);
          }
        }
      }
    }
  } 
}

void animUpLine(long currentTime, long startAnimationTime) {
  float barCycleTime = (60000 / bpm) * (tweakBPM / 16) * tweakPhase;
  
  // Iterate over two phases
  for (int phase = 0; phase < tweakPhase; phase++) {
    uint8_t pos = (uint8_t) 37 - (uint8_t)(((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 37) / barCycleTime) + (phase * (37 / tweakPhase))) % 37;

    for (int i = 0; i < 72; i++) {
      if (pos == i) {
        for (int k = 0; k < 72; k++) {
          if (pos > 15 && random(1, 38 - pos) == 1) {
            uint8_t pulseBrightness = (uint8_t) brightness * 1.5;
            leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CHSV(((256 - i * 256 / 72) + (256 - pos * (256 / 37))) & 255, 255, pulseBrightness);
          } else {
            leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CHSV(((256 - i * 256 / 72) + (256 - pos * (256 / 37))) & 255, 255, brightness);
          }
        }
      }
    }
  }
}

void animLeftLine(long currentTime, long startAnimationTime) {
  float barCycleTime = (float) (60000 / bpm) * (tweakBPM / 16) * tweakPhase;

  // Iterate over two phases
  for (int phase = 0; phase < tweakPhase; phase++) {
        uint8_t pos = (uint8_t)(((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 72) / barCycleTime) + (phase * (72 / tweakPhase))) % 72;

        for (uint8_t j = 0; j < (uint8_t) (log2(tweakQuantity) + 1); j++) {
          if ((uint8_t) (pos - j) >= 0 && pos < 72) {
            for (int k = 0; k < ledMappingVertical[pos - j].numbersOfLeds - 1; k++) {
              leds[ledMappingVertical[pos - j].pwmChannel][k + ledMappingVertical[pos - j].indexInPwm] = CHSV((hue - ((pos - j) * 256) / 72) & 255, 255, (uint8_t) brightness * 0.75 );
            }  
          }
        }
  }
}

void animRightLine(long currentTime, long startAnimationTime) {
  float barCycleTime = (float) (60000 / bpm) * (tweakBPM / 16) * tweakPhase;

  // Iterate over two phases
  for (int phase = 0; phase < tweakPhase; phase++) {
    uint8_t pos = (uint8_t) 72 - (uint8_t)(((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 72) / barCycleTime) + (phase * (72 / tweakPhase))) % 72;

    for (uint8_t j = 0; j < (uint8_t) (log2(tweakQuantity) + 1); j++) {
      if ((uint8_t) (pos - j) >= 0 && pos < 72) {
        for (int k = 0; k < ledMappingVertical[pos - j].numbersOfLeds - 1; k++) {
          leds[ledMappingVertical[pos - j].pwmChannel][k + ledMappingVertical[pos - j].indexInPwm] = CHSV((hue - ((pos - j) * 256) / 72) & 255, 255, (uint8_t) brightness * 0.75);
        }  
      }
    }
  }
}

void animDiagonalLine(long currentTime, long startAnimationTime) {

  float barCycleTime = (60000 / bpm) * (tweakBPM / 16) * tweakPhase;
  
  // Iterate over two phases
  for (int phase = 0; phase < tweakPhase; phase++) {
    uint8_t pos = (uint8_t) 37 - (uint8_t)(((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 37) / barCycleTime) + (phase * (37 / tweakPhase))) % 37;

    for (int i = 0; i < 72; i++) {
      if (pos == i) {
        for (int k = 0; k < 140; k++) {
          if (pos > 15 && random(1, 38 - pos) == 1) {
            uint8_t pulseBrightness = (uint8_t) brightness * 1.5;
            leds[ledMappingDiagonal[i][k].pwmChannel][ledMappingDiagonal[i][k].indexInPwm] = CHSV(((256 - i * 256 / 72) + (256 - pos * (256 / 37))) & 255, 255, pulseBrightness);
          } else {
            leds[ledMappingDiagonal[i][k].pwmChannel][ledMappingDiagonal[i][k].indexInPwm] = CHSV(((256 - i * 256 / 72) + (256 - pos * (256 / 37))) & 255, 255, brightness);
          }
        }
      }
    }
  }
}

void animCircleLine(long currentTime, long startAnimationTime) {

  float barCycleTime = (60000 / bpm) * (tweakBPM / 16) * tweakPhase;
  
  // Iterate over two phases
  for (int phase = 0; phase < tweakPhase; phase++) {
    uint8_t pos = (uint8_t) 37 - (uint8_t)(((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 37) / barCycleTime) + (phase * (37 / tweakPhase))) % 37;

    for (int i = 0; i < 40; i++) {
      if (pos == i) {
        for (int k = 0; k < 200; k++) {
          if (pos > 15 && random(1, 38 - pos) == 1) {
            uint8_t pulseBrightness = (uint8_t) brightness * 1.5;
            leds[ledMappingCylinder[i][k].pwmChannel][ledMappingCylinder[i][k].indexInPwm] = CHSV(((256 - i * 256 / 72) + (256 - pos * (256 / 37))) & 255, 255, pulseBrightness);
          } else {
            leds[ledMappingCylinder[i][k].pwmChannel][ledMappingCylinder[i][k].indexInPwm] = CHSV(((256 - i * 256 / 72) + (256 - pos * (256 / 37))) & 255, 255, brightness);
          }
        }
      }
    }
  }
}

// --------------------------------------------------------------------------------------------------------------------------------------
// LINE OF PATTERN 2 --------------------------------------------------------------------------------------------------------------------

void animColorFull(long currentTime, long startAnimationTime) {
  float barCycleTime = (60000 / bpm) * (tweakBPM / 4);
  uint8_t j = (uint8_t)((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 255) / barCycleTime);
  uint8_t lowerBrightness = (uint8_t) brightness * 0.5;
  CHSV colorValue = CHSV(j, 255, lowerBrightness);
  
  for (uint16_t i = 0; i < 451; i++) {
    leds[0][i] = colorValue;
    leds[1][i] = colorValue;
  }
  for (uint16_t i = 0; i < 477; i++) {
    leds[2][i] = colorValue;
    leds[3][i] = colorValue;
  }
}

void animAlertColorFull(long currentTime, long startAnimationTime) {
  float barCycleTime = (60000 / bpm) * (tweakBPM / 4);
  float phase = (float)(currentTime % (uint32_t)barCycleTime) / barCycleTime;
  uint8_t t = (uint8_t)(((sin(phase * 1.3 / 3.5 * 3.14159265359)) * 255)) % 255;
  uint8_t lowerBrightness = (uint8_t) brightness * 0.5;
  uint8_t j = (uint8_t)((sin(phase * 2 * 3.14159265359) + 1) * (lowerBrightness / 2));

  CHSV colorValue = CHSV((uint8_t)(t), 255, j);
  
  for (uint16_t i = 0; i < 451; i++) {
    leds[0][i] = colorValue;
    leds[1][i] = colorValue;
  }
  for (uint16_t i = 0; i < 477; i++) {
    leds[2][i] = colorValue;
    leds[3][i] = colorValue;
  }
}

// The first one anim
void animVerticalRainbow(long currentTime, long startAnimationTime) {
  float barCycleTime = ((60000 / bpm)) * (tweakBPM / 4);
  uint8_t j = (uint8_t)((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 255) / barCycleTime);
  uint8_t lowerBrightness = (uint8_t) brightness * 0.5;
  for (uint16_t i = 0; i < 72; i++) {
    if (!ledMappingVertical[i].isGoingUp) {
      for (int k = 0; k < ledMappingVertical[i].numbersOfLeds; k++) {
        leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm] = CHSV(((ledMappingVertical[i].indexTotal + k) * 256 / SIZE_ANIM) + j, 255, lowerBrightness);
      }
    } else {
      for (int k = ledMappingVertical[i].numbersOfLeds - 1; k >= 0; k--) {
        leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm] = CHSV(((ledMappingVertical[i].indexTotal - k + ledMappingVertical[i].numbersOfLeds - 1) * 256 / SIZE_ANIM) + j, 255, lowerBrightness);
      }
    }
  }
}

void animHorizontalRainbow(long currentTime, long startAnimationTime) {
  uint8_t lowerBrightness = (uint8_t) brightness * 0.5;
  float barCycleTime = ((60000 / bpm)) * (tweakBPM / 4);
  uint8_t j = (uint8_t)((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 255) / barCycleTime);
  for (int i = 0; i < 72; i++) {
    for (int k = 0; k < 72; k++) {
      leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CHSV(((i * 256 / 72) + j) & 255, 255, lowerBrightness);
    }
  }
}

void animDiagonalRainbow(long currentTime, long startAnimationTime) {
  uint8_t lowerBrightness = (uint8_t) brightness * 0.5;
  float barCycleTime = ((60000 / bpm)) * (tweakBPM / 4);
  uint8_t j = (uint8_t)((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 255) / barCycleTime);
  for (int i = 0; i < 72; i++) {
    for (int k = 0; k < 140; k++) {
      leds[ledMappingDiagonal[i][k].pwmChannel][ledMappingDiagonal[i][k].indexInPwm] = CHSV(((i * 256 / 72) + j) & 255, 255, lowerBrightness);
    }
  }
}

void animCircleRainbow(long currentTime, long startAnimationTime) {
  uint8_t lowerBrightness = (uint8_t) brightness * 0.5;
  float barCycleTime = ((60000 / bpm)) * (tweakBPM / 4);
  uint8_t j = (uint8_t)((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 255) / barCycleTime);
  for (int i = 0; i < 40; i++) {
    for (int k = 0; k < 200; k++) {
      leds[ledMappingCylinder[i][k].pwmChannel][ledMappingCylinder[i][k].indexInPwm] = CHSV(((i * 256 / 72) + j) & 255, 255, lowerBrightness);
    }
  }
}

void animColorfulRain(long currentTime, long startAnimationTime) {

  fadeToBlackBy(leds[0], 451, 40);
  fadeToBlackBy(leds[1], 451, 40);
  fadeToBlackBy(leds[2], 477, 40);
  fadeToBlackBy(leds[3], 477, 40);

  float barCycleTime = ((60000 / bpm) * (tweakBPM) / 8); // tweak at 4 look good

  //uint8_t scalingFactor = map(tweakQuantity, 1, 128, 1, 16);
  //if ((currentTime % scalingFactor) == 0) {
    int m = random(0, NUM_VERTICAL_STRIPS - 1);
    if (rainPosition[m] == 0) {
      rainPosition[m] = currentTime;
    }
  //}

  for (int i = 0; i < NUM_VERTICAL_STRIPS; i++) {
    if (rainPosition[i] != 0) {
      uint8_t outOfOne = (uint8_t)((((currentTime - rainPosition[i]) % (uint32_t)barCycleTime)) / barCycleTime);
      uint8_t k = (uint8_t)((((currentTime - rainPosition[i]) % (uint32_t)barCycleTime) * ledMappingVertical[i].numbersOfLeds) / barCycleTime);
      uint8_t j = (uint8_t) ((rainPosition[i] + ((k * tweakColor) / 4)) % 255);
      if (!ledMappingVertical[i].isGoingUp) {
        leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm] = CHSV(j, 255, brightness);
      } else {
        leds[ledMappingVertical[i].pwmChannel][ledMappingVertical[i].indexInPwm - k + ledMappingVertical[i].numbersOfLeds - 1] = CHSV(j, 255, brightness);
      }
      if (k >= ledMappingVertical[i].numbersOfLeds - 3) {
        rainPosition[i] = 0;
      }
    }
  }
}

void animColorfulSparkle() {
  // Gradually fade each LED strip separately
  fadeToBlackBy(leds[0], 451, 20);
  fadeToBlackBy(leds[1], 451, 20);
  fadeToBlackBy(leds[2], 477, 20);
  fadeToBlackBy(leds[3], 477, 20);

  for (uint8_t i = 0; i < 2; i++) {
    leds[i][random(451)] = CHSV(random(0, 255), 255, 255);  // Random color with full saturation and brightness
  }

  for (uint8_t i = 2; i < 4; i++) {
    leds[i][random(477)] = CHSV(random(0, 255), 255, 255);
  }
}

// --------------------------------------------------------------------------------------------------------------------------------------
// LINE OF PATTERN 3 --------------------------------------------------------------------------------------------------------------------

void sparkle() {
  FastLED.clear();
  uint8_t originalBrightness = FastLED.getBrightness();
  FastLED.setBrightness(MAX_BRIGHTNESS);
  for (uint8_t i = 0; i < 2; i++) {
    leds[i][random(451)] = CHSV(0, 0, 255);  // Full white in HSV
  }
  for (uint8_t i = 2; i < 4; i++) {
    leds[i][random(477)] = CHSV(0, 0, 255);  // Full white in HSV
  }
  FastLED.show();
  FastLED.setBrightness(originalBrightness);
}

void fadeToBlackBy(CRGB* leds, int num_leds, uint8_t fadeBy) {
  uint8_t* p = (uint8_t*)leds;
  while (num_leds--) {
    p[0] = scale8(p[0], 255 - fadeBy);
    p[1] = scale8(p[1], 255 - fadeBy);
    p[2] = scale8(p[2], 255 - fadeBy);
    p += 3;
  }
}

void bigTempoPulse(long currentTime, long startAnimationTime) {
  float barCycleTime = (60000 / bpm) / 2;
  uint8_t j = (uint8_t)((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 255) / barCycleTime);
  CHSV colorHSV = CHSV(hue, 255, 255 - j);

  if (!animDone) {
    originalBrightness = FastLED.getBrightness();
    FastLED.setBrightness(MAX_BRIGHTNESS);

    for (uint16_t i = 0; i < 451; i++) {
      leds[0][i] = colorHSV;
      leds[1][i] = colorHSV;
    }
    for (uint16_t i = 0; i < 477; i++) {
      leds[2][i] = colorHSV;
      leds[3][i] = colorHSV;
    }

    FastLED.show();

    if (j >= 230) {
      animDone = true;  // Mark the pulse as done
      FastLED.setBrightness(originalBrightness);
    }
  }
}

void gradientPulse(long currentTime, long startAnimationTime) {
  float barCycleTime = (60000 / bpm) / 2;
  uint8_t j = (uint8_t)((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 255) / barCycleTime);

  // Calculate brightness level based on pulse progress
  uint8_t brightnessLevel = 255 - j;

  // Gradient colors based on the position
  for (uint16_t i = 0; i < 451; i++) {
    uint8_t gradientHue = hue + (i * 255 / 451);  // Spread hue over the LED strip
    CHSV colorHSV = CHSV(gradientHue, 255, brightnessLevel);
    leds[0][i] = colorHSV;
    leds[1][i] = colorHSV;
  }

  for (uint16_t i = 0; i < 477; i++) {
    uint8_t gradientHue = hue + (i * 255 / 477);  // Spread hue over the LED strip
    CHSV colorHSV = CHSV(gradientHue, 255, brightnessLevel);
    leds[2][i] = colorHSV;
    leds[3][i] = colorHSV;
  }

  FastLED.show();

  if (!animDone) {
    originalBrightness = FastLED.getBrightness();
    FastLED.setBrightness(MAX_BRIGHTNESS);

    if (j >= 230) {
      animDone = true;
      FastLED.setBrightness(originalBrightness);
    }
  }
}

void allWhiteStep(CHSV colorValue) {
  for (uint16_t i = 0; i < 451; i++) {
    leds[1][i] = colorValue;
    leds[0][i] = colorValue;
  }
  for (uint16_t i = 0; i < 477; i++) {
    leds[2][i] = colorValue;
    leds[3][i] = colorValue;
  }
  FastLED.show();
}

void explosion(uint8_t loop) {
  for (uint8_t l = 0; l < loop; l++) {

    //for(uint16_t j=0; j < 256; j++) {
    for (int i = 0; i < 40; i += 2) {
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 200; k++) {
          leds[ledMappingCylinder[i + j][k].pwmChannel][ledMappingCylinder[i + j][k].indexInPwm] = CHSV(((i * 256 / 72) + l * (256 / loop)) & 255, 255, brightness);
        }
      }
      FastLED.show();
      float logValue = log(i + 1);
      int roundedLog = round(logValue) * 4;
      //int delayTime = roundedLog * 100;
      delay(roundedLog);
      //delay(i);
    }

    for (int i = 0; i < 40; i += 4) {
      for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 200; k++) {
          leds[ledMappingCylinder[i + j][k].pwmChannel][ledMappingCylinder[i + j][k].indexInPwm] = CHSV(0, 0, 0);  // Off in HSV
        }
      }
      FastLED.show();
    }
  }
}

void blink() {
  for (uint16_t j = 0; j < 20; j++) {
    if (j % 2 == 0) {
      for (uint16_t i = 0; i < 477; i++) {
        for (int l = 3; l >= 0; l--) {
          leds[l][i] = CHSV(((5 * 256 / SIZE_ANIM) + j * (256 / 20)) & 255, 255, brightness);
        }
      }
    } else {
      for (uint16_t i = 0; i < 477; i++) {
        for (int l = 3; l >= 0; l--) {
          leds[l][i] = CHSV(0, 0, 0);  // Off in HSV
        }
      }
    }
    FastLED.show();
    delay(100);
  }
}

void breathing() {
  for (uint16_t j = 0; j < 256; j++) {
    for (uint16_t i = 0; i < 477; i++) {
      for (int l = 3; l >= 0; l--) {
        leds[l][i] = CHSV(((5 * 256 / SIZE_ANIM) + j) & 255, 255, brightness);
      }
    }
    FastLED.show();
  }
}

void horizontalLignRainbowCycle(uint8_t wait) {
  for (uint16_t j = 0; j < 37; j++) {
    for (int i = 0; i < 72; i++) {
      if (j == i) {
        for (int k = 0; k < 72; k++) {
          leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CHSV(((i * 256 / 72) + j * (256 / 37)) & 255, 255, brightness);
        }
      } else {
        for (int k = 0; k < 72; k++) {
          leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CHSV(0, 0, 0);  // Off in HSV
        }
      }
    }
    FastLED.show();
    delay(wait);
  }
}



// The first one anim
void myMatrixRain(long currentTime, long startAnimationTime) {

  fadeToBlackBy(leds[0], 451, 40);
  fadeToBlackBy(leds[1], 451, 40);
  fadeToBlackBy(leds[2], 477, 40);
  fadeToBlackBy(leds[3], 477, 40);

  float barCycleTime = ((60000 / bpm) * (tweakBPM) / 8); // tweak at 4 look good

  if (currentTime % (uint8_t)(16 / tweakQuantity) == 0) { // tweak at 1 looks good
    int m = random(0, NUM_VERTICAL_STRIPS - 1);
    if (rainPosition[m] == 0) {
      rainPosition[m] = currentTime;
    }
  }

  for (int i = 0; i < NUM_VERTICAL_STRIPS; i++) {
    if (rainPosition[i] != 0) {
      uint8_t outOfOne = (uint8_t)((((currentTime - rainPosition[i]) % (uint32_t)barCycleTime)) / barCycleTime);
      uint8_t k = (uint8_t)((((currentTime - rainPosition[i]) % (uint32_t)barCycleTime) * ledMappingVertical[i].numbersOfLeds) / barCycleTime);
      uint8_t j = (uint8_t) ((rainPosition[i] + ((k * tweakColor) / 4)) % 255);
      if (!ledMappingVertical[i].isGoingUp) {
        leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm] = CHSV(j, 255, brightness);
      } else {
        leds[ledMappingVertical[i].pwmChannel][ledMappingVertical[i].indexInPwm - k + ledMappingVertical[i].numbersOfLeds - 1] = CHSV(j, 255, brightness);
      }
      if (k >= ledMappingVertical[i].numbersOfLeds - 3) {
        rainPosition[i] = 0;
      }
    }
  }
}

void blueRain(long currentTime, long startAnimationTime) {
  float barCycleTime = (60000 / bpm) / 16;
  uint8_t j = (uint8_t)((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 255) / barCycleTime);
  int l = 0;

  // Iterate over each vertical LED strip
  for (uint16_t i = 0; i < 72; i++) {
    // Determine if this strip should animate a droplet
    bool shouldRain = random(0, 100) < 20;  // 20% chance for rain on this strip
    if (shouldRain) {
      int dropletPosition = random(0, ledMappingVertical[i].numbersOfLeds);  // Random position for the droplet
      int dropletLength = random(1, 5);                                      // Random length of the droplet

      // Create the droplet effect
      for (int k = 0; k < dropletLength; k++) {
        int ledIndex = dropletPosition + k;

        if (ledIndex < ledMappingVertical[i].numbersOfLeds) {
          CHSV color = CHSV(160, 255, 255 - (k * 50));  // Shades of blue with a gradient effect
          leds[ledMappingVertical[i].pwmChannel][ledIndex + ledMappingVertical[i].indexInPwm] = color;
        }
      }
    } else {
      // Dim the LED strip if no rain on this strip
      for (int k = 0; k < ledMappingVertical[i].numbersOfLeds; k++) {
        leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm].fadeToBlackBy(10);  // Gradually fade to black
      }
    }
  }

  FastLED.show();
}

void matrixRain(long currentTime, long startAnimationTime) {
  float barCycleTime = (60000 / bpm) / 16;
  uint8_t j = (uint8_t)((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 255) / barCycleTime);

  for (uint16_t i = 0; i < NUM_STRIPS; i++) {
    // Create a trailing effect by fading all LEDs slightly
    for (int k = 0; k < ledMappingVertical[i].numbersOfLeds; k++) {
      leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm].fadeToBlackBy(20);
    }

    // Draw the rain drop at the current position
    leds[ledMappingVertical[i].pwmChannel][rainPosition[i] + ledMappingVertical[i].indexInPwm] = CHSV(160, 255, brightness);

    // Create a fading trail effect by lighting up the previous LEDs
    for (int t = 1; t < 5; t++) {
      int trailPos = rainPosition[i] - t;
      if (trailPos >= 0) {
        leds[ledMappingVertical[i].pwmChannel][trailPos + ledMappingVertical[i].indexInPwm] = CHSV(160, 255, 255 - (t * 50));  // Fading trail effect
      }
    }

    // Move the rain drop down
    rainPosition[i]++;

    // If the rain drop reaches the bottom, reset it to the top
    if (rainPosition[i] >= ledMappingVertical[i].numbersOfLeds) {
      rainPosition[i] = 0;
    }
  }

  FastLED.show();
}


CHSV Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;  // Reverse direction for smoother color transition
  if (WheelPos < 85) {
    // For the first third of the spectrum
    return CHSV(WheelPos * 3, 255, brightness);  // Red to Yellow in HSV
  } else if (WheelPos < 170) {
    // For the second third of the spectrum
    WheelPos -= 85;
    return CHSV(WheelPos * 3 + 85, 255, brightness);  // Yellow to Blue in HSV
  } else {
    // For the final third of the spectrum
    WheelPos -= 170;
    return CHSV(WheelPos * 3 + 170, 255, brightness);  // Blue to Red in HSV
  }
}

#endif
