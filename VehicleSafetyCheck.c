/*
*author Group9
*/

#include <Servo.h>
int right = 120, left = 0, straight = 70;

int servoPin = 3;
int feedbackPin = 5;
int speedPin = 11;

Servo EscServo;
Servo SteerServo;

void setup(){
  Serial.begin(9600);
  
  pinMode(servoPin, INPUT);
  pinMode(feedbackPin, INPUT);
  
  pinMode(speedPin, OUTPUT);
  EscServo.attach(speedPin); 
  SteerServo.attach(servoPin);
  
}

void loop(){

  int i = pulseIn(3, HIGH);
  int j = pulseIn(5, HIGH);
  //Serial.println(steer);
  SteerServo.write(i);   
  
  
  //Serial.println(j);
  EscServo.writeMicroseconds(j);
}
