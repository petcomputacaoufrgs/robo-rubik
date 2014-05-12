/*
  RubikTimerModule.cpp - Library for 7 Rubik Timer Module
  Created by Victor V. M. Guimaraes, September 26, 2011.
  Released into the public domain.
*/

#include "WProgram.h"
#include "RubikTimerModule.h"

// Public Methods

RubikTimerModule::RubikTimerModule(byte ID,
								   byte pinA, byte pinB, byte pinC, byte pinD, byte pinE, byte pinAnalog,					 
								   byte maskMin, byte maskSec1, byte maskSec0, byte maskDec1, byte maskDec0,
								   Display7Seg* disp7segRef
								  )	
{
	_ID = ID;
	_pinA = pinA;
	_pinB = pinB;
	_pinC = pinC;
	_pinD = pinD;
	_pinE = pinE;
  
	_pinAnalog = pinAnalog;
	
	_maskMin  = maskMin;
	_maskSec1 = maskSec1;
	_maskSec0 = maskSec0;
	_maskDec1 = maskDec1;
	_maskDec0 = maskDec0;
	
	_StateChanged = false;
	
	_disp7segRef = disp7segRef;
	
	_AcomodationTime = 10;//10;
	Reset(false);
}
void RubikTimerModule::Reset(bool ativo){
	_Estado.Ativo = ativo;
	_Estado.Tipo  = stReset;
	_Estado.BotaoPressed = false;
	_Estado.ElapsedTime = 0;
	
	_Tempo.Min  = 0;
	_Tempo.Sec1 = 0;
	_Tempo.Sec0 = 0;
	_Tempo.Dec1 = 0;
	_Tempo.Dec0 = 0;
	
	if (ativo){
		SendTime();
	}

}
void RubikTimerModule::IncTime(){
	if ((_Estado.Ativo) && (_Estado.Tipo == stStart) && (_Tempo.Min<10)){
		if (_Tempo.Dec0 == 9){
			_Tempo.Dec0 = 0;
			if (_Tempo.Dec1 == 9){
				_Tempo.Dec1 = 0;
				if (_Tempo.Sec0 == 9){
					_Tempo.Sec0 = 0;
					if (_Tempo.Sec1 == 5){
						_Tempo.Sec1 = 0;
						_Tempo.Min++;
						if (_Tempo.Min == 10){							
							_Tempo.Sec1=9;
							_Tempo.Sec0=9;
							_Tempo.Dec1=9;
							_Tempo.Dec0=9;
						}
					}
					else{
						_Tempo.Sec1++;
					}
				}
				else{
					_Tempo.Sec0++;
				}
			}
			else{
				_Tempo.Dec1++;
			}
		}
		else{
			_Tempo.Dec0++;
		}
	}
}
void RubikTimerModule::IncElapsedTime(){
	
	if ((_Estado.ElapsedTime < 255) && (_Estado.Ativo) ) {
		_Estado.ElapsedTime++;
	}
}
void RubikTimerModule::SendTime(){
	if (_Estado.Ativo){
		SendMin();
		SendSec();
		SendDec();
	}
}
unsigned char* RubikTimerModule::ToStream(){
	unsigned char buffer[5] = {0 , 0, 0, 0, 0};
    boolean colocaTempo = true;
	int numBytes = 0;
	
	// cria informação de byte 1
	// coloca informação de ID no 1º byte
	buffer[numBytes] = _ID << 3;
	// coloca informação de ativo no 1º byte
	if (_Estado.Ativo) {
	  buffer[numBytes]++;
	  colocaTempo = false;
    }
	switch (_Estado.Tipo) {
		case stPause:
			buffer[numBytes] |= 4;
			break;
		case stStart:
			buffer[numBytes] |= 2;
			break;
	}
	
	numBytes++;
	if (colocaTempo) {
	    // coloca informação 
	    buffer[numBytes++] = _Tempo.Min;
		buffer[numBytes] = _Tempo.Sec1 << 4;
		buffer[numBytes++] |= _Tempo.Sec0;
		buffer[numBytes] = _Tempo.Dec1 << 4;
		buffer[numBytes++] |= _Tempo.Dec0;
	}
	buffer[numBytes] = 255;
	
	return buffer;
}
void RubikTimerModule::VerifyStateChanged(){
    _StateChanged = false;
	State newState = ReadState();
	//////////////////////////////////////////////////////////////////////////////
	// Verifica se trocou o estado de ativo (on/off)
	if (_Estado.Ativo != newState.Ativo) {
		Reset(newState.Ativo);
		_StateChanged = true;
	}
	/////////////////////////////////////////////////////////////////////////////
	// Verifica se botão foi pressionado
	if (_Estado.ElapsedTime >= c_MinElapsedTime) {
		if ( (newState.Tipo == stButtonPressed) && (!_Estado.BotaoPressed) ) {
			/////////////////////////////////////////////////////////////////////////
			// Usuário apertou o botão, começa a contar o tempo que o botão fica apertado.
			_Estado.BotaoPressed = true;
			_Estado.ElapsedTime = 0;      
		}
		else if ( (newState.Tipo == stButtonNotPressed) && (_Estado.BotaoPressed) ) {
			/////////////////////////////////////////////////////////////////////////
			// Usuário soltou o botão, hora de trocar o estado
			_Estado.BotaoPressed = false;
			_Estado.ElapsedTime = 0;
			switch (_Estado.Tipo) {
				case stPause: _Estado.Tipo = stReset;
							  _StateChanged = true;
							  _Tempo.Min  = 0;
							  _Tempo.Sec1 = 0;
							  _Tempo.Sec0 = 0;
							  _Tempo.Dec1 = 0;
							  _Tempo.Dec0 = 0;
							  break;
				case stStart: _Estado.Tipo = stPause;
				              _StateChanged = true;
							  break;
				case stReset: _Estado.Tipo = stStart;
				              _StateChanged = true;
							  break; 
			}  
		}
	}
}
void RubikTimerModule::SetState(StateType newStateType){
	_Estado.Tipo = newStateType; 
}
byte RubikTimerModule::ID(){
	return _ID;
}
bool RubikTimerModule::IsActive(){
	return _Estado.Ativo;
}

// Private Methods
State RubikTimerModule::ReadState(){
	State newState;
  
	delayMicroseconds(c_ADCRestTime);
	int voltage = analogRead(_pinAnalog);  
	//////////////////////////////////////////////////////////////////////////////
	// Converte Tensão em Estado
	if (voltage < c_NotAtivo) {
		newState.Ativo  = false;
		newState.Tipo = stButtonNotPressed;
	}
	else if (voltage < c_AtivoNotPressed) {
		newState.Ativo  = true;
		newState.Tipo = stButtonNotPressed;
	}
	else {
		newState.Ativo = true;
		newState.Tipo = stButtonPressed;
	}  
	return newState;
}
void RubikTimerModule::SelectDisplay(byte mask){
	digitalWrite(_pinA, 1  & mask);
	digitalWrite(_pinB, 2  & mask);
	digitalWrite(_pinC, 4  & mask);
	digitalWrite(_pinD, 8  & mask);	 	
	// Espera o tempo de acomodação
	delayMicroseconds(_AcomodationTime);
	digitalWrite(_pinE, 16 & mask);
	delayMicroseconds(_AcomodationTime);
	digitalWrite(pinNone,LOW);

}
void RubikTimerModule::SelectNone(){
	digitalWrite(pinNone,HIGH);
	digitalWrite(_pinE,LOW);
	delayMicroseconds(_AcomodationTime);
}
void RubikTimerModule::SendToDisplay(byte mask, byte numb){
	// seleciona nenhum display
	//SelectDisplay(c_maskNone);
	SelectNone();
	// envia numero para display
	_disp7segRef->printNumber(numb);
	// seleciona display correto
	SelectDisplay(mask);
	// seleciona nenhum display
	SelectNone();
	//SelectDisplay(c_maskNone);
}
void RubikTimerModule::SendMin(){	
	// Envia minuto p/ display
	if (_Tempo.Min == 10){
		SendToDisplay(_maskMin,9);
	}
	else{
		SendToDisplay(_maskMin,_Tempo.Min);
	}
}
void RubikTimerModule::SendSec(){
	// Envia Segundo para display mais significativo
	SendToDisplay(_maskSec1, _Tempo.Sec1);
	// Envia segundo para display menos significativo
	SendToDisplay(_maskSec0, _Tempo.Sec0);
}
void RubikTimerModule::SendDec(){
	// Envia Segundo para display mais significativo
	SendToDisplay(_maskDec1, _Tempo.Dec1);
	// Envia segundo para display menos significativo
	SendToDisplay(_maskDec0, _Tempo.Dec0);	
}
boolean RubikTimerModule::StateChanged(){
	return _StateChanged;
}
StateType RubikTimerModule::GetState(){
	return _Estado.Tipo;
}












