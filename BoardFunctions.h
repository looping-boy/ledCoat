#ifndef BOARD_FUNCTIONS_H
#define BOARD_FUNCTIONS_H

int mapPotValueToBrightness(int potValue);

void readBatteryVoltage() {
  int batteryValue = analogRead(BATTERY_PIN);
  if (batteryValue < 1700) {
    delay(1000);
    digitalWrite(SHUT_DOWN_PIN, LOW);
    delay(1000);
    digitalWrite(SHUT_DOWN_PIN, HIGH);
    digitalWrite(SHUT_DOWN_PIN, LOW);
  }
}

void updateBrightness() {
  int potValue = analogRead(POT_PIN);
  int brightness = mapPotValueToBrightness(potValue);
  FastLED.setBrightness(brightness);
}

int mapPotValueToBrightness(int potValue) {
  //Serial.printf("Pot value %.2f \n",(float)potValue);
  float scale = (float)potValue / 3000.0; // Scale to range 0.0 to 1.0
  float expBrightness = 10 + pow(scale, 2.5) * (MAX_BRIGHTNESS - 10); 
  return constrain((int)expBrightness, 10, MAX_BRIGHTNESS);
}

#endif 