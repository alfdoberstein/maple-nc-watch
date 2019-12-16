#include "ClockMover.h"
#include "Arduino.h"

// Include the Arduino Stepper.h library:
#include <Stepper.h>

// Define number of steps per rotation:
const int stepsPerRevolution = 2048;

const int stepsPerMinute = stepsPerRevolution / 60;

const int crazyIterationDelay = 100;

const int moveSteps = 5;

// Wiring:
// Pin 9-8 to IN1 on the ULN2003 driver
// Pin 8-9 to IN2 on the ULN2003 driver
// Pin 7-10 to IN3 on the ULN2003 driver
// Pin 6-11 to IN4 on the ULN2003 driver
Stepper myStepper = Stepper(stepsPerRevolution, 9, 7, 8, 6);

void ClockMover::setup (void)
{
  // Set the speed max 17 rpm:
  myStepper.setSpeed(10);

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

void ClockMover::executeCorrectTime(void)
{
  myStepper.setSpeed(10);
  myStepper.step(stepsPerMinute * -25);
  //delay(10);
}

void ClockMover::oneStep(void)
{
  myStepper.setSpeed(5);
  myStepper.step(stepsPerMinute);
  //delay(10);
}

void ClockMover::executeGoCrazy(void)
{
  myStepper.setSpeed(17);
  myStepper.step(stepsPerMinute * -15);
  delay(crazyIterationDelay);
  myStepper.step(stepsPerMinute * +20);
  delay(crazyIterationDelay);
  myStepper.step(stepsPerMinute * -35);
  delay(crazyIterationDelay);
  myStepper.step(stepsPerMinute * +10);
  delay(crazyIterationDelay);
  myStepper.step(stepsPerMinute * -5);
  delay(crazyIterationDelay);
  myStepper.step(stepsPerMinute * +40);
  delay(crazyIterationDelay);
  myStepper.step(stepsPerMinute * -20);
  delay(crazyIterationDelay);
  myStepper.step(stepsPerMinute * +5);
}

void ClockMover::executeMoveForward(void)
{
  myStepper.setSpeed(10);
  myStepper.step(moveSteps);
  delay(accelerateStep());
  if (sd > 0) 
  {
    Serial.println("Moved forward (delay " + String(sd) + ").");
  }
}

void ClockMover::executeMoveBackward(void)
{
  myStepper.setSpeed(10);
  myStepper.step(-moveSteps);
  delay(accelerateStep());
  if (sd > 0) 
  {
    Serial.println("Moved backward (delay " + String(sd) + ").");
  }
}

int ClockMover::accelerateStep(void)
{
  sd -= sd > 0 ? 5 : 0;
  return sd;
}
