/*******************************************************************************
                  Constantes

*/
const int pinA = 8;
const int pinB = 6;
const int pinC = 4;
const int pinD = 2;
const int pinE = 7;
const int pinF = 5;
const int pinG = 3;

const int minuto;
const int sec1;
const int sec2;
const int dec1;
const int dec2;

/*******************************************************************************
                  Send0ToDisplay
    Envia 0
*/
void Send0ToDisplay(){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
}
/*******************************************************************************
                  Send1ToDisplay
    Envia 1
*/
void Send1ToDisplay(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}
/*******************************************************************************
                  Send2ToDisplay
    Envia 2
*/
void Send2ToDisplay(){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);
}
/*******************************************************************************
                  Send3ToDisplay
    Envia 3
*/
void Send3ToDisplay(){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);
}
/*******************************************************************************
                  Send4ToDisplay
    Envia 4
*/
void Send4ToDisplay(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}
/*******************************************************************************
                  Send5ToDisplay
    Envia 5
*/
void Send5ToDisplay(){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}
/*******************************************************************************
                  Send6ToDisplay
    Envia 6
*/
void Send6ToDisplay(){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}
/*******************************************************************************
                  Send7ToDisplay
    Envia 7
*/
void Send7ToDisplay(){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
}
/*******************************************************************************
                  Send8ToDisplay
    Envia 8
*/
void Send8ToDisplay(){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}
/*******************************************************************************
                  Send9ToDi
    Envia 9
*/
void Send9ToDisplay(){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}


/*******************************************************************************
                  SendNumberToDisplay
    Envia um número para o display
*/
void SendNumberToDisplay(char number){
  switch (number){
    case '0' : Send0ToDisplay();
               break;
    case '1' : Send1ToDisplay();
               break;
    case '2' : Send2ToDisplay();
               break;
    case '3' : Send3ToDisplay();
               break;
    case '4' : Send4ToDisplay();
               break;
    case '5' : Send5ToDisplay();
               break;
    case '6' : Send6ToDisplay();
               break;
    case '7' : Send7ToDisplay();
               break;
    case '8' : Send8ToDisplay();
               break;
    case '9' : Send9ToDisplay();
               break;              
  }
}

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
  // start serial port at 9600 bps:
  Serial.begin(9600);
}

/*******************************************************************************
                  LOOP
*/
void loop() {
  char numb; 
  while (true){    
    numb = ReadSerial();
    SendNumberToDisplay(numb);
  }
}
