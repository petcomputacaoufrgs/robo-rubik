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
	byte min;
	byte sec;
	byte dec;
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