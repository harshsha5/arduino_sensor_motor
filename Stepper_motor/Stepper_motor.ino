
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

void setup() {
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EN, OUTPUT);
  
  resetEDPins(); //Set step, direction, microstep and enable pins to default states
  Serial.begin(9600); //Open Serial connection for debugging
  
//  myStepper.setSpeed(60);
  
  Serial.println("Motor Control has started");
  Serial.println();
  //Print function list for user selection
  Serial.println("Enter angle by which you wish to rotate motor");
  Serial.println();
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
  Serial.println("Moving motor in forward..");
  Serial.println(angle);
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

//void ReverseStep(float angle)
//{ Serial.println("Moving motor in reverse");
//  float steps;
//  steps = 8.89*angle;
//  steps = int(steps);
//
//  digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
//  for(x= 1; x<steps; x++)  //Loop the stepping enough times for motion to be visible
//  {
//    digitalWrite(stp,HIGH); //Trigger one step
//    delay(1);
//    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
//    delay(1);
//  }
//}

void ReverseStepDefault(float angle)
{
  Serial.println("Moving motor in reverse..");
  digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
  float stepo;
  stepo = 8.89*angle;
  stepo = int(stepo);
  stepo = stepo*-1;
  for(x= 1; x<stepo; x++)  //Loop the stepping enough times for motion to be visible
  {
    digitalWrite(stp,HIGH); //Trigger one step
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }

}

void loop() {
  while(Serial.available()){
      //user_input = Serial.readString(); //Read user input and trigger appropriate function
      digitalWrite(EN, LOW); //Pull enable pin low to allow motor control
      user_angle = Serial.parseFloat();
      if(user_angle >0)
      {
        StepForward(user_angle);
      }
      
      else if(user_angle <0)
      {
        ReverseStepDefault(user_angle);
      }
      
      else
      {
        continue;
      }

      resetEDPins();
  }

}
