/*        ~~~ Arduino Tiny Robot Vehicle ~~~
                   avoid obstacles
Information at: http://www.ardumotive.com/tiny-robot.html
  dev by Vasilakis Michalis, mi.vasilakis@gmail.com
Project date: 14/12/2013 / Version: 3.0 / updated 31/12/2013
*/
//Include libraries
#include <Ultrasonic.h>
//Ultrasonic variable_name(Trig_Pin, Echo_Pin)
Ultrasonic sensor (A0,A1);
// L293 pins
const int motorPin1  = 6; // Pin  2 of L293
const int motorPin2  = 5; // Pin  7 of L293
const int motorPin3  = 9;  // Pin 10 of L293
const int motorPin4  = 10;  // Pin 14 of L293
//Lights
const int redLed   = 3;
const int greenLed = 4;
//Speaker
const int speaker  = 7;
//Variables 
int  distance;
char state;              //State stores the income data
char mode='m';           // a for auto or m for bt controlled
long previousMillis = 0; // Use it to make a red led blink without delay() ! ;)
int  ledState = LOW;     // ledState to LOW. 
long interval = 500;     // interval at which to blink (milliseconds), change it if you want!
unsigned long currentMillis;

void setup(){
    Serial.begin(9600);
    // Set pins as outputs:
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT); 
    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
}
void loop(){
    //Read distance
    distance=sensor.Ranging(CM);
    //Print distance on serial port for debugging...
    /*Serial.println(distance);*/
    // If some data is sent, read it and save it in "state"
    if(Serial.available() > 0){     
       state = Serial.read(); 
       if (state == 'A'){mode = 'a'; }
       if (state == 'M'){mode = 'm'; 
          digitalWrite(motorPin1, LOW);digitalWrite(motorPin2, LOW); 
          digitalWrite(motorPin3, LOW);digitalWrite(motorPin4, LOW);
          digitalWrite(redLed,  LOW);
          digitalWrite(greenLed,LOW);
       }  
    }
    if (mode == 'a'){
       //If object detected < 20 cm, slow down
       if (distance >=5 && distance < 20){
           analogWrite(motorPin1, 180);analogWrite(motorPin2, 0);
           analogWrite(motorPin3, 180);analogWrite(motorPin4, 0);
           digitalWrite(greenLed, LOW);
           // The following code will make red led to blink without dalay() function
           currentMillis = millis();
           if(currentMillis - previousMillis > interval) {
              // save the last time you blinked the LED 
              previousMillis = currentMillis;   
              // if the LED is off turn it on and vice-versa:
              if (ledState == LOW){
                 ledState = HIGH;
                 tone(speaker, 500); //Speaker on
              } 
              else{
                 ledState = LOW;
                 noTone(speaker);    //Speaker off
              }
              digitalWrite(redLed, ledState);// set the LED with the ledState of the variable:
            }
       }
       //If object detected < 5 cm, turn right to avoid object (or left...)
       else if (distance < 5){
            digitalWrite(motorPin1, HIGH);digitalWrite(motorPin2, LOW);
            digitalWrite(motorPin3, LOW) ;digitalWrite(motorPin4, HIGH);
            digitalWrite(redLed, HIGH);
            digitalWrite(greenLed, LOW);
            tone(speaker, 1000);  //Speaker on
            delay(1000); // small delay, change value if necessary to make robot turn 90 deg.
       }
       //No object detected? Ok... all crear to move forward!  
       else {
    	    digitalWrite(motorPin1, HIGH); digitalWrite(motorPin2, LOW); 
            digitalWrite(motorPin3, HIGH); digitalWrite(motorPin4, LOW);
            digitalWrite(redLed, LOW);
            digitalWrite(greenLed, HIGH);
            noTone(speaker); //Speaker off
       }
    }
    //Bluetooth Mode
    else if (mode == 'm'){
       /***********************Forward****************************/
       // If the "state" is 'F', robot will go forward
       if (state == 'F') {
            //If object detected < 5 cm, stop and wait for new command
            if (distance < 5){
               digitalWrite(motorPin1, LOW); digitalWrite(motorPin2, LOW); 
               digitalWrite(motorPin3, LOW); digitalWrite(motorPin4, LOW);
            }    
            else if (distance>= 5){
               digitalWrite(motorPin1, HIGH);digitalWrite(motorPin2, LOW); 
               digitalWrite(motorPin3, HIGH);digitalWrite(motorPin4, LOW);
            } 
       }
       /***********************Backward****************************/
       // If the "state" is 'B', robot will go backward
       else if (state == 'B') {
    	    digitalWrite(motorPin1, LOW); digitalWrite(motorPin2, HIGH); 
            digitalWrite(motorPin3, LOW); digitalWrite(motorPin4, HIGH); 
       }
       /*************************Left******************************/
       // If the "state" is 'L', robot will turn left
       else if (state == 'L') {  
    	    digitalWrite(motorPin1, LOW) ; digitalWrite(motorPin2, HIGH); 
            digitalWrite(motorPin3, HIGH); digitalWrite(motorPin4, LOW); 
       }       
       /*************************Right*****************************/
       // If the "state" is 'R', robot will turn right
       else if (state == 'R') {  
    	    digitalWrite(motorPin1, HIGH); digitalWrite(motorPin2, LOW); 
            digitalWrite(motorPin3, LOW) ; digitalWrite(motorPin4, HIGH); 
       }
       /*************************Stop*****************************/
       // If the "state" is 'S', robot will stop
       else if (state == 'S') {  
    	    digitalWrite(motorPin1, LOW); digitalWrite(motorPin2, LOW); 
            digitalWrite(motorPin3, LOW); digitalWrite(motorPin4, LOW); 
       }       
    }  
    delay(50); //small delay to read a new distance value from sensor
}
