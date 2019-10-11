

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Directions from the pov of the robot
const int sensorLeftPin = A1;
const int sensorRightPin = A0;

// Values read from the sensors
int sensorLeft = 0;
int sensorRight = 0;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motorRight = AFMS.getMotor(2);
Adafruit_DCMotor *motorLeft = AFMS.getMotor(3);

void setup() {
  AFMS.begin();
  motorLeft->setSpeed(20);
  motorRight->setSpeed(20);
  motorLeft->run(BACKWARD);
  motorRight->run(BACKWARD);
  Serial.begin(9600);
}

void loop() {
  sensorLeft = analogRead(sensorLeftPin);
  sensorRight = analogRead(sensorRightPin);
  // Print sensor values
  Serial.print("sensorLeft = ");
  Serial.println(sensorLeft);
  Serial.print("sensorRight = ");
  Serial.println(sensorRight);
  
  if (sensorLeft > 450) {
    // turn left
    motorLeft->setSpeed(0);
    motorRight->setSpeed(20);
    delay(300);
  }
  else if (sensorRight > 420) {
    // turn right
    motorLeft->setSpeed(20);
    motorRight->setSpeed(0);
    delay(300);
  }
  else {
    // go straight
    motorLeft->setSpeed(20);
    motorRight->setSpeed(20);
  }
}
