// The ports of all of the devices
const int buttonPin = 2;
const int yellow1 = 5;
const int red1 = 6;
const int yellow2 = 10;
const int red2 = 11;

unsigned long nextTime = 500; // next time in millis() to change light, unsigned - no neg time
int inc = 500; // increment of changing lights
int light_mode = 1; // The initial lighting mode
int state = 0; // state of the leds

bool ignoreButton = true; // ignore button input
unsigned long buttonResetTime = 500; // time until the button will be read again

void setup() {
  // Set the pinmodes
  pinMode(yellow1, OUTPUT);
  pinMode(red1, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  if (ignoreButton == false) {
    int buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      // if the button is pressed
      light_mode += 1;
      if (light_mode > 5) {
        light_mode = 0; // wrap around to the first light_mode
      }
      // buttonState = false;
      ignoreButton = true;
      buttonResetTime = millis() + 500;
    }
  }
  else if (millis() > buttonResetTime) {
    // if have reached the time for the button to reset
    ignoreButton = false;
  }

  int pot = analogRead(A0); // brightness control

  if (millis() > nextTime) {
    nextTime = millis() + inc; // the next time to update
    if (light_mode == 0) {
      state = all_off();
    }
    else if (light_mode == 1) {
      state = all_on(pot);
    }
    else if (light_mode == 2) {
      state = all_flash(pot, state);
    }
    else if (light_mode == 3) {
      state = sequence(pot, state);
    }
    else if (light_mode == 4) {
      state = left(pot, state);
    }
    else if (light_mode == 5) {
      state = right(pot, state);
    }
  }
}

int all_off() {
  //turns all the leds off
  digitalWrite(yellow1, LOW);
  digitalWrite(red1, LOW);
  digitalWrite(yellow2, LOW);
  digitalWrite(red2, LOW);
  return 0;
}

int all_on(int pot) {
  //turns all the leds on
  analogWrite(yellow1, pot / 4);
  analogWrite(red1, pot / 4);
  analogWrite(yellow2, pot / 4);
  analogWrite(red2, pot / 4);
  return 1;
}

int all_flash(int pot, int state) {
  //make all the leds flash together
  if (state != 0) { // if not off, turn off
    return all_off();
  }
  else {
    return all_on(pot);
  }
}

int sequence(int pot, int state) {
  //have the leds run in order
  if (state > 0) {
    return all_off();
  }
  else if (state == 0) {
    // turn on yellow1
    analogWrite(yellow1, pot / 4);
    return -1;
  }
  else if (state == -1) {
    // turn off yellow1
    digitalWrite(yellow1, LOW);
    return -2;
  }
  else if (state == -2) {
    // turn on red1
    analogWrite(red1, pot / 4);
    return -3;
  }
  else if (state == -3) {
    digitalWrite(red1, LOW);
    return -4;
  }
  else if (state == -4) {
    // turn on yellow2
    analogWrite(yellow2, pot / 4);
    return -5;
  }
  else if (state == -5) {
    // turn off yellow2
    digitalWrite(yellow2, LOW);
    return -6;
  }
  else if (state == -6) {
    // turn on red1
    analogWrite(red2, pot / 4);
    return -7;
  }
  else if (state == -7) {
    digitalWrite(red2, LOW);
    return 0;
  }
}

int left(int pot, int state) {
  //use the left two lights as a turn signal
  if (state != 0) {
    return all_off();
  }
  else {
    analogWrite(red2, pot / 4);
    analogWrite(yellow2, pot / 4);
    return 11;
  }
}

int right(int pot, int state) {
  //use the right two lights as a turn signal
  if (state != 0) {
    return all_off();
  }
  else {
    analogWrite(red1, pot / 4);
    analogWrite(yellow1, pot / 4);
    return 12;
  }
}
