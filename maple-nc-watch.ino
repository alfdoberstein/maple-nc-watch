#include "TestClass.h"

int counter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  TestClass test;
  test.setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  counter++;

  String message = "Status :";
  Serial.println(String(counter, DEC) + " " + message + "On");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);

  Serial.println(message + "Off");
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
