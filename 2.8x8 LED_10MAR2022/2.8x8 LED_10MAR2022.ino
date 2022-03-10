int pins_cathode[8] = {2, 3, 4, 5, 6, 7, 8, 9};
int ic_digit_pin[3] = {10, 11, 12};
int delayTime = 100;

int H_lt[7] = {17, 17, 17, 31, 17, 17, 17};
int E_lt[7] = {31, 1, 1, 15, 1, 1, 31};
int L_lt[7] = {1, 1, 1, 1, 1, 1, 31};
int O_lt[7] = {14, 17, 17, 17, 17, 17, 14};
int star_lt[7] = {0, 1 + 4 + 16, 2 + 4 + 8, 31, 2 + 4 + 8, 1 + 4 + 16, 0};


void prntstar() {
  for (int i = 0 ; i < 7 ; i++) {
    anode(i);
    cathode(star_lt[i] * 4);
    delayMicroseconds(500);
    cathode(0);

  }
}

void prntH() {
  for (int i = 0 ; i < 7 ; i++) {
    anode(i);
    cathode(H_lt[i] * 4);
    delayMicroseconds(1000);
    cathode(0);

  }
}

void prntE() {
  for (int i = 0 ; i < 7 ; i++) {
    anode(i);
    cathode(E_lt[i] * 4);
    delayMicroseconds(500);
    cathode(0);

  }
}

void prntL() {
  for (int i = 0 ; i < 7 ; i++) {
    anode(i);
    cathode(L_lt[i] * 4);
    delayMicroseconds(500);
    cathode(0);

  }
}

void prntO() {
  for (int i = 0 ; i < 7 ; i++) {
    anode(i);
    cathode(O_lt[i] * 4);
    delayMicroseconds(500);
    cathode(0);

  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  for (int i = 0; i < 8; ++i) {
    pinMode(pins_cathode[i], OUTPUT);
    digitalWrite(pins_cathode[i], HIGH);
  }
  for (int i = 0; i < 3; ++i) {
    pinMode(ic_digit_pin[i], OUTPUT);
    digitalWrite(ic_digit_pin[i], LOW);
  }
  pinMode(13, OUTPUT);


}


void loop() {
  // put your main code here, to run repeatedly:
  if (analogRead(A3) < 100) {
    rise();
    highAll(0.5);
    dim();
  }

  if (analogRead(A4) < 100) {
    unsigned long temp = millis();
    pattern4(50);
    digitalWrite(13, 1);
    resetLed();
    delay(500);
  }
  if (analogRead(A5) < 100) {
  unsigned long temp = millis();
    while (millis() - temp < 500) {


      //    pattern2(50);
      //  pattern1(50);
      //  pattern2(50);
      //  pattern3(50);
      //  pattern4(50);


      prntH();
    }
    resetLed();
    delay(500);
    temp = millis();
    while (millis() - temp < 500) {
      prntE();
    }
    resetLed();
    delay(500);
    temp = millis();
    while (millis() - temp < 500) {
      prntL();
    }
    resetLed();
    delay(500);
    temp = millis();
    while (millis() - temp < 500) {
      prntL();
    }
    resetLed();
    delay(500);
    temp = millis();
    while (millis() - temp < 500) {
      prntO();
    }

    resetLed();
    delay(500);
    temp = millis();
    while (millis() - temp < 500) {
      prntstar();
    }
  }






}

void dim() {
  unsigned long temp = micros();
  int j = 0;
  for (int i = 0 ; i < 100 ; i++) {
    temp = micros();
    while (micros() - temp < 200) {
      highAllMicroSec(10000 - j);
      resetLed();
      delayMicroseconds(j);
      j += 100;
    }
  }
}

void rise() {
  unsigned long temp = micros();
  int j = 0;
  for (int i = 0 ; i < 100 ; i++) {
    temp = micros();
    while (micros() - temp < 300) {
      highAllMicroSec(j);
      resetLed();
      delayMicroseconds(10000 - j);
      j += 100;
    }
  }
}

void pattern1(double sec) {
  for (int i = 0 ; i < 8 ; i++) {
    anode(i);
    int pin = 1;
    for (int j = 0 ; j < 8 ; j++) {
      cathode(pin);
      pin = pin * 2;
      delay(sec);
    }
  }
}

void pattern2(double sec) {
  for (int i = 0 ; i < 8 ; i++) {
    anode(i);
    int pin = 1;
    for (int j = 0 ; j < 7 ; j++) {
      cathode(pin + pin * 2);
      pin = pin * 2;
      delay(sec);
    }
  }
}

void pattern3(double sec) {
  for (int i = 0 ; i < 8 ; i++) {
    anode(i);
    int pin = 15;
    for (int j = 0 ; j < 5 ; j++) {
      cathode(pin);
      pin = pin * 2;
      delay(sec);
    }
  }
}

void pattern4(double sec) {
  int pattern[5] = {129, 66, 36, 24, 255};
  for (int i = 0 ; i < 8 ; i++) {
    anode(i);
    int pin = 1;
    for (int j = 0 ; j < 5 ; j++) {
      cathode(pattern[j]);
      delay(sec);
    }
  }
}

void highAllMicroSec(unsigned long microSec) {
  unsigned long temp = micros();
  while (micros() - temp < microSec) {
    cathode(255);
    for (int i = 0; i < 8; ++i) {
      anode(i);
    }
  }
}

void highAll(double sec) {
  unsigned long temp = millis();
  while (millis() - temp < sec * 1000) {
    cathode(255);
    for (int i = 0; i < 8; ++i) {
      anode(i);
    }
  }
}

void resetLed() {
  for (int i = 0; i < 8; ++i) {
    digitalWrite(pins_cathode[i], HIGH);
  }
}

void cathode(int data) {
  for (int i = 0; i < 8; ++i) {
    digitalWrite(pins_cathode[i], !(data & 1));
    data = data >> 1;
  }
}

void anode(int pin) {
  switch (pin) {
    case 0:
      digitalWrite(ic_digit_pin[0], LOW);
      digitalWrite(ic_digit_pin[1], LOW);
      digitalWrite(ic_digit_pin[2], LOW);
      break;
    case 1:
      digitalWrite(ic_digit_pin[0], HIGH);
      digitalWrite(ic_digit_pin[1], LOW);
      digitalWrite(ic_digit_pin[2], LOW);
      break;
    case 2:
      digitalWrite(ic_digit_pin[0], LOW);
      digitalWrite(ic_digit_pin[1], HIGH);
      digitalWrite(ic_digit_pin[2], LOW);
      break;
    case 3:
      digitalWrite(ic_digit_pin[0], HIGH);
      digitalWrite(ic_digit_pin[1], HIGH);
      digitalWrite(ic_digit_pin[2], LOW);
      break;
    case 4:
      digitalWrite(ic_digit_pin[0], LOW);
      digitalWrite(ic_digit_pin[1], LOW);
      digitalWrite(ic_digit_pin[2], HIGH);
      break;
    case 5:
      digitalWrite(ic_digit_pin[0], HIGH);
      digitalWrite(ic_digit_pin[1], LOW);
      digitalWrite(ic_digit_pin[2], HIGH);
      break;
    case 6:
      digitalWrite(ic_digit_pin[0], LOW);
      digitalWrite(ic_digit_pin[1], HIGH);
      digitalWrite(ic_digit_pin[2], HIGH);
      break;
    case 7:
      digitalWrite(ic_digit_pin[0], HIGH);
      digitalWrite(ic_digit_pin[1], HIGH);
      digitalWrite(ic_digit_pin[2], HIGH);
      break;

  }
}
