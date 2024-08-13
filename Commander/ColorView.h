#ifndef COLOR_VIEW_H
#define COLOR_VIEW_H

#include "ESPSender.h"

#define EASY                         0
#define ALERT                        1
#define SWEEP_VERTICAL_BAR           2
#define SWEEP_HORIZONTAL_BAR         3
#define SWEEP_DIAGONAL_BAR           4

#define TAB_WIDTH                    280
#define TAB_HEIGHT                   40
#define INSIDE_SIZE                  36
#define COLOR_BAR_HEIGHT             20
#define COLOR_BAR_COMPONENTS         40
#define M_20                         20
#define M_40                         40
#define GAP                          2
#define SPACE                        10

const int TEXT_HEIGHT = M_20;
const int DOWN_TEXT_Y_OFFSET    = TAB_HEIGHT + SPACE + COLOR_BAR_COMPONENTS + SPACE;
const int DOWN_BUTTONS_Y_OFFSET = TAB_HEIGHT + SPACE + COLOR_BAR_COMPONENTS + SPACE + TEXT_HEIGHT;

uint8_t selectedAnim = EASY;

void drawColorBar();
void drawSelectedColor(int position);
void drawCursor(int x);
uint16_t hueToRGB565(float hue);

void drawColorPickerView(int cursorPosition) {
  sprite.fillRect(20, 50, TAB_WIDTH, COLOR_BAR_COMPONENTS, TFT_BLACK);  // Top and left
  drawColorBar();
  drawCursor(cursorPosition);
  drawSelectedColor(cursorPosition);
}

void drawColorBar() {
  for (int i = 0; i < TAB_WIDTH - 4; i++) {
    float hue = (float)i / (TAB_WIDTH - 1);  // Normalize i to range [0, 1]
    uint16_t color = hueToRGB565(hue);
    sprite.drawLine(i + M_20 + GAP, TAB_HEIGHT + SPACE + TEXT_HEIGHT + GAP, i + M_20 + GAP, TAB_HEIGHT + SPACE + TEXT_HEIGHT + COLOR_BAR_HEIGHT - GAP - 1, color);
  }
  sprite.setTextColor(TFT_WHITE);
  sprite.drawString("COLOR PICKER", M_20, TAB_HEIGHT + SPACE, 2);
  // Draw the white border around the color bar
  sprite.drawRect(M_20, TAB_HEIGHT + SPACE + TEXT_HEIGHT, TAB_WIDTH, COLOR_BAR_HEIGHT, TFT_WHITE);  // Top and left
}

uint16_t hueToRGB565(float hue) {
  int r, g, b;
  float s = 1.0, v = 1.0;  // Saturation and Value are maxed

  int i = int(hue * 6);
  float f = hue * 6 - i;
  float p = v * (1 - s);
  float q = v * (1 - f * s);
  float t = v * (1 - (1 - f) * s);

  switch (i % 6) {
    case 0: r = v * 255; g = t * 255; b = p * 255; break;
    case 1: r = q * 255; g = v * 255; b = p * 255; break;
    case 2: r = p * 255; g = v * 255; b = t * 255; break;
    case 3: r = p * 255; g = q * 255; b = v * 255; break;
    case 4: r = t * 255; g = p * 255; b = v * 255; break;
    case 5: r = v * 255; g = p * 255; b = q * 255; break;
  }

  // Convert RGB to 16-bit color format
  return tft.color565(r, g, b);
}

int findSelectedColorInColorBar(int position) {
  float hue = (float)position / (TAB_WIDTH - 1);  // Normalize position to range [0, 1]
  return hueToRGB565(hue);
}

void drawCursor(int x) {
  sprite.fillRect(x + M_20, TAB_HEIGHT + SPACE + TEXT_HEIGHT, 10, COLOR_BAR_HEIGHT, TFT_WHITE);
}

void drawSelectedColor(int position) {
  boolean selected = (selectedAnim == EASY);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  sprite.drawString("EASY", M_20, DOWN_TEXT_Y_OFFSET, 2);
  sprite.drawRoundRect(M_20, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
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

void drawAlertColorAnim(int position, uint32_t currentTime) {
  uint16_t selectedColor = findSelectedColorInColorBar(position);
  uint16_t blackColor = TFT_BLACK;  // assuming TFT_BLACK is defined

  float cycleTime = 60000 / bpmMain * 4;  // 2 seconds for a full cycle
  float elapsed = (currentTime % (uint32_t)cycleTime) / cycleTime;

  float t = (sin(elapsed * 2 * 3.14159265359) + 1) / 2;

  uint16_t interpolatedColor = interpolateColor(blackColor, selectedColor, t);

  boolean selected = (selectedAnim == ALERT);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  sprite.drawString("ALERT", M_20 + BUTTON_SIZE + SPACE, DOWN_TEXT_Y_OFFSET, 2);
  sprite.drawRoundRect(M_20 + BUTTON_SIZE + SPACE, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
  sprite.fillRoundRect(M_20 + BUTTON_SIZE + SPACE + GAP, DOWN_BUTTONS_Y_OFFSET + GAP, INSIDE_SIZE, INSIDE_SIZE, 8, interpolatedColor);
  sprite.pushSprite(0, 0);
}

void drawVerticalBarColorAnim(int position, uint32_t currentTime) {
  sprite.fillRect(M_20 + (BUTTON_SIZE + SPACE) * 2, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, TFT_BLACK);
  uint16_t selectedColor = findSelectedColorInColorBar(position);

  float barCycleTime = 60000 / bpmMain * 4;
  float barElapsed = (currentTime % (uint32_t)barCycleTime) / barCycleTime;

  int barPositionX = M_20 + (BUTTON_SIZE + SPACE) * 2 + GAP + (INSIDE_SIZE - 4) * (0.5 * (1 + sin(barElapsed * 2 * 3.14159265359)));

  sprite.fillRoundRect(barPositionX, DOWN_BUTTONS_Y_OFFSET + GAP, 4, INSIDE_SIZE, 2, selectedColor);

  boolean selected = (selectedAnim == SWEEP_VERTICAL_BAR);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  sprite.drawString("SWEEP", M_20 + (BUTTON_SIZE + SPACE) * 2, DOWN_TEXT_Y_OFFSET, 2);
  
  sprite.drawRoundRect(M_20 + (BUTTON_SIZE + SPACE) * 2, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);

  sprite.pushSprite(0, 0);
}

void drawHorizontalBarColorAnim(int position, uint32_t currentTime) {
  sprite.fillRect(M_20 + (BUTTON_SIZE + SPACE) * 3, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, TFT_BLACK);
  uint16_t selectedColor = findSelectedColorInColorBar(position);

  float barCycleTime = 60000 / bpmMain * 4; 
  float barElapsed = (currentTime % (uint32_t)barCycleTime) / barCycleTime;

  int barPositionY = DOWN_BUTTONS_Y_OFFSET + GAP + (INSIDE_SIZE - 4) * (0.5 * (1 + sin(barElapsed * 2 * 3.14159265359)));

  sprite.fillRoundRect(M_20 + (BUTTON_SIZE + SPACE) * 3 + GAP, barPositionY, INSIDE_SIZE, 4, 2, selectedColor);

  boolean selected = (selectedAnim == SWEEP_HORIZONTAL_BAR);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  sprite.drawString("SWEEP", M_20 + (BUTTON_SIZE + SPACE) * 3, DOWN_TEXT_Y_OFFSET, 2);
  
  sprite.drawRoundRect(M_20 + (BUTTON_SIZE + SPACE) * 3, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);

  sprite.pushSprite(0, 0);
}

void drawDiagonalBarColorAnim(int position, uint32_t currentTime) {
  sprite.fillRect(M_20 + (BUTTON_SIZE + SPACE) * 4, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, TFT_BLACK);

  uint16_t selectedColor = findSelectedColorInColorBar(position);

  float barCycleTime = 60000 / bpmMain * 4;
  float barElapsed = (currentTime % (uint32_t)barCycleTime) / barCycleTime;

  int startX = M_20 + (BUTTON_SIZE + SPACE) * 4 + GAP;
  int startY = DOWN_BUTTONS_Y_OFFSET + GAP;
  int endX = startX + INSIDE_SIZE;
  int endY = startY + INSIDE_SIZE;

  int lineStartX, lineStartY, lineEndX, lineEndY;

  if (barElapsed < 0.5) {
    float t = barElapsed * 2;
    lineStartX = startX;
    lineStartY = startY + t * INSIDE_SIZE;
    lineEndX = startX + t * INSIDE_SIZE;
    lineEndY = startY;
  } else {
    float t = (barElapsed - 0.5) * 2;
    lineStartX = startX + t * INSIDE_SIZE;
    lineStartY = endY;
    lineEndX = endX;
    lineEndY = startY + t * INSIDE_SIZE;
  }

  sprite.drawLine(lineStartX, lineStartY, lineEndX, lineEndY, selectedColor);

  boolean selected = (selectedAnim == SWEEP_DIAGONAL_BAR);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  sprite.drawString("SWEEP", M_20 + (BUTTON_SIZE + SPACE) * 4, DOWN_TEXT_Y_OFFSET, 2);

  sprite.drawRoundRect(M_20 + (BUTTON_SIZE + SPACE) * 4, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);

  sprite.pushSprite(0, 0);
}

void drawMultiColorAnim(uint16_t position, uint32_t currentTime) {
  float cycleTime = 3.0;  // 20 seconds for a full cycle
  float elapsed = (currentTime % (uint32_t)(cycleTime * 1000)) / (cycleTime * 1000.0);

  float t = elapsed * (TAB_WIDTH - 1);  // TAB_WIDTH - 1 for full color range

  uint16_t interpolatedColor = findSelectedColorInColorBar((int)t);

  sprite.setTextColor(TFT_WHITE);
  sprite.drawString("MULTI", M_20 + (BUTTON_SIZE + SPACE) * 2, DOWN_TEXT_Y_OFFSET, 2);
  sprite.drawRoundRect(M_20 + (BUTTON_SIZE + SPACE) * 2, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, 8, TFT_WHITE);
  sprite.fillRoundRect(M_20 + (BUTTON_SIZE + SPACE) * 2 + GAP, DOWN_BUTTONS_Y_OFFSET + GAP, INSIDE_SIZE, INSIDE_SIZE, 8, interpolatedColor);
  sprite.pushSprite(0, 0);
}

void drawMultiColordzAnim(uint16_t position, uint32_t currentTime) {
  float cycleTime = 3.0;  // 20 seconds for a full cycle
  float elapsed = (currentTime % (uint32_t)(cycleTime * 1000)) / (cycleTime * 1000.0);

  float t = elapsed * (TAB_WIDTH - 1);

  uint16_t interpolatedColor = findSelectedColorInColorBar((int)t);

  sprite.setTextColor(TFT_WHITE);
  sprite.drawString("MULTI", M_20 + (BUTTON_SIZE + SPACE) * 2, DOWN_TEXT_Y_OFFSET, 2);
  sprite.drawRoundRect(M_20 + (BUTTON_SIZE + SPACE) * 2, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, 8, TFT_WHITE);
  sprite.fillRoundRect(M_20 + (BUTTON_SIZE + SPACE) * 2 + GAP, DOWN_BUTTONS_Y_OFFSET + GAP, INSIDE_SIZE, INSIDE_SIZE, 8, interpolatedColor);
  sprite.pushSprite(0, 0);
}

void handleColorTabClick(int x, int y) {
  if (y >= M_20 && y < M_20 + TAB_WIDTH) {
    if (x >= TAB_HEIGHT + 10 && x < TAB_HEIGHT + 10 + COLOR_BAR_COMPONENTS) {
      colorSelected = findSelectedColorInColorBar(y - 20);
      cursorPosition = y - 20;
      drawColorPickerView(cursorPosition);
    } else if (x >= DOWN_BUTTONS_Y_OFFSET && x < DOWN_BUTTONS_Y_OFFSET + BUTTON_SIZE) {
      if (y >= M_20 && y < M_20 + BUTTON_SIZE) {
        selectedAnim = EASY;
        sendValue(MESSAGE_TYPE_PATTERN, EASY);
      } else if (y >= M_20 + (BUTTON_SIZE + SPACE) && y < M_20 + SPACE + BUTTON_SIZE * 2) {
        selectedAnim = ALERT;
        sendValue(MESSAGE_TYPE_PATTERN, ALERT);
      } else if (y >= M_20 + (BUTTON_SIZE + SPACE) * 2 && y < M_20 + SPACE * 2 + BUTTON_SIZE * 3) {
        selectedAnim = SWEEP_VERTICAL_BAR;
        sendValue(MESSAGE_TYPE_PATTERN, SWEEP_VERTICAL_BAR);
      } else if (y >= M_20 + (BUTTON_SIZE + SPACE) * 3 && y < M_20 + SPACE * 3 + BUTTON_SIZE * 4) {
        selectedAnim = SWEEP_HORIZONTAL_BAR;
        sendValue(MESSAGE_TYPE_PATTERN, SWEEP_HORIZONTAL_BAR);
      } else if (y >= M_20 + (BUTTON_SIZE + SPACE) * 4 && y < M_20 + SPACE * 4 + BUTTON_SIZE * 5) {
        selectedAnim = SWEEP_DIAGONAL_BAR;
        sendValue(MESSAGE_TYPE_PATTERN, SWEEP_DIAGONAL_BAR);
      }
    }
  } 
}

#endif  // COLOR_VIEW_H
