#include "InputReader.h"
#include "ClockMover.h"

InputReader inputReader = InputReader();
ClockMover clockMover = ClockMover();

int counter = 0;
bool autoMove = false;
int autoMoveSteps = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  inputReader.setup();

  clockMover.setup();

  Serial.println("Ready");
}

void loop() {

  if (inputReader.buttonPressed('A', 200))
  {
    Serial.println("Correcting time...");
    clockMover.executeCorrectTime();
    autoMove = true;
    autoMoveSteps = 0;
    Serial.println("Corrected time.");
  }
  else if (inputReader.buttonPressed('B', 200))
  {
    autoMove = false;
    Serial.println("Going crazy...");
    clockMover.executeGoCrazy();
    Serial.println("Go crazy end.");
  }
  else if (inputReader.buttonPressed('C', 1))
  {
    clockMover.executeMoveBackward();
  }
  else if (inputReader.buttonPressed('D', 1))
  {
    clockMover.executeMoveForward();
  }
  else
  {
    if (autoMove && counter++ > (15 * 100))
    {
      clockMover.oneStep();
      counter = 0;
    }
    clockMover.clear();
    delay(10);
  }

  //  digitalWrite(LED_BUILTIN, HIGH);
  //  delay(1000);
  //  digitalWrite(LED_BUILTIN, LOW);
}
