#include <sys/_stdint.h>
// ColorTab.h
#ifndef CONSTANT_H
#define CONSTANT_H

#include "Arduino.h"
#include "TFT_eSPI.h"

// Scroll
#define FRICTION 0.95       // Friction factor for slowing down
#define MIN_VELOCITY 0.1    // Minimum velocity to stop scrolling
#define HOLD_THRESHOLD 200  // Time in milliseconds to consider a hold
#define MOVE_THRESHOLD 5    // Minimum movement to consider a scroll

#define PIN_LCD_BL 38
#define PIN_BUTTON_1 0
#define PIN_BUTTON_2 14
#define PIN_BAT_VOLT 4
#define PIN_LCD_BL 38
#define PIN_POWER_ON 15
#define PIN_IIC_SCL 17
#define PIN_IIC_SDA 18
#define PIN_TOUCH_INT 16
#define PIN_TOUCH_RES 21

#define TOUCH_MODULES_CST_SELF
#include "Arduino.h"
#include "TFT_eSPI.h" /* Please use the TFT library provided in the library. */
#include "TouchLib.h"
#include "Wire.h"
#include "pin_config.h"

TouchLib touch(Wire, PIN_IIC_SDA, PIN_IIC_SCL, CTS820_SLAVE_ADDRESS, PIN_TOUCH_RES);

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

// Constants
const int STICKY_BAR_HEIGHT = 40;
const int SPACE_BETWEEN_SWITCH = 100;
const int STICKY_BAR_COLOR = TFT_BLACK;
const int BUTTON_SIZE = 40;
const int BIG_BUTTON_SIZE = 90;

// Scroll offset
int view1scrollY = 0;

// State values
int deb = 0;
bool switch1 = true;
bool switch2 = false;
bool switch3 = true;
bool switch4 = true;
bool switch5 = false;
bool switch6 = true;

// Define the scrollable area
const int VIRTUAL_WIDTH = 210;   // Adjusted to include sticky bar and screen width
const int VIRTUAL_HEIGHT = 480;  // Larger than the screen height
const int SCREEN_HEIGHT = 170;
const int SCREEN_WIDTH = 320;

// Velocity
float velocityY = 0;
bool isScrolling = false;
int lastTouchY = -1;

// Variables for touch handling
bool touchActive = false;
int cursorPosition = 150;  // Position of the cursor on the bar

// State value
int colorSelected = 0;
boolean isBPMMode = false;
uint8_t activeButton = 3;

// Anim values
uint8_t bpmMain = 120;

#endif