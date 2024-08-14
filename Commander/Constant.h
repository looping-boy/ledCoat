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

// Constants
#define TAB_WIDTH                    280
#define TAB_HEIGHT                   40
#define SMALL_INSIDE_SIZE            26
#define INSIDE_SIZE                  36
#define COLOR_BAR_HEIGHT             20
#define OPACITY_BAR_HEIGHT           20
#define COLOR_BAR_COMPONENTS         40
#define OPACITY_BAR_COMPONENTS       40
#define M_20                         20
#define M_0                          4
#define M_40                         40
#define GAP                          2
#define SPACE                        10
#define OPACITY_BAR_SHORTER          70
#define FORCE_BUTTON_WIDTH           60
#define FORCE_BUTTON_HEIGHT          30
#define STICKY_BAR_HEIGHT            40
#define SPACE_BETWEEN_SWITCH         100
#define BUTTON_SIZE                  40
#define BIG_BUTTON_SIZE              90
#define SMALL_BUTTON_SIZE            30
const int STICKY_BAR_COLOR = TFT_BLACK;
const int TEXT_HEIGHT = M_20;
const int DOWN_TEXT_Y_OFFSET    = TAB_HEIGHT + SPACE + COLOR_BAR_COMPONENTS + SPACE;
const int DOWN_BUTTONS_Y_OFFSET = TAB_HEIGHT + SPACE + COLOR_BAR_COMPONENTS + SPACE + TEXT_HEIGHT;
const int OPACITY_Y_OFFSET      = DOWN_BUTTONS_Y_OFFSET + INSIDE_SIZE + SPACE;
const int SECOND_LINE = TAB_HEIGHT + SPACE + SMALL_BUTTON_SIZE + SPACE;
const int THIRD_LINE = SECOND_LINE + SMALL_BUTTON_SIZE + SPACE;

// Define the scrollable area
#define VIRTUAL_WIDTH 210   // Adjusted to include sticky bar and screen width
#define VIRTUAL_HEIGHT 480  // Larger than the screen height
#define SCREEN_HEIGHT 170
#define SCREEN_WIDTH 320


#define TOUCH_MODULES_CST_SELF
#include "Arduino.h"
#include "TFT_eSPI.h" /* Please use the TFT library provided in the library. */
#include "TouchLib.h"
#include "Wire.h"
#include "pin_config.h"

TouchLib touch(Wire, PIN_IIC_SDA, PIN_IIC_SCL, CTS820_SLAVE_ADDRESS, PIN_TOUCH_RES);

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

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

// Tweak view
uint8_t tweak1 = 4;
uint8_t tweak2 = 4;
uint8_t tweak3 = 4;
uint8_t tweak4 = 1;
uint8_t tweak5 = 1;
uint8_t tweak6 = 1;

// Velocity
float velocityY = 0;
bool isScrolling = false;
int lastTouchY = -1;

// Variables for touch handling
bool touchActive = false;
int cursorPosition = 150;  // Position of the cursor on the bar
int opacityPosition = 50;

// State value
uint8_t hueSelected = 150;
uint8_t opacitySelected = 20;
uint32_t colorSelected = 0;
bool isForcedBrightness = false;
bool isBPMMode = false;
uint8_t activeButton = 3;

// Anim values
uint8_t bpmMain = 120;

// Screen Backlight Brightness
uint8_t backLight = 50;


// PATTERNS 
#define EASY                         0
#define ALERT                        1
#define SWEEP_VERTICAL_BAR           2
#define SWEEP_HORIZONTAL_BAR         3
#define SWEEP_DIAGONAL_BAR           4
#define SWEEP_ZIGZAG_BAR             5
#define SWEEP_CIRCULAR_BAR           6
#define SWEEP_CROSS_BAR              7


#endif