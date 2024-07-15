#ifndef COLOR_VIEW_H
#define COLOR_VIEW_H

const int TAB_WIDTH = 280;
const int TAB_HEIGHT = 40;
const int INSIDE_SIZE = 36;
const int COLOR_BAR_HEIGHT = 20;
const int COLOR_BAR_COMPONENTS = 40;
const int M_20 = 20;
const int M_40 = 40;
const int GAP = 2;
const int SPACE = 10;
const int TEXT_HEIGHT = M_20;
const int DOWN_TEXT_Y_OFFSET    = TAB_HEIGHT + SPACE + COLOR_BAR_COMPONENTS + SPACE;
const int DOWN_BUTTONS_Y_OFFSET = TAB_HEIGHT + SPACE + COLOR_BAR_COMPONENTS + SPACE + TEXT_HEIGHT;


void drawColorBar();
void drawSelectedColor(int position);
void drawCursor(int x);

void drawColorPickerView(int cursorPosition) {
  sprite.fillRect(20, 50, TAB_WIDTH, COLOR_BAR_COMPONENTS, TFT_BLACK);  // Top and left
  drawColorBar();
  drawCursor(cursorPosition);
  drawSelectedColor(cursorPosition);
}

void drawColorBar() {
  for (int i = 0; i < TAB_WIDTH - 4; i++) {
    float position = (float)i / (TAB_WIDTH - 1);
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
    sprite.drawLine(i + M_20 + GAP, TAB_HEIGHT + SPACE + TEXT_HEIGHT + GAP, i + M_20 + GAP, TAB_HEIGHT + SPACE + TEXT_HEIGHT + COLOR_BAR_HEIGHT - GAP - 1, tft.color565(r, g, b));
  }
  sprite.setTextColor(TFT_WHITE);
  sprite.drawString("COLOR PICKER", M_20, TAB_HEIGHT + SPACE, 2);
  // Draw the white border around the color bar
  sprite.drawRect(M_20, TAB_HEIGHT + SPACE + TEXT_HEIGHT, TAB_WIDTH, COLOR_BAR_HEIGHT, TFT_WHITE);  // Top and left
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

void drawCursor(int x) {
  sprite.fillRect(x + M_20, TAB_HEIGHT + SPACE + TEXT_HEIGHT, 10, COLOR_BAR_HEIGHT, TFT_WHITE);
}

void drawSelectedColor(int position) {
  sprite.setTextColor(TFT_WHITE);
  sprite.drawString("EASY", M_20, DOWN_TEXT_Y_OFFSET, 2);
  sprite.drawRoundRect(M_20, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, 8, TFT_WHITE);
  sprite.fillRoundRect(M_20 + GAP, DOWN_BUTTONS_Y_OFFSET + GAP, INSIDE_SIZE, INSIDE_SIZE, 8, findSelectedColorInColorBar(position));
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
void drawAlertColorAnim(int position, uint32_t currentTime) {
  uint16_t selectedColor = findSelectedColorInColorBar(position);
  uint16_t blackColor = TFT_BLACK;  // assuming TFT_BLACK is defined

  // Calculate the time factor (0.0 to 1.0) based on the elapsed time
  float cycleTime = 1500;  // 2 seconds for a full cycle
  float elapsed = (currentTime % (uint32_t)cycleTime) / cycleTime;

  // Calculate t for interpolation using sine wave
  float t = (sin(elapsed * 2 * 3.14159265359) + 1) / 2;

  // Interpolate between black and selected color
  uint16_t interpolatedColor = interpolateColor(blackColor, selectedColor, t);

  sprite.setTextColor(TFT_WHITE);
  // Draw the rounded rectangle with the interpolated color
  sprite.drawString("ALERT", M_20 + BUTTON_SIZE + SPACE, DOWN_TEXT_Y_OFFSET, 2);
  sprite.drawRoundRect(M_20 + BUTTON_SIZE + SPACE, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, 8, TFT_WHITE);
  sprite.fillRoundRect(M_20 + BUTTON_SIZE + SPACE + GAP, DOWN_BUTTONS_Y_OFFSET + GAP, INSIDE_SIZE, INSIDE_SIZE, 8, interpolatedColor);
  sprite.pushSprite(0, 0);
}

void drawHorizontalBarColorAnim(int position, uint32_t currentTime) {
  sprite.fillRect(M_20 + (BUTTON_SIZE + SPACE) * 2, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, TFT_BLACK);
  uint16_t selectedColor = findSelectedColorInColorBar(position);

  // Bar position
  float barCycleTime = 1500; 
  float barElapsed = (currentTime % (uint32_t)barCycleTime) / barCycleTime;

  // Bar position moves
  int barPositionX = M_20 + (BUTTON_SIZE + SPACE) * 2 + GAP + (INSIDE_SIZE - 4) * (0.5 * (1 + sin(barElapsed * 2 * 3.14159265359)));

  // Sweep bar
  sprite.fillRoundRect(barPositionX, DOWN_BUTTONS_Y_OFFSET + GAP, 4, INSIDE_SIZE, 2, selectedColor);

  sprite.setTextColor(TFT_WHITE);
  sprite.drawString("SWEEP", M_20 + (BUTTON_SIZE + SPACE) * 2, DOWN_TEXT_Y_OFFSET, 2);
  
  sprite.drawRoundRect(M_20 + (BUTTON_SIZE + SPACE) * 2, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, 8, TFT_WHITE);

  sprite.pushSprite(0, 0);
}

void drawVerticalBarColorAnim(int position, uint32_t currentTime) {
  sprite.fillRect(M_20 + (BUTTON_SIZE + SPACE) * 3, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, TFT_BLACK);
  uint16_t selectedColor = findSelectedColorInColorBar(position);

  // Calculate bar position for horizontal animation
  float barCycleTime = 1500;
  float barElapsed = (currentTime % (uint32_t)barCycleTime) / barCycleTime;

  // Bar position moves from left to right and back
  int barPositionY = DOWN_BUTTONS_Y_OFFSET + GAP + (INSIDE_SIZE - 4) * (0.5 * (1 + sin(barElapsed * 2 * 3.14159265359)));

  // Sweep bar
  sprite.fillRoundRect(M_20 + (BUTTON_SIZE + SPACE) * 3 + GAP, barPositionY, INSIDE_SIZE, 4, 2, selectedColor);

  sprite.setTextColor(TFT_WHITE);
  sprite.drawString("SWEEP", M_20 + (BUTTON_SIZE + SPACE) * 3, DOWN_TEXT_Y_OFFSET, 2);
  
  sprite.drawRoundRect(M_20 + (BUTTON_SIZE + SPACE) * 3, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, 8, TFT_WHITE);

  sprite.pushSprite(0, 0);
}

void drawDiagonalBarColorAnim(int position, uint32_t currentTime) {
  // Clear the area where the animation will take place
  sprite.fillRect(M_20 + (BUTTON_SIZE + SPACE) * 4, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, TFT_BLACK);

  uint16_t selectedColor = findSelectedColorInColorBar(position);

  // Calculate bar position for diagonal animation
  float barCycleTime = 1500;  // 1.5 seconds for a full diagonal cycle
  float barElapsed = (currentTime % (uint32_t)barCycleTime) / barCycleTime;

  // Determine the direction and calculate positions
  int startX = M_20 + (BUTTON_SIZE + SPACE) * 4 + GAP;
  int startY = DOWN_BUTTONS_Y_OFFSET + GAP;
  int endX = startX + INSIDE_SIZE;
  int endY = startY + INSIDE_SIZE;

  int lineStartX, lineStartY, lineEndX, lineEndY;

  if (barElapsed < 0.5) {
    // Moving from top-left to bottom-right
    float t = barElapsed * 2;
    lineStartX = startX;
    lineStartY = startY + t * INSIDE_SIZE;
    lineEndX = startX + t * INSIDE_SIZE;
    lineEndY = startY;
  } else {
    // Moving from bottom-right to top-left
    float t = (barElapsed - 0.5) * 2;
    lineStartX = startX + t * INSIDE_SIZE;
    lineStartY = endY;
    lineEndX = endX;
    lineEndY = startY + t * INSIDE_SIZE;
  }

  // Draw the diagonal line
  sprite.drawLine(lineStartX, lineStartY, lineEndX, lineEndY, selectedColor);

  sprite.setTextColor(TFT_WHITE);
  sprite.drawString("SWEEP", M_20 + (BUTTON_SIZE + SPACE) * 4, DOWN_TEXT_Y_OFFSET, 2);

  // Draw the border of the square
  sprite.drawRoundRect(M_20 + (BUTTON_SIZE + SPACE) * 4, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, 8, TFT_WHITE);

  sprite.pushSprite(0, 0);
}




// Function to draw the selected color with breathing effect
void drawMultiColorAnim(uint16_t position, uint32_t currentTime) {
  float cycleTime = 3.0;  // 20 seconds for a full cycle
  float elapsed = (currentTime % (uint32_t)(cycleTime * 1000)) / (cycleTime * 1000.0);

  // Map elapsed to a position in the color bar
  float t = elapsed * (TAB_WIDTH - 1);  // TAB_WIDTH - 1 for full color range

  // Find the interpolated color
  uint16_t interpolatedColor = findSelectedColorInColorBar((int)t);

  // Draw the rounded rectangle with the interpolated color
  sprite.setTextColor(TFT_WHITE);
  sprite.drawString("MULTI", M_20 + (BUTTON_SIZE + SPACE) * 2, DOWN_TEXT_Y_OFFSET, 2);
  sprite.drawRoundRect(M_20 + (BUTTON_SIZE + SPACE) * 2, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, 8, TFT_WHITE);
  sprite.fillRoundRect(M_20 + (BUTTON_SIZE + SPACE) * 2 + GAP, DOWN_BUTTONS_Y_OFFSET + GAP, INSIDE_SIZE, INSIDE_SIZE, 8, interpolatedColor);
  sprite.pushSprite(0, 0);
}

void drawMultiColordzAnim(uint16_t position, uint32_t currentTime) {
  float cycleTime = 3.0;  // 20 seconds for a full cycle
  float elapsed = (currentTime % (uint32_t)(cycleTime * 1000)) / (cycleTime * 1000.0);

  // Map elapsed to a position in the color bar
  float t = elapsed * (TAB_WIDTH - 1);

  // Find the interpolated color
  uint16_t interpolatedColor = findSelectedColorInColorBar((int)t);

  // Draw the rounded rectangle with the interpolated color
  sprite.setTextColor(TFT_WHITE);
  sprite.drawString("MULTI", M_20 + (BUTTON_SIZE + SPACE) * 2, DOWN_TEXT_Y_OFFSET, 2);
  sprite.drawRoundRect(M_20 + (BUTTON_SIZE + SPACE) * 2, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, 8, TFT_WHITE);
  sprite.fillRoundRect(M_20 + (BUTTON_SIZE + SPACE) * 2 + GAP, DOWN_BUTTONS_Y_OFFSET + GAP, INSIDE_SIZE, INSIDE_SIZE, 8, interpolatedColor);
  sprite.pushSprite(0, 0);
}

void handleColorTabClick(int x, int y) {
  if (y >= 20 && y < 20 + TAB_WIDTH) {
    if (x >= TAB_HEIGHT + 10 && x < TAB_HEIGHT + 10 + COLOR_BAR_COMPONENTS) {
      colorSelected = findSelectedColorInColorBar(y - 20);
      cursorPosition = y - 20;
      drawColorPickerView(cursorPosition);
    }
  }
}


#endif  // COLOR_VIEW_H