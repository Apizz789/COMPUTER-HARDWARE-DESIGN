#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
unsigned long int count = 0;
unsigned long int delaycount = 0;
unsigned long int delaycountdown = 0;
unsigned long int delaystopwatch = 0;
unsigned long int timer = 0;
unsigned long int delaybtn1 = 0;
unsigned long int delaybtn2 = 0;
unsigned long int delaybtn3 = 0;
unsigned long int delaybtn4 = 0;
unsigned long int delaybtn5 = 0;
unsigned long int countdown = 0;
unsigned long int setcount = 0;
unsigned long int stopwatch = 0;
unsigned long int stopwatchtemp = 0;
bool checkstopwatch = true;
int btn[] = {10, 9, 8, 7};
int readbtn[4];
int stateunit = 0;
int mode = 0;
long printTime(long);
byte customChar[12][8] = {
  // 0
  {
    B00000,
    B00000,
    B00000,
    B11111,
    B10001,
    B10001,
    B10001,
    B11111,
  },
  // 1
  {
    B00000,
    B00000,
    B00000,
    B11111,
    B10001,
    B10101,
    B10101,
    B11001,
  },

  // 2
  {
    B00000,
    B10000,
    B10000,
    B10101,
    B10111,
    B10101,
    B10001,
    B11111,
  },

  // 3
  {
    B00000,
    B00000,
    B00000,
    B11111,
    B10101,
    B10101,
    B10001,
    B11001,
  },

  // 4
  {
    B00000,
    B00000,
    B00001,
    B01110,
    B10000,
    B10000,
    B10010,
    B11111,
  },

  // 5
  {
    B00000,
    B00000,
    B00110,
    B11111,
    B10000,
    B10000,
    B10010,
    B11111,
  },

  // 6
  {
    B00000,
    B10000,
    B10000,
    B11111,
    B00001,
    B11001,
    B10001,
    B11111,
  },

  // 7
  {
    B00000,
    B00001,
    B00001,
    B11011,
    B10101,
    B10101,
    B10001,
    B11001
  },

  // 8
  {
    B00000,
    B00001,
    B00010,
    B11110,
    B10000,
    B10011,
    B11001,
    B10111,
  },

  // 9
  {
    B00000,
    B00000,
    B00001,
    B11011,
    B10100,
    B10010,
    B10101,
    B11101,
  },

  // :
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00100,
    B00000,
    B00100,
    B00000,
  },

  // น
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B11010,
    B01010,
    B01111,
    B01011,
  }
};

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < 4; i++)
    pinMode(btn[i], INPUT);
  lcd.begin(16, 2);
}

void loop()
{

  for (int i = 0; i < 4; i++)
    readbtn[i] = digitalRead(btn[i]);


  if (readbtn[0] && millis() - delaybtn1 > 500)
  {
    stateunit++;
    stateunit %= 3;
    delaybtn1 = millis();
  }

  if (readbtn[3] && millis() - delaybtn4 > 500)
  {
    mode++;
    mode %= 5;
    delaybtn4 = millis();
    lcd.clear();


    if (mode == 0) {
      count = setcount;
    }
    if (mode == 1) {
      countdown = 0;
    }
    //    if (mode == 3){setcount = count;}
    if (mode == 4) {
      stopwatch = 0;
    }



  }

  if (mode == 0) // Show Main Time
  {
    printTime(count);
    lcd.setCursor(3, 0);
    lcd.print("THAI TIME:");

  }

  if (mode == 1)
  {
    printTime(countdown);
    lcd.setCursor(2, 0);
    lcd.print("[SET] TIMER");
    Serial.println(countdown);

    // HOUR : HOUR
    if (stateunit == 0 && readbtn[1]  && countdown <= 86400 && millis() - delaybtn2 > 500)
    {
      countdown += 3600;
      delaybtn2 = millis();
    }
    if (countdown == 86400) {
      countdown = 3600;
    }

    if (stateunit == 0 && readbtn[2] && countdown >= 3600 && millis() - delaybtn3 > 500)
    {
      countdown -= 3600;
      delaybtn3 = millis();
    }


    // MIN : MIN
    if (stateunit == 1 && readbtn[1] && millis() - delaybtn2 > 500)
    {
      countdown += 60;
      delaybtn2 = millis();
    }

    if (stateunit == 1 && readbtn[2] && countdown >= 60 && millis() - delaybtn3 > 500)
    {
      countdown -= 60;
      delaybtn3 = millis();
    }
    // SEC : SEC
    if (stateunit == 2 && readbtn[1] && millis() - delaybtn2 > 500)
    {
      countdown += 1;
      delaybtn2 = millis();
    }
    if (stateunit == 2 && readbtn[2] && countdown > 0 && millis() - delaybtn3 > 500)
    {
      countdown -= 1;
      delaybtn3 = millis();
    }


  }
  if (mode == 2)
  {
    printTime(countdown);
    lcd.setCursor(5, 0);
    lcd.print("TIMER!");
    if (millis() - delaycountdown > 1000 && countdown > 0) {
      countdown--;
      delaycountdown = millis();
    }
  }

  if (mode == 3)
  {
    stopwatch * 2.2;
    printTime(stopwatch);
    lcd.setCursor(0, 0);
    lcd.print("[SET] STOPWATCH");
    if (
      readbtn[0] && millis() - delaystopwatch > 500) {
      Serial.print(readbtn[0]);
      checkstopwatch = true;
      delaystopwatch = millis();
    }
    if (checkstopwatch == true) {
      stopwatch++;
    }

    if (readbtn[1] && millis() - delaystopwatch > 500) {
      Serial.print(stopwatch);
      checkstopwatch = false;
      delaystopwatch = millis();
    }

    if (readbtn[2] && millis() - delaystopwatch > 500) {
      checkstopwatch = false;
      Serial.print(readbtn[2]);
      stopwatch = 0;
      delaystopwatch = millis();
    }





  }






  if (mode == 4)
  {
    printTime(setcount);
    lcd.setCursor(3, 0);
    lcd.print("[SET] TIME");

    if (stateunit == 0 && readbtn[1] && millis() - delaybtn2 > 500)
    {
      setcount += 3600;
      delaybtn2 = millis();
    }
    if (stateunit == 0 && readbtn[2] && setcount >= 3600 && millis() - delaybtn3 > 500)
    {
      setcount -= 3600;
      delaybtn3 = millis();
    }

    if (stateunit == 1 && readbtn[1] && millis() - delaybtn2 > 500)
    {
      setcount += 60;
      delaybtn2 = millis();
    }
    if (stateunit == 1 && readbtn[2] && setcount >= 60 && millis() - delaybtn3 > 500)
    {
      setcount -= 60;
      delaybtn3 = millis();
    }

    if (stateunit == 2 && readbtn[1] && millis() - delaybtn2 > 500)
    {
      setcount += 1;
      delaybtn2 = millis();
    }
    if (stateunit == 2 && readbtn[2] && setcount > 0 && millis() - delaybtn3 > 500)
    {
      setcount -= 1;
      delaybtn3 = millis();
    }
  }

  if (millis() - delaycount > 1000) {
    count ++;
    count %= 86400;
    delaycount = millis();
  }
}

long printTime(long count)
{
  long hh = (count / 3600) % 24;
  long mm = (count / 60) % 60;
  long ss = count % 60;


  Serial.print("COUNT :");
  Serial.println(count);

  Serial.print("HH :");
  Serial.println(hh);
  Serial.print("MM :");
  Serial.println(mm);
  Serial.print("SS :");
  Serial.println(ss);


  lcd.createChar(0, customChar[hh / 10]);
  lcd.createChar(1, customChar[hh % 10]);

  lcd.createChar(3, customChar[mm / 10]);
  lcd.createChar(4, customChar[mm % 10]);
  lcd.createChar(5, customChar[ss / 10]);
  lcd.createChar(6, customChar[ss % 10]);

  lcd.createChar(2, customChar[10]);
  lcd.createChar(7, customChar[11]);

  lcd.setCursor(2, 1);
  lcd.print("[");

  // 2 first digit HH
  lcd.setCursor(4, 1);
  lcd.write((uint8_t)0);

  lcd.setCursor(5, 1);
  lcd.write((uint8_t)1);

  // colon :
  lcd.setCursor(6, 1);
  lcd.write((uint8_t)2);

  // 2 next digit MM
  lcd.setCursor(7, 1);
  lcd.write((uint8_t)3);

  lcd.setCursor(8, 1);
  lcd.write((uint8_t)4);

  // 2 last digit SS
  lcd.setCursor(9, 1);
  lcd.write((uint8_t)2);

  lcd.setCursor(10, 1);
  lcd.write((uint8_t)5);

  // colon :
  lcd.setCursor(11, 1);
  lcd.write((uint8_t)6);


  lcd.setCursor(13, 1);
  lcd.print("]");

}
