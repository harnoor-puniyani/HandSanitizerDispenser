//ultra sonic
#define echopin 11 // echo pin
#define trigpin 12  // Trigger pin 
float distanceCm;
unsigned long ultra_time;
int set_cm = 20;
float distance_cm;
//pir sensor
#define pirOp 9
int flag = 0;
//relay
#define relay 5

//backlight
#define backLight 7


void setup()
{
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(pirOp, INPUT);
  pinMode(backLight, OUTPUT);
  pinMode(relay, OUTPUT);
}

void loop()
{
  delay(10); //delay for the functioning
  pirRead(); //reading the pir sensor output pin
  delay(10);
  ultrasonicRead(); //reading ultrasonic sensor

  if (distanceCm < set_cm && flag == 1)
  {
    delay(1000); //delay of 1 sec before triggering the pump
    digitalWrite(relay, HIGH);
    delay(1000); //delay of 1 sec after triggering the pump
    flag = 0;
  }

  delay(10000); // giving 10 sec break to the pump
}

void ultrasonicRead()
{
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  ultra_time = pulseIn (echopin, HIGH);
  distance_cm =  ultra_time / 29 / 2;
}

void pirRead()
{
  if (digitalRead(pirOp) == HIGH)
  {
    digitalWrite(backLight, HIGH);
    flag = 1;
  }

}


/*
  flow of the program
  read pir
  ignite lcd backlight
  1 sec relay before and after pump
  it wont dispense till next 10 sec
*/
