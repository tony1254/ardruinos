#include <Ultrasonic.h>


/*        ~~~ ROBOT Con MOTORES ESPEJO ~~~
                   avoid obstacles
Information at: https://github.com/tony1254/ardruinos/tree/master/robottelefono
by Luis Garcia cby@hotmail.es
Project date: 06/06/2015 / Version: 1.0 / updated 06/06/2015
*/
// Entradas
int arriba=A0;
int abajo=A1;
int izquirda=A2;
int drecha=A3;
int Q1=0,Q2=0,Q3=0,Q4=0;
// L293 pins
const int motorPin1  = 6; // Pin  2 of L293
const int motorPin2  = 5; // Pin  7 of L293
const int motorPin3  = 9;  // Pin 10 of L293
const int motorPin4  = 11;  // Pin 14 of L293
//Lights
const int redLed   = 3;
const int greenLed = 4;
//Speaker
const int speaker  = 7;
//Variables 
int  distance;
long previousMillis = 0; // Use it to make a red led blink without delay() ! ;)
int  ledState = LOW;      // ledState to LOW. 
int var = 0;
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
     //Pines de entrada
  pinMode(arriba, INPUT); // Set our input pins as such
  pinMode(abajo, INPUT);
  pinMode(izquirda, INPUT);
  pinMode(drecha, INPUT);
}
void loop(){
   Q1=pulseIn(arriba, HIGH, 25000);
   Q2=pulseIn(abajo, HIGH, 25000);
   Q3=pulseIn(izquirda, HIGH, 25000);
   Q4=pulseIn(drecha, HIGH, 25000);
    //If object detected < 20 cm, slow down
    /*if (distance >=5 && distance < 20){
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
//      *************************************************************************
       digitalWrite(greenLed, LOW);
    }*/

//ADELANTE
 if (Q1<12500 && Q2>12500 && Q3<12500 && Q4<12500){
      analogWrite(motorPin1, 255);
       analogWrite(motorPin2, 0);
       analogWrite(motorPin3, 255);
       analogWrite(motorPin4, 0);
       digitalWrite(redLed, LOW);
       digitalWrite(greenLed, HIGH);
       noTone(speaker); //Speaker off
    }
//DERECHA
     else if (Q1<12500 && Q2>12500 && Q3>12500 && Q4<12500){
       analogWrite(motorPin1, 0);
       analogWrite(motorPin2, 255);
       analogWrite(motorPin3, 255);
       analogWrite(motorPin4, 0);
       digitalWrite(redLed, HIGH);
       digitalWrite(greenLed, LOW);
 noTone(speaker); //Speaker off
    }    
//IZQUIERDA
        else if (Q1<12500 && Q2<12500 && Q3>12500 && Q4<12500){
       analogWrite(motorPin1, 255);
       analogWrite(motorPin2, 0);
       analogWrite(motorPin3, 0);
       analogWrite(motorPin4, 255);
       digitalWrite(redLed, HIGH);
       digitalWrite(greenLed, LOW);
 noTone(speaker); //Speaker off

    }

//ATRAS
    else if (Q1<12500 && Q2<12500 && Q3<12500 && Q4>12500){
       analogWrite(motorPin1, 0);
       analogWrite(motorPin2, 255);
       analogWrite(motorPin3, 0);
       analogWrite(motorPin4, 255);
       digitalWrite(redLed, HIGH);
       digitalWrite(greenLed, HIGH);
      tone(speaker, 1000);  //Speaker on
     }
//ALTO
else {
       analogWrite(motorPin1, 0);
       analogWrite(motorPin2, 0);
       analogWrite(motorPin3, 0);
       analogWrite(motorPin4, 0);
       digitalWrite(redLed, LOW);
       digitalWrite(greenLed, LOW);
 noTone(speaker); //Speaker off
    }
    delay(50);
}
