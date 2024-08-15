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

void dealWithAnimList(uint8_t animToToggle);
void addAnim(uint8_t anim);
void removeAnim(uint8_t anim);

void drawPatternView() {
  drawPatternLine1();
  drawPatternLine2();
  drawPatternLine3();
}

void handlePatternViewClick(int x, int y) {
  uint8_t animToToggle = 0;
  if (x >= TAB_HEIGHT + SPACE && x < TAB_HEIGHT + SPACE + SMALL_BUTTON_SIZE) {
    if (y >= M_0 && y < M_0 + SMALL_BUTTON_SIZE) {
      animToToggle = ANIM_STATIC_FULL;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) && y < M_0 + SPACE + SMALL_BUTTON_SIZE * 2) {
      animToToggle = ANIM_ALERT_FULL;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2 && y < M_0 + SPACE * 2 + SMALL_BUTTON_SIZE * 3) {
      animToToggle = ANIM_VERTICAL_LINE;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3 && y < M_0 + SPACE * 3 + SMALL_BUTTON_SIZE * 4) {
      animToToggle = ANIM_HORIZONTAL_LINE;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4 && y < M_0 + SPACE * 4 + SMALL_BUTTON_SIZE * 5) {
      animToToggle = ANIM_DIAGONAL_LINE;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5 && y < M_0 + SPACE * 5 + SMALL_BUTTON_SIZE * 6) {
      animToToggle = ANIM_CIRCLE_LINE;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6 && y < M_0 + SPACE * 6 + SMALL_BUTTON_SIZE * 7) {
      animToToggle = ANIM_CROSS_VERTICAL_LINE;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7 && y < M_0 + SPACE * 7 + SMALL_BUTTON_SIZE * 8) {
      animToToggle = ANIM_CROSS_HORIZONTAL_LINE;
    }
    dealWithAnimList(animToToggle);
    sendValue(MESSAGE_TYPE_PATTERN, animToToggle);
    // if (numSelectedAnims > 1) {
       drawPatternLine1();
    // }
  } else if (x >= SECOND_LINE && x < SECOND_LINE + SMALL_BUTTON_SIZE) {
    if (y >= M_0 && y < M_0 + SMALL_BUTTON_SIZE) {
      animToToggle = ANIM_COLOR_FULL;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) && y < M_0 + SPACE + SMALL_BUTTON_SIZE * 2) {
      animToToggle = ANIM_ALERT_COLOR_FULL;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2 && y < M_0 + SPACE * 2 + SMALL_BUTTON_SIZE * 3) {
      animToToggle = ANIM_VERTICAL_RAINBOW;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3 && y < M_0 + SPACE * 3 + SMALL_BUTTON_SIZE * 4) {
      animToToggle = ANIM_HORIZONTAL_RAINBOW;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4 && y < M_0 + SPACE * 4 + SMALL_BUTTON_SIZE * 5) {
      animToToggle = ANIM_DIAGONAL_RAINBOW;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5 && y < M_0 + SPACE * 5 + SMALL_BUTTON_SIZE * 6) {
      animToToggle = ANIM_CIRCLE_RAINBOW;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6 && y < M_0 + SPACE * 6 + SMALL_BUTTON_SIZE * 7) {
      animToToggle = ANIM_COLORFULL_RAIN;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7 && y < M_0 + SPACE * 7 + SMALL_BUTTON_SIZE * 8) {
      animToToggle = ANIM_COLORFULL_SPARKLE;
    }
    dealWithAnimList(animToToggle);
    sendValue(MESSAGE_TYPE_PATTERN, animToToggle);
    // if (numSelectedAnims > 1) {
       drawPatternLine2();
    // }
  } else if (x >= THIRD_LINE && x < THIRD_LINE + SMALL_BUTTON_SIZE) {
    if (y >= M_0 && y < M_0 + SMALL_BUTTON_SIZE) {
      animToToggle = ANIM_GIF_CHECK_BLUE;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) && y < M_0 + SPACE + SMALL_BUTTON_SIZE * 2) {
      animToToggle = ANIM_GIF_PONG;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 2 && y < M_0 + SPACE * 2 + SMALL_BUTTON_SIZE * 3) {
      animToToggle = ANIM_GIF_WARNING;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 3 && y < M_0 + SPACE * 3 + SMALL_BUTTON_SIZE * 4) {
      animToToggle = ANIM_GIF_SPIRAL;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 4 && y < M_0 + SPACE * 4 + SMALL_BUTTON_SIZE * 5) {
      animToToggle = ANIM_GIF_RAINBOW;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 5 && y < M_0 + SPACE * 5 + SMALL_BUTTON_SIZE * 6) {
      animToToggle = ANIM_GIF_PSY;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 6 && y < M_0 + SPACE * 6 + SMALL_BUTTON_SIZE * 7) {
      animToToggle = ANIM_COLOR_FULL;
    } else if (y >= M_0 + (SMALL_BUTTON_SIZE + SPACE) * 7 && y < M_0 + SPACE * 7 + SMALL_BUTTON_SIZE * 8) {
      animToToggle = ANIM_COLOR_FULL;
    }
    dealWithAnimList(animToToggle);
    sendValue(MESSAGE_TYPE_PATTERN, animToToggle);
    // if (numSelectedAnims > 1) {
       drawPatternLine3();
    // }
  }
}

void dealWithAnimList(uint8_t animToToggle) {
  uint8_t isSelected = 0;
  for (uint8_t i = 0; i < numSelectedAnims; i++) {
    if (selectedAnims[i] == animToToggle) {
      isSelected = 1;
      break;
    }
  }

  if (isSelected) {
    removeAnim(animToToggle);
  } else {
    addAnim(animToToggle);
  }
}


void addAnim(uint8_t anim) {
  for (uint8_t i = 0; i < numSelectedAnims; i++) {
    if (selectedAnims[i] == anim) {
      return; 
    }
  }

  if (numSelectedAnims < MAX_ANIMS) {
    selectedAnims[numSelectedAnims++] = anim;
  }
}

void removeAnim(uint8_t anim) {
  if (numSelectedAnims > 1) {
    for (uint8_t i = 0; i < numSelectedAnims; i++) {
      if (selectedAnims[i] == anim) {
        for (uint8_t j = i; j < numSelectedAnims - 1; j++) {
          selectedAnims[j] = selectedAnims[j + 1];
        }
        numSelectedAnims--;
        return;
      }
    }
  }
}


#endif