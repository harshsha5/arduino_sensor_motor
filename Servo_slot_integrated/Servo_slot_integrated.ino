
#include <Servo.h>
int val;
const int slot_sensor = A5;
Servo myservo;

void setup() 
{
    Serial.begin(9600);
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}


void move_servo(float angle)
{

    myservo.write(angle);              
 
}

void loop() 
{
  val = analogRead(slot_sensor);

  if (val<=15)
  {
    move_servo(0);
  }

  else
  {
    move_servo(180);
  }

 
//  Serial.println(val);
//  delay(100);
}
