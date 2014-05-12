#ifndef ROBOT_H
#define ROBOT_H

	enum Moviment	//definindo algumas enuns para enviar dados para o arduino
	{
		UP90 = 0x02,
		DOWN90 = 0x04,
		TOGGLE = 0x06,
	};

	enum Claws
	{
		RIGHT = 0x20,
		LEFT = 0x21
	};



#include <Arduino.h>
#include "Claw.h"
#include "RobotSerial.h"

class Robot {

    private:

    /**
      Claws
    **/
    Claw * leftClaw;
    Claw * rightClaw;
    
    RobotSerial * serial;
    boolean error;

    // testes (colocar como private)
    public:
    Claw * getRightClaw();
    Claw * getLeftClaw();
    RobotSerial * getSerial();
    boolean getError();

    void moveRightClaw90Up();
    void moveRightClaw90Down();
    void moveLeftClaw90Up();
    void moveLeftClaw90Down();
    
    void openLeftClaw();
    void closeLeftClaw();
    void negLeftClaw();
    void openRightClaw();
    void closeRightClaw();
    void negRightClaw();

    
    void inicialize(int leftClawOutputs[6], int rightClawOutputs[6]);
    Robot();
    Robot(int leftClawOutputs[6], int rightClawOutputs[6]);
    ~Robot();

};


#endif
