

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(3);

void setup() {
  // put your setup code here, to run once:
AFMS.begin();
myMotor->setSpeed(0);
myMotor2->setSpeed(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  myMotor->run(FORWARD);
  myMotor2->run(FORWARD);


}
