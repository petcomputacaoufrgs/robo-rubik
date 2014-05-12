#include "Classe_Serial.h"

//Constructor
RobotSerial::RobotSerial() {}
//Destructor
RobotSerial::~RobotSerial() {}

void RobotSerial::receiveData()
{
   if ( Serial.available() )
    {
     newChar = Serial.read();
     switch (newChar) //only valid data will be processed
        {
          default:
            buffer += newChar;
        }
     }
}

char RobotSerial::getInput ()
{
  if (buffer.length()>0)
  {
    lastInput =  buffer.charAt(0);
    buffer = buffer.substring(1,buffer.length());
    return lastInput;
  }
}

void RobotSerial::printBuffer()
{
  Serial.println(buffer);
}

