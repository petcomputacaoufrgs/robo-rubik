/*
  Display.cpp - Library for 7 segmented display.
  Created by Victor V. M. Guimaraes, September 12, 2011.
  Released into the public domain.
*/

#include "WProgram.h"
#include "Display.h"

Display7Seg::Display7Seg(byte pinA,
						 byte pinB,
						 byte pinC,
						 byte pinD,
						 byte pinE,
						 byte pinF,
						 byte pinG)
{
  _pinA = pinA;
  _pinB = pinB;
  _pinC = pinC;
  _pinD = pinD;
  _pinE = pinE;
  _pinF = pinF;
  _pinG = pinG;
  
  //_AcomodationTime = 0;
}

void Display7Seg::printNumber(byte numb){

	switch (numb) {
		case 0 : print0();
				 break;
		case 1 : print1();
				 break;
		case 2 : print2();
				 break;
		case 3 : print3();
				 break;
		case 4 : print4();
				 break;
		case 5 : print5();
				 break;
		case 6 : print6();
				 break;
		case 7 : print7();
				 break;
		case 8 : print8();
				 break;
		case 9 : print9();
				 break;		
	}
	// Espera tempo de acomodação
	//delayMicroseconds(_AcomodationTime);

}

void Display7Seg::print0(){
  digitalWrite(_pinA, LOW);
  digitalWrite(_pinB, LOW);
  digitalWrite(_pinC, LOW);
  digitalWrite(_pinD, LOW);
  digitalWrite(_pinE, LOW);
  digitalWrite(_pinF, LOW);
  digitalWrite(_pinG, HIGH);
}
void Display7Seg::print1(){
  digitalWrite(_pinA, HIGH);
  digitalWrite(_pinB, LOW);
  digitalWrite(_pinC, LOW);
  digitalWrite(_pinD, HIGH);
  digitalWrite(_pinE, HIGH);
  digitalWrite(_pinF, HIGH);
  digitalWrite(_pinG, HIGH);
}
void Display7Seg::print2(){
  digitalWrite(_pinA, LOW);
  digitalWrite(_pinB, LOW);
  digitalWrite(_pinC, HIGH);
  digitalWrite(_pinD, LOW);
  digitalWrite(_pinE, LOW);
  digitalWrite(_pinF, HIGH);
  digitalWrite(_pinG, LOW);
}
void Display7Seg::print3(){
  digitalWrite(_pinA, LOW);
  digitalWrite(_pinB, LOW);
  digitalWrite(_pinC, LOW);
  digitalWrite(_pinD, LOW);
  digitalWrite(_pinE, HIGH);
  digitalWrite(_pinF, HIGH);
  digitalWrite(_pinG, LOW);
}
void Display7Seg::print4(){
  digitalWrite(_pinA, HIGH);
  digitalWrite(_pinB, LOW);
  digitalWrite(_pinC, LOW);
  digitalWrite(_pinD, HIGH);
  digitalWrite(_pinE, HIGH);
  digitalWrite(_pinF, LOW);
  digitalWrite(_pinG, LOW);
}
void Display7Seg::print5(){
  digitalWrite(_pinA, LOW);
  digitalWrite(_pinB, HIGH);
  digitalWrite(_pinC, LOW);
  digitalWrite(_pinD, LOW);
  digitalWrite(_pinE, HIGH);
  digitalWrite(_pinF, LOW);
  digitalWrite(_pinG, LOW);
}
void Display7Seg::print6(){
  digitalWrite(_pinA, LOW);
  digitalWrite(_pinB, HIGH);
  digitalWrite(_pinC, LOW);
  digitalWrite(_pinD, LOW);
  digitalWrite(_pinE, LOW);
  digitalWrite(_pinF, LOW);
  digitalWrite(_pinG, LOW);
}
void Display7Seg::print7(){
  digitalWrite(_pinA, LOW);
  digitalWrite(_pinB, LOW);
  digitalWrite(_pinC, LOW);
  digitalWrite(_pinD, HIGH);
  digitalWrite(_pinE, HIGH);
  digitalWrite(_pinF, HIGH);
  digitalWrite(_pinG, HIGH);
}
void Display7Seg::print8(){
  digitalWrite(_pinA, LOW);
  digitalWrite(_pinB, LOW);
  digitalWrite(_pinC, LOW);
  digitalWrite(_pinD, LOW);
  digitalWrite(_pinE, LOW);
  digitalWrite(_pinF, LOW);
  digitalWrite(_pinG, LOW);
}
void Display7Seg::print9(){
  digitalWrite(_pinA, LOW);
  digitalWrite(_pinB, LOW);
  digitalWrite(_pinC, LOW);
  digitalWrite(_pinD, LOW);
  digitalWrite(_pinE, HIGH);
  digitalWrite(_pinF, LOW);
  digitalWrite(_pinG, LOW);
}