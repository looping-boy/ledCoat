#ifndef PATTERN_VIEW_H
#define PATTERN_VIEW_H

#include "ESPSender.h"
#include "PatternLine1.h"
#include "PatternLine2.h"
#include "PatternLine3.h"

void drawSelectedColor();
void drawAlertColorAnim();
void drawVerticalBarColorAnim();
void drawHorizontalBarColorAnim();
void drawDiagonalBarColorAnim();
void drawCircularBarColorAnim();
void drawCrossBarColorAnim();
void drawZigZagBarColorAnim();

void drawPatternView() {
  drawPatternLine1();
  drawPatternLine2();
  drawPatternLine3();
}

void handlePatternViewClick(int x, int y) {
  
  if (x >= TAB_HEIGHT + SPACE && x < TAB_HEIGHT + SPACE + SMALL_BUTTON_SIZE) {
    if (y >= M_0 && y < M_0 + SMALL_BUTTON_SIZE) {
      selectedAnim = ANIM_STATIC_FULL;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) && y < M_0 + SPACE + SMALL_BUTTON_SIZE * 2) {
      selectedAnim = ANIM_ALERT_FULL;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2 && y < M_0 + SPACE * 2 + SMALL_BUTTON_SIZE * 3) {
      selectedAnim = ANIM_VERTICAL_LINE;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3 && y < M_0 + SPACE * 3 + SMALL_BUTTON_SIZE * 4) {
      selectedAnim = ANIM_HORIZONTAL_LINE;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4 && y < M_0 + SPACE * 4 + SMALL_BUTTON_SIZE * 5) {
      selectedAnim = ANIM_DIAGONAL_LINE;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5 && y < M_0 + SPACE * 5 + SMALL_BUTTON_SIZE * 6) {
      selectedAnim = ANIM_CIRCLE_LINE;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6 && y < M_0 + SPACE * 6 + SMALL_BUTTON_SIZE * 7) {
      selectedAnim = ANIM_CROSS_VERTICAL_LINE;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7 && y < M_0 + SPACE * 7 + SMALL_BUTTON_SIZE * 8) {
      selectedAnim = ANIM_CROSS_HORIZONTAL_LINE;
    }
    sendValue(MESSAGE_TYPE_PATTERN, selectedAnim);
    drawPatternLine1();
  } else if (x >= SECOND_LINE && x < SECOND_LINE + SMALL_BUTTON_SIZE){
    if (y >= M_0 && y < M_0 + SMALL_BUTTON_SIZE) {
      selectedAnim = ANIM_COLOR_FULL;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) && y < M_0 + SPACE + SMALL_BUTTON_SIZE * 2) {
      selectedAnim = ANIM_ALERT_COLOR_FULL;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2 && y < M_0 + SPACE * 2 + SMALL_BUTTON_SIZE * 3) {
      selectedAnim = ANIM_VERTICAL_RAINBOW;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3 && y < M_0 + SPACE * 3 + SMALL_BUTTON_SIZE * 4) {
      selectedAnim = ANIM_HORIZONTAL_RAINBOW;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4 && y < M_0 + SPACE * 4 + SMALL_BUTTON_SIZE * 5) {
      selectedAnim = ANIM_DIAGONAL_RAINBOW;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5 && y < M_0 + SPACE * 5 + SMALL_BUTTON_SIZE * 6) {
      selectedAnim = ANIM_CIRCLE_RAINBOW;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6 && y < M_0 + SPACE * 6 + SMALL_BUTTON_SIZE * 7) {
      selectedAnim = ANIM_COLORFULL_RAIN;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7 && y < M_0 + SPACE * 7 + SMALL_BUTTON_SIZE * 8) {
      selectedAnim = ANIM_COLORFULL_SPARKLE;
    }
    sendValue(MESSAGE_TYPE_PATTERN, selectedAnim);
    drawPatternLine2();
  } else if (x >= THIRD_LINE && x < THIRD_LINE + SMALL_BUTTON_SIZE){
    if (y >= M_0 && y < M_0 + SMALL_BUTTON_SIZE) {
      selectedAnim = ANIM_COLOR_PULSE;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) && y < M_0 + SPACE + SMALL_BUTTON_SIZE * 2) {
      selectedAnim = ANIM_COLOR_FULL;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2 && y < M_0 + SPACE * 2 + SMALL_BUTTON_SIZE * 3) {
      selectedAnim = ANIM_COLOR_FULL;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3 && y < M_0 + SPACE * 3 + SMALL_BUTTON_SIZE * 4) {
      selectedAnim = ANIM_COLOR_FULL;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4 && y < M_0 + SPACE * 4 + SMALL_BUTTON_SIZE * 5) {
      selectedAnim = ANIM_COLOR_FULL;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5 && y < M_0 + SPACE * 5 + SMALL_BUTTON_SIZE * 6) {
      selectedAnim = ANIM_COLOR_FULL;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6 && y < M_0 + SPACE * 6 + SMALL_BUTTON_SIZE * 7) {
      selectedAnim = ANIM_COLOR_FULL;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7 && y < M_0 + SPACE * 7 + SMALL_BUTTON_SIZE * 8) {
      selectedAnim = ANIM_COLOR_FULL;
    }
    sendValue(MESSAGE_TYPE_PATTERN, selectedAnim);
    drawPatternLine3();
  }
}

#endif