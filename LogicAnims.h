#ifndef LOGIC_ANIMS_H
#define LOGIC_ANIMS_H

#include "Squeletons.h"

uint32_t Wheel(byte WheelPos);
uint32_t rgbToUint32(uint8_t red, uint8_t green, uint8_t blue);
void fadeToBlackByIndex(CRGB* leds, int num_leds, uint8_t fadeBy);

void breathingSmall() {
  for (uint16_t j = 0; j < 256; j++) {
    for (uint16_t i = 0; i < 200; i++) {
      leds[1][i] = CRGB(Wheel(((5 * 256 / 200) + j) & 255));
    }
  }
  FastLED.show();
}

void alertBPM(long currentTime) {
  float barCycleTime = 60000 / bpm;
  uint8_t j = (uint8_t)(((currentTime % (uint32_t)barCycleTime) * 255) / barCycleTime);
  CRGB colorValue = CRGB(Wheel(((5 * 256 / 200) + j) & 255));
  for (uint16_t i = 0; i < 451; i++) {
    leds[0][i] = colorValue;
    leds[1][i] = colorValue;
  }
  for (uint16_t i = 0; i < 477; i++) {
    leds[2][i] = colorValue;
    leds[3][i] = colorValue;
  }
  FastLED.show();
}

void sparkle() {
  FastLED.clear();
  uint8_t originalBrightness = FastLED.getBrightness();
  FastLED.setBrightness(MAX_BRIGHTNESS);
  for (uint8_t i = 0; i < 2; i++) {
    leds[i][random(451)] = CRGB::White;
  }
  for (uint8_t i = 2; i < 4; i++) {
    leds[i][random(477)] = CRGB::White;
  }
  FastLED.show();
  FastLED.setBrightness(originalBrightness);
}

void colorfulSparkle() {
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

  FastLED.show();
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

  if (!pulseDone) {
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
      pulseDone = true;  // Mark the pulse as done
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

  if (!pulseDone) {
    originalBrightness = FastLED.getBrightness();
    FastLED.setBrightness(MAX_BRIGHTNESS);

    if (j >= 230) {
      pulseDone = true;  // Mark the pulse as done
      FastLED.setBrightness(originalBrightness);
    }
  }
}

void allWhiteStep(CRGB colorValue) {
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
          leds[ledMappingCylinder[i + j][k].pwmChannel][ledMappingCylinder[i + j][k].indexInPwm] = CRGB(Wheel((((i)*256 / 72) + l * (256 / loop)) & 255));
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
          leds[ledMappingCylinder[i + j][k].pwmChannel][ledMappingCylinder[i + j][k].indexInPwm] = CRGB(0x00000000);
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
          leds[l][i] = CRGB(Wheel(((5 * 256 / SIZE_ANIM) + j * (256 / 20)) & 255));
        }
      }
    } else {
      for (uint16_t i = 0; i < 477; i++) {
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
  for (uint16_t j = 0; j < 256; j++) {
    for (uint16_t i = 0; i < 477; i++) {
      for (int l = 3; l >= 0; l--) {
        leds[l][i] = CRGB(Wheel(((5 * 256 / SIZE_ANIM) + j) & 255));
      }
    }
    FastLED.show();
  }
}

void verticalRainbowCycle(uint8_t wait) {
  for (uint16_t j = 0; j < 256; j++) {
    for (int i = 0; i < 72; i++) {
      for (int k = 0; k < 72; k++) {
        leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CRGB(Wheel((((i)*256 / 72) + j) & 255));
      }
    }
    FastLED.show();
    delay(wait);
  }
}

void horizontalLignRainbowCycle(uint8_t wait) {
  for (uint16_t j = 0; j < 37; j++) {
    for (int i = 0; i < 72; i++) {
      if (j == i) {
        for (int k = 0; k < 72; k++) {
          leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CRGB(Wheel((((i)*256 / 72) + j * (256 / 37)) & 255));
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

void downLine(long currentTime, long startAnimationTime) {
  float barCycleTime = (60000 / bpm) * (tweakBPM / 16);
  uint8_t j = (uint8_t)((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 37) / barCycleTime);
  FastLED.clear();
  for (int i = 0; i < 72; i++) {
    if (j == i) {
        for (int k = 0; k < 72; k++) {
          leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CRGB(Wheel(((256 - i * 256 / 72) + (256 - j * (256 / 37))) & 255));
        }
      } 
    }
  FastLED.show();
}

// void upLine(long currentTime, long startAnimationTime) {
//   float barCycleTime = (60000 / bpm) * (tweakBPM / 8);
//   uint8_t j = (uint8_t) 37 - ((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 37) / barCycleTime);
//   uint8_t h = (uint8_t) 37 - (uint8_t)(((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 37) / barCycleTime) + 19 ) % 37;  
//   FastLED.clear();
//   for (int i = 0; i < 72; i++) {
//     if (j == i) {
//         for (int k = 0; k < 72; k++) {
//           leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CRGB(Wheel(((256 - i * 256 / 72) + (256 - j * (256 / 37))) & 255));
//         }
//     } 
//     if (h == i) {
//         for (int k = 0; k < 72; k++) {
//           leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CRGB(Wheel(((256 - i * 256 / 72) + (256 - j * (256 / 37))) & 255));
//         }
//     } 
//   }
//   FastLED.show();
// }

void upLine(long currentTime, long startAnimationTime) {
  float barCycleTime = (60000 / bpm) * (tweakBPM / (16 / tweakPhase));

  FastLED.clear();
  
  // Iterate over two phases
  for (int phase = 0; phase < tweakPhase; phase++) {
    uint8_t pos = (uint8_t) 37 - (uint8_t)(((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 37) / barCycleTime) + (phase * (37 / 2))) % 37;

    for (int i = 0; i < 72; i++) {
      if (pos == i) {
        for (int k = 0; k < 72; k++) {
          if (pos > 15 && random(1, 38 - pos) == 1) {
            leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CRGB::White;
          } else {
            leds[ledMappingHorizontal[i][k].pwmChannel][ledMappingHorizontal[i][k].indexInPwm] = CRGB(Wheel(((256 - i * 256 / 72) + (256 - pos * (256 / 37))) & 255));
          }
        }
      }
    }
  }
  
  FastLED.show();
}


void diagonalRainbowCycle(uint8_t wait) {
  for (uint16_t j = 0; j < 256; j++) {
    for (int i = 0; i < 72; i++) {
      for (int k = 0; k < 140; k++) {
        leds[ledMappingDiagonal[i][k].pwmChannel][ledMappingDiagonal[i][k].indexInPwm] = CRGB(Wheel((((i)*256 / 72) + j) & 255));
      }
    }
    FastLED.show();
    delay(wait);
  }
}

void circleRainbowCycle(uint8_t loop) {
  for (uint8_t l = 0; l < loop; l++) {
    for (uint16_t j = 0; j < 256; j++) {
      for (int i = 0; i < 40; i++) {
        for (int k = 0; k < 200; k++) {
          leds[ledMappingCylinder[i][k].pwmChannel][ledMappingCylinder[i][k].indexInPwm] = CRGB(Wheel((((i)*256 / 72) + j) & 255));
        }
      }
      FastLED.show();
      delay(1);
    }
  }
}

// The first one anim
void rainbowCycle(long currentTime, long startAnimationTime) {
  float barCycleTime = ((60000 / bpm)) * (tweakBPM / 4);
  uint8_t j = (uint8_t)((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 255) / barCycleTime);
  int l = 0;
  for (uint16_t i = 0; i < 72; i++) {
    if (!ledMappingVertical[i].isGoingUp) {
      for (int k = 0; k < ledMappingVertical[i].numbersOfLeds; k++) {
        leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm] = CRGB(Wheel((((ledMappingVertical[i].indexTotal + k) * 256 / SIZE_ANIM) + j) & 255));
      }
    } else {
      for (int k = ledMappingVertical[i].numbersOfLeds - 1; k >= 0; k--) {
        leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm] = CRGB(Wheel((((ledMappingVertical[i].indexTotal - k + ledMappingVertical[i].numbersOfLeds - 1) * 256 / SIZE_ANIM) + j) & 255));
      }
    }
  }
  FastLED.show();
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
        leds[ledMappingVertical[i].pwmChannel][k + ledMappingVertical[i].indexInPwm] = CRGB(Wheel(j));
      } else {
        leds[ledMappingVertical[i].pwmChannel][ledMappingVertical[i].indexInPwm - k + ledMappingVertical[i].numbersOfLeds - 1] = CRGB(Wheel(j));
      }
      if (k >= ledMappingVertical[i].numbersOfLeds - 3) {
        rainPosition[i] = 0;
      }
    }
  }

  FastLED.show();
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
          CRGB color = CHSV(160, 255, 255 - (k * 50));  // Shades of blue with a gradient effect
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
    leds[ledMappingVertical[i].pwmChannel][rainPosition[i] + ledMappingVertical[i].indexInPwm] = CRGB::Blue;

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


uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;  // Reverse direction for smoother color transition
  if (WheelPos < 85) {
    // For the first third of the spectrum
    return rgbToUint32(255 - WheelPos * 3, WheelPos * 3, 0);  // Red to Yellow
  } else if (WheelPos < 170) {
    // For the second third of the spectrum
    WheelPos -= 85;
    return rgbToUint32(0, 255 - WheelPos * 3, WheelPos * 3);  // Yellow to Blue
  } else {
    // For the final third of the spectrum
    WheelPos -= 170;
    // Ensure smooth transition between full blue and full red
    return rgbToUint32(WheelPos * 3, 0, 255 - WheelPos * 3);  // Blue to Red
  }
}

uint32_t rgbToUint32(uint8_t red, uint8_t green, uint8_t blue) {
  return ((uint32_t)red << 16) | ((uint32_t)green << 8) | blue;
}

#endif