int val;
const int slot_sensor = A5;


void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  val = analogRead(slot_sensor);
  Serial.println(val);
  delay(100);
}
