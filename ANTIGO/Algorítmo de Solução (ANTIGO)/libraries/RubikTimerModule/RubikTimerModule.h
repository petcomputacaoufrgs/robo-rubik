/*
  RubikTimerModule.h - Library for rubik timer module
  Created by Victor V. M. Guimaraes, September 26, 2011.
  Released into the public domain.
*/
#ifndef RubikTimerModule_h
#define RubikTimerModule_h

extern "C"{
	#include "..\Display\Display.h"
}

#include "WProgram.h"
#include "RubikData.h"

class RubikTimerModule
{	
  public:
    RubikTimerModule(byte ID,
					 byte pinA, byte pinB, byte pinC, byte pinD, byte pinE, byte pinAnalog,					 
					 byte maskMin, byte maskSec1, byte maskSec0, byte maskDec1, byte maskDec0,
					 Display7Seg* disp7segRef
					);	

	void Reset(bool ativo);	
	void IncTime();			
	void IncElapsedTime();
    void SendTime();
	void VerifyStateChanged();	
	void SetState(StateType newStateType);
	unsigned char*  ToStream();			
	bool IsActive();	
	byte ID();	
	StateType GetState();
	boolean StateChanged();
	
  private:
    byte _pinA;
    byte _pinB;
    byte _pinC;
    byte _pinD;
    byte _pinE;
	byte _pinAnalog;
	
    byte _maskMin;
    byte _maskSec1;
	byte _maskSec0;
	byte _maskDec1;
	byte _maskDec0;
	
	Display7Seg* _disp7segRef;
	
	byte  _ID;
	State _Estado;
	Time  _Tempo;
	boolean _StateChanged;
	
	byte _AcomodationTime; // tempo de acomodação da seleção do demux em us

	void SelectDisplay(byte mask);
	void SelectNone();
	void SendToDisplay(byte mask, byte numb);
	
	void SendMin();
	void SendSec();
	void SendDec();
	
	State ReadState();
};

#endif