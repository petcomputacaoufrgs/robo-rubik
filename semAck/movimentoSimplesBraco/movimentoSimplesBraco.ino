// ROBO RUBIK - CONTROLE DE MOVIMENTOS - CÓDIGO ARDUINO //

// ------------ ÁREA DE DEFINES ------------

// posições dos braços
#define ESQ_POS1 10
#define ESQ_POS2 4
#define ESQ_POS3 5 
#define ESQ_POS4 3

#define DIR_POS1 11
#define DIR_POS2 9
#define DIR_POS3 13
#define DIR_POS4 12

// controle das garras

#define ESQ_ABRE 6 
#define ESQ_FECHA 7

#define DIR_ABRE 8
#define DIR_FECHA 2

// retorno de estado
#define ESQ_ACK A0
#define DIR_ACK A1

// outras constantes
#define ESQUERDO 0
#define DIREITO 1

#define ABERTO HIGH
#define FECHADO LOW

#define POSICAO1 1
#define POSICAO2 2
#define POSICAO3 3
#define POSICAO4 4

#define TEMPO_ESPERA 300
#define ENTREONOFF 100

// posições default dos braços
static int POS_DEFAULT_ESQ = POSICAO1;
static int POS_DEFAULT_DIR = POSICAO1;//POSICAO2;


// ------------ ÁREA DE VARIÁVEIS ------------

int posicaoAtualEsq, posicaoAtualDir;
int bracoSerial, posicaoSerial, garraSerial;
int esqAckTemp, dirAckTemp;


// ------------ INICIALIZAÇÃO ------------

void setup ()
{
	// habilitando comunicação serial
	Serial.begin (9600);
	
	// setando entradas e saídas
	pinMode (ESQ_POS1,OUTPUT);
	pinMode (ESQ_POS2,OUTPUT);
	pinMode (ESQ_POS3,OUTPUT);
	pinMode (ESQ_POS4,OUTPUT);
	
	pinMode (DIR_POS1,OUTPUT);
	pinMode (DIR_POS2,OUTPUT);
	pinMode (DIR_POS3,OUTPUT);
	pinMode (DIR_POS4,OUTPUT);
	
	pinMode (ESQ_ABRE,OUTPUT);
	pinMode (ESQ_FECHA,OUTPUT);
	
	pinMode (DIR_ABRE,OUTPUT);
	pinMode (DIR_FECHA,OUTPUT);
	
	pinMode (ESQ_ACK,INPUT); //analógico
	pinMode (DIR_ACK,INPUT); //analógico
	
	// setando estado inicial
	

        digitalWrite(DIR_FECHA, LOW);
        digitalWrite(DIR_ABRE, LOW);
        digitalWrite(ESQ_FECHA, LOW);
        digitalWrite(ESQ_ABRE, LOW);
        
        digitalWrite(ESQ_POS1, LOW);
        digitalWrite(ESQ_POS2, LOW);
        digitalWrite(ESQ_POS3, LOW);
        digitalWrite(ESQ_POS4, LOW);
        digitalWrite(DIR_POS1, LOW);
        digitalWrite(DIR_POS2, LOW);
        digitalWrite(DIR_POS3, LOW);
        digitalWrite(DIR_POS4, LOW);
          
	posicaoAtualEsq = POSICAO1;
	posicaoAtualDir = POSICAO1;//POSICAO2;
	
	delay(3000);
        
        setEsq (POS_DEFAULT_ESQ, FECHADO);
	setDir (POS_DEFAULT_DIR, FECHADO);


	esqAckTemp = 1;
	dirAckTemp = 1;
}

// ------------ MAIN ------------

void loop ()
{	


        
        
        movimento (ESQUERDO, POSICAO2, FECHADO);
        movimento (DIREITO, POSICAO2, FECHADO);

//        
//        dirABRE ();
//        dirFECHA ();

//        esqABRE ();
//        esqFECHA ();

      //delay(000);
}

// ------------ MOVIMENTOS GERAIS ------------
void movimento (int braco, int posicao, int garra)
{
	if (braco == ESQUERDO)
		setEsq (posicao, garra);
	else if (braco == DIREITO)
		setDir (posicao, garra);
}

int setEsq (int posicao, int garra)
{
	switch (posicao)
	{
		case POSICAO1:
			garraESQ (FECHADO);
			esqPOS1 ( );
                        garraESQ (ABERTO);
                        esqPOSdefault ();
			break;
		case POSICAO2:
			garraESQ (FECHADO);
			esqPOS2 ( );
                        garraESQ (ABERTO);
                        esqPOSdefault ();
			break;
		case POSICAO3:
			garraESQ (FECHADO);
			esqPOS3 ( );
                        garraESQ (ABERTO);
                        esqPOSdefault ();
			break;
		case POSICAO4:
			garraESQ (FECHADO);
			esqPOS4 ( );
                        garraESQ (ABERTO);
                        esqPOSdefault ();
			break;
					
	}
}

int setDir (int posicao, int garra)
{
	switch (posicao)
	{
		case POSICAO1:
			garraDIR (FECHADO);
			dirPOS1 ( );
                        garraDIR (ABERTO);
                        dirPOSdefault ();
			break;
		case POSICAO2:
			garraDIR (FECHADO);
			dirPOS2 ( );
                        garraDIR (ABERTO);
                        dirPOSdefault ();
			break;
		case POSICAO3:
			garraDIR (FECHADO);
			dirPOS3 ( );
                        garraDIR (ABERTO);
                        dirPOSdefault ();
			break;
		case POSICAO4:
			garraDIR (FECHADO);
			dirPOS4 ( );
                        garraDIR (ABERTO);
                        dirPOSdefault ();
			break;
					
	}
}

// ------------ MOVIMENTO DE BRACO ------------


//braço esquerdo
void esqPOS1 ( )
{	
	switch (posicaoAtualEsq)
	{
		case POSICAO1:
			break;
		case POSICAO2:
	
			digitalWrite (ESQ_POS1,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (ESQ_POS1,LOW);
                        
			posicaoAtualEsq = POSICAO1;
			break;
		case POSICAO3:
			esqPOS2 ();
			digitalWrite (ESQ_POS1,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (ESQ_POS1,LOW);
                        
			posicaoAtualEsq = POSICAO1;
			break;
		case POSICAO4:                        
                        
			digitalWrite (ESQ_POS1,HIGH);
			delay(ENTREONOFF);
                        digitalWrite (ESQ_POS1,LOW);
                        
                        posicaoAtualEsq = POSICAO1;
			break;
					
	}
	
	delay (TEMPO_ESPERA);	
}
////
void esqPOS2 ( )
{
	switch (posicaoAtualEsq)
	{
		case POSICAO1:
			digitalWrite (ESQ_POS2,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (ESQ_POS2,LOW);
                        
			posicaoAtualEsq = POSICAO2;
			break;
		case POSICAO2:
			break;
		case POSICAO3:

			digitalWrite (ESQ_POS2,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (ESQ_POS2,LOW);

                        posicaoAtualEsq = POSICAO2;
			break;
		case POSICAO4:
			esqPOS1 ();

			digitalWrite (ESQ_POS2,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (ESQ_POS2,LOW);

			posicaoAtualEsq = POSICAO2;
			break;
					
	}
	delay (TEMPO_ESPERA);
}
////
void esqPOS3 ( )
{
	switch (posicaoAtualEsq)
	{
		case POSICAO1:
			esqPOS2 ();
			digitalWrite (ESQ_POS3,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (ESQ_POS3,LOW);

			posicaoAtualEsq = POSICAO3;
			break;
		case POSICAO2:

			digitalWrite (ESQ_POS3,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (ESQ_POS3,LOW);

			posicaoAtualEsq = POSICAO3;
			break;
		case POSICAO3:
			break;
		case POSICAO4:
			esqPOS1 ();
			esqPOS2 ();


			digitalWrite (ESQ_POS3,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (ESQ_POS3,LOW);

			posicaoAtualEsq = POSICAO3;
			break;
					
	}
	delay (TEMPO_ESPERA);
}
////
void esqPOS4 ( )
{
	switch (posicaoAtualEsq)
	{
		case POSICAO1:
			digitalWrite (ESQ_POS4,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (ESQ_POS4,LOW);

			posicaoAtualEsq = POSICAO4;
			break;
		case POSICAO2:
			esqPOS1 ();

			digitalWrite (ESQ_POS4,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (ESQ_POS4,LOW);

			posicaoAtualEsq = POSICAO4;
			break;
		case POSICAO3:
			esqPOS2 ();
			esqPOS1 ();

			digitalWrite (ESQ_POS4,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (ESQ_POS4,LOW);

			posicaoAtualEsq = POSICAO4;
			break;
		case POSICAO4:
			break;
					
	}
	delay (TEMPO_ESPERA);
}
////
void esqPOSdefault ()
{
  switch (POS_DEFAULT_ESQ)
  {
    case POSICAO1:
        esqPOS1 ();
	break;
    case POSICAO2:
        esqPOS2 ();
	break;
    case POSICAO3:
        esqPOS3 ();
	break;
    case POSICAO4:
        esqPOS4 ();
        break;
  }
  delay (TEMPO_ESPERA);
}

//braço direito
void dirPOS1 ( )
{
	switch (posicaoAtualDir)
	{
		case POSICAO1:
			break;
		case POSICAO2:
			digitalWrite (DIR_POS1,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (DIR_POS1,LOW);
                        
			posicaoAtualDir = POSICAO1;
			break;
		case POSICAO3:
			dirPOS2 ();

			digitalWrite (DIR_POS1,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (DIR_POS1,LOW);

			posicaoAtualDir = POSICAO1;
			break;
		case POSICAO4:

			digitalWrite (DIR_POS1,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (DIR_POS1,LOW);

			posicaoAtualDir = POSICAO1;
			break;
					
	}
	delay (TEMPO_ESPERA);
}
////
void dirPOS2 ( )
{
	switch (posicaoAtualDir)
	{
		case POSICAO1:
			digitalWrite (DIR_POS2,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (DIR_POS2,LOW);
			posicaoAtualDir = POSICAO2;
			break;
		case POSICAO2:
			break;
		case POSICAO3:

			digitalWrite (DIR_POS2,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (DIR_POS2,LOW);
			posicaoAtualDir = POSICAO2;
			break;
		case POSICAO4:
			dirPOS1 ();
			digitalWrite (DIR_POS2,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (DIR_POS2,LOW);
			posicaoAtualDir = POSICAO2;
			break;
					
	}
	delay (TEMPO_ESPERA);
}
////
void dirPOS3 ( )
{
	switch (posicaoAtualDir)
	{
		case POSICAO1:
			dirPOS2 ();
			digitalWrite (DIR_POS3,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (DIR_POS3,LOW);
			posicaoAtualDir = POSICAO3;
			break;
		case POSICAO2:

			digitalWrite (DIR_POS3,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (DIR_POS3,LOW);
			posicaoAtualDir = POSICAO3;
			break;
		case POSICAO3:
			break;
		case POSICAO4:
			dirPOS1 ();
			dirPOS2 ();

			digitalWrite (DIR_POS3,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (DIR_POS3,LOW);
			posicaoAtualDir = POSICAO3;
			break;
					
	}
	delay (TEMPO_ESPERA);
}
////
void dirPOS4 ( )
{
	switch (posicaoAtualDir)
	{
		case POSICAO1:
			digitalWrite (DIR_POS4,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (DIR_POS4,LOW);
			posicaoAtualDir = POSICAO4;
			break;
		case POSICAO2:
			dirPOS1 ();

			digitalWrite (DIR_POS4,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (DIR_POS4,LOW);
			posicaoAtualDir = POSICAO4;
			break;
		case POSICAO3:
			dirPOS2 ();
			dirPOS1 ();

			digitalWrite (DIR_POS4,HIGH);
                        delay(ENTREONOFF);
                        digitalWrite (DIR_POS4,LOW);
			posicaoAtualDir = POSICAO4;
			break;
		case POSICAO4:
			break;
					
	}
	delay (TEMPO_ESPERA);
}
////
void dirPOSdefault ()
{
  switch (POS_DEFAULT_DIR)
  {
    case POSICAO1:
        dirPOS1 ();
	break;
    case POSICAO2:
        dirPOS2 ();
	break;
    case POSICAO3:
        dirPOS3 ();
	break;
    case POSICAO4:
        dirPOS4 ();
        break;
  }
}



// ------------ MOVIMENTO DE GARRA ------------
void garraESQ (int garra)
{
	if (garra == ABERTO)
		esqABRE ();
	else if (garra == FECHADO)
		esqFECHA ();

        delay (TEMPO_ESPERA);
}

void garraDIR (int garra)
{
	if (garra == ABERTO)
		dirABRE ();
	else if (garra == FECHADO)
		dirFECHA ();

        delay (TEMPO_ESPERA);
}

void esqABRE ()
{
        digitalWrite(ESQ_ABRE,HIGH);
        delay(ENTREONOFF);
        digitalWrite(ESQ_ABRE,LOW);
  
  
  
}

void esqFECHA ()
{
        digitalWrite(ESQ_FECHA,HIGH);
        delay(ENTREONOFF);
        digitalWrite(ESQ_FECHA,LOW);
}

void dirABRE ()
{
        digitalWrite(DIR_ABRE,HIGH);
        delay(ENTREONOFF);
        digitalWrite(DIR_ABRE,LOW);
}

void dirFECHA ()
{
        digitalWrite(DIR_FECHA,HIGH);
        delay(ENTREONOFF);
        digitalWrite(DIR_FECHA,LOW);
}


// ------------ FUNÇÕES AUXILIARES ------------

int leituraAck (int braco)
{
	int leitura;
	if (braco == ESQUERDO)
		{
			leitura = analogRead (ESQ_ACK);
			if (leitura > 900) // valor de sinal aceitável para se interpretar como 1 lógico
				return 1;
			else
				return 0;
		}
	else if (braco == DIREITO)
		{
			leitura = analogRead (DIR_ACK);
			if (leitura > 900) // valor de sinal aceitável para se interpretar como 1 lógico
				return 1;
			else
				return 0;
		}
}
