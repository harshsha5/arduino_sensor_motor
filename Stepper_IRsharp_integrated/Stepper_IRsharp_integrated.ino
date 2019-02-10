#include <SharpIR.h>
#define IR A0 // define signal pin
#define model 20150 // used 1080 because model GP2Y0A02YK0F is used


SharpIR SharpIR(IR, model);

//Declare pin functions on Arduino
#define stp 2
#define dir 3
#define MS1 4
#define MS2 5
#define EN  6

//Declare variables for functions
char user_input;
int x;
int y;
int state;
float user_angle;
int prev = 0;

void setup() {
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EN, OUTPUT);
  
  resetEDPins(); //Set step, direction, microstep and enable pins to default states
  Serial.begin(9600); //Open Serial connection for debugging
  Serial.println("Starting IR sensor and stepper motor");
}

void resetEDPins()
{
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(EN, HIGH);
}

void StepForward(float angle)
{
  Serial.println("Moving motor by");
  Serial.println(angle);
  Serial.println("°");
  if(angle > 0)
  {
    digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  }
  else
  {
    digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
  }
  float steps;
  steps = 8.89*angle;
  steps = int(steps);
  
  for(x= 0; x<steps; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp,HIGH); //Trigger one step forward
    delayMicroseconds(1000);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delayMicroseconds(1000);
  }
  Serial.println();
}


void loop() {
      delay(2000); 
      unsigned long startTime=millis();  // gets the start times
      int dis=SharpIR.distance();  // this returns the distance to the object 
      
      digitalWrite(EN, LOW); //Pull enable pin low to allow motor control
      Serial.print("Previous Distance to the object is (cm): ");  // returns it to the serial monitor
      Serial.println(prev);

      if(dis>80)
      {dis=80;}
      Serial.print("New Distance to the object is (cm): ");  // returns it to the serial monitor
      Serial.println(dis);
      
      user_angle = (dis-prev)*5;
      digitalWrite(EN, LOW); //Pull enable pin low to allow motor control
      digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
      StepForward(user_angle);
      resetEDPins();
      unsigned long endTime=millis()-startTime;  // end time
      
      //Serial.print("Time taken for process (ms): ");
//      Serial.println(endTime);  
      prev = dis;
  }
