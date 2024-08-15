#ifndef COLOR_UTILS_H
#define COLOR_UTILS_H

uint16_t interpolateColor(uint16_t color1, uint16_t color2, float t);
int findSelectedColorInColorBar(int position);

uint16_t interpolateColor(uint16_t color1, uint16_t color2, float t) {
  // Extract RGB components from RGB565
  uint8_t r1 = (color1 >> 11) & 0x1F;
  uint8_t g1 = (color1 >> 5) & 0x3F;
  uint8_t b1 = color1 & 0x1F;

  uint8_t r2 = (color2 >> 11) & 0x1F;
  uint8_t g2 = (color2 >> 5) & 0x3F;
  uint8_t b2 = color2 & 0x1F;

  // Interpolate each channel in full range
  uint8_t r = r1 + t * (r2 - r1);
  uint8_t g = g1 + t * (g2 - g1);
  uint8_t b = b1 + t * (b2 - b1);

  // Repack interpolated RGB into RGB565 format
  return (r << 11) | (g << 5) | b;
}

int findSelectedColorInColorBar(int position) {
  int r, g, b;

  // Position goes to 280 max and min 0
  // Normalize position to range [0, 1]
  float normalizedPosition = (float)position / (TAB_WIDTH - 1);

  // Determine the RGB values based on the normalized position
  if (normalizedPosition < 1.0 / 6.0) {
    r = 255;
    g = (int)(255 * normalizedPosition * 6);
    b = 0;
  } else if (normalizedPosition < 2.0 / 6.0) {
    r = (int)(255 - 255 * (normalizedPosition - 1.0 / 6.0) * 6);
    g = 255;
    b = 0;
  } else if (normalizedPosition < 3.0 / 6.0) {
    r = 0;
    g = 255;
    b = (int)(255 * (normalizedPosition - 2.0 / 6.0) * 6);
  } else if (normalizedPosition < 4.0 / 6.0) {
    r = 0;
    g = (int)(255 - 255 * (normalizedPosition - 3.0 / 6.0) * 6);
    b = 255;
  } else if (normalizedPosition < 5.0 / 6.0) {
    r = (int)(255 * (normalizedPosition - 4.0 / 6.0) * 6);
    g = 0;
    b = 255;
  } else {
    r = 255;
    g = 0;
    b = (int)(255 - 255 * (normalizedPosition - 5.0 / 6.0) * 6);
  }

  // Convert RGB to 16-bit color format
  return tft.color565(r, g, b);
}

int isSelected(int anim) {
    for (int i = 0; i < numSelectedAnims; i++) {
        if (selectedAnims[i] == anim) {
            return 1; // Animation is selected
        }
    }
    return 0; // Animation is not selected
}

#endif