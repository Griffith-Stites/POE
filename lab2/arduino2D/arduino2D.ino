#include <Servo.h> // Include the servo library

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the IR sensor
const int panPin = 5; // Digital output pin for the servo angle signal
const int tiltPin = 6; // Digital output pin for the servo angle signal

// values read from the IR sensor
int sensorValue = 0;
int read1 = 0;
int read2 = 0;
int read3 = 0;

int pan = 0; // variable to store the servo position

Servo servo1;  // create servo object to control a servo

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  servo1.attach(panPin);  // attaches the servo on pin 5 to the servo object
}

void loop() {
  Serial.println("start");
  for (pan = 80; pan <= 110; pan += 1) { // goes from 0 degrees to 60 degrees in steps of 1 degree
    servo1.write(pan); // tell servo1 to go to position in variable 'pan'
    delay(100); // waits 100ms for the sensor power to fluctuate, 40ms according to the datasheet, 100ms for good measure
    sensorValue = readSensor();
    printStatus(sensorValue, pan, 1);
  }
  Serial.println("finished");
  delay(3000);
}

int readSensor(){
  // read the sensor and average the results
  read1 = analogRead(analogInPin); // read the sensor value
  delay(15);
  read2 = analogRead(analogInPin); // read the sensor value
  delay(15);
  read3 = analogRead(analogInPin); // read the sensor value
  delay(15);
  sensorValue = (read1 + read2 + read3) / 3;
  return sensorValue;
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
