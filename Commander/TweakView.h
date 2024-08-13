#ifndef TWEAK_VIEW_H
#define TWEAK_VIEW_H

void drawTweakViewSliders() {
  sprite.drawString("QUANTITY", 20 - view1scrollY, STICKY_BAR_HEIGHT + 10, 2);
  sprite.drawRoundRect(20 - view1scrollY, STICKY_BAR_HEIGHT + 30, 80, 30, 15, TFT_WHITE);
  sprite.fillRoundRect(20 - view1scrollY + ((uint8_t)((tweak1 - 1) * (50 / 6))), STICKY_BAR_HEIGHT + 30, 30, 30, 15, TFT_GREEN);

  sprite.drawString("BPM", SPACE_BETWEEN_SWITCH + 20 - view1scrollY, STICKY_BAR_HEIGHT + 10, 2);
  sprite.drawRoundRect(SPACE_BETWEEN_SWITCH + 20 - view1scrollY, STICKY_BAR_HEIGHT + 30, 80, 30, 15, TFT_WHITE);
  sprite.fillRoundRect(SPACE_BETWEEN_SWITCH + 20 - view1scrollY + ((uint8_t)((tweak2 - 1) * (50 / 6))), STICKY_BAR_HEIGHT + 30, 30, 30, 15, TFT_GREEN);

  sprite.drawString("COLOR", SPACE_BETWEEN_SWITCH * 2 + 20 - view1scrollY, STICKY_BAR_HEIGHT + 10, 2);
  sprite.drawRoundRect(SPACE_BETWEEN_SWITCH * 2 + 20 - view1scrollY, STICKY_BAR_HEIGHT + 30, 80, 30, 15, TFT_WHITE);
  sprite.fillRoundRect(SPACE_BETWEEN_SWITCH * 2 + 20 - view1scrollY + ((uint8_t)((tweak3 - 1) * (50 / 6))), STICKY_BAR_HEIGHT + 30, 30, 30, 15, TFT_GREEN);

  // DOWN
  sprite.drawString("PHASE", 20 - view1scrollY, STICKY_BAR_HEIGHT + 10 + 60, 2);
  sprite.drawRoundRect(20 - view1scrollY, STICKY_BAR_HEIGHT + 30 + 60, 80, 30, 15, TFT_WHITE);
  sprite.fillRoundRect(20 - view1scrollY + ((uint8_t)((tweak4 - 1) * (50 / 6))), STICKY_BAR_HEIGHT + 30 + 60, 30, 30, 15, TFT_GREEN);

  sprite.drawString("UNUSED", SPACE_BETWEEN_SWITCH + 20 - view1scrollY, STICKY_BAR_HEIGHT + 10 + 60, 2);
  sprite.drawRoundRect(SPACE_BETWEEN_SWITCH + 20 - view1scrollY, STICKY_BAR_HEIGHT + 30 + 60, 80, 30, 15, TFT_WHITE);
  sprite.fillRoundRect(SPACE_BETWEEN_SWITCH + 20 - view1scrollY + ((uint8_t)((tweak5 - 1) * (50 / 6))), STICKY_BAR_HEIGHT + 30 + 60, 30, 30, 15, TFT_WHITE);

  sprite.drawString("UNUSED", SPACE_BETWEEN_SWITCH * 2 + 20 - view1scrollY, STICKY_BAR_HEIGHT + 10 + 60, 2);
  sprite.drawRoundRect(SPACE_BETWEEN_SWITCH * 2 + 20 - view1scrollY, STICKY_BAR_HEIGHT + 30 + 60, 80, 30, 15, TFT_WHITE);
  sprite.fillRoundRect(SPACE_BETWEEN_SWITCH * 2 + 20 - view1scrollY + ((uint8_t)((tweak6 - 1) * (50 / 6))), STICKY_BAR_HEIGHT + 30 + 60, 30, 30, 15, TFT_WHITE);
}

void drawTweakView() {
  sprite.fillRect(0, STICKY_BAR_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, TFT_BLACK);
  drawTweakViewSliders();
  sprite.pushSprite(0, 0);
}


#endif