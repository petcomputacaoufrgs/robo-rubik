#include "Claw.h"

// ruan say: geralmente se deixa as definições de constantes no .h, mas whatever
/** Rotate speed  **/
const int ROTATE_FAST_SPEED = 200;
const int ROTATE_SPEED = 400;

/** Open-close claw speed **/
const int OPEN_CLOSE_TIME = 300;

/**

int rele1 = 8;
int rele2 = 2;
int rele3 = 6;
int rele4 = 7;
int esq1 = 4;
int esq2 = 5;
int esq3 = 3;
int esq4 = 10;
int dir1 = 12;
int dir2 = 11;
int dir3 = 9;
int dir4 = 13;

**/

// << Constructor >>
Claw::Claw(int position1, int position2, int position3, int position4, int open, int close)
{
    inicialize(position1, position2, position3, position4, open, close);   
}


// << Destructor >>
Claw::~Claw() {}

Claw::Claw() {}


void Claw::inicialize(int position1, int position2, int position3, int position4, int open, int close)
{
    this->_position1 = position1;
    this->_position2 = position2;
    this->_position3 = position3;
    this->_position4 = position4;
    this->_open = open;
    this->_close = close;

    pinMode(this->_position1, OUTPUT);
    pinMode(this->_position2, OUTPUT);
    pinMode(this->_position3, OUTPUT);
    pinMode(this->_position4, OUTPUT);
    pinMode(this->_open, OUTPUT);
    pinMode(this->_close, OUTPUT);
    
    //setPosition(2);
    moveToPosition2();
    openClaw();
    
    /** Wait the cube **/
    delay(500);
    
}


int Claw::getPosition()
{
    return this->position;
}

int Claw::getOpen()
{
    return this->open;
}

void Claw::setPosition(int newPosition)
{
    this->position = newPosition;
}

void Claw::negOpen()
{
    if(! this->open)
        openClaw();
    else
        closeClaw();

}

void Claw::openClaw()
{
    digitalWrite(this->_open, HIGH);
    digitalWrite(this->_close, LOW);
    delay(OPEN_CLOSE_TIME);
digitalWrite(this->_open, LOW);
    this->open = true;
}

void Claw::closeClaw()
{
    digitalWrite(this->_open,LOW);
    digitalWrite(this->_close,HIGH);
    delay(OPEN_CLOSE_TIME);
  digitalWrite(this->_close,LOW);
    this->open = false;
}

void Claw::setOpen(bool open)
{
    this->open = open;
}


void Claw::moveToPosition1()
{
    digitalWrite(this->_position1, HIGH);
    digitalWrite(this->_position2, LOW);
    digitalWrite(this->_position3, LOW);
    digitalWrite(this->_position4, LOW);
    
    setPosition(1);
    
    delay(ROTATE_SPEED);
    digitalWrite(this->_position1, LOW);
}

void Claw::moveToPosition2()
{
    digitalWrite(this->_position1, LOW);
    digitalWrite(this->_position2, HIGH);
    digitalWrite(this->_position3, LOW);
    digitalWrite(this->_position4, LOW);
    
    setPosition(2);
    
    delay(ROTATE_SPEED);
    digitalWrite(this->_position2, LOW);
    
}

void Claw::moveToPosition3()
{
    digitalWrite(this->_position1, LOW);
    digitalWrite(this->_position2, LOW);
    digitalWrite(this->_position3, HIGH);
    digitalWrite(this->_position4, LOW);
    
    setPosition(3);
    
    delay(ROTATE_SPEED);
    digitalWrite(this->_position3, LOW);
}

void Claw::moveToPosition4()
{
    digitalWrite(this->_position1, LOW);
    digitalWrite(this->_position2, LOW);
    digitalWrite(this->_position3, LOW);
    digitalWrite(this->_position4, HIGH);
    
    setPosition(4);
    
    delay(ROTATE_SPEED);
    digitalWrite(this->_position4, LOW);
}

void Claw::move90Up()
{
    switch(getPosition())
    {
        case 2:
          moveToPosition3();
        break;
        case 3:
          moveToPosition4();
        break;
    }
}

void Claw::move90Down()
{
    switch(getPosition())
    {
        case 3:
          moveToPosition2();
        break;
        case 4:
          moveToPosition3();
        break;
    }
}


void Claw::test()
{
  move90Up();

  
}
