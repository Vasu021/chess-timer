// code of arduino
#include <LiquidCrystal.h>
const int rs = 9, en = 8, d4 = 4, d5 = 5, d6 = 6, d7 = 7, x = 4.5, trigger = 3, echo = 2;
double d, t, dw;
int time_white = 300, time_black = 300, minutes = 5;

double getDist();
void displayBlack(int);
void displayWhite(int);

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Initial setup
void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(1, 0);
  lcd.print("Black");
  lcd.setCursor(11, 0);
  lcd.print("White");

  lcd.setCursor(0, 1);
  lcd.print(minutes);
  lcd.setCursor(1, 1);
  lcd.print(":");
  lcd.setCursor(2, 1);
  lcd.print(0);
  lcd.setCursor(3, 1);
  lcd.print(0);

  lcd.setCursor(12, 1);
  lcd.print(minutes);
  lcd.setCursor(13, 1);
  lcd.print(":");
  lcd.setCursor(14, 1);
  lcd.print(0);
  lcd.setCursor(15, 1);
  lcd.print(0);
}

void loop() {
  // dw = getDist();
  if (dw < x) {
    while (1) {
      dw = getDist();
      if (dw < x) {
        time_black = time_black - 1;
        displayBlack(time_black);
      }
      if (dw > x) {
        time_white = time_white - 1;
        displayWhite(time_white);
      }
      if (time_white == 0 || time_black == 0) {
        if (time_white == 0) {
          lcd.setCursor(6, 1);
          lcd.print("Black wins");
        }
        if (time_black == 0) {
          lcd.setCursor(0, 1);
          lcd.print("White wins");
        }
        delay(10000);
        break;
      }
      delay(1000);
    }
  }
}

// function to get the distance
double getDist() {
  int intigerDistance;
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  t = pulseIn(echo, HIGH);
  d = 0.017 * t;
  intigerDistance = (int)d;
  return intigerDistance;
}

// function to display white side
void displayWhite(int t) {
  int m, s;
  m = (int)t / 60;
  s = t % 60;

  lcd.setCursor(12, 1);
  lcd.print(m);
  lcd.setCursor(13, 1);
  lcd.print(":");
  lcd.setCursor(14, 1);
  lcd.print(s);
}

// function to display black side
void displayBlack(int t) {
  int m, s;
  m = (int)t / 60;
  s = t % 60;

  lcd.setCursor(0, 1);
  lcd.print(m);
  lcd.setCursor(1, 1);
  lcd.print(":");
  lcd.setCursor(2, 1);
  lcd.print(s);
}