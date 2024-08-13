#ifndef BPM_VIEW_H
#define BPM_VIEW_H

const int BIG_BUTTONS_Y_OFFSET = TAB_HEIGHT + SPACE + TEXT_HEIGHT;




// Control modes
#define MODE_BRIGHTNESS 1
#define MODE_PATTERN 0
#define MODE_COLOR 3
#define MODE_MAX 3

// Colors
#define HUE_RED 0
#define HUE_YELLOW 65536/6
#define HUE_GREEN 65536/3
#define HUE_TEAL 65536/2
#define HUE_BLUE 65536/3*2
#define HUE_MAGENTA 65536/6*5

#define N_PATTERNS 4

const uint16_t HUES[] = {HUE_RED, HUE_YELLOW, HUE_GREEN, HUE_TEAL, HUE_BLUE, HUE_MAGENTA};

// state
uint8_t pattern = 1;
uint16_t hue_primary = 3;
uint16_t hue_secondary = 4;

// controls
uint8_t mode = MODE_PATTERN;
uint32_t leftButtonDown = 0;
uint32_t rightButtonDown = 0;
bool switchValue;
bool newSwitchValue = true;
bool combo = false;
uint32_t modeSelectionActive = 0;
uint8_t modeSelectionPressCount = 0;
uint32_t tapModeActive = 0;
uint8_t tapCount = 0;

// timing
uint32_t t;
uint8_t bpm = 120;
uint32_t timeOffset = 0;
float beatRatio;
uint16_t beatCounter;

float lastBeatRatio;  // used to detect if a new beat has started

#define MAX_BRIGHT 200
#define MIN_BRIGHT 50

#define MAX_DROPS 16
#define DROPS_PER_SECOND 1
#define DROP_RISE_MS 300
#define DROP_FLASH_MS 100
#define DROP_FALL_MS 800
#define DROP_DURATION DROP_RISE_MS + DROP_FLASH_MS + DROP_FALL_MS
#define DROP_SIZE 7

uint32_t dropLocation[MAX_DROPS];
uint32_t dropStart[MAX_DROPS];
uint8_t nDrops;
uint8_t dropBeat = 0;

uint32_t tapStart;
uint32_t tapTimes[8];
uint32_t lastTap;

#define MAX_INTERVALS 32
uint32_t intervals[MAX_INTERVALS];
uint8_t nIntervals = 0;


void drawBigButton();
void drawModeButton();
void drawBPMButton();
void drawStuffButton();
void drawBPM(uint8_t bpmModified);

void drawBPMView() {
  sprite.fillRect(20, 50, TAB_WIDTH, COLOR_BAR_COMPONENTS, TFT_BLACK);  // Top and left
  drawModeButton();
  drawBPMButton();
  drawStuffButton();
  drawBPM(bpm);
}

void drawBPM(uint8_t bpmModified) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d", bpmModified);
    const char* resultString = buffer;
    sprite.fillRect(M_20 + M_20 + M_20 + M_20 + M_20 + M_20 + M_20 + M_20 + M_20 + M_20 , M_20 , M_20 + M_20 + M_20 + M_20, M_20 + M_20, TFT_BLACK);
    sprite.drawString(resultString, M_20 + M_20 + M_20 + M_20 + M_20 + M_20 + M_20 + M_20 + M_20 + M_20 , M_20 , 2);
    sprite.pushSprite(0, 0);
}

void drawModeButton() {
  uint16_t blackColor = TFT_BLACK;
  sprite.setTextColor(TFT_WHITE);
  sprite.drawString("BPM MODE", M_20, TAB_HEIGHT + SPACE, 2);
  sprite.drawRoundRect(M_20, BIG_BUTTONS_Y_OFFSET, BIG_BUTTON_SIZE, BIG_BUTTON_SIZE, 16, TFT_WHITE);
  sprite.fillRoundRect(M_20 + GAP, BIG_BUTTONS_Y_OFFSET + GAP, BIG_BUTTON_SIZE - 4, BIG_BUTTON_SIZE - 4, 16, TFT_PINK);
  sprite.pushSprite(0, 0);
}

void drawBPMButton() {
  uint16_t blackColor = TFT_BLACK;
  sprite.setTextColor(TFT_WHITE);
  sprite.drawString("SET BPM", M_20 + (BIG_BUTTON_SIZE + SPACE), TAB_HEIGHT + SPACE, 2);
  sprite.drawRoundRect(M_20 + (BIG_BUTTON_SIZE + SPACE), BIG_BUTTONS_Y_OFFSET, BIG_BUTTON_SIZE, BIG_BUTTON_SIZE, 16, TFT_WHITE);
  sprite.fillRoundRect(M_20 + (BIG_BUTTON_SIZE + SPACE) + GAP, BIG_BUTTONS_Y_OFFSET + GAP, BIG_BUTTON_SIZE - 4, BIG_BUTTON_SIZE - 4, 16, TFT_BLUE);
  sprite.pushSprite(0, 0);
}

void drawStuffButton() {
  uint16_t blackColor = TFT_BLACK;
  sprite.setTextColor(TFT_WHITE);
  sprite.drawString("SET STUFF", M_20 + (BIG_BUTTON_SIZE + SPACE), TAB_HEIGHT + SPACE, 2);
  sprite.drawRoundRect(M_20 + (BIG_BUTTON_SIZE + SPACE) * 2, BIG_BUTTONS_Y_OFFSET, BIG_BUTTON_SIZE, BIG_BUTTON_SIZE, 16, TFT_WHITE);
  sprite.fillRoundRect(M_20 + (BIG_BUTTON_SIZE + SPACE) * 2 + GAP, BIG_BUTTONS_Y_OFFSET + GAP, BIG_BUTTON_SIZE - 4, BIG_BUTTON_SIZE - 4, 16, TFT_BLUE);
  sprite.pushSprite(0, 0);
}



void sortIntervals() {
  uint32_t tmp;
  for(int i=0; i<nIntervals; i++) {
    for(int j=i+1; j<nIntervals; j++) {
      if (intervals[j] < intervals[i]) {
        tmp = intervals[i];
        intervals[i] = intervals[j];
        intervals[j] = tmp;
      }
    }
  }
}

void updateBeats() {
  // Based on BPM, timeOffset and current time, where we are in the current beat
  // from 0 (start of beat) to 0.9999 (just before next beat)
  uint32_t period_u = 60000000 / bpm;  // use micro seconds for period otherwise time drift can start getting noticeable after 1-2 min
  uint32_t period = period_u / 1000;
  uint32_t t_relative = t - timeOffset;
  beatCounter = t_relative * 1000 / period_u; 
  uint32_t t_relative_in_period = ((t_relative * 1000) % period_u) / 1000;
  beatRatio = float(t_relative_in_period) / period;
  if (beatRatio < lastBeatRatio) {

  }
  lastBeatRatio = beatRatio;
}

void addInterval(uint32_t interval) {
  // ignore too big interval
  if (interval > 6000) return;
  if (nIntervals == MAX_INTERVALS) {
    // drop the most extreme intervals to make room for new ones
    int intervalsToDrop = MAX_INTERVALS / 8;
    nIntervals -= 2 * intervalsToDrop;
    for(int i=0; i<nIntervals; i++) intervals[i] = intervals[i+intervalsToDrop];
  }
  intervals[nIntervals] = interval;
  nIntervals++;
  sortIntervals();
}

void setBPMFromIntervals() {
  // always ignore the first and last intervals
  uint8_t intervalsIgnored = nIntervals / 4;
  uint32_t total = 0;
  for(int i=intervalsIgnored; i<nIntervals-intervalsIgnored; i++) {
    total += intervals[i];
  }
  bpm = 60000 * (nIntervals - 2 * intervalsIgnored) / total;
  // for(int i=0; i<nIntervals; i++) {
  //   Serial.println((String) " interval[" + i + "] " + intervals[i]);
  // }
  Serial.println((String) "bpm " + bpm + " nIntervals " + nIntervals + " ignored " + intervalsIgnored + " total " + total + " average " + total/(nIntervals - 2 * intervalsIgnored));
}

void processInputs() {
  TP_Point touching = touch.getPoint(0);
  int transformedX = touching.y;
  int transformedY = SCREEN_HEIGHT - touching.x;
  //drawBPM(transformedX);

  bool leftButtonJustPressed = false;
  bool leftButtonJustReleased = false;
  bool rightButtonJustPressed = false;
  bool rightButtonJustReleased = false;
  bool buttonPressed = false;
  bool buttonReleased = false;
  bool switchJustFlipped = false;
  
  // check all button states and changes
  if (transformedY < BIG_BUTTONS_Y_OFFSET + BIG_BUTTON_SIZE && transformedY > BIG_BUTTONS_Y_OFFSET && transformedX >= M_20 && transformedX < M_20 + BIG_BUTTON_SIZE) {
    
    if (leftButtonDown == 0) {
      //drawBPM(140);
      leftButtonJustPressed = true;
      leftButtonDown = t;
    }
  } else {
    if (leftButtonDown > 0) {
      //drawBPM(160);
      leftButtonJustReleased = true;
      leftButtonDown = 0;
    }
  }
  if (transformedY < BIG_BUTTONS_Y_OFFSET + BIG_BUTTON_SIZE && transformedY > BIG_BUTTONS_Y_OFFSET && transformedX >= M_20 + (BIG_BUTTON_SIZE + SPACE) && transformedX < M_20 + (BIG_BUTTON_SIZE + SPACE) + BIG_BUTTON_SIZE) {
    if (rightButtonDown == 0) {
      //drawBPM(180);
      rightButtonJustPressed = true;
      rightButtonDown = t;
    }
  } else {
    if (rightButtonDown > 0) {
      //drawBPM(200);
      rightButtonJustReleased = true;
      rightButtonDown = 0;
    }
  }
  buttonPressed = leftButtonJustPressed || rightButtonJustPressed;
  buttonReleased = leftButtonJustReleased || rightButtonJustReleased;

  if (transformedY < BIG_BUTTONS_Y_OFFSET + BIG_BUTTON_SIZE && transformedY > BIG_BUTTONS_Y_OFFSET && transformedX >= M_20 + (BIG_BUTTON_SIZE + SPACE)*2 && transformedX < M_20 + (BIG_BUTTON_SIZE + SPACE)*2 + BIG_BUTTON_SIZE) {
    newSwitchValue = !newSwitchValue;
    isBPMMode = !isBPMMode;
    if (newSwitchValue) drawBPM(111);
    else drawBPM(222);
  }
  if (newSwitchValue != switchValue) {
    switchJustFlipped = true;
    switchValue = newSwitchValue;
  }

  if (switchValue) {
    if (leftButtonDown > 0 && rightButtonDown > 0 && modeSelectionActive == 0) {
      // activate mode selection - check which button was pressed down first, and we'll check which gets released first
      modeSelectionActive = t;
      if (rightButtonDown < leftButtonDown) mode = 2;
      else mode = 0;
      // don't do anything else with these inputs (otherwise button presses will be double counted)
      return;
    }
    if (modeSelectionActive > 0 && buttonReleased) {
      if (rightButtonJustReleased && leftButtonDown)
        // right button released first
        mode++;
      if (!leftButtonDown && !rightButtonDown) {
        // we're done selecting mode
        modeSelectionActive = 0;
        //Serial.println((String) "selected mode " + mode);
      }
      return;
    }

    // button actions depend on the mode
    switch (MODE_PATTERN) {
      case MODE_BRIGHTNESS:
        if (rightButtonJustReleased) {
          // if (brightness < 9) brightness++;
          // else brightness *= 1.2;
          // if (brightness > 200) brightness = 200;
          // Serial.println((String) "brightness increased to " + brightness);
          // strip.setBrightness(brightness);
          // ring.setBrightness(brightness);
        }
        if (leftButtonJustReleased) {
          // if (brightness < 10) brightness--;
          // else brightness /= 1.2;
          // if (brightness < 1) brightness = 1;
          // Serial.println((String) "brightness decreased to " + brightness);
          // strip.setBrightness(brightness);
          // ring.setBrightness(brightness);
        }
        break;
      case MODE_PATTERN:
        if (rightButtonJustReleased) pattern = (pattern + 1) % N_PATTERNS;
        if (leftButtonJustReleased) pattern = (pattern == 0 ? N_PATTERNS - 1: pattern - 1);
        break;
      case MODE_COLOR:
        if (rightButtonJustReleased) hue_primary = (hue_primary + 1) % 6;
        if (leftButtonJustReleased) hue_secondary = (hue_secondary + 1) % 6;
        break;
    }
  } else {
    //drawBPM(205);
    // flip in right position: BPM mode
    if (switchJustFlipped) {
      //drawBPM(207);
      // do BPM tracking for 4 beats
      tapModeActive = t;
      tapCount = 0;
      return;
    }
    // tap to set BPM
    if (tapModeActive > 0 && buttonPressed) {
      drawBPM(tapCount);
      tapTimes[tapCount] = t;
      tapCount++;
      if (tapCount == 4) {
        
        for(int i=0; i<3; i++) {
          intervals[i] = tapTimes[i+1] - tapTimes[i];
        }
        nIntervals = 3;
        sortIntervals();
        setBPMFromIntervals();
        timeOffset = tapTimes[0];
        tapModeActive = 0;
        lastTap = tapTimes[3];
        drawBPM(bpm);
        sendValue(MESSAGE_TYPE_BPM, bpm);
        //Serial.println((String) "updated bpm to " + bpm);
      }
      return;
    }
    // add more intervals with right button
    if (rightButtonJustPressed) {
      addInterval(t - lastTap);
      setBPMFromIntervals();
      drawBPM(bpm);
      sendValue(MESSAGE_TYPE_BPM, bpm);
      lastTap = t;
    }
    if (leftButtonJustPressed) {
      timeOffset = t;
    }
  }
}


uint32_t lastFpsLog;
uint32_t itCount = 0;
uint32_t lastT = 0;
uint32_t maxItTiming = 0;
#define FPS_LOG 500

uint8_t BPMViewEvent() {
  t = millis();

  if (itCount % FPS_LOG == 0) {
    uint32_t timing = t - lastFpsLog;
    //Serial.println((String) "time for FPS_LOG frames: " + timing + " FPS: " + 1000*FPS_LOG/timing + " max: " + maxItTiming);
    lastFpsLog = t;
    maxItTiming = 0;
  }
  if ((t - lastT) > maxItTiming) maxItTiming = t - lastT;
  lastT = t;
  itCount++;

  processInputs();

  updateBeats();

  return bpm;

  // switch(pattern) {
  //   case PLAIN:
  //     plain();
  //     break;
  //   case HALF_PLAIN:
  //     halfPlain();
  //     break;
  //   case HALF_PLAIN_SWITCH:
  //     halfPlainSwitch();
  //     break;
  //   case VEGAS:
  //     vegas();
  //     break;
  //   case PULSE:
  //     pulse2();
  //     break;
  //   case RAINBOW_BEATS:
  //     rainbowBeats();
  //     break;
  //   case RAINBOW:
  //     rainbow2();
  //     break;
  //   case RAIN_DROPS:
  //     rainDrops();
  //     break;
  //   case SPARKLE:
  //     sparkle();
  //     break;
  // }
}



#endif