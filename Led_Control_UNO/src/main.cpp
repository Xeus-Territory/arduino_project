#include <Arduino.h>

void setup()
{
  // put your setup code here, to run once:
  for (int i = 2; i < 12; i++)
  {
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  // // LED chạy từ trái sáng phải và tắt dần từ phải sáng trái
  // for (int i = 2; i < 12; i++)
  // {
  //   digitalWrite(i, HIGH);
  //   delay(100);
  // }
  // delay(100);
  // for (int i = 12 - 1; i >= 2; i--)
  // {
  //   digitalWrite(i, LOW);
  //   delay(100);
  // }
  // delay(100);
  //// LED chạy từ hai bên vô chính giữa và tắt dần từ chính giữa sang 2 bên
  // for (int i = 2; i <= 6; i++)
  // {
  //   digitalWrite(i, HIGH);
  //   digitalWrite(13 - i, HIGH);
  //   delay(100);
  // }
  // delay(100);
  // for (int i = 6; i >= 2; i--)
  // {
  //   digitalWrite(i, LOW);
  //   digitalWrite(13 - i , LOW);
  //   delay(100);
  // }
  // delay(100);
  // // LED chạy theo chẵn lẻ 
  // for (int i = 2; i < 12; i++)
  // {
  //   if (i % 2 != 0)
  //   {
  //     digitalWrite(i, HIGH);
  //     delay(500);
  //     digitalWrite(i, LOW);
  //     delay(500);
  //   }
  // }
  // delay(1000);
  // for (int i = 12 - 1; i >= 2; i--)
  // {
  //   if (i % 2 == 0)
  //   {
  //     digitalWrite(i, HIGH);
  //     delay(500);
  //     digitalWrite(i, LOW);
  //     delay(500);
  //   }
  // }
  // delay(1000);
  // LED sáng từ từ rồi tắt từ từ 
  // for (int i = 0; i <= 255; i++)
  // {
  //   analogWrite(3 , i);
  //   delay(5);
  // }
  // for (int i = 255; i >= 0; i--)
  // {
  //   analogWrite(3 , i);
  //   delay(5);
  // }
}