#define TOUCH_MODULES_CST_SELF
#include "Constant.h"
#include "Arduino.h"
#include "TFT_eSPI.h" /* Please use the TFT library provided in the library. */
#include "TouchLib.h"
#include "Wire.h"
#include "pin_config.h"
#include "ColorTab.h"


#define PIN_LCD_BL 38

#define FRICTION 0.95       // Friction factor for slowing down
#define MIN_VELOCITY 0.1    // Minimum velocity to stop scrolling
#define HOLD_THRESHOLD 200  // Time in milliseconds to consider a hold
#define MOVE_THRESHOLD 5    // Minimum movement to consider a scroll

unsigned long lastTouchTime = 0;
const unsigned long screenTimeout = 1000000;
bool screenOn = true;



// Define the scrollable area
const int VIRTUAL_WIDTH = 210;   // Adjusted to include sticky bar and screen width
const int VIRTUAL_HEIGHT = 480;  // Larger than the screen height
const int SCREEN_HEIGHT = 170;
const int SCREEN_WIDTH = 320;

// Sticky bar dimensions

const int STICKY_BAR_COLOR = TFT_BLACK;
const int BUTTON_SIZE = 40;
const int BUTTON_MARGIN = 5;
const int BUTTON_COLOR_INACTIVE = TFT_WHITE;
const int BUTTON_COLOR_ACTIVE = TFT_GREEN;

const int SPACE_BETWEEN_SWITCH = 100;

// Scroll offset
int scrollX = 0;
int scrollY = 0;

// Variables for touch handling
int lastTouchY = -1;
bool isScrolling = false;
bool touchActive = false;
int activeButton = 3;  // 0: None, 1: B1, 2: B2, 3: B3

int cursorPosition = 150;  // Position of the cursor on the bar

// State values
int deb = 0;
bool switch1 = true;
bool switch2 = false;
bool switch3 = true;
bool switch4 = true;
bool switch5 = false;
bool switch6 = true;
int colorSelected = findSelectedColorInColorBar(cursorPosition);

void setup() {
  pinMode(PIN_POWER_ON, OUTPUT);
  digitalWrite(PIN_POWER_ON, HIGH);
  pinMode(PIN_TOUCH_RES, OUTPUT);
  digitalWrite(PIN_TOUCH_RES, LOW);
  delay(500);
  digitalWrite(PIN_TOUCH_RES, HIGH);
  tft.begin();
  tft.setRotation(1);
  sprite.createSprite(320, 170);
  sprite.setTextColor(TFT_WHITE, TFT_BLACK);
  Wire.begin(PIN_IIC_SDA, PIN_IIC_SCL);
  draw();
  pinMode(PIN_LCD_BL, OUTPUT);
  lastTouchTime = millis();  // Initialize last touch time
}

void draw() {
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

void drawButton(int x, int y, const char* label, int buttonId) {
  int buttonColor = (buttonId == activeButton) ? TFT_GREEN : TFT_BLACK;
  int borderColor = TFT_WHITE;  // Color of the border/stroke

  // Draw the button background with rounded corners
  sprite.fillRoundRect(x, y, BUTTON_SIZE, BUTTON_SIZE, 8, buttonColor);  // 8 is the radius for rounded corners

  // Draw the border around the button
  sprite.drawRoundRect(x, y, BUTTON_SIZE, BUTTON_SIZE, 8, borderColor);  // 8 is the radius for rounded corners

  // Set text color and size
  sprite.setTextColor(TFT_WHITE, buttonColor);
  sprite.setTextSize(1);  // Smaller text size

  // Draw the button label (text)
  int textWidth = sprite.textWidth(label);
  int textHeight = sprite.fontHeight();
  int textX = x + (BUTTON_SIZE - textWidth) / 2;
  int textY = y + (BUTTON_SIZE - textHeight) / 2;
  sprite.drawString(label, textX, textY);
}


void drawSwitchesView() {
  // UP
  sprite.drawString("SHOE 1", 20 - scrollY, STICKY_BAR_HEIGHT + 10, 2);
  sprite.drawRoundRect(20 - scrollY, STICKY_BAR_HEIGHT + 30, 80, 30, 15, TFT_GREEN);
  sprite.fillRoundRect(20 - scrollY + (switch1 * 50), STICKY_BAR_HEIGHT + 30, 30, 30, 15, TFT_GREEN);

  sprite.drawString("ARM 1", SPACE_BETWEEN_SWITCH + 20 - scrollY, STICKY_BAR_HEIGHT + 10, 2);
  sprite.drawRoundRect(SPACE_BETWEEN_SWITCH + 20 - scrollY, STICKY_BAR_HEIGHT + 30, 80, 30, 15, TFT_BLUE);
  sprite.fillRoundRect(SPACE_BETWEEN_SWITCH + 20 - scrollY + (switch2 * 50), STICKY_BAR_HEIGHT + 30, 30, 30, 15, TFT_BLUE);

  sprite.drawString("COAT", SPACE_BETWEEN_SWITCH * 2 + 20 - scrollY, STICKY_BAR_HEIGHT + 10, 2);
  sprite.drawRoundRect(SPACE_BETWEEN_SWITCH * 2 + 20 - scrollY, STICKY_BAR_HEIGHT + 30, 80, 30, 15, TFT_RED);
  sprite.fillRoundRect(SPACE_BETWEEN_SWITCH * 2 + 20 - scrollY + (switch3 * 50), STICKY_BAR_HEIGHT + 30, 30, 30, 15, TFT_RED);

  // DOWN
  sprite.drawString("SHOE 2", 20 - scrollY, STICKY_BAR_HEIGHT + 10 + 60, 2);
  sprite.drawRoundRect(20 - scrollY, STICKY_BAR_HEIGHT + 30 + 60, 80, 30, 15, TFT_YELLOW);
  sprite.fillRoundRect(20 - scrollY + (switch4 * 50), STICKY_BAR_HEIGHT + 30 + 60, 30, 30, 15, TFT_YELLOW);

  sprite.drawString("ARM 2", SPACE_BETWEEN_SWITCH + 20 - scrollY, STICKY_BAR_HEIGHT + 10 + 60, 2);
  sprite.drawRoundRect(SPACE_BETWEEN_SWITCH + 20 - scrollY, STICKY_BAR_HEIGHT + 30 + 60, 80, 30, 15, TFT_PURPLE);
  sprite.fillRoundRect(SPACE_BETWEEN_SWITCH + 20 - scrollY + (switch5 * 50), STICKY_BAR_HEIGHT + 30 + 60, 30, 30, 15, TFT_PURPLE);

  sprite.drawString("HEAD-BAND", SPACE_BETWEEN_SWITCH * 2 + 20 - scrollY, STICKY_BAR_HEIGHT + 10 + 60, 2);
  sprite.drawRoundRect(SPACE_BETWEEN_SWITCH * 2 + 20 - scrollY, STICKY_BAR_HEIGHT + 30 + 60, 80, 30, 15, TFT_PINK);
  sprite.fillRoundRect(SPACE_BETWEEN_SWITCH * 2 + 20 - scrollY + (switch6 * 50), STICKY_BAR_HEIGHT + 30 + 60, 30, 30, 15, TFT_PINK);
}

void drawTextView() {
  sprite.setTextColor(TFT_WHITE, TFT_BLACK);
  sprite.setTextSize(2);
  sprite.drawString("This is a text view", STICKY_BAR_HEIGHT + 10, SCREEN_WIDTH / 2 - 10);
}



void handleTouch(int x, int y) {
  // Example for a 90-degree clockwise rotation:
  // Original (x, y) -> Transformed (y, SCREEN_HEIGHT - x)

  // Adjust touch coordinates based on the screen rotation
  int transformedY = y;
  int transformedX = SCREEN_HEIGHT - x;

  int virtualX = transformedX;
  int virtualY = transformedY + scrollY;

  // Check if touch is within sticky bar buttons
  if (transformedX < STICKY_BAR_HEIGHT) {
    // Check button areas based on their actual position
    if (transformedY >= 0 && transformedY < BUTTON_SIZE) {                 // Button B1
      activeButton = (activeButton == 1) ? 0 : 1;                          // Toggle active state
    } else if (transformedY >= 50 && transformedY < 50 + BUTTON_SIZE) {    // Button B2
      activeButton = (activeButton == 2) ? 0 : 2;                          // Toggle active state
    } else if (transformedY >= 100 && transformedY < 100 + BUTTON_SIZE) {  // Button B3
      activeButton = (activeButton == 3) ? 0 : 3;                          // Toggle active state
    }
  } else {
    // Handle touch interactions for different views
    if (activeButton == 1) {                       // Switches view
      if (virtualY >= 20 && virtualY < 20 + 80) {  // Switch 1
        if (virtualX >= STICKY_BAR_HEIGHT + 30 && virtualX < STICKY_BAR_HEIGHT + 30 + 30) {
          switch1 = !switch1;
        } else if (virtualX >= STICKY_BAR_HEIGHT + 30 + 60 && virtualX < STICKY_BAR_HEIGHT + 30 + 30 + 60) {
          switch4 = !switch4;
        }
      } else if (virtualY >= SPACE_BETWEEN_SWITCH + 20 && virtualY < SPACE_BETWEEN_SWITCH + 20 + 80) {  // Switch 2
        if (virtualX >= STICKY_BAR_HEIGHT + 30 && virtualX < STICKY_BAR_HEIGHT + 30 + 30) {
          switch2 = !switch2;
        } else if (virtualX >= STICKY_BAR_HEIGHT + 30 + 60 && virtualX < STICKY_BAR_HEIGHT + 30 + 30 + 60) {
          switch5 = !switch5;
        }
      } else if (virtualY >= SPACE_BETWEEN_SWITCH * 2 + 20 && virtualY < SPACE_BETWEEN_SWITCH * 2 + 20 + 80) {  // Switch 3
        if (virtualX >= STICKY_BAR_HEIGHT + 30 && virtualX < STICKY_BAR_HEIGHT + 30 + 30) {
          switch3 = !switch3;
        } else if (virtualX >= STICKY_BAR_HEIGHT + 30 + 60 && virtualX < STICKY_BAR_HEIGHT + 30 + 30 + 60) {
          switch6 = !switch6;
        }
      }
    }
    if (activeButton == 3) {
      if (virtualY >= 20 && virtualY < 20 + COLOR_BAR_WIDTH) {
        if (virtualX >= STICKY_BAR_HEIGHT + 10 && virtualX < STICKY_BAR_HEIGHT + 10 + COLOR_BAR_HEIGHT) {
          colorSelected = findSelectedColorInColorBar(virtualY - 20);
          cursorPosition = virtualY - 20;
        }
      }
    }
    // Add more touch handling if needed for text or color picker
  }

  draw();  // Redraw content after interaction
}


// Variables to handle scrolling and momentum
float velocityY = 0;
unsigned long lastUpdateTime = 0;
unsigned long touchStartTime = 0;

void loop() {

  if (activeButton == 3) {
    uint32_t currentTime = millis(); // get the current time in milliseconds
    drawBreathingColor(cursorPosition, currentTime);
    delay(16); // approximately 60 frames per second
  }

  unsigned long currentTime = millis();
  float deltaTime = (currentTime - lastUpdateTime) / 1000.0;  // Time in seconds since last update
  lastUpdateTime = currentTime;

  if (touch.read()) {
    lastTouchTime = millis();  // Update last touch time
    if (!screenOn) {
      screenOn = true;
      digitalWrite(PIN_LCD_BL, HIGH);
      tft.writecommand(TFT_DISPON);  // Turn on the screen
      sprite.pushSprite(0, 0);       // Refresh screen content
    } else {
      TP_Point t = touch.getPoint(0);
      // Check if the touch is within the screen bounds
      if (t.x < SCREEN_HEIGHT) {
        int touchY = t.y;

        if (lastTouchY == -1) {
          // Starting a touch
          lastTouchY = touchY;
          touchActive = true;
          isScrolling = false;
          velocityY = 0;                 // Reset velocity when a new touch starts
          touchStartTime = currentTime;  // Record the start time of the touch
        } else {
          // Handle scrolling
          if (activeButton == 1) {
            int deltaY = touchY - lastTouchY;

            if (abs(deltaY) > MOVE_THRESHOLD) {  // Threshold to start scrolling
              isScrolling = true;
              scrollY -= deltaY;                                               // Update scroll position
              scrollY = constrain(scrollY, 0, VIRTUAL_HEIGHT - SCREEN_WIDTH);  // Constrain scroll position

              draw();               // Redraw content based on new scroll position
              lastTouchY = touchY;  // Update last touch position

              // Calculate the velocity
              velocityY = deltaY / deltaTime;
            }
          }
        }
      }
    }
  } else {
    if (touchActive) {
      if (!isScrolling) {
        // If touch ended and scrolling wasn't detected, handle as a click
        TP_Point t = touch.getPoint(0);
        handleTouch(t.x, t.y);
      }

      // Check if the touch was a hold without significant movement
      if (currentTime - touchStartTime > HOLD_THRESHOLD && abs(lastTouchY - touch.getPoint(0).y) <= MOVE_THRESHOLD) {
        // Reset velocity to prevent scrolling after a hold
        velocityY = 0;
      }

      // End of touch
      lastTouchY = -1;
      touchActive = false;
    }

    if (screenOn && millis() - lastTouchTime > screenTimeout) {
      screenOn = false;
      tft.writecommand(TFT_DISPOFF);
      digitalWrite(PIN_LCD_BL, LOW);  // Turn off the screen
    }


    // SCROLL MOMENTUM
    if (abs(velocityY) > MIN_VELOCITY) {
      scrollY -= velocityY * deltaTime;                                // Update scroll position with velocity
      scrollY = constrain(scrollY, 0, VIRTUAL_HEIGHT - SCREEN_WIDTH);  // Constrain scroll position
      draw();                                                          // Redraw content based on new scroll position
      velocityY *= FRICTION;                                           // Apply friction to velocity
    } else {
      velocityY = 0;  // Stop scrolling if velocity is very low
    }
  }

  delay(10);
}
