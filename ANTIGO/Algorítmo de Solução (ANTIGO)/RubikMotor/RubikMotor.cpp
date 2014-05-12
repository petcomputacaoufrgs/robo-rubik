/*
  RubikMotor.cpp - Library for 7 Rubik Motor
  Created by Victor V. M. Guimaraes, October 15, 2011.
  Released into the public domain.
*/

#include "WProgram.h"
#include "RubikMotor.h"

// Public Methods

RubikMotor::RubikMotor(byte pinPos0, byte pinPos90, byte pinPos_90, byte pinPos180, byte pinGarraOpen, byte pinGarraClose, byte pinACK){
	_pinPos0 		= pinPos0;
	_pinPos90		= pinPos90;
	_pinPos_90		= pinPos_90;
	_pinPos180		= pinPos180;
	_pinGarraOpen	= pinGarraOpen;
	_pinGarraClose	= pinGarraClose;
	_pinACK			= pinACK;

	//_AcomodationTime = 10; // 10 milisegundos para a garra abrir ou fechar
	_ActualPosition = pos0;
}
void RubikMotor::BackToPosition(){
	// Abre a Garra
	if (_ActualPosition != pos180){
		OpenGarra();
		// Vai para posição 0
		GotoPosition(_pinPos0);	
		// Fecha a Garra
		CloseGarra();
	}
	else{
		// Posição atual é 180, vai para 0 passando por 90
		OpenGarra();
		// Vai para 90
		GotoPosition(_pinPos90);
		// Vai para 0
		GotoPosition(_pinPos0);
		// Fecha a Garra
		CloseGarra();
	}
	_ActualPosition = pos0;
}
void RubikMotor::GotoPos90(){
	// Vai para posição 90º
	GotoPosition(_pinPos90);
	_ActualPosition = pos90;
}
void RubikMotor::GotoPos_90(){
	// Vai para posição -90º
	GotoPosition(_pinPos_90);
	_ActualPosition = pos_90;
}
void RubikMotor::GotoPos180(){
	// Vai para posição 180º
	//GotoPosition(_pinPos180);
	// Deve passar pela posição 0 -> 90 -> 180
	GotoPosition(_pinPos90);
	GotoPosition(_pinPos180);
	_ActualPosition = pos180;
}
void RubikMotor::OpenGarra(){
	SetGarra(true);
}
void RubikMotor::CloseGarra(){
	SetGarra(false);
}
void RubikMotor::GotoPosition(byte pinPos){
	// Vai para a posição correspondente
	digitalWrite(pinPos, HIGH);
	// Espera tempo do motor zerar o ACK
	delay(c_DelayMotorAck);
	// Espera o motor chegar na posição correta
	WaitForAck();
	// Seta pino da posição para LOW
	digitalWrite(pinPos, LOW);	
}
void RubikMotor::WaitForAck(){
	while (digitalRead(_pinACK) == LOW){
		delay(c_DelayWaitForAck);
	}
}
void RubikMotor::SetGarra(bool bOpen){
	// Seta os dois pinos para zero (garra não pode ficar com dois pinos em 1)
	digitalWrite(_pinGarraOpen,LOW);
	digitalWrite(_pinGarraClose,LOW);
	// Espera chegar LOW nas garras
	delayMicroseconds(c_DelayGarraLow);
	// Seta o pino de abrir ou fechar a garra
	if (bOpen){
		digitalWrite(_pinGarraOpen,HIGH);
	}
	else{
		digitalWrite(_pinGarraClose,HIGH);
	}
	// Espera a garra abrir / fechar
	delay(c_DelayGarraSet);
}




