#include "TestClass.h"

// Include the Arduino Stepper.h library:
#include <Stepper.h>

// Define number of steps per rotation:
const int stepsPerRevolution = 2048;

// Wiring:
// Pin 9-8 to IN1 on the ULN2003 driver
// Pin 8-9 to IN2 on the ULN2003 driver
// Pin 7-10 to IN3 on the ULN2003 driver
// Pin 6-11 to IN4 on the ULN2003 driver

Stepper myStepper = Stepper(stepsPerRevolution, 9, 7, 8, 6);

//
//Arduino 4 channel Wireless RF Receiver EV1527/PT2262 Decoding module
//
int D3 = 2;
int D2 = 3;
int D1 = 4;
int D0 = 5;
//int VT = 8;

// variable for reading the input status
int buttonState = 0;
int lastState = 0;

int counter = 0;

void setup() {
  // Set the speed to 5 rpm:
  myStepper.setSpeed(10);

  // Setup 4 channel Wireless RF Receiver EV1527/PT2262 Decoding module
  pinMode(D3, INPUT);
  pinMode(D2, INPUT);
  pinMode(D1, INPUT);
  pinMode(D0, INPUT);
  //pinMode(VT, INPUT);

  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  //Waiting for rf receiver module startup
  delay(2000);
  Serial.println("Ready");

  //TestClass test;
  //test.setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  counter++;

  buttonState = digitalRead(D3) ? 1 : 0;
  buttonState = digitalRead(D2) ? 2 : buttonState;

  if(buttonState != lastState) 
  {
    Serial.print("Button A: ");
    if (buttonState) Serial.println("ON");
    else Serial.println("OFF");

    lastState = buttonState;
  }  

  if (buttonState == 1) 
  {
    myStepper.step(10);
  }
  else if (buttonState == 2) 
  {
    myStepper.step(-10);
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
}
