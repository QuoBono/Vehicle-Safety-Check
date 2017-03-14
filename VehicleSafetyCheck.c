
/*author Group9
  */
 
#define NEUTRAL 1400
#define FULL 1600
#define BREAK 1000
#define NEUTRALREVERSE 1200
#define RIGHT 80
#define LEFT 60

#include <Servo.h>
 
int speedCarInput = 5; //speed
int steerCarInput = 6; //steering
int steerCarOutput = 9 ;
int SpeedCarOutput = 11;

int straight = 70;
bool joystick = false;
char userInput;
int speedValue = NEUTRAL;
int right = RIGHT;
int left = LEFT;
int speedValueRev = NEUTRALREVERSE;
bool controller = false;
int steerValue = straight;
 
 Servo EscServo;
 Servo SteerServo;
void setup(){
 
    Serial.begin(9600);
    EscServo.attach(11); //11 speed pin
    SteerServo.attach(9); //steering
    SteerServo.write(straight);
    EscServo.writeMicroseconds(NEUTRAL);
 }
 
 void loop(){
     
    int i = pulseIn(speedCarInput, HIGH); //speed
    int j = pulseIn(steerCarInput, HIGH); //steering
   
    if(pulseIn(speedCarInput, HIGH, 27000) > 800 && pulseIn(steerCarInput, HIGH, 27000) > 800){
        joystick = true;
    }else{
        joystick = false;
   }
   
    if(joystick) {
       Serial.println("joystick");  
     

      if(!controller){
        
        SteerServo.write(straight);
        EscServo.writeMicroseconds(NEUTRAL);
        controller = true;
        delay(20);
      }
    
        int accelerate = pulseIn(speedCarInput, HIGH); //speed
        int steer = pulseIn(steerCarInput, HIGH); //steering
        
        SteerServo.write(steer);
        EscServo.writeMicroseconds(accelerate);

    } else if (!joystick) {
      controller = false;
      userInput = Serial.read();

        switch(userInput){
            case 'w': 
                  speedValue = speedValue+50;
                  break;
                  
            case 's': 
                  speedValue = NEUTRAL;
                  steerValue = straight;
                  right = RIGHT;
                  left = LEFT;
                  speedValueRev = NEUTRALREVERSE;
                  break;
                  
            case 'd':
                  right = right + 10;
                  steerValue = right;
                  break;
                  
            case 'a':  
                  left  = left - 10;
                  steerValue = left;
                  break;
                  
            case 'x': 
                  EscServo.writeMicroseconds(NEUTRAL);
                  delay(100);
                  speedValueRev = speedValueRev - 50;
                  speedValue = speedValueRev;
                  break;
        }
    }
    
    if (speedValue > FULL) {
        speedValue = FULL;
    }
    if (speedValue < BREAK){
        speedValue = BREAK;
    }
    if(right >= 120){
        steerValue = 120;
        right = 120;
    }
    if(left <= 0){
      steerValue = 0;
      left = 0;
    }
     
     SteerServo.write(steerValue);
     EscServo.writeMicroseconds(speedValue);
    delay(10);
   
}
