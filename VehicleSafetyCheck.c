/*
 *author Group9
 */

#include <Servo.h>
int right = 120, left = 0, straight = 70;

int speedCarInput = 5; //speed
int steerCarInput = 6; //steering
int steerCarOutput = 9 ;
int SpeedCarOutput = 11;

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
    
}

void loop(){
    
    //SteerServo.write(100);
    int i = pulseIn(speedCarInput, HIGH); //speed
    int j = pulseIn(steerCarInput, HIGH); //steering
    
    Serial.println("this is speed");
    Serial.println(i);
    
    /*
     Serial.println("this is steer");
     Serial.println(j);
     
     */
    // Max over 1800
    // Min around 900
    //Neutral 1340 to 1380
    
    SteerServo.write(j);
    //SteerServo.write(30);
    
    
    //EscServo.writeMicroseconds(i);
    delay(500);
}
