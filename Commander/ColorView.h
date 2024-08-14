#ifndef COLOR_VIEW_H
#define COLOR_VIEW_H

#include "ESPSender.h"

const int TEXT_HEIGHT = M_20;
const int DOWN_TEXT_Y_OFFSET    = TAB_HEIGHT + SPACE + COLOR_BAR_COMPONENTS + SPACE;
const int DOWN_BUTTONS_Y_OFFSET = TAB_HEIGHT + SPACE + COLOR_BAR_COMPONENTS + SPACE + TEXT_HEIGHT;
const int OPACITY_Y_OFFSET      = DOWN_BUTTONS_Y_OFFSET + INSIDE_SIZE + SPACE;

uint8_t selectedAnim = EASY;

void drawForceBrightnessButton();
void drawColorBar();
void drawOpacityBar();
void drawCursor(int x);
void drawOpacityCursor(int x);
uint16_t hueToRGB565(float hue);
uint32_t hueToRGB(uint8_t hue);
int findSelectedColorInColorBar(int position);
uint16_t getOpacityColor(uint16_t color, float opacity);

void drawColorPickerView() {
  drawColorBar();
  drawOpacityBar();
  drawCursor(cursorPosition);
  drawOpacityCursor(opacityPosition);
  drawForceBrightnessButton();
  sprite.pushSprite(0, 0);
}

void drawColorBar() {
  sprite.fillRect(M_20, TAB_HEIGHT + SPACE + TEXT_HEIGHT, TAB_WIDTH, COLOR_BAR_COMPONENTS, TFT_BLACK); 
  for (int i = 0; i < TAB_WIDTH - 4; i++) {
    float hue = (float)i / (TAB_WIDTH - 1);
    uint16_t color = hueToRGB565(hue);
    sprite.drawLine(i + M_20 + GAP, TAB_HEIGHT + SPACE + TEXT_HEIGHT + GAP, i + M_20 + GAP, TAB_HEIGHT + SPACE + TEXT_HEIGHT + COLOR_BAR_HEIGHT - GAP - 1, color);
  }
  sprite.setTextColor(TFT_WHITE);
  sprite.drawString("COLOR PICKER", M_20, TAB_HEIGHT + SPACE, 2);

  char hueStr[4];
  sprintf(hueStr, "%d", hueSelected);
  sprite.fillRect(TAB_WIDTH + SPACE - 24, TAB_HEIGHT + SPACE, 34, TEXT_HEIGHT - 3, TFT_WHITE);
  sprite.setTextColor(TFT_BLACK);
  sprite.drawString(hueStr, TAB_WIDTH + SPACE - sprite.textWidth(hueStr), TAB_HEIGHT + SPACE, 2);

  // Draw the white border around the color bar
  sprite.drawRect(M_20, TAB_HEIGHT + SPACE + TEXT_HEIGHT, TAB_WIDTH, COLOR_BAR_HEIGHT, TFT_WHITE);
}

void drawOpacityBar() {
  sprite.fillRect(M_20, DOWN_BUTTONS_Y_OFFSET, TAB_WIDTH - OPACITY_BAR_SHORTER, OPACITY_BAR_HEIGHT, TFT_BLACK);
  for (int i = 0; i < TAB_WIDTH - OPACITY_BAR_SHORTER - 4 ; i++) {
    float opacity = (float)i / (TAB_WIDTH - 1);
    uint16_t color = getOpacityColor(TFT_WHITE, opacity);
    sprite.drawLine(i + M_20 + GAP, DOWN_BUTTONS_Y_OFFSET + GAP, i + M_20 + GAP, DOWN_BUTTONS_Y_OFFSET + COLOR_BAR_HEIGHT - GAP - 1, color);
  }
  sprite.setTextColor(TFT_WHITE);
  sprite.drawString("BRIGHTNESS", M_20, DOWN_BUTTONS_Y_OFFSET - TEXT_HEIGHT, 2);

  char opacityStr[4];
  sprintf(opacityStr, "%d", opacitySelected);
  sprite.fillRect(TAB_WIDTH - OPACITY_BAR_SHORTER + SPACE - 24, DOWN_BUTTONS_Y_OFFSET - TEXT_HEIGHT, 34, TEXT_HEIGHT - 3, TFT_WHITE);
  sprite.setTextColor(TFT_BLACK);
  sprite.drawString(opacityStr, TAB_WIDTH - OPACITY_BAR_SHORTER + SPACE - sprite.textWidth(opacityStr), DOWN_BUTTONS_Y_OFFSET - TEXT_HEIGHT, 2);
  
  sprite.drawRect(M_20, DOWN_BUTTONS_Y_OFFSET, TAB_WIDTH - OPACITY_BAR_SHORTER, OPACITY_BAR_HEIGHT, TFT_WHITE);
}

void drawForceBrightnessButton() {
  int buttonColor = (isForcedBrightness) ? TFT_WHITE : TFT_BLACK;
  int textColor = (isForcedBrightness) ? TFT_BLACK : TFT_WHITE;
  int borderColor = TFT_WHITE;

  sprite.fillRoundRect(TAB_WIDTH - 50 + SPACE, DOWN_BUTTONS_Y_OFFSET - 5, FORCE_BUTTON_WIDTH, FORCE_BUTTON_HEIGHT, 8, buttonColor);

  sprite.drawRoundRect(TAB_WIDTH - 50 + SPACE, DOWN_BUTTONS_Y_OFFSET - 5, FORCE_BUTTON_WIDTH, FORCE_BUTTON_HEIGHT, 8, borderColor);

  sprite.setTextColor(textColor, buttonColor);
  sprite.setTextSize(1);

  int textWidth = sprite.textWidth("FORCE");
  int textHeight = sprite.fontHeight();
  int textX = (TAB_WIDTH - 50 + SPACE) + ((60 - textWidth) / 2);
  int textY = DOWN_BUTTONS_Y_OFFSET - 5 + ((30 - textHeight) / 2);
  sprite.drawString("FORCE", textX, textY);
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

  return tft.color565(r, g, b);
}

uint16_t getOpacityColor(uint16_t color, float opacity) {
  uint8_t r = ((color >> 11) & 0x1F) * 8;
  uint8_t g = ((color >> 5) & 0x3F) * 4;
  uint8_t b = (color & 0x1F) * 8;

  r = r * opacity;
  g = g * opacity;
  b = b * opacity;

  return tft.color565(r, g, b);
}

uint8_t findSelectedHueInColorBar(int position) {
  float ratio = (float)position / (TAB_WIDTH - 1);
  return (uint8_t)(ratio * 255);
}

uint8_t findSelectedOpacityInOpacityBar(int position) {
  // Calculate the ratio as a float before multiplying by 255
  float ratio = (float)position / (TAB_WIDTH - OPACITY_BAR_SHORTER - 1);
  return (uint8_t)(ratio * 255);
}

void drawCursor(int x) {
  sprite.fillRect(x + M_20, TAB_HEIGHT + SPACE + TEXT_HEIGHT, 10, COLOR_BAR_HEIGHT, TFT_WHITE);
}

void drawOpacityCursor(int x) {
  sprite.fillRect(x + M_20, DOWN_BUTTONS_Y_OFFSET, 10, OPACITY_BAR_HEIGHT, TFT_WHITE);
}

void handleColorTabClick(int x, int y) {
  if (x >= TAB_HEIGHT + 10 && x < DOWN_BUTTONS_Y_OFFSET - TEXT_HEIGHT) {
    if (y >= M_20 && y < M_20 + TAB_WIDTH - 10) {
      hueSelected = findSelectedHueInColorBar(y - M_20);
      sendValue(MESSAGE_TYPE_HUE, hueSelected);
      colorSelected = findSelectedColorInColorBar(y - M_20);
      cursorPosition = y - M_20;
    } 
    drawColorPickerView();
  } else if (x >= DOWN_BUTTONS_Y_OFFSET - 10 && x < DOWN_BUTTONS_Y_OFFSET + OPACITY_BAR_COMPONENTS + 10) {
    if (y >= M_20 && y < M_20 + TAB_WIDTH - OPACITY_BAR_SHORTER - 10) {
      opacitySelected = findSelectedOpacityInOpacityBar(y - M_20);
      opacityPosition = y - M_20;
      sendValue(MESSAGE_TYPE_BRIGHTNESS, opacitySelected);
    } else if (y >= M_20 + TAB_WIDTH - OPACITY_BAR_SHORTER + SPACE && y < M_20 + TAB_WIDTH - OPACITY_BAR_SHORTER + SPACE + FORCE_BUTTON_WIDTH) {
      isForcedBrightness = !isForcedBrightness;
      if (isForcedBrightness) {
        sendValue(MESSAGE_TYPE_FORCE_BRIGHTNESS, (isForcedBrightness) ? 1 : 0);
      }
    }
    drawColorPickerView();
  } 
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


#endif 
