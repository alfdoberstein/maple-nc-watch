#include "InputReader.h"

// Include the Arduino Stepper.h library:
#include <Stepper.h>


InputReader inputReader = InputReader();

// Define number of steps per rotation:
const int stepsPerRevolution = 2048;

// Wiring:
// Pin 9-8 to IN1 on the ULN2003 driver
// Pin 8-9 to IN2 on the ULN2003 driver
// Pin 7-10 to IN3 on the ULN2003 driver
// Pin 6-11 to IN4 on the ULN2003 driver
Stepper myStepper = Stepper(stepsPerRevolution, 9, 7, 8, 6);


int counter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  // Set the speed max 17 rpm:
  myStepper.setSpeed(17);

  inputReader.setup();

  Serial.println("Ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  counter++;

  // if (inputReader.readButtons() == false)
  // {
  //   delay(0);
  //   return;
  // }

  if (inputReader.buttonPressed('A', 1000)) 
  {
    myStepper.step(stepsPerRevolution);
  }
  else if (inputReader.buttonPressed('B', 1000)) 
  {
    myStepper.step(-stepsPerRevolution);
  }
  else if (inputReader.buttonPressed('C', 1)) 
  {
    myStepper.step(stepsPerRevolution/10);
  }
  else if (inputReader.buttonPressed('D', 1)) 
  {
    myStepper.step(-stepsPerRevolution/10);
  }
  else
  {
    delay(0);
  }
  
  
//  String message = "Status 2:";
//  Serial.println(String(counter, DEC) + " " + message + "On");
//  digitalWrite(LED_BUILTIN, HIGH);
//  delay(1000);
//
//  Serial.println(message + "Off");
//  digitalWrite(LED_BUILTIN, LOW);
//  delay(1000);
  delay(0);
}
