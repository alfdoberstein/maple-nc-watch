#include "InputReader.h"
#include "ClockMover.h"

InputReader inputReader = InputReader();
ClockMover clockMover = ClockMover();

int counter = 0;
bool autoMove = false;

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
    clockMover.executeCorrectTime();
    autoMove = true;
  }
  else if (inputReader.buttonPressed('B', 200))
  {
    autoMove = false;
    clockMover.executeGoCrazy();
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
    if (autoMove && counter++ > (15 * 100)) {
      clockMover.oneStep();
      counter = 0;
    }
    if (counter % 100) {
      Serial.println(counter);
    }
    clockMover.clear();
    delay(10);
  }

  //  digitalWrite(LED_BUILTIN, HIGH);
  //  delay(1000);
  //  digitalWrite(LED_BUILTIN, LOW);
}
