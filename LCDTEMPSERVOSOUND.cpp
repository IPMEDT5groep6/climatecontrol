
/* LCD: VSS = GND, VDD = 3,5; potmeter links, V0 = potmeter midden, RS = 12, RW = potmeter rechts; GND, E = 11 ; A, D4 = 5, D5 = 4, D6=3, D7=2.
 * Thermisotor: links=volt, midden=A0, rechts=GND
 * Servo: geel=PWM9, Rood = GND, Bruin=power
 * Sound: GND, 7
 */
#include <Servo.h>
#include "pitches.h"
#include <LiquidCrystal.h>

Servo myservo;  // Servo object aangemaakt om de servo aan te sturen 
                

int pos = 20;    // variabele om de servo positie te bepalen
bool raam = 0;
String raamPos;

bool geluid = 0;

int tempPin = 0;
int lightPin = 1;

const int thermistorPin = A0;
int thermistorValue;
int miliVolts;
int temperature;

//Pin configuratie RS  E  D4 D5  D6 D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


// Noten voor het geluidje:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// noot duur: 4 = Kwart noot, 8 = achtste noot, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
void setup()
{
  lcd.begin(16, 2);
  myservo.attach(9);  // Servo is op pin 9 van de Arduini Mega 2560 aangesloten 
  Serial.begin(9600);

}

void loop()
{
  thermistorValue = analogRead(thermistorPin);
  miliVolts = analogToMilliVolts(thermistorValue);
  temperature = miliVoltsToTemp(miliVolts);

  // Toont Temperatuur in Celsius
  int tempReading = analogRead(tempPin);
  float tempVolts = tempReading * 5.0 / 1024.0;
  float tempC = (tempVolts - 0.5) * 100.0;
  float tempF = tempC * 9.0 / 5.0 + 32.0;
  //         ----------------
  lcd.setCursor(0, 0);
  lcd.print("Temp     C  ");  //Toont temperatuur op lcd
  lcd.setCursor(6, 0);
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print("Raam:");         //Toont raam op LCD
  delay(50);

  if (temperature > 31) {
    if (geluid == 0) {
      sound();
      geluid = 1;
    }

    pos = 177;
    myservo.write(pos);
    raam = 1;
    Serial.println("Position: " + pos);
    Serial.println("Temperature: " + temperature);
    if (raam == 1) {
      raamPos = "Open ";      //Toont raam OPEN op LCD
      lcd.setCursor(0, 1);
      lcd.print("Raam:   ");
      lcd.setCursor(6, 1);
      lcd.print(raamPos);


    }
    delay(1000);
  }

  if (temperature < 28) {
    if (geluid == 1){
      sound();
      geluid = 0;
    }
    pos = 10;
    myservo.write(pos);
    raam = 0;
    Serial.println("Position: " + pos);
    Serial.println("Temperature: " + temperature);
    if (raam == 0) {
      raamPos = "Dicht";        //Toont raam Dicht op LCD
      lcd.setCursor(0, 1);
      lcd.print("Raam:   ");
      lcd.setCursor(6, 1);
      melody;
      lcd.print(raamPos);

    }
    delay(1000);
  }

  

}



void sound() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // Berekend de duur van de noten
    // verschilt per noot.
    // kwart noot = 1000 / 4, achtste noot = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(7, melody[thisNote], noteDuration);

    // Geeft een minimale pauze tussen de noten in
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(7);
  }
}


int analogToMilliVolts(int analogValue)
{
  return map(analogValue, 0, 1023, 0, 5000);
}
int miliVoltsToTemp(int miliVolts)
{
  return map(miliVolts, 400, 2870, 0, 125);
}