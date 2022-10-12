#include <arduino.h>
#include <TinyStepper_28BYJ_48.h>
#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12
TinyStepper_28BYJ_48 stepper;

int timer1;
int timer2;

float Time;

int flag1 = 0;
int flag2 = 0;

float distance = 10.0;
float speed;

int ir_s1 = 4;
int ir_s2 = 5;

int buzzer = 13;

void setup()
{
  pinMode(ir_s1, INPUT);
  pinMode(ir_s2, INPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);

  Serial.begin(9600);
  stepper.connectToPins(STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4);
}
void RunStepper(bool direction)
{
  if (direction == true)
  {
    stepper.setSpeedInStepsPerSecond(500);
    stepper.setAccelerationInStepsPerSecondPerSecond(600);

    stepper.setCurrentPositionInSteps(0);
    stepper.setupMoveInSteps(512);
    while (!stepper.motionComplete())
    {
      stepper.processMovement();
    }
  }
  else
  {
    stepper.setSpeedInStepsPerSecond(500);
    stepper.setAccelerationInStepsPerSecondPerSecond(600);

    stepper.setCurrentPositionInSteps(0);
    stepper.setupMoveInSteps(-512);
    while (!stepper.motionComplete())
    {
      stepper.processMovement();
    }
  }
}

void loop()
{
  if (digitalRead(ir_s1) == LOW && flag1 == 0)
  {
    timer1 = millis();
    flag1 = 1;
  }

  if (digitalRead(ir_s2) == LOW && flag2 == 0)
  {
    timer2 = millis();
    flag2 = 1;
  }

  if (flag1 == 1 && flag2 == 1)
  {
    if (timer1 > timer2)
    {
      Time = timer1 - timer2;
    }
    else if (timer2 > timer1)
    {
      Time = timer2 - timer1;
    }
    Time = Time / 1000;
    speed = (distance / Time);
    speed = speed * 3600;
    speed = speed / 100000;
  }

  if (speed == 0)
  {
    if (flag1 == 0 && flag2 == 0)
    {
      Serial.print("No car  detected");
    }
    else
    {
      Serial.print("Searching...    ");
    }
  }
  else
  {
    Serial.print("Speed:");
    Serial.print(speed, 1);
    Serial.print("Km/Hr  ");
    if (speed > 3)
    {
      Serial.print("  Over Speeding  ");
      digitalWrite(buzzer, HIGH);
    
    }
    else
    {
      Serial.print("  Normal Speed   ");
      RunStepper(false);
      delay(3000);
      RunStepper(true);
    }
    delay(2000);
    digitalWrite(buzzer, LOW);
    speed = 0;
    flag1 = 0;
    flag2 = 0;
  }
}