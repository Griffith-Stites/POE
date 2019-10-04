

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
  // put your setup code here, to run once:
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
  Serial.print("sensorLeft = ");
  Serial.println(sensorLeft);
  Serial.print("sensorRight = ");
  Serial.println(sensorRight);
  // if in even farther left and off, go right

  //  if (sensorLeft < 290 && sensorRight < 420) {
  //    // if on the line
  //  }

  // have a state of the last one
  // if it goes off, we can use the integer 
  // if it was too

  // if off the line, look at the last state, correct that direction

  if (sensorLeft < 65 && sensorRight > 420) {
    // if slightly to the left, turn right
    Serial.println("RIGHT");
    motorLeft->setSpeed(20);
    motorRight->setSpeed(0);
    delay(100);
  }
  else if (sensorLeft > 450 && sensorRight < 420) {
    // if slightly to the right, turn left
    Serial.println("LEFT");
    motorLeft->setSpeed(0);
    motorRight->setSpeed(20);
    delay(100);
  }
  else {
    // go forward
    Serial.println("FORWARD");
    motorLeft->setSpeed(20);
    motorRight->setSpeed(20);
  }

  // put your main code here, to run repeatedly:
}
