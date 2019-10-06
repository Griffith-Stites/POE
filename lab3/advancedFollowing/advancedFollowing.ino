

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Directions from the pov of the robot
const int sensorLeftPin = A1;
const int sensorRightPin = A0;

// Values read from the sensors
int sensorLeft = 0;
int sensorRight = 0;

int state = 0; // state of the robot (0: on line, -1: left of line, 1: right of line)

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motorRight = AFMS.getMotor(2);
Adafruit_DCMotor *motorLeft = AFMS.getMotor(3);

// functions to go to the right, straight, and left
// able to control speed over serial

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
    sensorLeft = analogRead(sensorLeftPin);
    sensorRight = analogRead(sensorRightPin);
  //  Serial.print("sensorLeft = ");
  //  Serial.println(sensorLeft);
  //  Serial.print("sensorRight = ");
  //  Serial.println(sensorRight);

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
    Serial.println("FAILSAFE");
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

  // put your main code here, to run repeatedly:
}

int turnR() {
  Serial.println("RIGHT");
  motorLeft->setSpeed(35);
  motorRight->setSpeed(0);
  delay(100);
  return -1;
}
int turnL() {
  Serial.println("LEFT");
  motorLeft->setSpeed(0);
  motorRight->setSpeed(35);
  delay(100);
  return 1;
}

void straight() {
  // go forward
  Serial.println("FORWARD");
  motorLeft->setSpeed(25);
  motorRight->setSpeed(25);
  delay(100);
}
