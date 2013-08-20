/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:

#define DELAY   900
#define ENTREONOFF  50

#define DIR_ABRE  8
#define DIR_FECHA  2
#define ESQ_ABRE  6
#define ESQ_FECHA  7
#define esq1  3
#define esq2  10
#define esq3  4
#define esq4  5
#define dir1  9
#define dir2  11
#define dir3  12
#define dir4  13



// the setup routine runs once when you press reset:

void setup() {                
  
  pinMode(DIR_ABRE, OUTPUT);
  pinMode(DIR_FECHA, OUTPUT);
  pinMode(ESQ_ABRE, OUTPUT);
  pinMode(ESQ_FECHA, OUTPUT);  
  pinMode(esq1, OUTPUT);
  pinMode(esq2, OUTPUT);
  pinMode(esq3, OUTPUT);
  pinMode(esq4, OUTPUT);  
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(dir3, OUTPUT);
  pinMode(dir4, OUTPUT);
  
  digitalWrite(DIR_FECHA, LOW);
  digitalWrite(DIR_ABRE, LOW);
  digitalWrite(ESQ_FECHA, LOW);
  digitalWrite(ESQ_ABRE, LOW);
  
  //delay(3000);
}
  
// the loop routine runs over and over again forever:
void loop() {
  
  delay(DELAY);
  
  digitalWrite(DIR_ABRE, HIGH);
  digitalWrite(ESQ_ABRE,HIGH);
  delay(ENTREONOFF);
  digitalWrite(DIR_ABRE, LOW);
  digitalWrite(ESQ_ABRE,LOW);
  
  delay(DELAY);
  
  digitalWrite(DIR_FECHA, HIGH);
  digitalWrite(ESQ_FECHA,HIGH);
  delay(ENTREONOFF);
  digitalWrite(DIR_FECHA, LOW);
  digitalWrite(ESQ_FECHA,LOW);
  
}
