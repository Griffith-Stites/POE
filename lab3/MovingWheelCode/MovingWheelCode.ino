

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
  motorLeft->setSpeed(20);
  motorRight->setSpeed(20);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorLeft = analogRead(sensorLeftPin);
  sensorRight = analogRead(sensorRightPin);
  Serial.print("sensorLeft = ");
  Serial.println(sensorLeft);
  Serial.print("sensorRight = ");
  Serial.println(sensorRight);
  // 500
  if (sensorLeft > 500) {
    // turn right
    motorRight->setSpeed(0);
    delay(300);
  }
  // 295
  else if (sensorRight > 400) {
    // turn left
    motorLeft->setSpeed(0);
    delay(300);
  }
  else {
    Serial.print("HELLO");
    motorLeft->setSpeed(20);
    motorRight->setSpeed(20);
    motorLeft->run(BACKWARD);
    motorRight->run(BACKWARD);
  }
}
