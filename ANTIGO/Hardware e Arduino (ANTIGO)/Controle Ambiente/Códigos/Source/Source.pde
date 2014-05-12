/*******************************************************************************
                            DADOS
/*******************************************************************************
/*******************************************************************************
              ESTRUTURAS
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
const unsigned short c_NotAtivo = 300;
const unsigned short c_AtivoNotPressed = 400;



/*******************************************************************************
              VARIÁVEIS
*/
  StateType estadoJuiz = stPause;
  Module Modules[c_MaxModules];

/*******************************************************************************
                              Código Programa
/*******************************************************************************/

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
    InitializeModules    
    Inicializa os módulos           
*/
void InitializeModules(){
  for (int i = 0; i < c_MaxModules ; i++) {
    InitializeModule(&(Modules[i]));
    Modules[i].Estado.Ativo = false;
    Modules[i].ID = i;    
  }
}
/*******************************************************************************
    ModuleAnalogPin    
    Retorna o AnalogPin referente ao módulo              
*/
int ModuleAnalogPin(int ModuleID){
  switch (ModuleID) {
    case 0: return A4; 
    case 1: return A3; 
    case 2: return A2; 
    case 3: return A1; 
    case 4: return A0; 
  }
}
/*******************************************************************************
    VoltageToState    
    Retorna o estado (modulo ativo e botão) de cada módulo              
*/
struct _State VoltageToState(int Voltage){
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
  newState = VoltageToState(analogRead(ModuleAnalogPin(Mod->ID)));
  //////////////////////////////////////////////////////////////////////////////
  // Verifica se trocou o estado de ativo (on/off)
  if (Mod->Estado.Ativo != newState.Ativo) {
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
      Mod->Estado.BotaoPressed = true;
      Mod->Estado.ElapsedTime = 0;      
    }
    else if ( (newState.Tipo == stButtonNotPressed) && (Mod->Estado.BotaoPressed) ) {
      /////////////////////////////////////////////////////////////////////////
      // Usuário soltou o botão, hora de trocar o estado
      Mod->Estado.BotaoPressed = false;
      Mod->Estado.ElapsedTime = 0;
      switch (Mod->Estado.Tipo) {
        case stPause: Mod->Estado.Tipo = stReset;
                      Mod->Tempo.Min = 0;
                      Mod->Tempo.Sec = 0;
                      Mod->Tempo.Dec = 0;
                      break;
        case stStart: Mod->Estado.Tipo = stPause;
                      break;
        case stReset: Mod->Estado.Tipo = stStart;
                      break; 
      }  
    }
  }
  return changed;      
}
/*******************************************************************************
    VerifyJudgeStateChanged    
    Muda o estado do juiz, se precisar. Responde ok (10) e software do pc está
    livre para mandar outro estado.    
    1 = Pause
    2 = Start
    3 = Reset
*/
boolean VerifyJudgeStateChanged(){
  int inByte;
  int outByte = 10;
  boolean changed = false;
  //////////////////////////////////////////////////////////////////////////////
  // Verifica se alguma coisa foi enviada pela serial.
  inByte = Serial.read();
  if (inByte >= 0){
    changed = true;
    //////////////////////////////////////////////////////////////////////////
    // Veio algum comando
    switch (inByte) {
      case stStart: estadoJuiz = stStart;
                    break;
      case stPause: estadoJuiz = stPause;
                    break;
      case stReset: estadoJuiz = stReset;
                    break;
    }      
   /////////////////////////////////////////////////////////////////////////
   // Envia resposta (Acho que não precisa)
 //  Serial.write(outByte);
  } 
  return changed;  
}
/*******************************************************************************
    IncModulesTime    
    Incrementa o tempo dos módulos em 1 dec (se tiver em stStart)
*/
void IncModulesTime(){
  for (int i = 0; i < c_MaxModules; i++){
    if (Modules[i].Estado.Tipo == stStart) {
      IncTime(&(Modules[i]));  
    }
  }
}
/*******************************************************************************
    IncTime 
    Incrementa o tempo do módulo em 1 dec 
*/
void IncTime(struct _Module *Mod){
  ////////////////////////////////////////////////////////////////////////////
  // Incrementa Dec
  if (Mod->Tempo.Dec == 9) {
    Mod->Tempo.Dec = 0;
    //////////////////////////////////////////////////////////////////////////
    // Incrementa segundo
    if (Mod->Tempo.Sec == 59){
      Mod->Tempo.Sec = 0;
      ///////////////////////////////////////////////////////////////////////
      // Incrementa Minuto
      if (Mod->Tempo.Min == 99) {
        Mod->Tempo.Dec = 9;
        Mod->Tempo.Sec = 99;
      }
      else {
        Mod->Tempo.Min++;
      }        
    }
    else {
      Mod->Tempo.Sec++;
    }
  }
  else {
    Mod->Tempo.Dec++;
  }
}
/*******************************************************************************
    SendTimes    
    Envia os tempos para os módulos disponíveis
*/
void SendTimes(){
  for (int i = 0; i < c_MaxModules; i++){
    SendTime(Modules[i]);    
  }
}
/*******************************************************************************
    SendTimeToPC    
    Envia o tempo para o módulo (se estiver ativo)
      - Envia Estado do módulo para o PC
      ModuloID,Ativo,Tipo do estado,BotãoPress,ElapsedTime,Min,Sec,Dec
*/
void SendTimeToPC(struct _Module Mod){
/*  byte buff[8];

  buff[0] = Mod.ID;
  buff[1] =(Mod.Estado.Ativo ? 1 : 0);
  buff[2] = Mod.Estado.Tipo;
  buff[3] =(Mod.Estado.BotaoPressed ? 1 : 0);
  buff[4] = Mod.Estado.ElapsedTime;
  buff[5] = Mod.Tempo.Min;
  buff[6] = Mod.Tempo.Sec;
  buff[7] = Mod.Tempo.Dec;
  Serial.write(buff,sizeof(buff));*/
  
  // TESTE
  if (Mod.ID !=4) {
    return;
  }
  
  Serial.println("");
  Serial.print("ModID: ");
  Serial.print(Mod.ID,DEC);  
  if (Mod.Estado.Ativo){
    Serial.print("; Ativo; Estado:");
  }
  else{
    Serial.print("; Inativo; Estado:");
  }
  switch(Mod.Estado.Tipo){
    case stReset : Serial.print(" Reset; Tempo: ");
                   break;
    case stPause : Serial.print(" Pause; Tempo:");
                   break;
    case stStart : Serial.print(" Start; Tempo:");
                   break;
  }  
  Serial.print(Mod.Tempo.Min,DEC);
  Serial.print(":");
  Serial.print(Mod.Tempo.Sec,DEC);
  Serial.print(":");
  Serial.print(Mod.Tempo.Dec,DEC);
}
/*******************************************************************************
    SendTime   
    Envia o tempo para o módulo (se estiver ativo)
      - Envia tempo para o PC
      - Traduz digito para display (depende do módulo)
      - Espera saída estabilizar (entrada do ffp)
      - Escolhe saída do demux
      - Espera ffp estabilizar
      - Zera saídas do ffp
    
*/
void SendTime(struct _Module Mod){
  ///////////////////////////////////////////////////////////////////////////////
  // Envia estado do módulo para o pc
  SendTimeToPC(Mod);
  //////////////////////////////////////////////////////////////////////////////
  // Envia tempo para os módulos
  if (Mod.Estado.Ativo) {
  }
}
/*******************************************************************************
              SETUP
*/
void setup() {
  // Inicializa Pinos In/Out
  pinMode(A0, INPUT); 
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  // start serial port at 9600 bps:
  Serial.begin(9600);
  // Estabelece contato
  while ((Serial.available() <= 0)){
    delay(300);
  }
  Serial.flush();
  Serial.println("Conectado");
}

/*******************************************************************************
              LOOP
*/
void loop() {
  unsigned long timeNow;
  unsigned long timeLastSend = 0;  // tempo em ms do último envio

  // Inicializa módulos
  InitializeModules();
  estadoJuiz = stStart;
  
  while (true){    
    ////////////////////////////////////////////////////////////////////////////
    // Percorre os módulos lendo o estado de cada um
    for (int i =0;i<c_MaxModules;i++){
      if (VerifyStateChanged(&(Modules[i]))) {
        ////////////////////////////////////////////////////////////////////////
        // Mudou estado, se for reset, envia 0 para o módulo
        if (Modules[i].Estado.Tipo == stReset) {
          SendTime(Modules[i]);
        }
      }
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Verifica se o juiz mudou de estado 
    if (VerifyJudgeStateChanged()) {
      //////////////////////////////////////////////////////////////////////////
      // Se estado do juiz for de reset, zera tempo de todos os módulos
      if (estadoJuiz == stReset) {
        for (int i = 0; i < c_MaxModules; i++) {
          Modules[i].Tempo.Min = 0;
          Modules[i].Tempo.Sec = 0;
          Modules[i].Tempo.Dec = 0;                    
        }
        SendTimes();
      }
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Verifica se deve enviar tempo para os módulos
    timeNow = millis();
    if (timeNow - timeLastSend >= c_TimeBetweenSend) {
      timeLastSend = timeNow;
      // Incrementa ElapsedTime de cada módulo (controle botão)
      for (int i = 0; i < c_MaxModules; i++){
        if ( (Modules[i].Estado.Ativo) && (Modules[i].Estado.ElapsedTime < 255) ){          
          Modules[i].Estado.ElapsedTime++;
        }
      }
      // Incrementa e envia tempo para cada módulo
      if (estadoJuiz == stStart) {
        IncModulesTime();
        SendTimes();
      }            
    }
  }
}












