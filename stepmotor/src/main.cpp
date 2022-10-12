#include <Arduino.h>
#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12
#include <TinyStepper_28BYJ_48.h>

TinyStepper_28BYJ_48 stepper;

void setup() 
{
  Serial.begin(9600);
  stepper.connectToPins(STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4);
  stepper.setSpeedInStepsPerSecond(500);
  stepper.setAccelerationInStepsPerSecondPerSecond(600);

  stepper.setCurrentPositionInSteps(0);
  stepper.setupMoveInSteps(-50);
  while(!stepper.motionComplete())
  {
    stepper.processMovement();

  }
}
void loop() 
{
}

