#ifndef CLASSE_SERIAL_H
#define CLASSE_SERIAL_H

#include <Arduino.h>

class RobotSerial
{
  private:
    char lastInput, newChar;
    String buffer;
    boolean ready;
    
  public:
    RobotSerial();
    ~RobotSerial();
    void receiveData();
    char getInput();
    void printBuffer();
    int getBufferSize();
    boolean getReady();
    
};

#endif
