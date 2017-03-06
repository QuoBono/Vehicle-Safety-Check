#include <Servo.h>

int right = 120; 
int left = 0;
int straight = 70;

int servoPin = 9;
int analogPin = A8;
Servo myServo;


void setup(){
  Serial.begin(9600);
  myServo.attach(servoPin);
  pinMode(3, INPUT);
  pinMode(5, INPUT);

}


void loop(){

  //read the byte values of the pins
  int i = pulseIn(3, HIGH);
  int j = pulseIn(5, HIGH);
  
  int steer = i/20;
  Serial.println(steer);
  //delay(5);

  //initial algorithm for the steering angles 
  if(steer>63 || steer <75){
    myServo.write(steer);
  }else if(steer>75){
    myServo.write(steer*2);
  }else if(steer<65){
    myServo.write(steer/2);
  }
    
}
