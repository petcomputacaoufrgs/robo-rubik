/*
  RubikData.h - Library for rubik data struct
  Created by Victor V. M. Guimaraes, September 26, 2011.
  Released into the public domain.
*/
#ifndef RubikData_h
#define RubikData_h

  ////////////////////////////////////////////////////////////////////////////////
  // Estados
	enum StateType {stPause = 1, stStart = 2, stReset = 3, stButtonPressed = 4, stButtonNotPressed = 5};
  
  ////////////////////////////////////////////////////////////////////////////////
  // Estrutura de tempo
	struct _Time{
		byte Min;
		byte Sec1;
		byte Sec0;
		byte Dec1;
		byte Dec0;
	};
	typedef struct _Time Time;  
  
  ////////////////////////////////////////////////////////////////////////////////
  // Estrutura de Estado
	struct _State{
		boolean   Ativo;
		StateType Tipo;
		boolean   BotaoPressed; 
		byte      ElapsedTime;
	};
	typedef struct _State State;
  
  ////////////////////////////////////////////////////////////////////////////////
  // Constantes
	// Pinos do Display
	const byte pinA = 8;
	const byte pinB = 6;
	const byte pinC = 4;
	const byte pinD = 2;
	const byte pinE = 7;
	const byte pinF = 5;
	const byte pinG = 3;
	
	// Pinos de Seleção
	const byte pin13 = 13;
	const byte pin12 = 12;
	const byte pin11 = 11;
	const byte pin10 = 10;
	const byte pin09 = 9;
	
	const byte pinNone = A5;
	
	// Pinos de Entrada Analógica
	const byte pinAnalog0 = A0;
	const byte pinAnalog1 = A1;
	const byte pinAnalog2 = A2;
	const byte pinAnalog3 = A3;
	const byte pinAnalog4 = A4;
	
	// Máscaras de seleção dos displays
	// modulo0
	const byte mask0Min  = 0;
	const byte mask0Sec1 = 1;
	const byte mask0Sec0 = 2;
	const byte mask0Dec1 = 3;
	const byte mask0Dec0 = 4;
	
	// modulo1
	const byte mask1Min  = 5;
	const byte mask1Sec1 = 6;
	const byte mask1Sec0 = 7;
	const byte mask1Dec1 = 8;
	const byte mask1Dec0 = 9;
	
	// modulo 2
	const byte mask2Min  = 11;
	const byte mask2Sec1 = 12;
	const byte mask2Sec0 = 13;
	const byte mask2Dec1 = 14;
	const byte mask2Dec0 = 15;
	
	// modulo 3
	const byte mask3Min  = 16;
	const byte mask3Sec1 = 17;
	const byte mask3Sec0 = 18;
	const byte mask3Dec1 = 19;
	const byte mask3Dec0 = 20;
	
	// modulo 4
	const byte mask4Min  = 27;
	const byte mask4Sec1 = 28;
	const byte mask4Sec0 = 29;
	const byte mask4Dec1 = 30;
	const byte mask4Dec0 = 31;
	
	// nenhum modulo
	const byte c_maskNone = 24;
	
	const int c_MaxModules = 5;
	const int c_MinElapsedTime = 30;    // incrementa a cada 10 ms (30 = 0.3 segundos)
	const int c_ADCRestTime = 100;      // 100us de descanço para o conversor AD
	const unsigned long c_TimeBetweenSend = 9800;//10000;//10; 	// a cada 10 ms deve ser enviado um tempo para os módulo
	const unsigned short c_NotAtivo = 270;
	const unsigned short c_AtivoNotPressed = 400;  
  
  #endif;