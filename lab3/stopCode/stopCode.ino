

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motorRight = AFMS.getMotor(2);
Adafruit_DCMotor *motorLeft = AFMS.getMotor(3);

void setup() {
  // put your setup code here, to run once:
  AFMS.begin();
  motorLeft->setSpeed(0);
  motorRight->setSpeed(0);
}

void loop() {
  motorLeft->run(BACKWARD);
  motorRight->run(BACKWARD);
}
