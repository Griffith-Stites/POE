#include <Servo.h> // Include the servo library

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the IR sensor
const int panPin = 5; // Digital output pin for the servo angle signal
const int tiltPin = 6; // Digital output pin for the servo angle signal

// values read from the IR sensor
int sensorValue = 0;

int pan = 0; // variable to store the pan
int tilt = 0; // variable to store the tilt

Servo servoPan;  // create servo object to control pan servo
Servo servoTilt; // create servo object to control tilt servo

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  servoPan.attach(panPin);
  servoTilt.attach(tiltPin);
}

void loop() {
  Serial.println("start");
  for (pan = 65; pan <= 115; pan += 1) { // goes from 80 degrees to 110 degrees in steps of 1 degree
    servoPan.write(pan); // tell servoPan to go to position in variable 'pan'
    delay(50); // waits 50ms for the servo to move
    for (tilt = -10; tilt <= 35; tilt += 1) { // for every pan degree, check every tilt degree from -20 to 20
      servoTilt.write(-tilt+90); // tell servoTilt to go to position in variable 'tilt'
      // +90 to account for the servo zero
      // -tilt because the servo domain is opposite the spherical domain we want our sensor to work in
      delay(500); // waits 80ms for the sensor power to fluctuate, 40ms according to the datasheet, 100ms for good measure and for the tilt to move
      sensorValue = analogRead(analogInPin);
      printStatus(sensorValue, pan, tilt);
    }
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
