#include "RobotSerial.h"

//Constructor
RobotSerial::RobotSerial() {}
//Destructor
RobotSerial::~RobotSerial() {}

void RobotSerial::receiveData()
{
  while(!Serial.available()) {}
     this->newChar = Serial.read();
     switch (newChar) //only valid data will be processed
        {
          default:
            buffer += newChar;
        }
}

char RobotSerial::getInput()
{
  if (buffer.length() > 0)
  {
    this->lastInput =  buffer.charAt(0);
    this->buffer = buffer.substring(1,buffer.length());
    return lastInput;
  }
}

void RobotSerial::printBuffer()
{
  Serial.println(buffer);
}

