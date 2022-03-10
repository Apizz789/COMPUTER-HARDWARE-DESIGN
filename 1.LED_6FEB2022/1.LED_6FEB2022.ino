int ledStep = 100;
unsigned long width = 10000;
unsigned long runTime = 0;
unsigned long patternTime = 0;
int currentLEDStep[8];
unsigned long onTime[8];
unsigned long offTime[8];
unsigned long onLength[8];
unsigned long offLength[8];
bool isOn[8];
int ledPin[8];
int pattern = 1;

void initVar() {
  for (int i = 0; i < 8; i++) {
    onLength[i] = 0;
    offLength[i] = width - onLength[i];
    currentLEDStep[i] = 0;
    isOn[i] = false;
  }
}

void calculatePluseWidth(int n, int i) {
  onLength[i] = (width / ledStep) * n;
  offLength[i] = width - onLength[i];
}

void led(int i) {

  if (onLength[i] != 0 && !isOn[i] && micros() >= onTime[i]) {
    digitalWrite(ledPin[i], HIGH);
    isOn[i] = true;
    offTime[i] = micros() + onLength[i];
  }

  if (offLength[i] != 0 && isOn[i] && micros() >= offTime[i]) {
    digitalWrite(ledPin[i], LOW);
    isOn[i] = false;
    onTime[i] = micros() + offLength[i];
  }

}

void setStep(int n) {
  switch (n) {
    case 1:
      for (int i = 0; i < 8; i += 1) {
        currentLEDStep[i] += 1;
        if (currentLEDStep[i] > ledStep) {
          currentLEDStep[i] = 0;
        }
      }
      break;
    case 2:
      for (int i = 0; i < 8; i += 1) {
        currentLEDStep[i] -= 1;
        if (currentLEDStep[i] <= 0 ) {
          currentLEDStep[i] = ledStep;
        }
      }
      break;
    default:
      for (int i = 0; i < 4; i += 1) {
        currentLEDStep[i] += 1;
        if (currentLEDStep[i] > ledStep) {
          currentLEDStep[i] = 0;
        }
      }
      for (int i = 4; i < 8; i += 1) {
        currentLEDStep[i] -= 1;
        if (currentLEDStep[i] <= 0) {
          currentLEDStep[i] = ledStep;
        }
      }
      break;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 2; i < 10; i++) {
    pinMode(i, OUTPUT);
    ledPin[i - 2] = i;
  }
  initVar();
}

void loop() {
  for (int i = 0; i < 8; i++)
    led(i);
  if (millis() - runTime >= 50) {
    runTime = millis();
    setStep(pattern);
    for (int i = 0; i < 8; i++) {
      calculatePluseWidth(currentLEDStep[i], i);
    }
  }

  if (millis() - patternTime >= 20000) {
    patternTime = millis();
    pattern += 1;
    if (pattern >= 2) {
      pattern = 0;
    }
    switch (pattern) {
      case 1:
        for (int i = 0; i < 8; i++)
          currentLEDStep[i] = 0;
        break;
      case 2:
        for (int i = 0; i < 8; i++)
          currentLEDStep[i] = int(ledStep / 8) * i;
        break;
    }
    for (int i = 2; i < 10; i++) {
      digitalWrite(i, HIGH);
    }
    delay(250);
    for (int i = 2; i < 10; i++) {
      digitalWrite(i, LOW);
    }
    delay(250);
    for (int i = 2; i < 10; i++) {
      digitalWrite(i, HIGH);
    }
    delay(250);
    for (int i = 2; i < 10; i++) {
      digitalWrite(i, LOW);
    }
    delay(250);

  }
}
