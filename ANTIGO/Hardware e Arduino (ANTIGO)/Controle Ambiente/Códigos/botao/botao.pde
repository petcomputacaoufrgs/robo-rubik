/*******************************************************************************
                  Constantes

*/
////////////////////////////////////////////////////////////////////////////////
// Estados
enum StateType {stPause = 1, stStart = 2, stReset = 3, stButtonPressed = 4, stButtonNotPressed = 5};

////////////////////////////////////////////////////////////////////////////////
// Estrutura de tempo
struct _Time{
  byte Min;
  byte Sec;
  byte Dec;
};
typedef struct _Time Time; 
////////////////////////////////////////////////////////////////////////////////
// Estrutura de Estado
struct _State{
  boolean   Ativo;
  StateType Tipo;
  boolean   BotaoPressed; 
  byte      ElapsedTime;  // Tempo decorrido desde a última troca de estado (incrementa a cada 100ms)
};
typedef struct _State State;
////////////////////////////////////////////////////////////////////////////////
// Estrutura dos Módulos
struct _Module {
 byte  ID; 
 State Estado;     
 Time  Tempo; 
};
typedef struct _Module Module;

/*******************************************************************************
              CONSTANTES
*/
const int c_MaxModules = 5;
const int c_MinElapsedTime = 3;    // incrementa a cada 100 ms (3 = 0.33 segundos)
const int c_ADCRestTime = 100;     // 100us de descanço para o conversor AD
const int c_TimeBetweenSend = 100; // a cada 100 ms deve ser enviado um tempo para os módulos
const int pinA0 = A0;
const unsigned short c_NotAtivo = 300;
const unsigned short c_AtivoNotPressed = 400;

/*******************************************************************************
    VoltageToState    
    Retorna o estado (modulo ativo e botão) de cada módulo              
*/
struct _State VoltageToState(unsigned short Voltage){
  State newState;
  //////////////////////////////////////////////////////////////////////////////
  // Converte Tensão em Estado
  if (Voltage < c_NotAtivo) {
    newState.Ativo  = false;
    newState.Tipo = stButtonNotPressed;
  }
  else if (Voltage < c_AtivoNotPressed) {
    newState.Ativo  = true;
    newState.Tipo = stButtonNotPressed;
  }
  else {
    newState.Ativo = true;
    newState.Tipo = stButtonPressed;
  }  
  return newState;
}
/*******************************************************************************
                  SendSerial
    Envia um estado para a serial
*/
void SendStateToSerial(struct _State estado){
  Serial.println("");
  if (estado.Ativo){
    Serial.print("Ativo ");
  }
  else{
    Serial.print("Inativo ");
  }
  switch (estado.Tipo) {
    case stButtonPressed : Serial.print(": Pressed "); 
                           break;
    case stButtonNotPressed : Serial.print(": Not Pressed "); 
                           break;
    case stPause : Serial.print(": Pause "); 
                           break;
    case stStart : Serial.print(": Start "); 
                           break;
    case stReset : Serial.print(": Reset "); 
                           break;
  }

}  
/*******************************************************************************
    InitializeModule    
    Inicializa um módulo             
*/
void InitializeModule(struct _Module *Mod){
  Mod->Estado.Tipo = stReset;
  Mod->Estado.BotaoPressed = false;
  Mod->Estado.ElapsedTime = 0;
  Mod->Tempo.Min = 0;
  Mod->Tempo.Sec = 0;
  Mod->Tempo.Dec = 0;  
}

/*******************************************************************************
    VerifyStateChanged    
    Muda o estado do módulo se precisar.              
*/
boolean VerifyStateChanged(struct _Module *Mod){
  State newState;
  boolean changed = false;
  //////////////////////////////////////////////////////////////////////////////
  // Espera um 100us para o AD poder trabalhar
  delayMicroseconds(c_ADCRestTime);
  //////////////////////////////////////////////////////////////////////////////
  // Lê novo estado
  newState = VoltageToState(analogRead(pinA0));
  //////////////////////////////////////////////////////////////////////////////
  // Verifica se trocou o estado de ativo (on/off)
  if (Mod->Estado.Ativo != newState.Ativo) {
    Serial.println("trocou estado");
    if (newState.Ativo) {
      Serial.println(" agora eh ativo");
    }
    Mod->Estado.Ativo = newState.Ativo;
    InitializeModule(Mod);   
    changed = true; 
  }
  /////////////////////////////////////////////////////////////////////////////
  // Verifica se botão foi pressionado
  if (Mod->Estado.ElapsedTime >= c_MinElapsedTime) {
    if ( (newState.Tipo == stButtonPressed) && (!Mod->Estado.BotaoPressed) ) {
      /////////////////////////////////////////////////////////////////////////
      // Usuário apertou o botão, começa a contar o tempo que o botão fica apertado.
      Serial.println("botao pressionado");
      Mod->Estado.BotaoPressed = true;
      Mod->Estado.ElapsedTime = 0;      
    }
    else if ( (newState.Tipo == stButtonNotPressed) && (Mod->Estado.BotaoPressed) ) {
      /////////////////////////////////////////////////////////////////////////
      // Usuário soltou o botão, hora de trocar o estado
      Serial.println("botao nao pressionado");
      changed = true;
      Mod->Estado.BotaoPressed = false;
      Mod->Estado.ElapsedTime = 0;
      switch (Mod->Estado.Tipo) {
        case stPause: Mod->Estado.Tipo = stReset;
                      Mod->Tempo.Min = 0;
                      Mod->Tempo.Sec = 0;
                      Mod->Tempo.Dec = 0;
                      //Serial.println("estado de reset");
                      break;
        case stStart: Mod->Estado.Tipo = stPause;
                      //Serial.println("estado de pause");
                      break;
        case stReset: Mod->Estado.Tipo = stStart;
                      //Serial.println("estado de start");
                      break; 
      }  
    }
  }
  return changed;      
}
/*******************************************************************************
                  SETUP
*/
void setup() {
  // Inicializa Pinos In/Out
  pinMode(pinA0, INPUT); 
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (Serial.available() <= 0){
    delay(100);  
  }
  Serial.println("Conectado");
  
}

/*******************************************************************************
                  LOOP
*/
void loop() {
  unsigned long timeNow;
  unsigned long timeLastSend = 0;  // tempo em ms do último envio
  Module myModule;
  InitializeModule(&myModule);
  
  State myState;
  State myOldState;
  myOldState.Ativo = false;
  myOldState.Tipo  = stButtonNotPressed;
  unsigned short voltage = 0;
  
 /* while (true) {
    //////////////////////////////////////////////////////////////////////////////
    // Espera um 100us para o AD poder trabalhar
    delayMicroseconds(c_ADCRestTime);
    //////////////////////////////////////////////////////////////////////////////
    // Lê novo estado
    voltage = analogRead(pinA0);
    Serial.println(voltage,DEC);
    myState = VoltageToState(voltage);    
    SendStateToSerial(myState);
    delay(500);
  /*  if ((myState.Ativo != myOldState.Ativo) || (myState.Tipo != myOldState.Tipo) ){
      myOldState.Ativo = myState.Ativo;
      myOldState.Tipo = myState.Tipo;
      SendStateToSerial(myState);
    }*/
    
  //}
  
  while (true){ 
    if (VerifyStateChanged(&myModule)){
      SendStateToSerial(myModule.Estado);
    }
    ////////////////////////////////////////////////////////////////////////////
    // Verifica se deve enviar tempo para os módulos
    timeNow = millis();
    if (timeNow - timeLastSend >= c_TimeBetweenSend) {
      timeLastSend = timeNow;
      // Incrementa ElapsedTime de cada módulo (controle botão)
      if (myModule.Estado.ElapsedTime < 255){          
        myModule.Estado.ElapsedTime++;
      }
    }
  }
}
