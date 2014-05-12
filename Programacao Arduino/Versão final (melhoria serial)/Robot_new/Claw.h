#ifndef CLAW_H
#define CLAW_H

#include <Arduino.h>

class Claw {

    private:

    /**
      Claw state
    **/
    bool open;
    int position;

    /**
      Arduino outputs
    **/
    int _position1;
    int _position2;
    int _position3;
    int _position4;
    int _open;
    int _close;

    // testes (colocar como private)
    public:
    int getPosition();
    int getOpen();
    
    void setPosition(int newPosition);
    void setOpen(bool open);
    void negOpen();
    void openClaw();
    void closeClaw();
    
    void move90Up();
    void move90Down();
    
    void moveToPosition1();
    void moveToPosition2();
    void moveToPosition3();
    void moveToPosition4();
    void inicialize(int position1, int position2, int position3, int position4, int open, int close);
    Claw();
    Claw(int position1, int position2, int position3, int position4, int open, int close);
    ~Claw();
    void test();

};


#endif
