#include <Display.h>

/*******************************************************************************
                  Constantes

*/
const byte pinA = 2;
const byte pinB = 3;
const byte pinC = 4;
const byte pinD = 5;
const byte pinE = 6;
const byte pinF = 7;
const byte pinG = 8;

const byte pinDispA = 9;
//const byte pinDispB = 33;

Display7Seg myDisplay(pinA,pinB,pinC,pinD,pinE,pinF,pinG);

/*******************************************************************************
                  ReadSerial
    Fica esperando chegar um byte da serial e retorna esse byte
*/
char ReadSerial(){
  int inByte = -1;
  /////////////////////////////////////////////////////////////////////////////
  // Serial está disponível, fica esperando chegar byte
  while (inByte < 0) {
    inByte = Serial.read();
  }
  return (char)inByte;
}
/*******************************************************************************
                  SelDisplay
    Fica esperando chegar um byte da serial e retorna esse byte
*/
void SelDisplay(boolean dispA){
 // digitalWrite(pinDispA, LOW);
 // digitalWrite(pinDispB, LOW);
  
  delayMicroseconds(1);
  
  if (dispA){
    digitalWrite(pinDispA, HIGH);
  }
  else{
    digitalWrite(pinDispA, LOW);
  }
  
  delayMicroseconds(1);
}

/*******************************************************************************
                  SETUP
*/
void setup() {
  // Inicializa Pinos In/Out
  pinMode(pinA, OUTPUT); 
  pinMode(pinB, OUTPUT); 
  pinMode(pinC, OUTPUT); 
  pinMode(pinD, OUTPUT); 
  pinMode(pinE, OUTPUT); 
  pinMode(pinF, OUTPUT); 
  pinMode(pinG, OUTPUT); 
  pinMode(pinDispA, OUTPUT);
//  pinMode(pinDispB, OUTPUT);
  // start serial port at 9600 bps:
  Serial.begin(9600);
}

/*******************************************************************************
                  LOOP
*/
void loop() {
  char numb;
  boolean ledA = true;
  while (true){   
    numb = ReadSerial();

    myDisplay.printNumber(numb);
    
    if (numb == 'a'){
      SelDisplay(true);
    } else if (numb == 'b'){
      SelDisplay(false);
    }  
  }
}


