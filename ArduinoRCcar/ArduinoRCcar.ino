#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include <SoftwareSerial.h>

int bluetoothTx = 2;
int bluetoothRx = 3;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *backMotor = AFMS.getMotor(1);
Adafruit_DCMotor *frontMotor = AFMS.getMotor(3);

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
  frontMotor->run(RELEASE);

}

void loop()
{ 
  //Read from bluetooth and write to usb serial 
  if(bluetooth.available())
  {
    char toSend = (char)bluetooth.read();
    Serial.print(toSend);


    // After the android device sends the data the arduino takes the information and reads it as a char,
    // This code is here to read that data and turn it into actions for the motors.
    if(toSend == 'f'){
      backMotor->run(FORWARD);
    } 

    if(toSend == 'b'){
      backMotor->run(BACKWARD);
    } 

    if(toSend == 'l'){
      frontMotor->run(FORWARD);
    } 

    if(toSend == 'r'){
      frontMotor->run(BACKWARD);
    } 

    if(toSend == 'rf'){
      frontMotor->run(BACKWARD);
      backMotor->run(FORWARD);
    } 

    if(toSend == 'lf'){
      frontMotor->run(FORWARD);
      backMotor->run(FORWARD);
    } 

    if(toSend == 'rb'){
      frontMotor->run(BACKWARD);
      backMotor->run(BACKWARD);
    } 

    if(toSend == 'lb'){
      frontMotor->run(FORWARD);
      backMotor->run(BACKWARD);
    } 

    if (toSend == 's'){
      frontMotor->run(RELEASE);
      backMotor->run(RELEASE);
    }

  }


  // This was for reading to serial during the testing phase

  //  //Read from usb serial to bluetooth
  if(Serial.available())
  {
    char toSend = (char)Serial.read();
    bluetooth.print(toSend);
  }
}






