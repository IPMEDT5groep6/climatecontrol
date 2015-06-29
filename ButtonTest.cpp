int ledPinaan = 5;
int ledPinuit = 6;
int buttonApin = 9;
int buttonBpin = 8;

byte leds = 0;

void setup() 
{
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
    
  }
  if (digitalRead(buttonBpin) == LOW)
  {
    digitalWrite(ledPinaan, LOW);
    digitalWrite(ledPinuit, HIGH);
  }
}