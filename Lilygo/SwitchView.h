#ifndef SWITCH_VIEW_H
#define SWITCH_VIEW_H

void redrawView1();

void drawSwitchesView() {
  // UP
  sprite.drawString("SHOE 1", 20 - view1scrollY, STICKY_BAR_HEIGHT + 10, 2);
  sprite.drawRoundRect(20 - view1scrollY, STICKY_BAR_HEIGHT + 30, 80, 30, 15, TFT_GREEN);
  sprite.fillRoundRect(20 - view1scrollY + (switch1 * 50), STICKY_BAR_HEIGHT + 30, 30, 30, 15, TFT_GREEN);

  sprite.drawString("ARM 1", SPACE_BETWEEN_SWITCH + 20 - view1scrollY, STICKY_BAR_HEIGHT + 10, 2);
  sprite.drawRoundRect(SPACE_BETWEEN_SWITCH + 20 - view1scrollY, STICKY_BAR_HEIGHT + 30, 80, 30, 15, TFT_BLUE);
  sprite.fillRoundRect(SPACE_BETWEEN_SWITCH + 20 - view1scrollY + (switch2 * 50), STICKY_BAR_HEIGHT + 30, 30, 30, 15, TFT_BLUE);

  sprite.drawString("COAT", SPACE_BETWEEN_SWITCH * 2 + 20 - view1scrollY, STICKY_BAR_HEIGHT + 10, 2);
  sprite.drawRoundRect(SPACE_BETWEEN_SWITCH * 2 + 20 - view1scrollY, STICKY_BAR_HEIGHT + 30, 80, 30, 15, TFT_RED);
  sprite.fillRoundRect(SPACE_BETWEEN_SWITCH * 2 + 20 - view1scrollY + (switch3 * 50), STICKY_BAR_HEIGHT + 30, 30, 30, 15, TFT_RED);

  // DOWN
  sprite.drawString("SHOE 2", 20 - view1scrollY, STICKY_BAR_HEIGHT + 10 + 60, 2);
  sprite.drawRoundRect(20 - view1scrollY, STICKY_BAR_HEIGHT + 30 + 60, 80, 30, 15, TFT_YELLOW);
  sprite.fillRoundRect(20 - view1scrollY + (switch4 * 50), STICKY_BAR_HEIGHT + 30 + 60, 30, 30, 15, TFT_YELLOW);

  sprite.drawString("ARM 2", SPACE_BETWEEN_SWITCH + 20 - view1scrollY, STICKY_BAR_HEIGHT + 10 + 60, 2);
  sprite.drawRoundRect(SPACE_BETWEEN_SWITCH + 20 - view1scrollY, STICKY_BAR_HEIGHT + 30 + 60, 80, 30, 15, TFT_PURPLE);
  sprite.fillRoundRect(SPACE_BETWEEN_SWITCH + 20 - view1scrollY + (switch5 * 50), STICKY_BAR_HEIGHT + 30 + 60, 30, 30, 15, TFT_PURPLE);

  sprite.drawString("HEAD-BAND", SPACE_BETWEEN_SWITCH * 2 + 20 - view1scrollY, STICKY_BAR_HEIGHT + 10 + 60, 2);
  sprite.drawRoundRect(SPACE_BETWEEN_SWITCH * 2 + 20 - view1scrollY, STICKY_BAR_HEIGHT + 30 + 60, 80, 30, 15, TFT_PINK);
  sprite.fillRoundRect(SPACE_BETWEEN_SWITCH * 2 + 20 - view1scrollY + (switch6 * 50), STICKY_BAR_HEIGHT + 30 + 60, 30, 30, 15, TFT_PINK);
}

void handleScrollingView1(int touchY, float deltaTime) {
  if (activeButton == 1) {
    int deltaY = touchY - lastTouchY;

    if (abs(deltaY) > MOVE_THRESHOLD) {  // Threshold to start scrolling
      isScrolling = true;
      view1scrollY -= deltaY;                                                    // Update scroll position
      view1scrollY = constrain(view1scrollY, 0, VIRTUAL_HEIGHT - SCREEN_WIDTH);  // Constrain scroll position
      lastTouchY = touchY;
      velocityY = deltaY / deltaTime;
      redrawView1();
    }
  }
}

void scrollMomentumView1(float deltaTime) {
  if (abs(velocityY) > MIN_VELOCITY) {
    view1scrollY -= velocityY * deltaTime;                                     // Update scroll position with velocity
    view1scrollY = constrain(view1scrollY, 0, VIRTUAL_HEIGHT - SCREEN_WIDTH);  // Constrain scroll position
    velocityY *= FRICTION;
    redrawView1();
  } else {
    velocityY = 0;  // Stop scrolling if velocity is very low
  }
}

void redrawView1() {
  sprite.fillRect(0, STICKY_BAR_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, TFT_BLACK);
  drawSwitchesView();
  sprite.pushSprite(0, 0);
}


#endif  // SWITCH_VIEW_H