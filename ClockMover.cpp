#include "ClockMover.h"

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

void ClockMover::setTime(int hour, int minute)
{
  timeHour = hour;
  timeMinute = minute;
  Serial.println("Time: " + getTime() + "");
}

String ClockMover::getTime(void)
{
  String hourString = "0" + String(timeHour);
  String minString = "0" + String(timeMinute);
  return String(hourString.substring(hourString.length() - 2) + ":" + minString.substring(minString.length() - 2));
}

void ClockMover::stepMinutes(int minuts)
{
  myStepper.step(stepsPerMinute * minuts);
  addTime(minuts);
  Serial.println("Time: " + getTime() + "");
}

void ClockMover::addTime(int minuts)
{
  timeMinute += minuts;
  while (timeMinute > 59)
  {
    timeHour++;
    timeMinute -= 60;
  }
  while (timeMinute < 0)
  {
    timeHour--;
    timeMinute += 60;
  }
  while (timeHour > 12)
  {
    timeHour -= 12;
  }
  while (timeHour < 1)
  {
    timeHour += 12;
  }
}

void ClockMover::executeCorrectTime(void)
{
  myStepper.setSpeed(10);
  stepMinutes(-25);
  //delay(10);
}

void ClockMover::oneStep(int minuts)
{
  myStepper.setSpeed(5);
  stepMinutes(minuts);
  //delay(10);
}

void ClockMover::executeGoCrazy(void)
{
  myStepper.setSpeed(17);
  for (int n = 0; n < 3; n++)
  {
    stepMinutes(-15);
    delay(crazyIterationDelay);
    stepMinutes(+20);
    delay(crazyIterationDelay);
    stepMinutes(-35);
    delay(crazyIterationDelay);
    stepMinutes(+10);
    delay(crazyIterationDelay);
    stepMinutes(-5);
    delay(crazyIterationDelay);
    stepMinutes(+40);
    delay(crazyIterationDelay);
    stepMinutes(-20);
    delay(crazyIterationDelay);
    stepMinutes(+5);
  }
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
