#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 in PCF8574 by NXP and Set to 0x3F in PCF8574A by Ti
LiquidCrystal_I2C lcd(0x3F, 16, 2);

byte a[] = {
  B00000,
  B00000,
  B01000,
  B01000,
  B01000,
  B01100,
  B01100,
  B00000
};

byte vo[] = {
  B00000,
  B00000,
  B01110,
  B01010,
  B00010,
  B00110,
  B00110,
  B00000
};

byte la[] = {
  B00000,
  B00000,
  B01110,
  B00010,
  B01110,
  B01010,
  B01010,
  B00000
};

byte r[] = {
  B00000,
  B00000,
  B01110,
  B01010,
  B00010,
  B00010,
  B00010,
  B00000
};

byte n0[] = {
  B00000,
  B00000,
  B01110,
  B10001,
  B10001,
  B10001,
  B01110,
  B00000
};

byte n1[] = {
  B00000,
  B00000,
  B01110,
  B10001,
  B01101,
  B00001,
  B01110,
  B00000
};

byte n2[] = {
  B10000,
  B10000,
  B11010,
  B10101,
  B10001,
  B10001,
  B11111,
  B00000
};

byte n3[] = {
  B00000,
  B00000,
  B01010,
  B10101,
  B10101,
  B10001,
  B11001,
  B00000
};

byte n4[] = {
  B00000,
  B00010,
  B01110,
  B10000,
  B10110,
  B10100,
  B11111,
  B00000
};

byte n5[] = {
  B00000,
  B00101,
  B01110,
  B10000,
  B10110,
  B10100,
  B11111,
  B00000
};

byte n6[] = {
  B00000,
  B10000,
  B01110,
  B00001,
  B01001,
  B10001,
  B01110,
  B00000
};

byte n7[] = {
  B00001,
  B00001,
  B01011,
  B10101,
  B10101,
  B10001,
  B11001,
  B00000
};

byte n8[] = {
  B00000,
  B00001,
  B01110,
  B10000,
  B10001,
  B10111,
  B01010,
  B00000
};

byte n9[] = {
  B00000,
  B00001,
  B00010,
  B01110,
  B10100,
  B11010,
  B01001,
  B00000
};

byte dc[] = {
  B00000,
  B00000,
  B00000,
  B00100,
  B00000,
  B00100,
  B00000,
  B00000
};

byte *numList[] = {n0, n1, n2, n3, n4, n5, n6, n7, n8, n9};
static uint32_t last_time, now = 0;

int h = 23;
int h1,h2;
int m = 59;
int m1,m2;
int s = 55;
int s1,s2;


bool clockSet = false;
struct SetButtonPin{
    uint8_t set = 0;
    uint8_t hour = 0;
    uint8_t min = 0;
    uint8_t sec = 0;

    unsigned long millisSet = 0;
    unsigned long millisHour = 0;
    unsigned long millisMin = 0;
    unsigned long millisSec = 0;
}button;

void buttonSetup(uint8_t modePin, uint8_t hourPin, uint8_t minPin, uint8_t secPin){
    button.set = modePin;
    button.hour = hourPin;
    button.min = minPin;
    button.sec = secPin;

    pinMode(button.set, INPUT_PULLUP);
    pinMode(button.hour, INPUT_PULLUP);
    pinMode(button.min, INPUT_PULLUP);
    pinMode(button.sec, INPUT_PULLUP);
}
void readButtonsInput(){
    const int debounceDelay = 100;

    if(digitalRead(button.set) == HIGH && millis() - button.millisSet > debounceDelay){
        clockSet = !clockSet;
        button.millisSet = millis();
    }
    if(clockSet){
        if(digitalRead(button.hour) == HIGH && millis() - button.millisHour > debounceDelay){
            h = (h + 1) % 24;
        }
        if(digitalRead(button.min) == HIGH && millis() - button.millisMin > debounceDelay){
            m = (m + 1) % 60;
        }
        if(digitalRead(button.sec) == HIGH && millis() - button.millisSec > debounceDelay){
            s = (s + 1) % 60;
        }
    }
}

void setup() {
  lcd.begin();
  now = millis();
  buttonSetup(0,0,0,0); // เปลี่ยนตาม pin ที่จะเซ็ต
}

void loop() {
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("Time ");
//  lcd.createChar(8, a);
//  lcd.setCursor(0, 0);
//  lcd.write(8);
//  lcd.createChar(9, vo);
//  lcd.setCursor(1, 0);
//  lcd.write(9);
//  lcd.createChar(10, la);
//  lcd.setCursor(2, 0);
//  lcd.write(10);
//  lcd.createChar(11, r);
//  lcd.setCursor(3, 0);
//  lcd.write(11);
  
  if (h < 10)
    lcd.createChar(0, numList[0]);
    lcd.setCursor(5, 0);
    lcd.write(0);
  h1 = h / 10;
  h2 = h % 10;
  lcd.createChar(6, numList[h2]);
  lcd.setCursor(6, 0);
  lcd.write(6);
  lcd.createChar(5, numList[h1]);
  lcd.setCursor(5, 0);
  lcd.write(5);

  lcd.createChar(7, dc);
  lcd.setCursor(7, 0);
  lcd.write(7);

  if (m < 10)
    lcd.createChar(0, numList[0]);
    lcd.setCursor(8, 0);
    lcd.write(0);
  m1 = m / 10;
  m2 = m % 10;
  lcd.createChar(4, numList[m2]);
  lcd.setCursor(9, 0);
  lcd.write(4);
  lcd.createChar(3, numList[m1]);
  lcd.setCursor(8, 0);
  lcd.write(3);

  lcd.setCursor(10, 0);
  lcd.write(7);
  
  if (s < 10)
    lcd.createChar(0, numList[0]);
    lcd.setCursor(11, 0);
    lcd.write(0);
  s1 = s / 10;
  s2 = s % 10;
  lcd.createChar(2, numList[s2]);
  lcd.setCursor(12, 0);
  lcd.write(2);
  lcd.createChar(1, numList[s1]);
  lcd.setCursor(11, 0);
  lcd.write(1);


  /// ตัวนับเวลา
  for (int i = 0 ; i < 5 ; i++)
  {
    while ((now - last_time) < 200) /// delay 200 ms
    {
      now = millis();
    }
    last_time = now;
    
    /// เขียนปุ่มตรงนี้จะมีดีเลย์ปุ่มน้อย
    
  }
  readButtonsInput();
  
  /// ตัวเดินวินาที
  s += 1;

  /// ตัวจัดการเวลา
  if (s == 60)
  {
    s = 0;
    m += 1;
  }
  if (m == 60)
  {
    m = 0;
    h += 1;
  }
  if (h == 24)
  {
    h = 0;
  }

}
