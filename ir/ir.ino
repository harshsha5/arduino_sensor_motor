#include <SharpIR.h>

#define IR A0 // define signal pin
#define model 20150 // used 1080 because model GP2Y0A02YK0F is used


SharpIR SharpIR(IR, model);
void setup() 
{
 Serial.begin(9600);
 Serial.println("Starting code...");
}

void loop() {
    delay(500);   

  unsigned long startTime=millis();  // gets the start times

  int dis=SharpIR.distance();  // this returns the distance to the object 
  
  Serial.print("Distance to the object is (cm): ");  // returns it to the serial monitor
  Serial.println(dis);
  //Serial.println(analogRead(A0));
  unsigned long endTime=millis()-startTime;  // end time
  Serial.print("Time taken (ms): ");
  Serial.println(endTime);  
     
}
