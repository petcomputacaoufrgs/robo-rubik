#include <Display.h>
#include <RubikTimerModule.h>


/*******************************************************************************
              VARIÁVEIS
*/
  Display7Seg myDisplay(pinA,pinB,pinC,pinD,pinE,pinF,pinG);
  
  RubikTimerModule Modules[c_MaxModules] = {
      RubikTimerModule(0,pin10,pin11,pin12,pin13,pin09,pinAnalog0,mask0Min,mask0Sec1,mask0Sec0,mask0Dec1,mask0Dec0,&myDisplay) , 
      RubikTimerModule(1,pin10,pin11,pin12,pin13,pin09,pinAnalog1,mask1Min,mask1Sec1,mask1Sec0,mask1Dec1,mask1Dec0,&myDisplay) , 
      RubikTimerModule(2,pin10,pin11,pin12,pin13,pin09,pinAnalog2,mask2Min,mask2Sec1,mask2Sec0,mask2Dec1,mask2Dec0,&myDisplay) , 
      RubikTimerModule(3,pin13,pin12,pin11,pin10,pin09,pinAnalog3,mask3Min,mask3Sec1,mask3Sec0,mask3Dec1,mask3Dec0,&myDisplay) , 
      RubikTimerModule(4,pin13,pin12,pin11,pin10,pin09,pinAnalog4,mask4Min,mask4Sec1,mask4Sec0,mask4Dec1,mask4Dec0,&myDisplay) , 
  };

/*******************************************************************************
                  SETUP
*/
void setup() {
  // Inicializa Pinos In/Out
  // Pinos do Display
  pinMode(pinA, OUTPUT); 
  pinMode(pinB, OUTPUT); 
  pinMode(pinC, OUTPUT); 
  pinMode(pinD, OUTPUT); 
  pinMode(pinE, OUTPUT); 
  pinMode(pinF, OUTPUT); 
  pinMode(pinG, OUTPUT); 
  
  // Pinos de seleção 
  pinMode(pin09, OUTPUT);
  digitalWrite(pin09,LOW);
  pinMode(pin10, OUTPUT);
  digitalWrite(pin10,LOW);
  pinMode(pin11, OUTPUT);
  digitalWrite(pin11,LOW);
  pinMode(pin12, OUTPUT);
  digitalWrite(pin12,LOW);
  pinMode(pin13, OUTPUT);  
  digitalWrite(pin13,LOW);
  
  pinMode(pinNone,OUTPUT);
  digitalWrite(pinNone,HIGH);
  
  // Pinos de Entrada Analógica
  pinMode(pinAnalog0,INPUT);
  pinMode(pinAnalog1,INPUT);
  pinMode(pinAnalog2,INPUT);
  pinMode(pinAnalog3,INPUT);
  pinMode(pinAnalog4,INPUT);  

  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (Serial.read() == -1){}
}

/*******************************************************************************
                  LOOP
*/
void loop() {
  unsigned long timeNow;
  unsigned long timeLastSend = micros();//millis();  // tempo em ms do último envio
  unsigned long timeBetween;
  byte buffer[5];
  
  boolean bFirst = true;  
  while (true){    
    ////////////////////////////////////////////////////////////////////////////
    // Percorre os módulos lendo o estado de cada um
    for (int i =0;i<c_MaxModules;i++){      
     if ( (Modules[i].VerifyStateChanged()) || (bFirst) ){
        // aqui manda para o pc o estado do módulo
        Modules[i].ToStream(buffer);
        int pos = 0;
        while (buffer[pos++] != 255){
        //  Serial.println(buffer[pos++],BIN);
        }
      //  Serial.println(buffer[pos++],BIN);
        Serial.write(buffer,pos);
       }
    }
    bFirst = false;
   
    ////////////////////////////////////////////////////////////////////////////
    // Verifica se deve enviar tempo para os módulos
    timeNow = micros();//millis();
    timeBetween = timeNow - timeLastSend;
    if (timeBetween >= c_TimeBetweenSend) {
      timeLastSend = timeNow - (timeBetween - c_TimeBetweenSend) ;
       // Incrementa ElapsedTime de cada módulo (controle botão)
      for (int i = 0; i < c_MaxModules; i++){
        Modules[i].IncElapsedTime();
        Modules[i].IncTime();   
        Modules[i].SendTime();      
      }    
    }    

  }
}



