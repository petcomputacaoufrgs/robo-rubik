/*
  RubikMotorData.h - Library for rubik motor data struct
  Created by Victor V. M. Guimaraes, October 15, 2011.
  Released into the public domain.
*/
#ifndef RubikMotorData_h
#define RubikMotorData_h

    ////////////////////////////////////////////////////////////////////////////
    // Estados
	enum Estado {eIdle = 1, eVision = 2, eAction = 3};
	
	enum Position {pos0 , pos90, pos_90, pos180};
  
    ////////////////////////////////////////////////////////////////////////////
    // Constantes	
	// Estados
	const byte InitVision = 3;
	const byte InitAction = 7;
	const byte Stop       = 15;
	const byte Nop        = 11;
	// Máscaras
	const byte MaskCommand = 3;
	const byte MaskGarra   = 8;
	const byte MaskMove    = 4;
	const byte MaskAng     = 2;
	const byte MaskClock   = 1;
	// protocolo
	const byte cGarraFrente = 8;
	const byte cTurnFace    = 4;
	const byte cAngle180    = 2;
	const byte cClockAnti   = 1;
	const byte cCommand     = 3;
	const byte Ack = 170;
	// pinos Motor 1
	const byte pinM1pos0   	 = A2;
	const byte pinM1pos90  	 = A3;
	const byte pinM1pos_90 	 = A4;
	const byte pinM1pos180 	 = A5;
	const byte pinM1Ack    	 = 2;
	const byte pinM1GarraEsq = A0;
	const byte pinM1GarraDir = A1;
	
	// pinos Motor 2
	const byte pinM2pos0   	 = 3;
	const byte pinM2pos90  	 = 4;
	const byte pinM2pos_90 	 = 5;
	const byte pinM2pos180 	 = 6;
	const byte pinM2Ack    	 = 7;
	const byte pinM2GarraEsq = 9;
	const byte pinM2GarraDir = 8;	
	
	// pinos Extras
	const byte pinExtra0 	 = 13;
	const byte pinExtra1	 = 12;
	const byte pinExtra2 	 = 11;
	const byte pinExtra3	 = 10;	

	const unsigned short c_MaxBufferSize = 1024; 
	const byte c_DelayMotorAck = 10; // 10 ms (tempo de o motor zerar o ACK após receber um comando)
	const byte c_DelayWaitForAck = 1; // 1 ms (tempo de o motor chegar na posição correta e enviar o ack)
	const byte c_DelayGarraLow = 100; // 100 us (tempo para chegar 0 nas duas garras)
	const unsigned short c_DelayGarraSet = 500; // 500 ms (tempo para abrir ou fechar a garra)
  
  #endif;