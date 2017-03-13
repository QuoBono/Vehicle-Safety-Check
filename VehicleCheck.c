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

int carSp = 0;

void setup(){
  Serial.begin(9600);
  
  pinMode(servoPin, INPUT);
  pinMode(feedbackPin, INPUT);
  
  pinMode(speedPin, OUTPUT);
  EscServo.attach(speedPin); 
  SteerServo.attach(servoPin); 
  SteerServo.write(70); 
}

void loop(){


  int i = pulseIn(3, HIGH);
  int j = pulseIn(5, HIGH);
  
  //Serial.println("Read the speed:"); 
  //Serial.println(steer);
  int sp = Serial.read();
  
  //Serial.println("Read movement:");
  
  //int st = Serial.read();  
 
  EscServo.writeMicroseconds(carSp);
  
  if (sp > 0 && sp < 100){
      carSp = sp;
  }
  
  //left
  if (sp == 'a'){
    SteerServo.write(0);
  }
  else 
  //right
  if (sp == 'd'){
    SteerServo.write(120);
  }
  else
  if (sp == 'q'){
    SteerServo.write(90);
  }
  else 
  if (sp == 'e'){
    SteerServo.write(30);
  }
  
//  SteerServo.write(i);   
  
  
  //Serial.println(j);
  //EscServo.writeMicroseconds(j);
}
