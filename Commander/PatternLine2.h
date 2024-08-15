#ifndef PATTERN_LINE_2_H
#define PATTERN_VIEW_2_H

void drawSelectedColor2() {
  bool selected =  isSelected(ANIM_COLOR_FULL);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  sprite.drawRoundRect(M_0, SECOND_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
  sprite.fillRoundRect(M_0 + GAP, SECOND_LINE + GAP, SMALL_INSIDE_SIZE, SMALL_INSIDE_SIZE, 8, colorSelected);
}

void drawAlertColorAnim2() {
  uint16_t blackColor = TFT_BLACK;  // assuming TFT_BLACK is defined

  float t = (sin(0.5 * 2 * 3.14159265359) + 1) / 2;

  uint16_t interpolatedColor = interpolateColor(blackColor, colorSelected, t);

  boolean selected =  isSelected(ANIM_ALERT_COLOR_FULL);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  sprite.drawRoundRect(M_0 + SMALL_BUTTON_SIZE + SPACE, SECOND_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
  sprite.fillRoundRect(M_0 + SMALL_BUTTON_SIZE + SPACE + GAP, SECOND_LINE + GAP, SMALL_INSIDE_SIZE, SMALL_INSIDE_SIZE, 8, interpolatedColor);
}

void drawVerticalBarColorAnim2() {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2, SECOND_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  int barPositionX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2 + GAP + (SMALL_INSIDE_SIZE - 4) * (0.5 * (1 + sin(0.5 * 2 * 3.14159265359)));

  sprite.fillRoundRect(barPositionX, SECOND_LINE + GAP, 4, SMALL_INSIDE_SIZE, 2, colorSelected);

  boolean selected =  isSelected(ANIM_VERTICAL_RAINBOW);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  
  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2, SECOND_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
}

void drawHorizontalBarColorAnim2() {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3, SECOND_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  int barPositionY = SECOND_LINE + GAP + (SMALL_INSIDE_SIZE - 4) * (0.5 * (1 + sin(0.5 * 2 * 3.14159265359)));

  sprite.fillRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3 + GAP, barPositionY, SMALL_INSIDE_SIZE, 4, 2, colorSelected);

  boolean selected =  isSelected(ANIM_HORIZONTAL_RAINBOW);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);
  
  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3, SECOND_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
}

void drawDiagonalBarColorAnim2() {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4, SECOND_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  int startX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4 + GAP;
  int startY = SECOND_LINE + GAP;
  int endX = startX + SMALL_INSIDE_SIZE;
  int endY = startY + SMALL_INSIDE_SIZE;

  sprite.drawLine(startX + 2, endY - 2, endX - 2, startY + 2, colorSelected);

  boolean selected =  isSelected(ANIM_DIAGONAL_RAINBOW);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);

  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4, SECOND_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
}

void drawCircularBarColorAnim2() {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5, SECOND_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  int centerX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5 + SMALL_BUTTON_SIZE / 2;
  int centerY = SECOND_LINE + SMALL_BUTTON_SIZE / 2;
  int radius = SMALL_INSIDE_SIZE / 3;

  for (int angle = 0; angle < 360; angle++) {
    int x = centerX + radius * cos(angle * 3.14159265359 / 180);
    int y = centerY + radius * sin(angle * 3.14159265359 / 180);
    sprite.drawPixel(x, y, colorSelected);
  }

  boolean selected =  isSelected(ANIM_CIRCLE_RAINBOW);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);

  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5, SECOND_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
}

void drawCrossBarColorAnim2() {
  // Clear the previous rectangle
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6, SECOND_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  // Define the start and end points for the cross lines
  int startX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6 + GAP;
  int startY = SECOND_LINE + GAP;
  int endX = startX + SMALL_INSIDE_SIZE;
  int endY = startY + SMALL_INSIDE_SIZE;

  // Draw the two lines to form a cross
  sprite.drawLine(startX + 2, startY + 2, endX - 2, endY - 2, colorSelected);
  sprite.drawLine(endX - 2, startY + 2, startX + 2, endY - 2, colorSelected);

  // Set text color based on selection
  boolean selected =  isSelected(ANIM_COLORFULL_RAIN);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);

  // Draw a rounded rectangle around the button
  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6, SECOND_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
}

void drawZigZagBarColorAnim2() {
  sprite.fillRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7, SECOND_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, TFT_BLACK);

  int startX = M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7 + GAP;
  int startY = SECOND_LINE + GAP;

  int zigzagPositionX = startX + 0.5 * SMALL_INSIDE_SIZE;
  int zigzagPositionY = startY + (SMALL_INSIDE_SIZE / 2) * (0.6 > 0.5 ? 1 : -1);

  sprite.drawLine(zigzagPositionX, startY, zigzagPositionX, zigzagPositionY, colorSelected);
  sprite.drawLine(zigzagPositionX, zigzagPositionY, zigzagPositionX + (SMALL_INSIDE_SIZE / 2), zigzagPositionY + (0.6 > 0.5 ? -1 : 1) * (SMALL_INSIDE_SIZE / 2), colorSelected);

  boolean selected =  isSelected(ANIM_COLORFULL_SPARKLE);
  sprite.setTextColor(selected ? TFT_BLACK : TFT_WHITE, selected ? TFT_WHITE : TFT_BLACK);

  sprite.drawRoundRect(M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7, SECOND_LINE, SMALL_BUTTON_SIZE, SMALL_BUTTON_SIZE, 8, (selected) ? TFT_RED : TFT_WHITE);
}

void drawPatternLine2() {
  drawSelectedColor2();
  drawAlertColorAnim2();
  drawVerticalBarColorAnim2();
  drawHorizontalBarColorAnim2();
  drawDiagonalBarColorAnim2();
  drawCircularBarColorAnim2();
  drawCrossBarColorAnim2();
  drawZigZagBarColorAnim2();
  sprite.pushSprite(0, 0);
}

#endif