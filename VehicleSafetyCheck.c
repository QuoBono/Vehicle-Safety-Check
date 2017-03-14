/*
 *author Group9
 *
 */


/*
 * Speed Max and Min Values
 */
// Max over 1850
// Min around 900
//Neutral 1340 to 1380 ~= 1350

#define NEUTRAL 1350
#define FULL 1850
#define BREAK 850

#include <Servo.h>
/*
 * Steering Max and Min Values
 */
//max right 120
//max left 0
//straight 70


/*
 * Car Set-Up
 */
int straight = 70;
const int speedCarInput = 5; //speed input
const int steerCarInput = 6; //steering input
const int steerCarOutput = 9 ;//steering output
const int SpeedCarOutput = 11; //speed output

/*
 * Remote Control
 */
bool joystick = false;

/*
 * Serial Control
 */
char userInput;
char lastPressed;
int neutral = NEUTRAL;
int right = straight + 10;
int left = straight - 10;

/*
 * Speed and Steer Servo
 */
Servo EscServo; //Speed
Servo SteerServo; //Steer

void setup(){
    Serial.begin(9600);
    pinMode(speedCarInput, INPUT);
    pinMode(steerCarInput, INPUT); //steering
    pinMode(steerCarOutput, OUTPUT);
    pinMode(SpeedCarOutput, OUTPUT);
    EscServo.attach(11); //speed pin
    SteerServo.attach(9); //steer pin
    /*
     * Set car wheels to the front and NEUTRAL speed.
     */
    SteerServo.write(straight);
    EscServo.write(NEUTRAL);
    
}

void loop(){
    /*
     * If the car receives a signal from the Remote control (either speed or steer) Joystick will be true else false.
     */
    if(pulseIn(speedCarInput, HIGH, 27000) > 800 && pulseIn(steerCarInput, HIGH, 27000) > 800){
        joystick = true;
    }else{
        joystick = false;
    }
    
    
    if(joystick) {
        int i = pulseIn(speedCarInput, HIGH); //Get speed
        int j = pulseIn(steerCarInput, HIGH); //Get steering
        
        Serial.println("this is speed");
        Serial.println(i);
        Serial.println("this is steer");
        Serial.println(j);
        
        EscServo.writeMicroseconds(i); //speed
        SteerServo.write(j); //steering
        
    } else if (!joystick || Serial.available() > 0) {
        
        /*
         * Get Input from Serial
         */
        userInput = Serial.read();
        
        /*
         * Switch case for moving the car
         */
        
        switch(userInput){
                /*
                 * Last key pressed is used in order to ovoid damaging the motors when someone goes from front to backwards or the other way.
                 */
            case 'w': if(lastPressed == 'x'){ EscServo.write(NEUTRAL); delay(1000);}EscServo.write(neutral + 100); if(neutral < 1550){neutral = neutral + 10;} lastPressed = 'w';
                break;
            case 's': EscServo.write(NEUTRAL); SteerServo.write(straight); lastPressed = 's';
                break;
            case 'd': SteerServo.write(right); if(right <= 120){ right = right +10;} lastPressed = 'd'; //increment the steering if you press more.
                break;
            case 'a': SteerServo.write(left); if(left > 0){ left = left - 10;} lastPressed = 'a'; //increment the steering if you press more.
                break;
            case 'x': if(lastPressed == 'w'){ EscServo.write(NEUTRAL); delay(1000);} EscServo.write(NEUTRAL - 200); SteerServo.write(straight); lastPressed = 'w';
                break;
        }
        
    }
    delay(50);
    
}


