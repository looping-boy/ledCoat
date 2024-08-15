#ifndef LOGIC_ANIMS_H
#define LOGIC_ANIMS_H

void animFullStatic() {
  CHSV colorValue = CHSV(hue, 255, brightness);
  for (uint8_t i = 0; i < totalLine * totalColumn; i++) {
    leds[1][i] = colorValue;
  }
  // Because static
  animDone = true;
}

#endif