/*
  RubikMotor.h - Library for rubik motor
  Created by Victor V. M. Guimaraes, October 15, 2011.
  Released into the public domain.
*/
#ifndef RubikMotor_h
#define RubikMotor_h


#include "WProgram.h"
#include "RubikMotorData.h"

class RubikMotor
{	
  public:
    RubikMotor(byte pinPos0, byte pinPos90, byte pinPos_90, byte pinPos180, byte pinGarraOpen, byte pinGarraClose, byte pinACK);

	void BackToPosition();
	void GotoPos90();
	void GotoPos_90();
	void GotoPos180();
	void OpenGarra();
	void CloseGarra();
	
  private:
	byte _pinPos0;
	byte _pinPos90;
	byte _pinPos_90;
	byte _pinPos180;
	byte _pinGarraOpen;
	byte _pinGarraClose; 
	byte _pinACK;

	//byte _AcomodationTime; // tempo de acomodação para a garra chegar a posição correta
	Position _ActualPosition;
	
	void GotoPosition(byte pinPos);
	void WaitForAck();	// Espera um ACK do motor
	void SetGarra(bool bOpen); 
};

#endif