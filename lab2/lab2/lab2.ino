// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot
unsigned long resetTime = 10000;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  printStatus(sensorValue, 1, 1);
  delay(100);
  if (millis() > resetTime){
    Serial.println("finished");
    resetTime += 10000;
    
  }
}

void printStatus(int sensor, int axis1, int axis2){
  // print the results to the Serial Monitor:
  Serial.print(sensorValue);
  Serial.print(',');
  Serial.print(axis1);
  Serial.print(',');
  Serial.print(axis2);
  Serial.println();
}
