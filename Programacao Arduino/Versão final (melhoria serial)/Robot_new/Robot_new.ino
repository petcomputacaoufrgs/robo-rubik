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
//int rightClawOptions[6] = {12,11, 10, 13, 3, 2};

int analogInput[2] = {0, 1}; // -- Analog input
boolean done = false;
char newChar;
String queue;
void setup()
{
  
  Serial.begin(9600);
  //while(!Serial){}  //for leonardo only
  queue = "";
  roborubik.inicialize(leftClawOptions , rightClawOptions);
  
  roborubik.openLeftClaw();
  roborubik.openRightClaw();
  // Wait for the cube
  delay(5000);
  roborubik.closeLeftClaw();
  delay(7000);
  roborubik.closeRightClaw();
 
}

void loop()
{
  
    done = false;
    
     
     while(!roborubik.getSerial()->getReady()) {
       
       roborubik.getSerial()->receiveData();
       roborubik.getSerial()->printBuffer();
       Serial.print("\n");
       
     }
     
     
     Serial.print("\nBuffer size:");
     Serial.print(roborubik.getSerial()->getBufferSize());
     Serial.print("\n");
     
     
     while(!done) {
      
        if(roborubik.getError())
        {
         roborubik.openLeftClaw();
         roborubik.openRightClaw();
         Serial.println('E');
         break;
        }
        
          
        
        newChar = roborubik.getSerial()->getInput();
        roborubik.getSerial()->printBuffer();
        Serial.print("\n");
        
        switch(newChar)
        {
          case 'a':
            roborubik.moveRightClaw90Up();
            break;
          case 'b':
            roborubik.moveRightClaw90Down();
            break;
          case 'c':
            roborubik.moveLeftClaw90Up();
            break;
          case 'd':
            roborubik.moveLeftClaw90Down();
            break;
          case 'e':
            roborubik.negLeftClaw();
            break;
          case 'f':
            roborubik.negRightClaw();
            Serial.print(newChar);
            break;
          case 'S':
            roborubik.openRightClaw();
            roborubik.openLeftClaw();
            done = true;
            while(1){}
            break;
          case 'z':
          default:
          roborubik.negRightClaw();
          roborubik.negRightClaw();
          roborubik.negRightClaw();
          roborubik.negRightClaw();
            //Serial.print("err");
            // nothing
        }
        
        
     }
  
}



