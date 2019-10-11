#include <Wire.h>
#include <stdlib.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Directions from the pov of the robot
const int sensorLeftPin = A1;
const int sensorRightPin = A0;

// Values read from the sensors
int sensorLeft = 0;
int sensorRight = 0;

// speed initialization
int speed = 25;
int leftWheelSpeed = speed;
int rightWheelSpeed = speed;

int state = 0; // state of the robot (-1: left of line, 1: right of line)

// initialize the motors
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motorRight = AFMS.getMotor(2);
Adafruit_DCMotor *motorLeft = AFMS.getMotor(3);

void setup() {
  // put your setup code here, to run once:
  AFMS.begin();
  motorLeft->setSpeed(25);
  motorRight->setSpeed(25);
  motorLeft->run(BACKWARD);
  motorRight->run(BACKWARD);
  Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {    // is a character available?
      speed = Serial.readString().toInt(); // read the number and set it to speed
    }

    // Print the sensor data, wheel speeds, andd time
    sensorLeft = analogRead(sensorLeftPin);
    sensorRight = analogRead(sensorRightPin);
    Serial.print(sensorLeft);
    Serial.print(",");
    Serial.print(sensorRight);
    Serial.print(",");
    Serial.print(leftWheelSpeed);
    Serial.print(",");
    Serial.print(rightWheelSpeed);
    Serial.print(",");
    Serial.println(millis());

  if (sensorLeft < 100 && sensorRight > 300) {
    // if slightly to the left, turn right
    state = turnR();
  }
  else if (sensorLeft > 450 && sensorRight < 420) {
    // if slightly to the right, turn left
    state = turnL();
  }
  else if (sensorLeft < 100 && sensorRight < 400) {
    // if off the line
    if (state == -1) { // if went off to the left
      state = turnR();
    }
    else if (state == 1) { // if went off to the right
      state = turnL();
    }
  }
  else {
    straight();
  }
}

int turnR() {
  leftWheelSpeed = speed + 10;
  rightWheelSpeed = 0;
  motorLeft->setSpeed(leftWheelSpeed);
  motorRight->setSpeed(rightWheelSpeed);
  delay(100);
  return -1;
}
int turnL() {
  rightWheelSpeed = speed + 10;
  leftWheelSpeed = 0;
  motorLeft->setSpeed(leftWheelSpeed);
  motorRight->setSpeed(rightWheelSpeed);
  delay(100);
  return 1;
}

void straight() {
  leftWheelSpeed = speed;
  rightWheelSpeed = speed;
  motorLeft->setSpeed(leftWheelSpeed);
  motorRight->setSpeed(rightWheelSpeed);
  delay(100);
}
