#include <Servo.h> 
 
Servo mijnServo;  // Maak het servo object aan

int pos = 0;    // Variabele voor de positie van de servo 
 
void setup() 
{ 
  mijnServo.attach(9);  // Koppelt de servo aan pin 9 (PWM pin)
} 
 
 
void loop() 
{ 
  If(pos < 30) 
  {    
    pos = 160;                              
    mijnServo.write(pos);              // servo gaat naar de positie van de variabele 
   delay(500);                    
  } 
  if(pos > 150)    
  {                                
   Pos = 20;
    mijnServo.write(pos);              // servo gaat naar de positie van de variabele 
    delay(500);                       
  } 
}
