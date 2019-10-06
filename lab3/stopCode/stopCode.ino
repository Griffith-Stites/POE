

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motorRight = AFMS.getMotor(2);
Adafruit_DCMotor *motorLeft = AFMS.getMotor(3);

// Directions from the pov of the robot
const int sensorLeftPin = A1;
const int sensorRightPin = A0;

// Values read from the sensors
int sensorLeft = 0;
int sensorRight = 0;

void setup() {
  // put your setup code here, to run once:
  AFMS.begin();
  motorLeft->setSpeed(0);
  motorRight->setSpeed(0);
  Serial.begin(9600);
}

void loop() {
  sensorLeft = analogRead(sensorLeftPin);
  sensorRight = analogRead(sensorRightPin);
  Serial.print("sensorLeft = ");
  Serial.println(sensorLeft);
  Serial.print("sensorRight = ");
  Serial.println(sensorRight);
  motorLeft->run(BACKWARD);
  motorRight->run(BACKWARD);
}
