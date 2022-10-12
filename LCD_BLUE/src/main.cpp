#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int pin_button = 8;
int dien;
float dien_val, t, t_f;
int stateC = 1;
int lastStateButton = 0;
int dem = 0;
unsigned long start = 0;

void setup()
{
  pinMode(pin_button, INPUT_PULLUP);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void caua();
void caub();
void cauc();
void caud();

void loop()
{
  caua();
  // unsigned long now = millis();
  // if (digitalRead(pin_button) == LOW)
  // {
  //   delay(500);
  //   if (digitalRead(pin_button) == LOW)
  //   {
  //     delay(500);
  //     Serial.println("Button pressed");
  //     ++ dem;
  //     Serial.println("Timer: " + String(now));
  //     if (digitalRead(pin_button) == LOW && (unsigned long)(now - start) < 2000)
  //     {
  //       start = now;
  //       Serial.println("Turnoff");
  //       lcd.noDisplay();
  //     }
  //     else
  //     {
  //       int reading = analogRead(A1);
  //       float vol = reading * 5.0 / 1024.0;
  //       float temp = (vol - 0.4) * 100.0;
  //       if (dem % 2 == 0)
  //       {
  //         lcd.setCursor(2, 0);
  //         lcd.print("Nhiet do: ");
  //         lcd.setCursor(2, 1);
  //         lcd.print("Celsius: " + String(temp));
  //       }
  //       else
  //       {
  //         lcd.setCursor(2, 0);
  //         lcd.print("Nhiet do: ");
  //         lcd.setCursor(2, 1);
  //         lcd.print("Fahrenheit: " + String(temp * 1.8 + 32));
  //       }
  //     }
  //   }
  // }
}

void caua()
{
  lcd.setCursor(2, 0);
  lcd.print("Nhiet do");
}

void caub()
{
  lcd.setCursor(4, 0);
  int vol = analogRead(A0);
  float tem_vol = (vol * 5) / 1024.0;
  float temp = (tem_vol - 0.4) * 100;
  lcd.setCursor(2, 1);
  lcd.print(temp);
  delay(500);
}

void cauc()
{
  //  int value = digitalRead(pin_button);
  //   if (value==1){
  //   		stateC = ~stateC;
  //  }
  //  Serial.println(stateC);

  //   int vol = analogRead(A0);
  //   float tem_vol = (vol *5)/1024.0;
  //   float temp = (tem_vol-0.4) * 100;

  //   if (stateC==1){
  //     lcd.begin(16, 2);
  //     lcd.clear();
  //     lcd.setCursor(1,0);
  //     lcd.print("Celsius: ");
  //     lcd.setCursor(10,0);
  //     lcd.print(temp);

  //   } else {
  //     lcd.begin(16, 2);
  //     lcd.clear();
  //     float t_f = temp *1.8 +32;
  //     lcd.setCursor(1,0);
  //     lcd.print("Fe: ");
  //     lcd.setCursor(10,0);
  //     lcd.print(t_f);
  //   }
  //   delay(100);
}
