

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Directions from the pov of the robot
const int sensorLeftPin = A0;
const int sensorRightPin = A1;

// Values read from the sensors
int sensorLeft = 0;
int sensorRight = 0;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motorRight = AFMS.getMotor(2);
Adafruit_DCMotor *motorLeft = AFMS.getMotor(3);

void setup() {
  // put your setup code here, to run once:
  AFMS.begin();
  motorLeft->setSpeed(15);
  motorRight->setSpeed(15);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorLeft = analogRead(sensorLeftPin);
  sensorRight = analogRead(sensorRightPin);

  if (sensorLeft > 500) {
    // turn right
    motorRight->setSpeed(0);
  }
  else if (sensorRight > 295) {
    // turn left
    motorLeft->setSpeed(0);
  }
  else {
    motorLeft->setSpeed(15);
    motorRight->setSpeed(15);
    motorLeft->run(BACKWARD);
    motorRight->run(BACKWARD);
  }
}
