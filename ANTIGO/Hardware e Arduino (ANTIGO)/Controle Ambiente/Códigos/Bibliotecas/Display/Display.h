/*
  Display.h - Library for 7 segmented display.
  Created by Victor V. M. Guimaraes, September 12, 2011.
  Released into the public domain.
*/
#ifndef Display_h
#define Display_h

#include "WProgram.h"
class Display7Seg
{
  public:
    Display7Seg(byte pinA,
                byte pinB,
                byte pinC,
                byte pinD,
                byte pinE,
                byte pinF,
                byte pinG);
    void printNumber(char numb);
  private:
    byte _pinA;
    byte _pinB;
    byte _pinC;
    byte _pinD;
    byte _pinE;
    byte _pinF;
    byte _pinG;
	
	void print0();
	void print1();
	void print2();
	void print3();
	void print4();
	void print5();
	void print6();
	void print7();
	void print8();
	void print9();
};

#endif