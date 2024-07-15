#include <sys/_stdint.h>
// ColorTab.h
#ifndef CONSTANT_H
#define CONSTANT_H

#include "Arduino.h"
#include "TFT_eSPI.h" 
#include "TouchLib.h"
#include "Wire.h"
#include "pin_config.h"

// Scroll
#define FRICTION 0.95       // Friction factor for slowing down
#define MIN_VELOCITY 0.1    // Minimum velocity to stop scrolling
#define HOLD_THRESHOLD 200  // Time in milliseconds to consider a hold
#define MOVE_THRESHOLD 5    // Minimum movement to consider a scroll

TouchLib touch(Wire, PIN_IIC_SDA, PIN_IIC_SCL, CTS820_SLAVE_ADDRESS, PIN_TOUCH_RES);

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

// Constants
const int STICKY_BAR_HEIGHT = 40;
const int SPACE_BETWEEN_SWITCH = 100;
const int STICKY_BAR_COLOR = TFT_BLACK;
const int BUTTON_SIZE = 40;

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

#endif