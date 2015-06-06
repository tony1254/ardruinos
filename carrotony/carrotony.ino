#include <Wire.h>
//#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_PWMServoDriver.h"
#include <SoftwareSerial.h>

int bluetoothTx = 2;
int bluetoothRx = 3;
int motorPins[] = {12, 11, 10, 9};
int arma[]={7,6,5};
int CierraEntrada=0;
int FuegoEntrada=0;
int ChispaEntrada=0;
int AdelanteEntrada=0;
int AtrasEntrada=0;
int IzquierdaEntrada=0;
int DerechaEntrada=0;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
/*Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *backMotor = AFMS.getMotor(1);
Adafruit_DCMotor *frontMotor = AfterMS.getMotor(3);
*/
void setup()
{
  //Setup usb serial connection to computer
  Serial.begin(9600);

  //Setup Bluetooth serial connection to android
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);
  for (int count = 0; count < 4; count++) {
    pinMode(motorPins[count], OUTPUT);
  }
    for (int count = 0; count < 3; count++) {
    pinMode(arma[count], OUTPUT);
  }
  pinMode(13,OUTPUT);
/*

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  // Set the speed to start, from 0 (off) to 255 (max speed)
  backMotor->setSpeed(255);
  backMotor->run(FORWARD);
  // turn on motor
  backMotor->run(RELEASE);

  frontMotor->setSpeed(255);
  frontMotor->run(FORWARD);
  // turn on motor
  frontMotor->run(RELEASE);*/

}

void loop()
{ 
  //Read from bluetooth and write to usb serial 
  if(bluetooth.available())
  {
    char toSend = (char)bluetooth.read();
    Serial.print(toSend);
 AdelanteEntrada=0;
 AtrasEntrada=0;
 IzquierdaEntrada=0;
 DerechaEntrada=0;

cierra(CierraEntrada);
fuego(FuegoEntrada);
chispa(ChispaEntrada);

    // After the android device sends the data the arduino takes the information and reads it as a char,
    // This code is here to read that data and turn it into actions for the motors.
    if(toSend == 'F'){
    //  backMotor->run(FORWARD);
      AdelanteEntrada=1;
      
//      delay(1500);
    } 

    if(toSend == 'B'){
       AtrasEntrada=1;
      
    //  delay(500);
      //backMotor->run(BACKWARD);
    } 

    if(toSend == 'L'){
         IzquierdaEntrada=1;
     // frontMotor->run(FORWARD);
    } 

    if(toSend == 'R'){
      DerechaEntrada=1;

   //   frontMotor->run(BACKWARD);
    } 

    if(toSend == 'G'){ //FL
          AdelanteEntrada=1;
          IzquierdaEntrada=1;
  
  //    frontMotor->run(BACKWARD);
   //   backMotor->run(FORWARD);
    } 

    if(toSend == 'I'){ //FR
          AdelanteEntrada=1;
      DerechaEntrada=1;
//frontMotor->run(FORWARD);
      //backMotor->run(FORWARD);
    } 

    if(toSend == 'H'){//BL 
       AtrasEntrada=1;
          IzquierdaEntrada=1;

       //frontMotor->run(BACKWARD);
      //backMotor->run(BACKWARD);
    } 

    if(toSend == 'J'){//BR
       AtrasEntrada=1;
      DerechaEntrada=1;
      //frontMotor->run(FORWARD);
      //backMotor->run(BACKWARD);
    } 

    if (toSend == 'S'){
      digitalWrite(motorPins[0], LOW);
      digitalWrite(motorPins[1], LOW);
      digitalWrite(motorPins[2], LOW);
      digitalWrite(motorPins[3], LOW);
      //frontMotor->run(RELEASE);
      //backMotor->run(RELEASE);
    }
       
    if (toSend == 'W'){
      CierraEntrada=1;
    
      //frontMotor->run(RELEASE);
      //backMotor->run(RELEASE);
    }
    if (toSend == 'w'){
    CierraEntrada=0;
      //frontMotor->run(RELEASE);
      //backMotor->run(RELEASE);
    }
    if (toSend == 'U'){
      FuegoEntrada=1;
      //frontMotor->run(RELEASE);
      //backMotor->run(RELEASE);
    }
    if (toSend == 'u'){
      FuegoEntrada=0;
      //frontMotor->run(RELEASE);
      //backMotor->run(RELEASE);
    }
    if (toSend == 'V'){
      ChispaEntrada=1;
      //frontMotor->run(RELEASE);
      //backMotor->run(RELEASE);
    }
    if (toSend == 'v'){
      ChispaEntrada=0;
      //frontMotor->run(RELEASE);
      //backMotor->run(RELEASE);
    }
    if (toSend == 'X'){
      FuegoEntrada=1;
      ChispaEntrada=1;
      //frontMotor->run(RELEASE);
      //backMotor->run(RELEASE);
    }
    if (toSend == 'x'){
      FuegoEntrada=0;
      ChispaEntrada=0;
      //frontMotor->run(RELEASE);
      //backMotor->run(RELEASE);
    }
      adelante(AdelanteEntrada);
    atras(AtrasEntrada);
    izquierda(IzquierdaEntrada);
    derecha(DerechaEntrada);

  }


  // This was for reading to serial during the testing phase

  //  //Read from usb serial to bluetooth
  if(Serial.available())
  {
    char toSend = (char)Serial.read();
    bluetooth.print(toSend);
  }
}

void cierra(int e){
  if (e==1){
digitalWrite(arma[0], HIGH);
}
if (e==0){
  digitalWrite(arma[0], LOW);
}
}
void fuego(int e){
  if (e==1){
digitalWrite(arma[1], HIGH);
}
if (e==0){
  digitalWrite(arma[1], LOW);
}
}
void chispa(int e){
  if (e==1){
digitalWrite(arma[2], HIGH);
}
if (e==0){
  digitalWrite(arma[2], LOW);
}
}
// MOVIMIENTO
void adelante(int e){
  if (e==1){
digitalWrite(motorPins[0], HIGH);
}
if (e==0){
  digitalWrite(motorPins[0], LOW);
}
}
void atras(int e){
  if (e==1){
digitalWrite(motorPins[1], HIGH);
}
if (e==0){
  digitalWrite(motorPins[1], LOW);
}
}
void izquierda(int e){
  if (e==1){
digitalWrite(motorPins[2], HIGH);
}
if (e==0){
  digitalWrite(motorPins[2], LOW);
}
}
void derecha(int e){
  if (e==1){
digitalWrite(motorPins[3], HIGH);
}
if (e==0){
  digitalWrite(motorPins[3], LOW);
}
}





