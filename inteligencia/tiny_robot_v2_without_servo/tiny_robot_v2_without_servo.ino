/*        ~~~ Arduino Tiny Robot Vehicle ~~~
                   avoid obstacles
Information at: http://www.ardumotive.com/tiny-robot.html
  dev by Vasilakis Michalis, mi.vasilakis@gmail.com
Project date: 14/12/2013 / Version: 2.0 / updated 21/12/2013
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
long previousMillis = 0; // Use it to make a red led blink without delay() ! ;)
int  ledState = LOW;      // ledState to LOW. 
long interval = 500;    // interval at which to blink (milliseconds), change it if you want!
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
    //Read distanse
    distance=sensor.Ranging(CM);
    //Print distance on rerial port for debuging...
    Serial.println(distance);
    //If object detected < 20 cm, slow down
    if (distance >=5 && distance < 20){
       analogWrite(motorPin1, 180);
       analogWrite(motorPin2, 0);
       analogWrite(motorPin3, 180);
       analogWrite(motorPin4, 0);
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
             noTone(speaker); //Speaker off
         }
         // set the LED with the ledState of the variable:
         digitalWrite(redLed, ledState);
       }
       /*************************************************************************/
       digitalWrite(greenLed, LOW);
    }
    //If object detected < 5 cm, turn left to avoid object (or right...)
    else if (distance < 5){
       analogWrite(motorPin1, 255);
       analogWrite(motorPin2, 0);
       analogWrite(motorPin3, 0);
       analogWrite(motorPin4, 255);
       digitalWrite(redLed, HIGH);
       digitalWrite(greenLed, LOW);
       tone(speaker, 1000);  //Speaker on
       delay(1000); // small delay, change value if necessary
    }else if (distance < 1){
       analogWrite(motorPin1, 0);
       analogWrite(motorPin2, 180);
       analogWrite(motorPin3, 0);
       analogWrite(motorPin4, 180);
       digitalWrite(redLed, HIGH);
       digitalWrite(greenLed, LOW);
       tone(speaker, 1000);  //Speaker on
       delay(1000); // small delay, change value if necessary
    }
    //No object detected? Ok... all crear to move forward!  
    else {
       analogWrite(motorPin1, 255);
       analogWrite(motorPin2, 0);
       analogWrite(motorPin3, 255);
       analogWrite(motorPin4, 0);
       digitalWrite(redLed, LOW);
       digitalWrite(greenLed, HIGH);
       noTone(speaker); //Speaker off
    }
    delay(50);
}
