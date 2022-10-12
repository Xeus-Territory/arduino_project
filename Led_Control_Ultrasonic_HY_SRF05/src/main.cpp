#include <Arduino.h>
const int TRIGGER_PIN = 6;
const int ECHO_PIN = 5;
long duration; 
int distance;
int heightoftank = 15;
int waterIntank;

void setup() {
  // put your setup code here, to run once:
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  for (int i = 9; i <= 11; i++)
  {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 18000);
  distance = duration * 0.034 / 2;

  // Calculate water level in tank
  waterIntank = heightoftank - distance;

  if (duration == 0)
  {
    Serial.println("Khong co vat can");
  }
  else
  {
    Serial.print("Distance between sensor with water: ");
    Serial.print(distance);
    Serial.println(" cm");
    Serial.print("Water level in tank: ");
    Serial.print(waterIntank);
    Serial.println(" cm");
  } 
  
  // // Water level in tank cause turn on led
  // if (waterIntank >= 7 && waterIntank <= 9)
  // {
  //   digitalWrite(10, LOW); digitalWrite(11, LOW);
  //   digitalWrite(9, HIGH);
  // }
  // if (waterIntank >= 10 && waterIntank <= 12)
  // {
  //   digitalWrite(9, LOW); digitalWrite(11, LOW);
  //   digitalWrite(10, HIGH);
  // }
  // if (waterIntank > 12)
  // {
  //   digitalWrite(9, LOW); digitalWrite(10, LOW);
  //   digitalWrite(11, HIGH);
  // }
  // if (waterIntank < 7)
  // {
  //   digitalWrite(9, LOW);
  //   digitalWrite(10, LOW);
  //   digitalWrite(11, LOW);
  // }
  delay(1000);
}