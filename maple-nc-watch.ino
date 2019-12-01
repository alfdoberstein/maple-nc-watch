#include "InputReader.h"
#include "ClockMover.h"

InputReader inputReader = InputReader();
ClockMover clockMover = ClockMover();

int counter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  inputReader.setup();
  
  clockMover.setup();

  Serial.println("Ready");
}

void loop() {

  if (inputReader.buttonPressed('A', 1000)) 
  {
    clockMover.executeCorrectTime();
  }
  else if (inputReader.buttonPressed('B', 1000)) 
  {
    clockMover.executeGoViral();
  }
  else if (inputReader.buttonPressed('C', 1)) 
  {
    clockMover.executeMoveForward();
  }
  else if (inputReader.buttonPressed('D', 1)) 
  {
    clockMover.executeMoveBackward();
  }
  else
  {
    delay(10);
  }
  
//  digitalWrite(LED_BUILTIN, HIGH);
//  delay(1000);
//  digitalWrite(LED_BUILTIN, LOW);
}
