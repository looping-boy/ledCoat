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
    drawPatternLine1();
  } else if (x >= SECOND_LINE && x < SECOND_LINE + SMALL_BUTTON_SIZE){
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
    drawPatternLine2();
  } else if (x >= THIRD_LINE && x < THIRD_LINE + SMALL_BUTTON_SIZE){
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
    drawPatternLine3();
  }
}

#endif