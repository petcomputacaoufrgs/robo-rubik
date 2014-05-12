#include "Claw.h"
#include "Robot.h"
#include "RobotSerial.h";


// << Constructor >>
Robot::Robot(int leftClawOutputs[6], int rightClawOutputs[6])
{
	this->leftClaw = new Claw();
	this->rightClaw = new Claw();

	inicialize(leftClawOutputs, rightClawOutputs);
}


// << Destructor >>
Robot::~Robot() {}

Robot::Robot()
{
	this->leftClaw = new Claw();
	this->rightClaw = new Claw();
        this->serial = new RobotSerial();
        this->error = false;
}


void Robot::inicialize(int leftClawOutputs[6], int rightClawOutputs[6])
{

	leftClaw->inicialize(leftClawOutputs[0],
			    leftClawOutputs[1],
			    leftClawOutputs[2],
			    leftClawOutputs[3],
			    leftClawOutputs[4],
			    leftClawOutputs[5]);

	rightClaw->inicialize(rightClawOutputs[0],
			    rightClawOutputs[1],
			    rightClawOutputs[2],
			    rightClawOutputs[3],
			    rightClawOutputs[4],
			    rightClawOutputs[5]);

}

Claw * Robot::getRightClaw()
{
    return this->rightClaw;
}

Claw * Robot::getLeftClaw()
{
    return this->leftClaw;
}

RobotSerial * Robot::getSerial()
{
   return this->serial;
}

boolean Robot::getError()
{
    return this->error;  
}

// If a claw is in position 3, it's impossible move the other.

void Robot::moveRightClaw90Up()
{
  
  if(getLeftClaw()->getPosition() != 3)
    getRightClaw()->move90Up();
  else
    this->error = true;
}

void Robot::moveRightClaw90Down()
{

  if(getLeftClaw()->getPosition() != 3)
    getRightClaw()->move90Down();
  else
    this->error = true;
  
}

void Robot::moveLeftClaw90Up()
{
  
  if(getRightClaw()->getPosition() != 3)
    getLeftClaw()->move90Up();
  else
    this->error = true;
  
}

void Robot::moveLeftClaw90Down()
{
  
  if(getRightClaw()->getPosition() != 3)
    getLeftClaw()->move90Down();
  else
    this->error = true;
    
}



void Robot::openLeftClaw()
{
  leftClaw->openClaw();
}

void Robot::closeLeftClaw()
{
  leftClaw->closeClaw();
}

void Robot::negLeftClaw()
{
 leftClaw->negOpen();
}

void Robot::openRightClaw()
{
  rightClaw->openClaw();
}

void Robot::closeRightClaw()
{
  rightClaw->closeClaw();
}

void Robot::negRightClaw()
{
  rightClaw->negOpen(); 
}
