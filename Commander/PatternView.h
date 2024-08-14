#ifndef PATTERN_VIEW_H
#define PATTERN_VIEW_H

#include "ESPSender.h"

void drawSelectedColor();
void drawAlertColorAnim(long currentTime);
void drawVerticalBarColorAnim(long currentTime);
void drawHorizontalBarColorAnim(long currentTime);
void drawDiagonalBarColorAnim(long currentTime);
void drawCircularBarColorAnim(long currentTime);
void drawCrossBarColorAnim(long currentTime);
void drawZigZagBarColorAnim(long currentTime);
uint16_t interpolateColor(uint16_t color1, uint16_t color2, float t);

void drawPatternView(unsigned long currentTime) {
  drawSelectedColor();
  drawAlertColorAnim(currentTime);
  drawVerticalBarColorAnim(currentTime);
  drawHorizontalBarColorAnim(currentTime);
  drawDiagonalBarColorAnim(currentTime);
  drawCircularBarColorAnim(currentTime);
  drawCrossBarColorAnim(currentTime);
  drawZigZagBarColorAnim(currentTime);
  sprite.pushSprite(0, 0);
}

void drawSelectedColor() {
  bool selected = (selectedAnim == EASY);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  sprite.drawRoundRect(M_0, DOWN_BUTTONS_Y_OFFSET, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
  sprite.fillRoundRect(M_0 + GAP, DOWN_BUTTONS_Y_OFFSET + GAP, SMALL_INSIDE_SIZE, SMALL_INSIDE_SIZE, 8, colorSelected);
}

void drawAlertColorAnim(long currentTime) {
  uint16_t blackColor = TFT_BLACK;  // assuming TFT_BLACK is defined

  float cycleTime = 60000 / bpmMain * 4;  // 2 seconds for a full cycle
  float elapsed = (currentTime % (uint32_t)cycleTime) / cycleTime;

  float t = (sin(elapsed * 2 * 3.14159265359) + 1) / 2;

  uint16_t interpolatedColor = interpolateColor(blackColor, colorSelected, t);

  boolean selected = (selectedAnim == ALERT);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  sprite.drawRoundRect(M_0 + SMALL_BUTTON_SIZE + SPACE, DOWN_BUTTONS_Y_OFFSET, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
  sprite.fillRoundRect(M_0 + SMALL_BUTTON_SIZE + SPACE + GAP, DOWN_BUTTONS_Y_OFFSET + GAP, SMALL_INSIDE_SIZE, SMALL_INSIDE_SIZE, 8, interpolatedColor);
  sprite.pushSprite(0, 0);
}

void drawVerticalBarColorAnim(long currentTime) {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2, DOWN_BUTTONS_Y_OFFSET, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  float barCycleTime = 60000 / bpmMain * 4;
  float barElapsed = (currentTime % (uint32_t)barCycleTime) / barCycleTime;

  int barPositionX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2 + GAP + (SMALL_INSIDE_SIZE - 4) * (0.5 * (1 + sin(barElapsed * 2 * 3.14159265359)));

  sprite.fillRoundRect(barPositionX, DOWN_BUTTONS_Y_OFFSET + GAP, 4, SMALL_INSIDE_SIZE, 2, colorSelected);

  boolean selected = (selectedAnim == SWEEP_VERTICAL_BAR);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  
  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2, DOWN_BUTTONS_Y_OFFSET, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);

  sprite.pushSprite(0, 0);
}

void drawHorizontalBarColorAnim(long currentTime) {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3, DOWN_BUTTONS_Y_OFFSET, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  float barCycleTime = 60000 / bpmMain * 4; 
  float barElapsed = (currentTime % (uint32_t)barCycleTime) / barCycleTime;

  int barPositionY = DOWN_BUTTONS_Y_OFFSET + GAP + (SMALL_INSIDE_SIZE - 4) * (0.5 * (1 + sin(barElapsed * 2 * 3.14159265359)));

  sprite.fillRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3 + GAP, barPositionY, SMALL_INSIDE_SIZE, 4, 2, colorSelected);

  boolean selected = (selectedAnim == SWEEP_HORIZONTAL_BAR);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  
  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3, DOWN_BUTTONS_Y_OFFSET, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);

  sprite.pushSprite(0, 0);
}

void drawDiagonalBarColorAnim(long currentTime) {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4, DOWN_BUTTONS_Y_OFFSET, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  float barCycleTime = 60000 / bpmMain * 4;
  float barElapsed = (currentTime % (uint32_t)barCycleTime) / barCycleTime;

  int startX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4 + GAP;
  int startY = DOWN_BUTTONS_Y_OFFSET + GAP;
  int endX = startX + SMALL_INSIDE_SIZE;
  int endY = startY + SMALL_INSIDE_SIZE;

  int lineStartX, lineStartY, lineEndX, lineEndY;

  if (barElapsed < 0.5) {
    float t = barElapsed * 2;
    lineStartX = startX;
    lineStartY = startY + t * SMALL_INSIDE_SIZE;
    lineEndX = startX + t * SMALL_INSIDE_SIZE;
    lineEndY = startY;
  } else {
    float t = (barElapsed - 0.5) * 2;
    lineStartX = startX + t * SMALL_INSIDE_SIZE;
    lineStartY = endY;
    lineEndX = endX;
    lineEndY = startY + t * SMALL_INSIDE_SIZE;
  }

  sprite.drawLine(lineStartX, lineStartY, lineEndX, lineEndY, colorSelected);

  boolean selected = (selectedAnim == SWEEP_DIAGONAL_BAR);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);

  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4, DOWN_BUTTONS_Y_OFFSET, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);

  sprite.pushSprite(0, 0);
}

void drawCircularBarColorAnim(long currentTime) {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5, DOWN_BUTTONS_Y_OFFSET, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  float barCycleTime = 60000 / bpmMain * 4;
  float barElapsed = (currentTime % (uint32_t)barCycleTime) / barCycleTime;

  int centerX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5 + SMALL_BUTTON_SIZE / 2;
  int centerY = DOWN_BUTTONS_Y_OFFSET + SMALL_BUTTON_SIZE / 2;
  int radius = SMALL_INSIDE_SIZE / 2;

  int angle = barElapsed * 360;
  int x = centerX + radius * cos(angle * 3.14159265359 / 180);
  int y = centerY + radius * sin(angle * 3.14159265359 / 180);

  sprite.drawPixel(x, y, colorSelected);

  boolean selected = (selectedAnim == SWEEP_CIRCULAR_BAR);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);

  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5, DOWN_BUTTONS_Y_OFFSET, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);

  sprite.pushSprite(0, 0);
}

void drawCrossBarColorAnim(long currentTime) {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6, DOWN_BUTTONS_Y_OFFSET, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  float barCycleTime = 60000 / bpmMain * 4;
  float barElapsed = (currentTime % (uint32_t)barCycleTime) / barCycleTime;

  int crossPosition = (int)((SMALL_INSIDE_SIZE - 4) * (0.5 * (1 + sin(barElapsed * 2 * 3.14159265359))));

  sprite.drawLine(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6 + GAP, DOWN_BUTTONS_Y_OFFSET + GAP + crossPosition,
                  M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6 + GAP + SMALL_INSIDE_SIZE, DOWN_BUTTONS_Y_OFFSET + GAP + SMALL_INSIDE_SIZE - crossPosition, colorSelected);
  sprite.drawLine(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6 + GAP + SMALL_INSIDE_SIZE, DOWN_BUTTONS_Y_OFFSET + GAP + crossPosition,
                  M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6 + GAP, DOWN_BUTTONS_Y_OFFSET + GAP + SMALL_INSIDE_SIZE - crossPosition, colorSelected);

  boolean selected = (selectedAnim == SWEEP_CROSS_BAR);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);

  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6, DOWN_BUTTONS_Y_OFFSET, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);

  sprite.pushSprite(0, 0);
}

void drawZigZagBarColorAnim(long currentTime) {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7, DOWN_BUTTONS_Y_OFFSET, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  float barCycleTime = 60000 / bpmMain * 4;
  float barElapsed = (currentTime % (uint32_t)barCycleTime) / barCycleTime;

  int startX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7 + GAP;
  int startY = DOWN_BUTTONS_Y_OFFSET + GAP;

  int zigzagPositionX = startX + barElapsed * SMALL_INSIDE_SIZE;
  int zigzagPositionY = startY + (SMALL_INSIDE_SIZE / 2) * (barElapsed > 0.5 ? 1 : -1);

  sprite.drawLine(zigzagPositionX, startY, zigzagPositionX, zigzagPositionY, colorSelected);
  sprite.drawLine(zigzagPositionX, zigzagPositionY, zigzagPositionX + (SMALL_INSIDE_SIZE / 2), zigzagPositionY + (barElapsed > 0.5 ? -1 : 1) * (SMALL_INSIDE_SIZE / 2), colorSelected);

  boolean selected = (selectedAnim == SWEEP_ZIGZAG_BAR);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);

  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7, DOWN_BUTTONS_Y_OFFSET, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);

  sprite.pushSprite(0, 0);
}

void handlePatternViewClick(int x, int y) {
  if (x >= DOWN_BUTTONS_Y_OFFSET && x < DOWN_BUTTONS_Y_OFFSET + SMALL_BUTTON_SIZE) {
      if (y >= M_0 && y < M_0 + SMALL_BUTTON_SIZE) {
        selectedAnim = EASY;
        sendValue(MESSAGE_TYPE_PATTERN, EASY);
      } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) && y < M_0 + SPACE + SMALL_BUTTON_SIZE * 2) {
        selectedAnim = ALERT;
        sendValue(MESSAGE_TYPE_PATTERN, ALERT);
      } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2 && y < M_0 + SPACE * 2 + SMALL_BUTTON_SIZE * 3) {
        selectedAnim = SWEEP_VERTICAL_BAR;
        sendValue(MESSAGE_TYPE_PATTERN, SWEEP_VERTICAL_BAR);
      } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3 && y < M_0 + SPACE * 3 + SMALL_BUTTON_SIZE * 4) {
        selectedAnim = SWEEP_HORIZONTAL_BAR;
        sendValue(MESSAGE_TYPE_PATTERN, SWEEP_HORIZONTAL_BAR);
      } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4 && y < M_0 + SPACE * 4 + SMALL_BUTTON_SIZE * 5) {
        selectedAnim = SWEEP_DIAGONAL_BAR;
        sendValue(MESSAGE_TYPE_PATTERN, SWEEP_DIAGONAL_BAR);
      } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5 && y < M_0 + SPACE * 5 + SMALL_BUTTON_SIZE * 6) {
        selectedAnim = SWEEP_CIRCULAR_BAR;
        sendValue(MESSAGE_TYPE_PATTERN, SWEEP_CIRCULAR_BAR);
      } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6 && y < M_0 + SPACE * 6 + SMALL_BUTTON_SIZE * 7) {
        selectedAnim = SWEEP_CROSS_BAR;
        sendValue(MESSAGE_TYPE_PATTERN, SWEEP_CROSS_BAR);
      } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7 && y < M_0 + SPACE * 7 + SMALL_BUTTON_SIZE * 8) {
        selectedAnim = SWEEP_ZIGZAG_BAR;
        sendValue(MESSAGE_TYPE_PATTERN, SWEEP_ZIGZAG_BAR);
      }
      // MAKE THE 3 BUTTONS HERE
    }
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


#endif