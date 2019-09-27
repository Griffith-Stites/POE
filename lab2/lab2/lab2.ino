#include <Servo.h> // Include the servo library

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int panPin = 5; // Digital input pin for the servo angle signal
const int tiltPin = 6; // Digital input pin for the servo angle signal

int sensorValue = 0;        // value read from the pot
int pan = 0; // variable to store the servo position

Servo servo1;  // create servo object to control a servo

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  servo1.attach(panPin);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (pan = 0; pan <= 60; pan += 1) { // goes from 0 degrees to 60 degrees in steps of 1 degree
    servo1.write(pan + 60); // tell servo1 to go to position in variable 'pan'
    delay(15); // waits 15ms for the servo to reach the position
    delay(100); // waits 100ms for the sensor power to fluctuate, 40ms according to the datasheet, 100ms for good measure
    sensorValue = analogRead(analogInPin); // read the sensnor value
    printStatus(sensorValue, pan, 1);
  }
  Serial.println("finished");
  delay(3000);
}


void printStatus(int sensor, int pan, int tilt) {
  // print the results to the Serial Monitor:
  Serial.print(sensorValue);
  Serial.print(',');
  Serial.print(pan);
  Serial.print(',');
  Serial.print(tilt);
  Serial.println();
}
