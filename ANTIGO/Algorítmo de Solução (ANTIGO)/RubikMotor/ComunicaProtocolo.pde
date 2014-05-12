#include <RubikMotor.h>
#include <RubikMotorData.h>

/*******************G************************************************************
              VARIÁVEIS
*/
Estado actualState = eIdle;
byte buffer[c_MaxBufferSize];
unsigned short indexBuffer = 0;
RubikMotor MotorFrente(pinM1pos0,pinM1pos90,pinM1pos_90,pinM1pos180,pinM1GarraEsq,pinM1GarraDir,pinM1Ack);
RubikMotor MotorEsq(pinM2pos0,pinM2pos90,pinM2pos_90,pinM2pos180,pinM2GarraEsq,pinM2GarraDir,pinM2Ack);

/*******************************************************************************
                              Código Programa
/*******************************************************************************/
/*******************************************************************************
                  ClearBuffer
*/
void ClearBuffer(){
  for (indexBuffer = c_MaxBufferSize -1;indexBuffer >= 0;indexBuffer--){
    buffer[indexBuffer] = 0;
  }
}
/*******************************************************************************
                  AddMovement
*/
void AddMovement(byte movement){
  if (indexBuffer < c_MaxBufferSize){
    buffer[indexBuffer] = movement;
    indexBuffer++;
  }
}
/*******************************************************************************
                  IsGarraFrente
*/
boolean IsGarraFrente(byte command) {
  return ((command & MaskGarra) == cGarraFrente);
}
/*******************************************************************************
                  IsTurnFace
*/
boolean IsTurnFace(byte command) {
  return ((command & MaskMove) == cTurnFace);
}
/*******************************************************************************
                  IsAngle180
*/
boolean IsAngle180(byte command) {
  return ((command & MaskAng) == cAngle180);
}
/*******************************************************************************
                  IsClockAnti
*/
boolean IsClockAnti(byte command) {
  return ((command & MaskClock) == cClockAnti);
}
/*******************************************************************************
                  IsCommand
*/
boolean IsCommand(byte command) {
  return ((command & MaskCommand) == cCommand);
}
/*******************************************************************************
                  ReadSerial
    Fica esperando chegar um byte da serial e retorna esse byte
*/
byte ReadSerial(){
  int inByte = -1;
  /////////////////////////////////////////////////////////////////////////////
  // Serial está disponível, fica esperando chegar byte
  while (inByte < 0) {
    inByte = Serial.read();
  }
  return (byte)inByte;
}
/*******************************************************************************
                  ExecuteMovements
    Executa todos os movimentos do buffer
    Primeiro movimento está nos bits menos significativos
    Segundo movimento está nos bits mais significativos. Porém pode ser um Nop
*/
void ExecuteMovements(){
  byte movement;
 // Serial.println("ExecuteMovements");
  for(int i=0;i<indexBuffer;i++){
    movement = buffer[i];
    //////////////////////////////////////////////////////////////////////////
    // Realiza primeiro movimento
    DoMovement(movement&15);
    //////////////////////////////////////////////////////////////////////////
    // Realizo segundo movimento
    movement &= 240;
    movement = movement >> 4;
    DoMovement(movement);
  }
}
/*******************************************************************************
                  DoMotorMovement
    Realiza o movimento dado no byte (4 bits menos signficativos do byte devem
    conter o movimento) com o motor correspondente
*/
void DoMotorMovement(byte movement, RubikMotor Motor){
  if (IsAngle180(movement)){
    // é movimento de 180º
  //  Serial.println("180º");
    Motor.GotoPos180();      
  }
  else{
    // é movimento de 90º, descobre o sentido
    if (IsClockAnti(movement)){
    //  Serial.println("-90 graus");
      Motor.GotoPos90();        
    }
    else{
    //  Serial.println("+90 graus");
      Motor.GotoPos_90();
    }
  }
}
/*******************************************************************************
                  DoMovement
    Realiza o movimento dado no byte (4 bits menos signficativos do byte devem
    conter o movimento)
*/
void DoMovement(byte movement){
  //////////////////////////////////////////////////////////////////////////////
  // Garanto que é um movimento
  if(!IsCommand(movement)){
    ///////////////////////////////////////////////////////////////////////////
    // Verifico se devo virar a face ou virar o cubo
    if (IsTurnFace(movement)){
      ////////////////////////////////////////////////////////////////////////
      // Devo virar a face
      DoTurn(movement);
      BackToPosition(movement);
    }
    else{
      ////////////////////////////////////////////////////////////////////////
      // Devo virar o cubo
      OpenGarra(movement);
      DoTurn(movement);
      CloseGarra(movement);
      BackToPosition(movement);
    }  
  }  
}
/*******************************************************************************
                  DoTurn
    Realiza o movimento de giro    
*/
void DoTurn(byte movement){
//  Serial.println("DoTurn");
  if (IsGarraFrente(movement)){
    // é garra frente, descobre qual o movimento
  //  Serial.println("  Garra Frente");
    DoMotorMovement(movement,MotorFrente);
  }
  else{
    // é Garra Esquerda, descobre qual o movimento
  //  Serial.println("  Garra Esquerda"); 
    DoMotorMovement(movement,MotorEsq);    
//    Serial.println("  GarraEsquerda");
  }
//  Serial.println();
}
/*******************************************************************************
                  BackToPosition
   Volta com a garra para a posição original
*/
void BackToPosition(byte movement){
 // Serial.println("BackToPosition");
 // Serial.println("");
  // Volta para posição original
  if (IsGarraFrente(movement)){
    MotorFrente.BackToPosition();
  }
  else{
    MotorEsq.BackToPosition();
  }
}
/*******************************************************************************
                  OpenGarra
   Abre a garra oposta ao movimento
*/
void OpenGarra(byte movement){
 // Serial.println("OpenGarra");
  if (IsGarraFrente(movement)){
 //  Serial.println("  Abre Esquerda");
    MotorEsq.OpenGarra();
  }
  else{
 //   Serial.println("  Abre Frente");
    MotorFrente.OpenGarra();
  }
//  Serial.println("");
}
/*******************************************************************************
                  CloseGarra
  Fecha a garra oposta ao movimento
*/
void CloseGarra(byte movement){
 // Serial.println("CloseGarra");
  if (IsGarraFrente(movement)){
  //  Serial.println("  Fecha Esquerda");
    MotorEsq.CloseGarra();
  }
  else{
 //   Serial.println("  Fecha Frente");
    MotorFrente.CloseGarra();
  }
 // Serial.println("");
}
/*******************************************************************************
                  SendAck
    Envia ack sinalizando que movimento foi realizado
*/
void SendAck(){
  Serial.write(Ack);
}
/*******************************************************************************
                  Reset
    Reinicia variaveis (buffer) e vai para estado de idle
*/
void Reset(){
  ClearBuffer();
  actualState = eIdle;
//  MotorFrente.BackToPosition();
//  MotorEsq.BackToPosition();
}
/*******************************************************************************
                  SETUP
*/
void setup() {
  // Inicializa Pinos In/Out
  // pinos Motor 1
  pinMode(pinM1pos0,OUTPUT);
  digitalWrite(pinM1pos0,LOW);
  pinMode(pinM1pos90,OUTPUT);
  digitalWrite(pinM1pos90,LOW);
  pinMode(pinM1pos_90,OUTPUT);
  digitalWrite(pinM1pos_90,LOW);
  pinMode(pinM1pos180,OUTPUT);
  digitalWrite(pinM1pos180,LOW);
  pinMode(pinM1GarraEsq,OUTPUT);
  digitalWrite(pinM1GarraEsq,LOW);
  pinMode(pinM1GarraDir,OUTPUT);
  digitalWrite(pinM1GarraDir,LOW);
  pinMode(pinM1Ack,INPUT);	
  // pinos Motor 2
  pinMode(pinM2pos0,OUTPUT);
  digitalWrite(pinM2pos0,LOW);
  pinMode(pinM2pos90,OUTPUT);
  digitalWrite(pinM2pos90,LOW);
  pinMode(pinM2pos_90,OUTPUT);
  digitalWrite(pinM2pos_90,LOW);
  pinMode(pinM2pos180,OUTPUT);
  digitalWrite(pinM2pos180,LOW);
  pinMode(pinM2GarraEsq,OUTPUT);
  digitalWrite(pinM2GarraEsq,LOW);
  pinMode(pinM2GarraDir,OUTPUT);
  digitalWrite(pinM2GarraDir,LOW);
  pinMode(pinM2Ack,INPUT);
 
  
  
  // start serial port at 9600 bps:
  Serial.begin(9600);
}

/*******************************************************************************
                  LOOP
*/
void loop() {
  byte inByte = 0;
  
//  MotorFrente.BackToPosition();
//  MotorEsq.BackToPosition();
  MotorFrente.CloseGarra();
  MotorEsq.CloseGarra();
 
  while (true){    
    ///////////////////////////////////////////////////////////////////////////
    // Verifico o estado
    //{eIdle = 1, eVision = 2, eAction = 3}
    switch (actualState) {
      case eIdle  : 
        ///////////////////////////////////////////////////////////////////////
        // Estado de Idle  
        // sai do estado quando receber um comando
        inByte = ReadSerial();
        if (IsCommand(inByte)){
          /////////////////////////////////////////////////////////////////////
          // Recebeu um comando (4 bits menos significativos)
          inByte &= 15;
          switch (inByte){
            case InitVision : actualState = eVision;                              
                              break;
            case InitAction : actualState = eAction;
                              break;
          }          
        }
        break;
      case eVision: 
        ///////////////////////////////////////////////////////////////////////
        // Estado de Visão 
        // Comandos e Movimentos nos 4 bits menos significativos.
        inByte = ReadSerial() & 15;
        if (IsCommand(inByte)){
          ////////////////////// ///////////////////////////////////////////////
          // Recebeu um comando          
          switch (inByte){
            case InitAction : actualState = eAction;
                              break;
            case Nop        :
            case Stop       : Reset();
                              break;
          }
        }
        else{
          /////////////////////////////////////////////////////////////////////
          // Recebeu movimento
          DoMovement(inByte);
      //    SendAck();          
        }
        break;
      case eAction:
        ///////////////////////////////////////////////////////////////////////
        // Estado de Ação
        // Espera chegar um comando de quit para começar a realizar os movimentos
        // Se chegar um movimento, adiciona ele no buffer
        inByte = ReadSerial();
        if (IsCommand(inByte)){
          ////////////////////////////////////////////////////////////////////
          // Chegou um comando
          switch(inByte&15){
            case Stop : // Serial.println("Executing movements...");  
                        ExecuteMovements();
                    //    SendAck();
                        Reset();
                        break;
            case Nop  : Reset();
                        break;
          }
        }
        else{
          ////////////////////////////////////////////////////////////////////
          // Chegou um movimento
          AddMovement(inByte);
        }
        break;
    }
 
  }
}












