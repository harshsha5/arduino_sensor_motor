#include "PinChangeInt.h" // PinChange Interrupt library

#define BUTTON_PIN 13 // Button Pin connected to UNO normal pin 13
int count;
void button_push() 
{ 
  Serial.println("In button pressed function");
  count +=1;
  Serial.println(count);

}

void setup() 
{
  pinMode(BUTTON_PIN, INPUT); // Set normal 13 pin to Input
  Serial.begin(9600);
  Serial.println("Starting Interrupt programme..");
  attachPinChangeInterrupt(BUTTON_PIN, button_push, RISING); // interrupt connected to pin 13
}

void loop () 
{ 
}
