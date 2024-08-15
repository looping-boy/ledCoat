// #define TOUCH_MODULES_CST_SELF
#include "Constant.h"
#include "ColorUtils.h"
#include "Tabs.h"
#include "ColorView.h"
#include "SwitchView.h"
#include "BPMView.h"
#include "TweakView.h"
#include "PatternView.h"
#include "ESPSender.h"

unsigned long lastTouchTime = 0;
const unsigned long screenTimeout = 1000000;
// bool screenOn = true;
unsigned long beatMillis = 0;
unsigned long UIMillis = 0;
unsigned long intervalUI = 1000 / 5;

// // Variables to handle scrolling and momentum
unsigned long lastUpdateTime = 0;
unsigned long touchStartTime = 0;

void draw(int page);

void setup() {
  // SCREEN PREP
  pinMode(PIN_POWER_ON, OUTPUT);
  digitalWrite(PIN_POWER_ON, HIGH);
  pinMode(PIN_TOUCH_RES, OUTPUT);
  digitalWrite(PIN_TOUCH_RES, LOW);
  delay(500);
  digitalWrite(PIN_TOUCH_RES, HIGH);
  ledcSetup(0, 10000, 8);
  ledcAttachPin(PIN_LCD_BL, 0);
  ledcWrite(0, backLight);
  tft.begin();
  tft.setRotation(1);
  sprite.createSprite(320, 170);
  sprite.setTextColor(TFT_WHITE, TFT_BLACK);
  Wire.begin(PIN_IIC_SDA, PIN_IIC_SCL);
  draw(activeButton);

  // STOP SCREEN PREP
  pinMode(PIN_LCD_BL, OUTPUT);

  // ESPNOW PREP
  setupESP();

  // INIT
  hueSelected = findSelectedHueInColorBar(cursorPosition);
  colorSelected = findSelectedColorInColorBar(cursorPosition);
  //draw(activeButton);
  lastTouchTime = millis();  // Initialize last touch time
}


void draw(int page) {
  activeButton = page;
  sprite.fillSprite(TFT_BLACK);

  // Draw the sticky bar
  sprite.fillRect(0, 0, SCREEN_WIDTH, STICKY_BAR_HEIGHT, STICKY_BAR_COLOR);

  // Draw buttons on the sticky bar
  drawButton(0, 0, "B1", 1);
  drawButton((BUTTON_SIZE + SPACE), 0, "B2", 2);
  drawButton((BUTTON_SIZE + SPACE) * 2, 0, "B3", 3);
  drawButton((BUTTON_SIZE + SPACE) * 3, 0, "B4", 4);
  drawButton((BUTTON_SIZE + SPACE) * 4, 0, "B5", 5);

  // Draw different views based on the active button
  switch (page) {
    case 1:
      drawSwitchesView();
      break;
    case 2:
      drawTweakView();
      break;
    case 3:
      drawColorPickerView();
      break;
    case 4:
      drawBPMView();
      break;
    case 5:
      drawPatternView();
      break;
    default:
      break;
  }
  sprite.pushSprite(0, 0);
}

void loop() {

  unsigned long currentTime = millis();

  if (currentTime - UIMillis >= intervalUI) {
    UIMillis = currentTime;

    // Backlight Screen Brightness
    if (digitalRead(14) == 0 && backLight < 240) {
      backLight += 10;
      ledcSetup(0, 10000, 8);
      ledcAttachPin(PIN_LCD_BL, 0);
      ledcWrite(0, backLight);
    }
    if (digitalRead(0) == 0 && backLight > 10) {
      backLight -= 10;
      ledcSetup(0, 10000, 8);
      ledcAttachPin(PIN_LCD_BL, 0);
      ledcWrite(0, backLight);
    }

    // Anim pattern screen
    // if (activeButton == 5) {
    //   drawSelectedColor();
    //   drawAlertColorAnim();
    //   drawHorizontalBarColorAnim();
    //   drawVerticalBarColorAnim();
    //   drawDiagonalBarColorAnim();
    //   drawCircularBarColorAnim();
    //   drawCrossBarColorAnim();
    //   drawZigZagBarColorAnim();
    // }
  }

  unsigned long intervalBPM = 60000 / bpmMain;  // Interval between beats in milliseconds

  // Check if the current time has passed the interval time
  if (isBPMMode) {
    if (currentTime - beatMillis >= intervalBPM) {
      beatMillis = currentTime;
      inTheSelectedAnims++;
      uint8_t inThe = inTheSelectedAnims % numSelectedAnims;
      sendValue(MESSAGE_TYPE_PATTERN, selectedAnims[inThe]);
    }
  }

  if (touch.read()) {
    if (deb == 0) {
      deb = 1;
      TP_Point t = touch.getPoint(0);
      if (t.x < 170)
        handleUnTouch(t.x, t.y, currentTime);
      //draw(t.x,t.y);
    }
  } else {
    delay(20);
    deb = 0;
  }
}

void handleUnTouch(int x, int y, unsigned long currentTime) {

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
    } else if (transformedY >= (BUTTON_SIZE + SPACE) && transformedY < (BUTTON_SIZE + SPACE) + BUTTON_SIZE) {
      (activeButton == 2) ? null() : draw(2);
    } else if (transformedY >= (BUTTON_SIZE + SPACE) * 2 && transformedY < (BUTTON_SIZE + SPACE) * 2 + BUTTON_SIZE) {
      (activeButton == 3) ? null() : draw(3);
    } else if (transformedY >= (BUTTON_SIZE + SPACE) * 3 && transformedY < (BUTTON_SIZE + SPACE) * 3 + BUTTON_SIZE) {
      (activeButton == 4) ? null() : draw(4);
    } else if (transformedY >= (BUTTON_SIZE + SPACE) * 4 && transformedY < (BUTTON_SIZE + SPACE) * 4 + BUTTON_SIZE) {
      (activeButton == 5) ? null() : draw(5);
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
    } else if (activeButton == 2) {
      if (transformedY >= 20 && transformedY < 20 + 80) {
        if (transformedX >= STICKY_BAR_HEIGHT + 30 && transformedX < STICKY_BAR_HEIGHT + 30 + 30) {
          tweak1 = (tweak1 % 7) + 1;
          sendValue(MESSAGE_TWEAK_QUANTITY, (uint8_t)pow(2, tweak1));
          drawTweakView();
        } else if (transformedX >= STICKY_BAR_HEIGHT + 30 + 60 && transformedX < STICKY_BAR_HEIGHT + 30 + 30 + 60) {
          tweak4 = (tweak4 % 7) + 1;
          sendValue(MESSAGE_TWEAK_PHASE, (uint8_t)tweak4);
          drawTweakView();
        }
      } else if (transformedY >= SPACE_BETWEEN_SWITCH + 20 && transformedY < SPACE_BETWEEN_SWITCH + 20 + 80) {
        if (transformedX >= STICKY_BAR_HEIGHT + 30 && transformedX < STICKY_BAR_HEIGHT + 30 + 30) {
          tweak2 = (tweak2 % 7) + 1;
          sendValue(MESSAGE_TWEAK_BPM, (uint8_t)pow(2, tweak2));
          drawTweakView();
        } else if (transformedX >= STICKY_BAR_HEIGHT + 30 + 60 && transformedX < STICKY_BAR_HEIGHT + 30 + 30 + 60) {
          // Nothing yet
        }
      } else if (transformedY >= SPACE_BETWEEN_SWITCH * 2 + 20 && transformedY < SPACE_BETWEEN_SWITCH * 2 + 20 + 80) {
        if (transformedX >= STICKY_BAR_HEIGHT + 30 && transformedX < STICKY_BAR_HEIGHT + 30 + 30) {
          tweak3 = (tweak3 % 7) + 1;
          sendValue(MESSAGE_TWEAK_COLOR, (uint8_t)pow(2, tweak3));
          drawTweakView();
        } else if (transformedX >= STICKY_BAR_HEIGHT + 30 + 60 && transformedX < STICKY_BAR_HEIGHT + 30 + 30 + 60) {
          // Nothing yet
        }
      }
    } else if (activeButton == 3) {  // VIEW 3
      handleColorTabClick(transformedX, transformedY);
    } else if (activeButton == 4) {  // VIEW 3
      bpmMain = BPMViewEvent();
    } else if (activeButton == 5) {  // VIEW 3
      handlePatternViewClick(transformedX, transformedY);
    }
  }
}

// void loop() {

//   unsigned long currentTime = millis();
//   float deltaTime = (currentTime - lastUpdateTime) / 1000.0;
//   lastUpdateTime = currentTime;

//   unsigned long interval = 60000 / bpmMain;  // Interval between beats in milliseconds
//   //srand(time(NULL)); // Seed the random number generator

//   // Check if the current time has passed the interval time
//   if (currentTime - beatMillis >= interval) {
//     beatMillis = currentTime;
//     x++;
//     sendValue(x % 4 + 1) ;
//   }









// ANIMATIONS ON THE PAGES

// TP_Point t = touch.getPoint(0);
// handleUnTouch(t.x, t.y);

// TOUCH :
//   if (touch.read()) {
//     // lastTouchTime = millis();
//     // (screenOn) ? ifScreenOn(deltaTime, currentTime) : ifScreenOff();
//   } else {

//     // TP_Point t = touch.getPoint(0);
//     // handleUnTouch(t.x, t.y);
//     // Untouch
//     // ifOnFingerUntouch(currentTime);

//     // Scroll momentum
//     //scrollMomentumView1(deltaTime);

//     // Sleep mode
//     // if (screenOn && millis() - lastTouchTime > screenTimeout) {
//     //   screenOn = false;
//     //   tft.writecommand(TFT_DISPOFF);
//     //   digitalWrite(PIN_LCD_BL, LOW);
//     // }
//   }

//   //delay(10);
// }

// void ifScreenOff() {
//   screenOn = true;
//   digitalWrite(PIN_LCD_BL, HIGH);
//   tft.writecommand(TFT_DISPON);  // Turn on the screen
//   sprite.pushSprite(0, 0);       // Refresh screen content
// }

// void ifScreenOn(float deltaTime, unsigned long currentTime) {
//   TP_Point t = touch.getPoint(0);
//   // Check if the touch is within the screen bounds
//   if (t.x < SCREEN_HEIGHT) {
//     int touchY = t.y;
//     if (lastTouchY == -1) {
//       // Starting a touch
//       lastTouchY = touchY;
//       touchActive = true;
//       isScrolling = false;
//       velocityY = 0;                 // Reset velocity when new touch
//       touchStartTime = currentTime;  // Record the start time of the touch
//     } else {
//       //handleScrollingView1(touchY, deltaTime);
//     }
//   }
// }

// void ifOnFingerUntouch(unsigned long currentTime) {
//   if (touchActive) {
//     // Handle normal touch
//     // if (!isScrolling) {
//     //   TP_Point t = touch.getPoint(0);
//     //   handleUnTouch(t.x, t.y);
//     // }

//     if (activeButton == 4) {
//      bpmMain = BPMViewEvent();

//      //sendValue(pattern);
//     }

//     // Check if the touch was a hold without significant movement
//     // if (currentTime - touchStartTime > HOLD_THRESHOLD && abs(lastTouchY - touch.getPoint(0).y) <= MOVE_THRESHOLD) {
//     //   velocityY = 0;
//     // }

//     // End of touch
//     lastTouchY = -1;
//     touchActive = false;
//   }
// }

void null() {
}
