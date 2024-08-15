#ifndef LOGIC_ANIMS_H
#define LOGIC_ANIMS_H

// --------------------------------------------------------------------------------------------------------------------------------------
// LINE OF PATTERN 1 --------------------------------------------------------------------------------------------------------------------

void animFullStatic() {
  CHSV colorValue = CHSV(hue, 255, brightness);
  for (uint8_t i = 0; i < totalLine * totalColumn; i++) {
    leds[1][i] = colorValue;
  }
  // Because static
  animDone = true;
}

void animAlertFull(long currentTime) {
  float barCycleTime = (60000 / bpm) * (tweakBPM / 4);
  float phase = (float)(currentTime % (uint32_t)barCycleTime) / barCycleTime;
  uint8_t j = (uint8_t)((sin(phase * 2 * 3.14159265359) + 1) * (brightness / 2));

  CHSV colorValue = CHSV(hue, 255, j);
  
  for (uint8_t i = 0; i < totalLine * totalColumn; i++) {
    leds[1][i] = colorValue;
  }
}

void animDownLine(long currentTime, long startAnimationTime) {
  float barCycleTime = (60000 / bpm) * (tweakBPM / 16) * tweakPhase;
  uint8_t pulseBrightness = (uint8_t) brightness * 1.5;
  // Iterate over two or more
  //for (int phase = 0; phase < tweakPhase; phase++) {
    //uint8_t pos = (uint8_t)(((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * totalLine) / barCycleTime) + (phase * (totalLine / tweakPhase))) % totalLine;
    for (int k = 24; k < 48; k++) {
        leds[1][k] = CHSV(200, 255, 255);
    }
  //} 
}

void animRightLine(long currentTime, long startAnimationTime) {
  float barCycleTime = ((60000 / bpm)) * (tweakBPM / 8);
  uint8_t j = (uint8_t)(((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * totalColumn / barCycleTime);
  uint8_t lowerBrightness = (uint8_t)(brightness * 0.5);

  for (int row = 0; row < totalLine; row++) {
    int index;
    if (row % 2 == 0) {
      index = row * (totalColumn - 1) + j;
    } else {
      index = row * (totalColumn - 1) + (totalColumn - 1 - j);
    }
    leds[1][index] = CHSV(hue, 255, lowerBrightness);
  }
}

void animLeftLine(long currentTime, long startAnimationTime) {
  float barCycleTime = ((60000 / bpm)) * (tweakBPM / 8);
  uint8_t j = (uint8_t)(((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * totalColumn / barCycleTime);
  uint8_t lowerBrightness = (uint8_t)(brightness * 0.5);

  for (int row = 0; row < totalLine; row++) {
    int index;
    if (row % 2 == 1) {
      index = row * (totalColumn - 1) + j;
    } else {
      index = row * (totalColumn - 1) + (totalColumn - 1 - j);
    }
    leds[1][index] = CHSV(hue, 255, lowerBrightness);
  }
}

void animHorizontalRainbow(long currentTime, long startAnimationTime) {
  float barCycleTime = (float) (((60000 / bpm)) * (tweakBPM / 8));
  uint8_t j = (uint8_t)(((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * totalColumn / barCycleTime);
  uint8_t hueMoving = (uint8_t)(((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 255 / barCycleTime);
  uint8_t lowerBrightness = (uint8_t)(brightness * 0.5);
  uint8_t hueStep = 255 / (totalLine * totalColumn - 1);

  for (int row = 0; row < totalLine; row++) {
    for (int col = 0; col < totalColumn; col++) {
      int index;
      if (row % 2 == 0) {
        index = row * (totalColumn) + col;  // Normal order for even rows
      } else {
        index = row * (totalColumn) + (totalColumn - 1 - col);  // Reversed order for odd rows
      }

      // Calculate the hue for the current LED
      uint8_t currentHue = hueStep * (row * totalColumn + col);

      // Set the color with the gradient hue
      leds[1][index] = CHSV((currentHue + hueMoving) & 255, 255, brightness);
    }
  }
}

void animVerticalRainbow(long currentTime, long startAnimationTime) {
  float barCycleTime = (float) (((60000 / bpm)) * (tweakBPM / 8));
  uint8_t j = (uint8_t)(((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * totalColumn / barCycleTime);
  uint8_t hueMoving = (uint8_t)(((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * 255 / barCycleTime);
  uint8_t lowerBrightness = (uint8_t)(brightness * 0.5);
  uint8_t hueStep = 255 / (totalLine * totalColumn - 1);

  for (int row = 0; row < totalLine; row++) {
    for (int col = 0; col < totalColumn; col++) {
      int index;
      if (row % 2 == 0) {
        index = row * (totalColumn) + col;  // Normal order for even rows
      } else {
        index = row * (totalColumn) + (totalColumn - 1 - col);  // Reversed order for odd rows
      }

      // Calculate the hue for the current LED
      uint8_t currentHue = hueStep * (col * totalLine + row);

      // Set the color with the gradient hue
      leds[1][index] = CHSV((currentHue + hueMoving) & 255, 255, brightness);
    }
  }
}

#endif