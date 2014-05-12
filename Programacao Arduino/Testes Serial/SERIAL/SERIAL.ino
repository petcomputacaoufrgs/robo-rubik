#include "Classe_Serial.h"

RobotSerial r_serial;

void setup ()
{
  Serial.begin (9600);
}

void loop ()
{
  r_serial.receiveData();
  r_serial.printBuffer();
  //r_serial.getInput();
}
