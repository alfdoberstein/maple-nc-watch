#include "InputReader.h"
#include "Arduino.h"

//
//Arduino 4 channel Wireless RF Receiver EV1527/PT2262 Decoding module
//
const int D3 = 2;
const int D2 = 3;
const int D1 = 4;
const int D0 = 5;
//const int VT = 8;

bool called = false;

void InputReader::setup(void)
{
  // Setup 4 channel Wireless RF Receiver EV1527/PT2262 Decoding module
  pinMode(D3, INPUT);
  pinMode(D2, INPUT);
  pinMode(D1, INPUT);
  pinMode(D0, INPUT);
  //pinMode(VT, INPUT);

  //Waiting for rf receiver module startup
  delay(2000);

  Serial.println("RF Receiver ready.");
}

bool InputReader::buttonPressed(char button, int minDuration)
{
  /* For testing 
  if (called == false && button == 'A')
  {
    called = true;
    return true;
  }
  return false;
  */
 
  int input;

  switch (button)
  {
    case 'A': input = D3; break;
    case 'B': input = D2; break;
    case 'C': input = D1; break;
    case 'D': input = D0; break;
    default:
      Serial.println(String("Unknown button ") + String(button));
      return false;
  }

  int pressed = minDuration;
  while (digitalRead(input) > 0)
  {
    pressed -= 10;
    if (pressed <= 0) return true;
    delay(10);
  }
  return false;
}
