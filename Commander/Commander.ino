#define TOUCH_MODULES_CST_SELF
#include "Constant.h"
#include "Arduino.h"
#include "TFT_eSPI.h" /* Please use the TFT library provided in the library. */
#include "TouchLib.h"
#include "Wire.h"
#include "pin_config.h"
#include "Tabs.h"
#include "ColorView.h"
#include "SwitchView.h"
#include "ESPSender.h"

#define PIN_LCD_BL 38

unsigned long lastTouchTime = 0;
const unsigned long screenTimeout = 1000000;
bool screenOn = true;

// Variables to handle scrolling and momentum
unsigned long lastUpdateTime = 0;
unsigned long touchStartTime = 0;

void setup() {
  pinMode(PIN_POWER_ON, OUTPUT);
  digitalWrite(PIN_POWER_ON, HIGH);
  pinMode(PIN_TOUCH_RES, OUTPUT);
  digitalWrite(PIN_TOUCH_RES, LOW);
  delay(500);
  digitalWrite(PIN_TOUCH_RES, HIGH);
  tft.begin();
  setupESP();
  tft.setRotation(1);
  sprite.createSprite(320, 170);
  sprite.setTextColor(TFT_WHITE);
  Wire.begin(PIN_IIC_SDA, PIN_IIC_SCL);
  colorSelected = findSelectedColorInColorBar(cursorPosition);
  draw(activeButton);
  pinMode(PIN_LCD_BL, OUTPUT);
  lastTouchTime = millis();  // Initialize last touch time
}

void draw(uint8_t page) {
  activeButton = page;
  sprite.fillSprite(TFT_BLACK);

  // Draw the sticky bar
  sprite.fillRect(0, 0, SCREEN_WIDTH, STICKY_BAR_HEIGHT, STICKY_BAR_COLOR);

  // Draw buttons on the sticky bar
  drawButton(0, 0, "B1", 1);
  drawButton(50, 0, "B2", 2);
  drawButton(100, 0, "B3", 3);

  // Draw different views based on the active button
  switch (activeButton) {
    case 1:
      drawSwitchesView();
      break;
    case 2:
      drawTextView();
      break;
    case 3:
      drawColorPickerView(cursorPosition);
      break;
    default:
      break;
  }

  sprite.pushSprite(0, 0);
}


void drawTextView() {
  sprite.setTextColor(TFT_WHITE);
  sprite.setTextSize(2);
  sprite.drawString("This is a text view", STICKY_BAR_HEIGHT + 10, SCREEN_WIDTH / 2 - 10);
}


void handleUnTouch(int x, int y) {

  // For static views
  int transformedY = y;
  int transformedX = SCREEN_HEIGHT - x;

  // For scrolling views
  int virtualX = transformedX;
  int virtualY = transformedY + view1scrollY;

  // BUTTONS
  if (transformedX < STICKY_BAR_HEIGHT) {
    if (transformedY >= 0 && transformedY < BUTTON_SIZE) {
      (activeButton == 1) ? null() : draw(1);
      sendValue(1);
    } else if (transformedY >= 50 && transformedY < 50 + BUTTON_SIZE) {
      (activeButton == 2) ? null() : draw(2);
      sendValue(2);
    } else if (transformedY >= 100 && transformedY < 100 + BUTTON_SIZE) {
      (activeButton == 3) ? null() : draw(3);
      sendValue(3);
    }
  }
  // VIEWS
  else {
    if (activeButton == 1) {  // VIEW 1
      if (virtualY >= 20 && virtualY < 20 + 80) {
        if (virtualX >= STICKY_BAR_HEIGHT + 30 && virtualX < STICKY_BAR_HEIGHT + 30 + 30) {
          switch1 = !switch1;
          redrawView1();
        } else if (virtualX >= STICKY_BAR_HEIGHT + 30 + 60 && virtualX < STICKY_BAR_HEIGHT + 30 + 30 + 60) {
          switch4 = !switch4;
          redrawView1();
        }
      } else if (virtualY >= SPACE_BETWEEN_SWITCH + 20 && virtualY < SPACE_BETWEEN_SWITCH + 20 + 80) {
        if (virtualX >= STICKY_BAR_HEIGHT + 30 && virtualX < STICKY_BAR_HEIGHT + 30 + 30) {
          switch2 = !switch2;
          redrawView1();
        } else if (virtualX >= STICKY_BAR_HEIGHT + 30 + 60 && virtualX < STICKY_BAR_HEIGHT + 30 + 30 + 60) {
          switch5 = !switch5;
          redrawView1();
        }
      } else if (virtualY >= SPACE_BETWEEN_SWITCH * 2 + 20 && virtualY < SPACE_BETWEEN_SWITCH * 2 + 20 + 80) {
        if (virtualX >= STICKY_BAR_HEIGHT + 30 && virtualX < STICKY_BAR_HEIGHT + 30 + 30) {
          switch3 = !switch3;
          redrawView1();
        } else if (virtualX >= STICKY_BAR_HEIGHT + 30 + 60 && virtualX < STICKY_BAR_HEIGHT + 30 + 30 + 60) {
          switch6 = !switch6;
          redrawView1();
        }
      }
    } else if (activeButton == 2) {  // VIEW 2

    } else if (activeButton == 3) {  // VIEW 3
      handleColorTabClick(transformedX, transformedY);
    }
  }
}

void loop() {

  unsigned long currentTime = millis();
  float deltaTime = (currentTime - lastUpdateTime) / 1000.0;
  lastUpdateTime = currentTime;

  // ANIMATIONS ON THE PAGES :
  if (activeButton == 3) {
    drawAlertColorAnim(cursorPosition, currentTime);
    drawHorizontalBarColorAnim(cursorPosition, currentTime);
    drawVerticalBarColorAnim(cursorPosition, currentTime);
    drawDiagonalBarColorAnim(cursorPosition, currentTime);
    //drawMultiColorAnim(cursorPosition, currentTime);
    delay(15);
  }

  // TOUCH :
  if (touch.read()) {
    lastTouchTime = millis();
    (screenOn) ? ifScreenOn(deltaTime, currentTime) : ifScreenOff();
  } else {

    // Untouch
    ifOnFingerUntouch(currentTime);

    // Scroll momentum
    scrollMomentumView1(deltaTime);

    // Sleep mode
    if (screenOn && millis() - lastTouchTime > screenTimeout) {
      screenOn = false;
      tft.writecommand(TFT_DISPOFF);
      digitalWrite(PIN_LCD_BL, LOW);
    }
  }

  delay(10);
}

void ifScreenOff() {
  screenOn = true;
  digitalWrite(PIN_LCD_BL, HIGH);
  tft.writecommand(TFT_DISPON);  // Turn on the screen
  sprite.pushSprite(0, 0);       // Refresh screen content
}

void ifScreenOn(float deltaTime, unsigned long currentTime) {
  TP_Point t = touch.getPoint(0);
  // Check if the touch is within the screen bounds
  if (t.x < SCREEN_HEIGHT) {
    int touchY = t.y;
    if (lastTouchY == -1) {
      // Starting a touch
      lastTouchY = touchY;
      touchActive = true;
      isScrolling = false;
      velocityY = 0;                 // Reset velocity when new touch
      touchStartTime = currentTime;  // Record the start time of the touch
    } else {
      handleScrollingView1(touchY, deltaTime);
    }
  }
}

void ifOnFingerUntouch(unsigned long currentTime) {
  if (touchActive) {
    // Handle normal touch
    if (!isScrolling) {
      TP_Point t = touch.getPoint(0);
      handleUnTouch(t.x, t.y);
    }

    // Check if the touch was a hold without significant movement
    if (currentTime - touchStartTime > HOLD_THRESHOLD && abs(lastTouchY - touch.getPoint(0).y) <= MOVE_THRESHOLD) {
      velocityY = 0;
    }

    // End of touch
    lastTouchY = -1;
    touchActive = false;
  }
}

void null() {
  
}
