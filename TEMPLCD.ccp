/*
Adafruit Arduino - Lesson 12. Light and Temperature
*/
 
#include <LiquidCrystal.h>
 
int tempPin = 0;
int lightPin = 1;

const int thermistorPin = A0;
int thermistorValue;
int miliVolts;
int tempature;
 
//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
void setup() 
{
  lcd.begin(16, 2);
}
 
void loop()
{
  thermistorValue = analogRead(thermistorPin);
 miliVolts = analogToMilliVolts(thermistorValue);
 tempature = miliVoltsToTemp(miliVolts);
 
  // Display Temperature in C
  int tempReading = analogRead(tempPin);
  float tempVolts = tempReading * 5.0 / 1024.0;
  float tempC = (tempVolts - 0.5) * 100.0;
  float tempF = tempC * 9.0 / 5.0 + 32.0;
  //         ----------------
  lcd.print("Temp         C  ");
  lcd.setCursor(6, 0);
  lcd.print(tempature);
  
  // Display Light on second row
  int lightReading = analogRead(lightPin);
  lcd.setCursor(0, 1);
  //         ----------------
  lcd.print("Tijd           ");  
  lcd.setCursor(6, 1);
  lcd.print(lightReading);
  delay(500);
}

int analogToMilliVolts(int analogValue)
{
 return map(analogValue, 0, 1023, 0, 5000);
}
int miliVoltsToTemp(int miliVolts)
{
 return map(miliVolts, 400, 2870, 0, 125);
}
