#ifndef PATTERN_VIEW_H
#define PATTERN_VIEW_H


void drawSelectedColor(int position);


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

void drawSelectedColor(int position) {
  boolean selected = (selectedAnim == EASY);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  sprite.drawString("EASY", M_20, DOWN_TEXT_Y_OFFSET, 2);
  sprite.drawRoundRect(M_20, DOWN_BUTTONS_Y_OFFSET, BUTTON_SIZE, BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
  sprite.fillRoundRect(M_20 + GAP, DOWN_BUTTONS_Y_OFFSET + GAP, INSIDE_SIZE, INSIDE_SIZE, 8, findSelectedColorInColorBar(position));
}


void handlePatternViewClick(int x, int y) {
  if (x >= DOWN_BUTTONS_Y_OFFSET && x < DOWN_BUTTONS_Y_OFFSET + BUTTON_SIZE) {
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

#endif