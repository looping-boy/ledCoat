#ifndef PATTERN_LINE_3_H
#define PATTERN_VIEW_3_H

void drawSelectedColor3() {
  bool selected = (selectedAnim == EASY);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  sprite.drawRoundRect(M_0, THIRD_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
  sprite.fillRoundRect(M_0 + GAP, THIRD_LINE + GAP, SMALL_INSIDE_SIZE, SMALL_INSIDE_SIZE, 8, colorSelected);
}

void drawAlertColorAnim3() {
  uint16_t blackColor = TFT_BLACK;  // assuming TFT_BLACK is defined

  float t = (sin(0.5 * 2 * 3.14159265359) + 1) / 2;

  uint16_t interpolatedColor = interpolateColor(blackColor, colorSelected, t);

  boolean selected = (selectedAnim == ALERT);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  sprite.drawRoundRect(M_0 + SMALL_BUTTON_SIZE + SPACE, THIRD_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
  sprite.fillRoundRect(M_0 + SMALL_BUTTON_SIZE + SPACE + GAP, THIRD_LINE + GAP, SMALL_INSIDE_SIZE, SMALL_INSIDE_SIZE, 8, interpolatedColor);
}

void drawVerticalBarColorAnim3() {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2, THIRD_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  int barPositionX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2 + GAP + (SMALL_INSIDE_SIZE - 4) * (0.5 * (1 + sin(0.5 * 2 * 3.14159265359)));

  sprite.fillRoundRect(barPositionX, THIRD_LINE + GAP, 4, SMALL_INSIDE_SIZE, 2, colorSelected);

  boolean selected = (selectedAnim == SWEEP_VERTICAL_BAR);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  
  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2, THIRD_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
}

void drawHorizontalBarColorAnim3() {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3, THIRD_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  int barPositionY = THIRD_LINE + GAP + (SMALL_INSIDE_SIZE - 4) * (0.5 * (1 + sin(0.5 * 2 * 3.14159265359)));

  sprite.fillRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3 + GAP, barPositionY, SMALL_INSIDE_SIZE, 4, 2, colorSelected);

  boolean selected = (selectedAnim == SWEEP_HORIZONTAL_BAR);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  
  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3, THIRD_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
}

void drawDiagonalBarColorAnim3() {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4, THIRD_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  int startX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4 + GAP;
  int startY = THIRD_LINE + GAP;
  int endX = startX + SMALL_INSIDE_SIZE;
  int endY = startY + SMALL_INSIDE_SIZE;

  sprite.drawLine(startX + 2, endY - 2, endX - 2, startY + 2, colorSelected);

  boolean selected = (selectedAnim == SWEEP_DIAGONAL_BAR);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);

  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4, THIRD_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
}


void drawCircularBarColorAnim3() {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5, THIRD_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  int centerX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5 + SMALL_BUTTON_SIZE / 2;
  int centerY = THIRD_LINE + SMALL_BUTTON_SIZE / 2;
  int radius = SMALL_INSIDE_SIZE / 3;

  for (int angle = 0; angle < 360; angle++) {
    int x = centerX + radius * cos(angle * 3.14159265359 / 180);
    int y = centerY + radius * sin(angle * 3.14159265359 / 180);
    sprite.drawPixel(x, y, colorSelected);
  }

  boolean selected = (selectedAnim == SWEEP_CIRCULAR_BAR);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);

  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5, THIRD_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
}


void drawCrossBarColorAnim3() {
  // Clear the previous rectangle
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6, THIRD_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  // Define the start and end points for the cross lines
  int startX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6 + GAP;
  int startY = THIRD_LINE + GAP;
  int endX = startX + SMALL_INSIDE_SIZE;
  int endY = startY + SMALL_INSIDE_SIZE;

  // Draw the two lines to form a cross
  sprite.drawLine(startX + 2, startY + 2, endX - 2, endY - 2, colorSelected);
  sprite.drawLine(endX - 2, startY + 2, startX + 2, endY - 2, colorSelected);

  // Set text color based on selection
  boolean selected = (selectedAnim == SWEEP_CROSS_BAR);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);

  // Draw a rounded rectangle around the button
  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6, THIRD_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
}

void drawZigZagBarColorAnim3() {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7, THIRD_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  int startX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7 + GAP;
  int startY = THIRD_LINE + GAP;

  int zigzagPositionX = startX + 0.5 * SMALL_INSIDE_SIZE;
  int zigzagPositionY = startY + (SMALL_INSIDE_SIZE / 2) * (0.6 > 0.5 ? 1 : -1);

  sprite.drawLine(zigzagPositionX, startY, zigzagPositionX, zigzagPositionY, colorSelected);
  sprite.drawLine(zigzagPositionX, zigzagPositionY, zigzagPositionX + (SMALL_INSIDE_SIZE / 2), zigzagPositionY + (0.6 > 0.5 ? -1 : 1) * (SMALL_INSIDE_SIZE / 2), colorSelected);

  boolean selected = (selectedAnim == SWEEP_ZIGZAG_BAR);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);

  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7, THIRD_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
}

void drawPatternLine3() {
  drawSelectedColor3();
  drawAlertColorAnim3();
  drawVerticalBarColorAnim3();
  drawHorizontalBarColorAnim3();
  drawDiagonalBarColorAnim3();
  drawCircularBarColorAnim3();
  drawCrossBarColorAnim3();
  drawZigZagBarColorAnim3();
  sprite.pushSprite(0, 0);
}

#endif