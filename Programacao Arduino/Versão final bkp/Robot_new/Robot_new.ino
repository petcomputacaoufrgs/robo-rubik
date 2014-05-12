#include "Robot.h"

//Claw rightClaw(12, 11, 9, 13, 6, 7);
//Claw leftClaw(3, 10, 4, 5, 8, 2);

/**
Digital:
2->4
3->5
4->8
5->9
6->3
7->13
8->6
9->10
10->7
11->11
12->12
13->2
Analog:
0->1
1->0
**/

Robot roborubik;

int rightClawOptions[6] = {12, 11, 10, 2, 3, 13};
int leftClawOptions[6] = {5, 7, 8, 9, 6, 4};


//int leftClawOptions[6] = {5, 7, 8, 9, 6, 4};
//int rightClawOptions[6] = {12, 11, 10, 13, 3, 2};

int analogInput[2] = {0, 1}; // -- Analog input
boolean done = false;
char newChar;

void setup()
{
  
  Serial.begin (9600);
  
  roborubik.inicialize(leftClawOptions , rightClawOptions);
  
  roborubik.openLeftClaw();
  roborubik.openRightClaw();
  // Wait for the cube
  delay(5000);
  roborubik.closeLeftClaw();
  delay(3000);
  roborubik.closeRightClaw();
 
}

void loop()
{
    
      while(!Serial.available()) {}
     newChar = Serial.read();
     Serial.print(newChar);

    
    if(roborubik.getError())
    {
//     roborubik.openLeftClaw();
//     roborubik.openRightClaw();
//     Serial.println('E');
//     break;
    }
    switch(newChar)
    {
      case (RIGHT|UP90):
        roborubik.moveRightClaw90Up();
        break;
      case (RIGHT|DOWN90):
        roborubik.moveRightClaw90Down();
        break;
      case (LEFT|UP90):
        roborubik.moveLeftClaw90Up();
        break;
      case (LEFT|DOWN90):
        roborubik.moveLeftClaw90Down();
        break;
      case (LEFT|TOGGLE):
        roborubik.negLeftClaw();
        break;
      case (RIGHT|TOGGLE):
        roborubik.negRightClaw();
        break;
      case 0xff:
      default:
      roborubik.negRightClaw();
      roborubik.negRightClaw();
      roborubik.negRightClaw();
      roborubik.negRightClaw();
        //Serial.print("err");
        // nothing
    }
  
  
}



