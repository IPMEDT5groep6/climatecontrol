

/* LCD: VSS = GND, VDD = 3,5; potmeter links, V0 = potmeter midden, RS = 12, RW = potmeter rechts; GND, E = 11 ; A, D4 = 5, D5 = 4, D6=3, D7=2.
 * Thermisotor: links=volt, midden=A0, rechts=GND
 * Servo: geel=PWM9, Rood = GND, Bruin=power
 *
 */
#include <Servo.h>
#include "Pitches.h"
#include <LiquidCrystal.h>

Servo myservoR;  // Servo voor rechter raam , op pin 9 (PWM Pin)
//Servo myservoL; // Servo voor het linker raam, op Pin 8 (PWM pin)


//int posR;    //variabele om de servo positie te bepalen
//int posRdicht;
//int posL;
bool raam = 0;
String raamPos;

bool geluid = 0;

int tempPin = 0;
int lightPin = 1;
int ledPinaan = 6;
int ledPinuit = 7;
int buttonApin = 40;
int buttonBpin = 42;
int thermistorPin = A1;
int thermistorValue;
int miliVolts;
int temperature;

//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

    // Noten voor het geluidje:
    int melody1[] = {
      // NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0,
      NOTE_B3, NOTE_C4
    };

    // noot duur: 4 = Kwart noot, 8 = achtste noot, etc.:
    int noteDurations1[] = {
      //8, 4, 8, 4, 8, 4,
      8, 4
    };

    // Noten voor het geluidje:
    int melody2[] = {
      // NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0,
      NOTE_C4, NOTE_B3
    };

    // noot duur: 4 = Kwart noot, 8 = achtste noot, etc.:
    int noteDurations2[] = {
      //8, 4, 8, 4, 8, 4,
      8, 4
    };


void setup()
{
  lcd.begin(16, 2);
  myservoR.attach(13);  // Servo voor rechter raam , op pin 9 (PWM Pin)
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
  pinMode(ledPinaan, OUTPUT);
  pinMode(ledPinuit, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  thermistorValue = analogRead(thermistorPin);
  miliVolts = analogToMilliVolts(thermistorValue);
  temperature = miliVoltsToTemp(miliVolts);

  lcd.setCursor(0, 0);
  lcd.print("Temp:     C  ");
  lcd.setCursor(6, 0);
  lcd.print(temperature);

  lcd.setCursor(0, 1);
  lcd.print("Raam:");
  delay(50);


  if (temperature > 30) {

    if (geluid == 0) {
      soundOpen();
      geluid = 1;
    }

    Serial.print("Servo Reading: ");
    Serial.println(myservoR.read());

    digitalWrite(ledPinaan, LOW);
    digitalWrite(ledPinuit, HIGH);

    myservoR.write(40);

    raam = 1;

    if (raam == 1) {

      raamPos = "Open ";
      lcd.setCursor(0, 1);
      lcd.print("Raam:   ");
      lcd.setCursor(6, 1);
      lcd.print(raamPos);
    }

    delay(25);
  }


  if (temperature < 28) {

    if (geluid == 1) {
      soundDicht();
      geluid = 0;
    }

    Serial.print("Servo Reading: ");
    Serial.println(myservoR.read());

    digitalWrite(ledPinaan, HIGH);
    digitalWrite(ledPinuit, LOW);
    myservoR.write(175);

    raam = 0;

    if (raam == 0) {

      raamPos = "Dicht";
      lcd.setCursor(0, 1);
      lcd.print("Raam:   ");
      lcd.setCursor(6, 1);
      lcd.print(raamPos);
    }

    delay(25);


  }


  // Display Light on second row
  knopRaamOpen();
  knopRaamDicht();
}
void knopRaamOpen() {

  if (digitalRead(buttonBpin) == LOW)
  {
    Serial.println("Knop gedrukt, raam open");
    digitalWrite(ledPinaan, LOW);
    digitalWrite(ledPinuit, HIGH);
    myservoR.write(40);

    soundOpen();
    raam = 1;

    if (raam == 1) {

      raamPos = "Open ";
      lcd.setCursor(0, 1);
      lcd.print("Raam:   ");
      lcd.setCursor(6, 1);
      lcd.print(raamPos);
    }

    delay(5000);

  }
}

void knopRaamDicht() {
  if (digitalRead(buttonApin) == LOW)
  {
    Serial.println("Knop gedrukt, raam dicht");
    digitalWrite(ledPinaan, HIGH);
    digitalWrite(ledPinuit, LOW);
    myservoR.write(175);

    soundDicht();
    raam = 0;

    if (raam == 0) {

      raamPos = "Dicht";
      lcd.setCursor(0, 1);
      lcd.print("Raam:   ");
      lcd.setCursor(6, 1);
      lcd.print(raamPos);
    }

    delay(5000);


  }
}

void soundOpen() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // Berekend de duur van de noten
    // verschilt per noot.
    // kwart noot = 1000 / 4, achtste noot = 1000/8, etc.
    int noteDuration1 = 1000 / noteDurations1[thisNote];
    tone(8, melody1[thisNote], noteDuration1);

    // Geeft een minimale pauze tussen de noten in
    int pauseBetweenNotes = noteDuration1 * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void soundDicht() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // Berekend de duur van de noten
    // verschilt per noot.
    // kwart noot = 1000 / 4, achtste noot = 1000/8, etc.
    int noteDuration2 = 1000 / noteDurations2[thisNote];
    tone(8, melody2[thisNote], noteDuration2);

    // Geeft een minimale pauze tussen de noten in
    int pauseBetweenNotes = noteDuration2 * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
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