#include "RobotSerial.h"

//Constructor
RobotSerial::RobotSerial() {

  this->ready = false;
  
}
//Destructor
RobotSerial::~RobotSerial() {}

void RobotSerial::receiveData()
{
  while(Serial.available() > 0) {
     this->newChar = Serial.read();
     if(this->newChar == -1)
       Serial.write("#");
     else {
       buffer += newChar;
       if(newChar == 'S')
         this->ready = true;
     }
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
  else
  {
     this->ready = false; 
  }
}

void RobotSerial::printBuffer()
{
  Serial.print(buffer);
}

int RobotSerial::getBufferSize()
{
  return this->buffer.length();
}

boolean RobotSerial::getReady()
{
   return this->ready; 
}
