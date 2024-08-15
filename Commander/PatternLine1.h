#ifndef PATTERN_LINE_1_H
#define PATTERN_VIEW_1_H

void drawSelectedColor() {
  bool selected = (selectedAnim == ANIM_STATIC_FULL);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  sprite.drawRoundRect(M_0, TAB_HEIGHT + SPACE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
  sprite.fillRoundRect(M_0 + GAP, TAB_HEIGHT + SPACE + GAP, SMALL_INSIDE_SIZE, SMALL_INSIDE_SIZE, 8, colorSelected);
}

void drawAlertColorAnim() {
  uint16_t blackColor = TFT_BLACK;  // assuming TFT_BLACK is defined

  float t = (sin(0.5 * 2 * 3.14159265359) + 1) / 2;

  uint16_t interpolatedColor = interpolateColor(blackColor, colorSelected, t);

  boolean selected = (selectedAnim == ANIM_ALERT_FULL);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  sprite.drawRoundRect(M_0 + SMALL_BUTTON_SIZE + SPACE, TAB_HEIGHT + SPACE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
  sprite.fillRoundRect(M_0 + SMALL_BUTTON_SIZE + SPACE + GAP, TAB_HEIGHT + SPACE + GAP, SMALL_INSIDE_SIZE, SMALL_INSIDE_SIZE, 8, interpolatedColor);
}

void drawVerticalBarColorAnim() {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2, TAB_HEIGHT + SPACE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  int barPositionX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2 + GAP + (SMALL_INSIDE_SIZE - 4) * (0.5 * (1 + sin(0.5 * 2 * 3.14159265359)));

  sprite.fillRoundRect(barPositionX, TAB_HEIGHT + SPACE + GAP, 4, SMALL_INSIDE_SIZE, 2, colorSelected);

  boolean selected = (selectedAnim == ANIM_VERTICAL_LINE);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  
  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2, TAB_HEIGHT + SPACE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
}

void drawHorizontalBarColorAnim() {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3, TAB_HEIGHT + SPACE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  int barPositionY = TAB_HEIGHT + SPACE + GAP + (SMALL_INSIDE_SIZE - 4) * (0.5 * (1 + sin(0.5 * 2 * 3.14159265359)));

  sprite.fillRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3 + GAP, barPositionY, SMALL_INSIDE_SIZE, 4, 2, colorSelected);

  boolean selected = (selectedAnim == ANIM_HORIZONTAL_LINE);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  
  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3, TAB_HEIGHT + SPACE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
}

void drawDiagonalBarColorAnim() {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4, TAB_HEIGHT + SPACE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  int startX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4 + GAP;
  int startY = TAB_HEIGHT + SPACE + GAP;
  int endX = startX + SMALL_INSIDE_SIZE;
  int endY = startY + SMALL_INSIDE_SIZE;

  sprite.drawLine(startX + 2, endY - 2, endX - 2, startY + 2, colorSelected);

  boolean selected = (selectedAnim == ANIM_DIAGONAL_LINE);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);

  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4, TAB_HEIGHT + SPACE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
}


void drawCircularBarColorAnim() {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5, TAB_HEIGHT + SPACE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  int centerX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5 + SMALL_BUTTON_SIZE / 2;
  int centerY = TAB_HEIGHT + SPACE + SMALL_BUTTON_SIZE / 2;
  int radius = SMALL_INSIDE_SIZE / 3;

  for (int angle = 0; angle < 360; angle++) {
    int x = centerX + radius * cos(angle * 3.14159265359 / 180);
    int y = centerY + radius * sin(angle * 3.14159265359 / 180);
    sprite.drawPixel(x, y, colorSelected);
  }

  boolean selected = (selectedAnim == ANIM_CIRCLE_LINE);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);

  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5, TAB_HEIGHT + SPACE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
}

void drawCrossBarColorAnim() {
  // Clear the previous rectangle
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6, TAB_HEIGHT + SPACE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  // Define the start and end points for the cross lines
  int startX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6 + GAP;
  int startY = TAB_HEIGHT + SPACE + GAP;
  int endX = startX + SMALL_INSIDE_SIZE;
  int endY = startY + SMALL_INSIDE_SIZE;

  // Draw the two lines to form a cross
  sprite.drawLine(startX + 2, startY + 2, endX - 2, endY - 2, colorSelected);
  sprite.drawLine(endX - 2, startY + 2, startX + 2, endY - 2, colorSelected);

  // Set text color based on selection
  boolean selected = (selectedAnim == ANIM_CROSS_VERTICAL_LINE);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);

  // Draw a rounded rectangle around the button
  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6, TAB_HEIGHT + SPACE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
}

void drawZigZagBarColorAnim() {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7, TAB_HEIGHT + SPACE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  int startX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7 + GAP;
  int startY = TAB_HEIGHT + SPACE + GAP;

  int zigzagPositionX = startX + 0.5 * SMALL_INSIDE_SIZE;
  int zigzagPositionY = startY + (SMALL_INSIDE_SIZE / 2) * (0.6 > 0.5 ? 1 : -1);

  sprite.drawLine(zigzagPositionX, startY, zigzagPositionX, zigzagPositionY, colorSelected);
  sprite.drawLine(zigzagPositionX, zigzagPositionY, zigzagPositionX + (SMALL_INSIDE_SIZE / 2), zigzagPositionY + (0.6 > 0.5 ? -1 : 1) * (SMALL_INSIDE_SIZE / 2), colorSelected);

  boolean selected = (selectedAnim == ANIM_CROSS_HORIZONTAL_LINE);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);

  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7, TAB_HEIGHT + SPACE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
}

void drawPatternLine1() {
  drawSelectedColor();
  drawAlertColorAnim();
  drawVerticalBarColorAnim();
  drawHorizontalBarColorAnim();
  drawDiagonalBarColorAnim();
  drawCircularBarColorAnim();
  drawCrossBarColorAnim();
  drawZigZagBarColorAnim();
  sprite.pushSprite(0, 0);
}

#endif