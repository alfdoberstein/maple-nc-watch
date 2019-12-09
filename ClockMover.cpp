#include "ClockMover.h"
#include "Arduino.h"

// Include the Arduino Stepper.h library:
#include <Stepper.h>

// Define number of steps per rotation:
const int stepsPerRevolution = 2048;

const int correctTimeSteps = stepsPerRevolution; // * 2;

const int viralTimeStepsStart = stepsPerRevolution / 4;
const int viralTimeSteps = stepsPerRevolution / 2;
const int viralIterations = 4;
const int viralIterationDelay = 100;

const int moveSteps = 1; // stepsPerRevolution / 10;

// Wiring:
// Pin 9-8 to IN1 on the ULN2003 driver
// Pin 8-9 to IN2 on the ULN2003 driver
// Pin 7-10 to IN3 on the ULN2003 driver
// Pin 6-11 to IN4 on the ULN2003 driver
Stepper myStepper = Stepper(stepsPerRevolution, 9, 7, 8, 6);

void ClockMover::setup (void)
{
  // Set the speed max 17 rpm:
  myStepper.setSpeed(17);

  clear();
}

void ClockMover::clear(void)
{
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);

  sd = 100;
}

bool ClockMover::executeCorrectTime(void)
{
  myStepper.step(correctTimeSteps);
}

bool ClockMover::executeGoViral(void)
{
  myStepper.step(viralTimeStepsStart);
  delay(viralIterationDelay);

  for (int i = 0; i < viralIterations; i++)
  {
    myStepper.step(viralTimeSteps);
    delay(viralIterationDelay);
    myStepper.step(-viralTimeSteps);
    delay(viralIterationDelay);
  }

  myStepper.step(-viralTimeStepsStart);
}

bool ClockMover::executeMoveForward(void)
{
  myStepper.step(moveSteps);
  delay(accelerateStep());
}

bool ClockMover::executeMoveBackward(void)
{
  myStepper.step(-moveSteps);
  delay(accelerateStep());
}

int ClockMover::accelerateStep(void)
{
  sd -= sd > 0 ? 5 : 0;
  return sd;
}
