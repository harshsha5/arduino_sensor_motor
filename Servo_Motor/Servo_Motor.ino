#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
float user_angle;
float previous_angle;
String inString;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(pos);  
  
  Serial.begin(9600);

  Serial.println("Servo motor set to (°): ");
  Serial.println(myservo.read()); 
  Serial.println("Servo Motor has started..");
  Serial.println();
  Serial.println("Enter angle by which you wish to rotate motor");
  Serial.println();
}

void move_servo(float angle)
{
  if(angle >= 0)
  {
    move_servo_forward(angle);
  }
  else
  {
    move_servo_reverse(angle);
  }
}

void move_servo_forward(float angle)
{
  Serial.println("Moving motor in forward direction");
  Serial.println();
  for (pos = 0; pos <= angle; pos += 1) 
  { 
    myservo.write(pos);              
    delay(5);                       // waits 5ms for the servo to reach the position
  }  
}

void move_servo_reverse(float angle)
{ angle = angle*-1;
  Serial.println("Moving motor in reverse direction");
  Serial.println();
  for (pos = angle; pos >= 0; pos -= 1) 
  { 
    myservo.write(pos);              
    delay(5);
  }
}


void loop() {
  while(Serial.available()){
      inString = Serial.readStringUntil('\n');
      user_angle = inString.toFloat();
              
      move_servo(user_angle);

      previous_angle = myservo.read(); 
      Serial.println("My previous angle is (in °): ");
      Serial.println(previous_angle);
  }
}
