#ifndef TABS_H
#define TABS_H

const int BUTTON_MARGIN = 5;
const int BUTTON_COLOR_INACTIVE = TFT_WHITE;
const int BUTTON_COLOR_ACTIVE = TFT_GREEN;

uint8_t activeButton = 4;  // 0: None, 1: B1, 2: B2, 3: B3


void drawButton(int x, int y, const char* label, int buttonId) {
  int buttonColor = (buttonId == activeButton) ? TFT_WHITE : TFT_BLACK;
  int textColor = (buttonId == activeButton) ? TFT_BLACK : TFT_WHITE;
  int borderColor = TFT_WHITE;  // Color of the border/stroke

  // Draw the button background with rounded corners
  sprite.fillRoundRect(x, y, BUTTON_SIZE, BUTTON_SIZE, 8, buttonColor);  // 8 is the radius for rounded corners

  // Draw the border around the button
  sprite.drawRoundRect(x, y, BUTTON_SIZE, BUTTON_SIZE, 8, borderColor);  // 8 is the radius for rounded corners

  // Set text color and size
  sprite.setTextColor(textColor, buttonColor);
  sprite.setTextSize(1);  // Smaller text size

  // Draw the button label (text)
  int textWidth = sprite.textWidth(label);
  int textHeight = sprite.fontHeight();
  int textX = x + (BUTTON_SIZE - textWidth) / 2;
  int textY = y + (BUTTON_SIZE - textHeight) / 2;
  sprite.drawString(label, textX, textY);
}

#endif