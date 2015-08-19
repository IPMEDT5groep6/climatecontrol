/*
ServoLinks, PWM4
ServoRechts PWM 7
LEDpinaan= PWM5
LedpinUit=PWM6
Button1 voor aan=PWM9
Button2 voor uit=PWM8

*/
#include <Servo.h> 

int ledPinaan = 5;
int ledPinuit = 6;
int buttonApin = 9;
int buttonBpin = 8;


Servo servoRechts;  // create servo object to control a servo 
Servo servoLinks;
                // a maximum of eight servo objects can be created 
int pos = 0;    // variable to store the servo position 
byte leds = 0;

void setup() 
{
  servoLinks.attach(4);
  servoRechts.attach(7);  // attaches the servo on pin 9 to the servo object 
  pinMode(ledPinaan, OUTPUT);
  pinMode(ledPinuit, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP);  
}

void loop() 
{
  if (digitalRead(buttonApin) == LOW)
  {
    digitalWrite(ledPinaan, HIGH);
    digitalWrite(ledPinuit, LOW);
    servoRechts.write(180);
    servoLinks.write(30);
    
  }
  if (digitalRead(buttonBpin) == LOW)
  {
    digitalWrite(ledPinaan, LOW);
    digitalWrite(ledPinuit, HIGH);
    servoRechts.write(50);
    servoLinks.write(180);
  }
}