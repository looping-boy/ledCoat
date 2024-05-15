// Print battery voltage
// to 16x2 LCD via I2C
// with Voltage Divider (2x 10K resistor)
/*
  Resistors are aligned in series.
  One end goes to Battery - and also to Arduino GND
  The other goes to Battery + and also to Arduino Vin
  The middle (connection between two resistors) goes to Arduino A0
*/

const int ledPinRed = 33;
const int ledPinYellow = 27;
const int ledPinGreen = 13;


void setup()
{
  Serial.begin(115200);
  pinMode (ledPinRed, OUTPUT);
  pinMode (ledPinYellow, OUTPUT);
  pinMode (ledPinGreen, OUTPUT);
}

void loop()
{
  Serial.printf("Test \n");
  printVolts();
}
 
 void printVolts()
{
  digitalWrite (ledPinRed, LOW);
  digitalWrite (ledPinYellow, LOW);
  digitalWrite (ledPinGreen, LOW);

  int sensorValue = analogRead(34); //read the A0 pin value
  float voltage = sensorValue * 2; //convert the value to a true voltage.
  Serial.printf("Voltage %.2f \n",(float) voltage);
  if (voltage >= 4200) {
    digitalWrite (ledPinGreen, HIGH);
  } else if (voltage >= 3700) {
    digitalWrite (ledPinYellow, HIGH);
  } else {
    digitalWrite (ledPinRed, HIGH);
  }

  delay(100);
}