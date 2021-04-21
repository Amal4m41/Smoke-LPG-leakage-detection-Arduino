#include <Servo.h> 
Servo myservo;  // create servo object to control a servo
int pos = 0;

const int led=7;
const int buzzer=3;
const int gasSensor=A0;


const int gasSensor_threshold=400;  //threshold to detect lpg gas(not sure about this value yet)


void setup()
{
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(gasSensor, INPUT);
  
  myservo.attach(11);
  myservo.write(pos);
  
  Serial.begin(9600);
}

void loop()
{
  int analogSensor_input = analogRead(gasSensor);
  Serial.println(analogSensor_input);
  
  if (analogSensor_input > gasSensor_threshold) //then lpg gas is detected 
  {
    openWindow();   //Open the window 
    blink();  //blink the led
    tone(buzzer,1000,300);  // alarm using buzzer
  }
  else
  {
    setWindowControl_to_InitialPosition();  //So that the user can open or close the window to their wish.
    digitalWrite(led, 0);
    noTone(buzzer);
  }
}

void blink()
{
  digitalWrite(led,1);
  delay(300);
  digitalWrite(led,0);
  delay(300); 
}

void openWindow()
{
  if(pos==0)
  {
    pos=90;
    myservo.write(pos);
    Serial.println("Window OPEN");
  }
}

void setWindowControl_to_InitialPosition()
{
  if(pos==90)    //if in Window open state the set to initial postion
  {
    pos=0;
    myservo.write(pos);
    Serial.println("Window controller set to initial position");
   }
}
