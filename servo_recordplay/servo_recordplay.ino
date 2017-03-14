/*
*author Group9
*/

#define NEUTRAL 1350
#define FULL 1850
#define BREAK 850

#include <Servo.h>
//max right 120
//max left 0
//straight 70

int straight = 70;
const int speedCarInput = 5; //speed
const int steerCarInput = 6; //steering
const int steerCarOutput = 9 ;
const int SpeedCarOutput = 11;
unsigned int softwareSpeed = 1450;
bool joystick = false;
char userInput;
char lastPressed;
int neutral = NEUTRAL;
int right = straight + 10;
int left = straight - 10;

Servo EscServo;
Servo SteerServo;

void setup(){
  Serial.begin(9600);
  
  pinMode(speedCarInput, INPUT);
  pinMode(steerCarInput, INPUT); //steering
  pinMode(steerCarOutput, OUTPUT);
  pinMode(SpeedCarOutput, OUTPUT);
  EscServo.attach(11); //11 speed pin
  //EscServo.attach(feedbackPin); 
  SteerServo.attach(9); //steering
  SteerServo.write(straight);
  EscServo.write(NEUTRAL);
  
}

void loop(){
  
  if(pulseIn(speedCarInput, HIGH, 27000) > 800 && pulseIn(steerCarInput, HIGH, 27000) > 800){
    joystick = true;
  }else{
    joystick = false;
  }


  if(joystick) {
  //SteerServo.write(100);
  int i = pulseIn(speedCarInput, HIGH); //speed
  int j = pulseIn(steerCarInput, HIGH); //steering
  
  Serial.println("this is speed");
  Serial.println(i);
   Serial.println("this is steer");
  Serial.println(j);

  // Max over 1800
  // Min around 900
  //Neutral 1340 to 1380
  
  SteerServo.write(j);   
  EscServo.writeMicroseconds(i); //speed

  } else if (!joystick || Serial.available() > 0) {
    userInput = Serial.read();
    switch(userInput){
      case 'w': if(lastPressed == 'x'){ EscServo.write(neutral); delay(1000);}EscServo.write(neutral + 100); if(neutral < 1550){neutral = neutral + 10;} lastPressed = 'w';
      break;
      case 's': EscServo.write(NEUTRAL); SteerServo.write(straight); lastPressed = 's';
      break;
      case 'd': SteerServo.write(right); if(right <= 120){ right = right +10;} lastPressed = 'd';
      break;
      case 'a': SteerServo.write(left); if(left > 0){ left = left - 10;} lastPressed = 'a';
      break;
      case 'x': if(lastPressed == 'w'){ EscServo.write(neutral); delay(1000);} EscServo.write(NEUTRAL - 200); SteerServo.write(straight); lastPressed = 'w';
      break;
    }
  
  }
  delay(50);
  
}



