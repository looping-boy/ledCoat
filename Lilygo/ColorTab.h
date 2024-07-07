// ColorTab.h
#ifndef COLOR_TAB_H
#define COLOR_TAB_H

const int COLOR_BAR_WIDTH = 280;  // Width of the color bar
const int COLOR_BAR_HEIGHT = 40;  // Height of the color bar  

void drawColorBar();
void drawSelectedColor(int position);
void drawCursor(int x);

void drawColorPickerView(int cursorPosition) {
  drawColorBar();
  drawCursor(cursorPosition);
  drawSelectedColor(cursorPosition);
}

void drawColorBar() {
  for (int i = 0; i < COLOR_BAR_WIDTH - 4; i++) {
    float position = (float)i / (COLOR_BAR_WIDTH - 1);
    int r, g, b;

    if (position < 1.0 / 6.0) {
      r = 255;
      g = (int)(255 * position * 6);
      b = 0;
    } else if (position < 2.0 / 6.0) {
      r = (int)(255 - 255 * (position - 1.0 / 6.0) * 6);
      g = 255;
      b = 0;
    } else if (position < 3.0 / 6.0) {
      r = 0;
      g = 255;
      b = (int)(255 * (position - 2.0 / 6.0) * 6);
    } else if (position < 4.0 / 6.0) {
      r = 0;
      g = (int)(255 - 255 * (position - 3.0 / 6.0) * 6);
      b = 255;
    } else if (position < 5.0 / 6.0) {
      r = (int)(255 * (position - 4.0 / 6.0) * 6);
      g = 0;
      b = 255;
    } else {
      r = 255;
      g = 0;
      b = (int)(255 - 255 * (position - 5.0 / 6.0) * 6);
    }
    sprite.drawLine(i + 20 + 2, 52, i + 20 + 2, 50 + COLOR_BAR_HEIGHT - 3, tft.color565(r, g, b));
  }
  // Draw the white border around the color bar
  sprite.drawRect(20, 50, COLOR_BAR_WIDTH , COLOR_BAR_HEIGHT, TFT_WHITE); // Top and left
}

int findSelectedColorInColorBar(int position) {
  int r, g, b;
  
  // Position goes to 280 max and min 0
  // Normalize position to range [0, 1]
  float normalizedPosition = (float)position / (COLOR_BAR_WIDTH - 1);

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

void drawCursor(int x) {
  sprite.fillRect(x + 20, 50, 10, COLOR_BAR_HEIGHT, TFT_WHITE);
}

void drawSelectedColor(int position) {
  sprite.drawRoundRect(20, STICKY_BAR_HEIGHT + 10 + COLOR_BAR_HEIGHT + 10, 40, 40, 8, TFT_WHITE);
  sprite.fillRoundRect(20 + 2, STICKY_BAR_HEIGHT + 10 + COLOR_BAR_HEIGHT + 10 + 2, 36, 36, 8, findSelectedColorInColorBar(position));
}

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

// Function to draw the selected color with breathing effect
void drawBreathingColorAnim(int position, uint32_t currentTime) {
    uint16_t selectedColor = findSelectedColorInColorBar(position);
    uint16_t blackColor = TFT_BLACK; // assuming TFT_BLACK is defined

    // Calculate the time factor (0.0 to 1.0) based on the elapsed time
    float cycleTime = 1500; // 2 seconds for a full cycle
    float elapsed = (currentTime % (uint32_t)cycleTime) / cycleTime;

    // Calculate t for interpolation using sine wave
    float t = (sin(elapsed * 2 * 3.14159265359) + 1) / 2;

    // Interpolate between black and selected color
    uint16_t interpolatedColor = interpolateColor(blackColor, selectedColor, t);

    // Draw the rounded rectangle with the interpolated color
    sprite.drawRoundRect(20 + 40 + 10, STICKY_BAR_HEIGHT + 10 + COLOR_BAR_HEIGHT + 10, 40, 40, 8, TFT_WHITE);
    sprite.fillRoundRect(20 + 40 + 10 + 2, STICKY_BAR_HEIGHT + 10 + COLOR_BAR_HEIGHT + 10 + 2, 36, 36, 8, interpolatedColor);
    sprite.pushSprite(0, 0);
}

// Function to draw the selected color with breathing effect
void drawMultiColorAnim(int position, uint32_t currentTime) {
    float cycleTime = 3.0; // 20 seconds for a full cycle
    float elapsed = (currentTime % (uint32_t)(cycleTime * 1000)) / (cycleTime * 1000.0);

    // Map elapsed to a position in the color bar
    float t = elapsed * (COLOR_BAR_WIDTH - 1); // COLOR_BAR_WIDTH - 1 for full color range

    // Find the interpolated color
    uint16_t interpolatedColor = findSelectedColorInColorBar((int)t);

    // Draw the rounded rectangle with the interpolated color
    sprite.drawRoundRect(20 + 40 + 10 + 40 + 10, STICKY_BAR_HEIGHT + 10 + COLOR_BAR_HEIGHT + 10, 40, 40, 8, TFT_WHITE);
    sprite.fillRoundRect(20 + 40 + 10 + 40 + 10 + 2, STICKY_BAR_HEIGHT + 10 + COLOR_BAR_HEIGHT + 10 + 2, 36, 36, 8, interpolatedColor);
    sprite.pushSprite(0, 0);
}



#endif // COLOR_TAB_H