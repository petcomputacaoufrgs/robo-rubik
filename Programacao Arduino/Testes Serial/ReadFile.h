#ifndef READ_FILE_H
#define READ_FILE_H

#include <Arduino.h>

class ReadFile
{
  private:
    String fileName;
    String buffer;

  public:
    ReadFile();
    ~ReadFile();
    void readFile();

};

#endif
