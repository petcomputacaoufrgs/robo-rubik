/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:

const int DELAY=500;


int rele1 = 8;
int rele2 = 2;
int rele3 = 6;
int rele4 = 7;
int esq1 = 3;
int esq2 = 10;
int esq3 = 4;
int esq4 = 5;
int dir1 = 9;
int dir2 = 11;
int dir3 = 12;
int dir4 = 13;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT);
  pinMode(rele4, OUTPUT);  
  pinMode(esq1, OUTPUT);
  pinMode(esq2, OUTPUT);
  pinMode(esq3, OUTPUT);
  pinMode(esq4, OUTPUT);  
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(dir3, OUTPUT);
  pinMode(dir4, OUTPUT);
  
  //digitalWrite(esq1,HIGH);
  //delay(10000);
  //digitalWrite(esq1, LOW);
  //delay(10000);
}
  
// the loop routine runs over and over again forever:
void loop() {

  digitalWrite(dir4, HIGH);
  delay(DELAY);                
  digitalWrite(dir4, LOW);
  delay(DELAY);

  digitalWrite(dir1, HIGH);
  delay(DELAY);                
  digitalWrite(dir1, LOW);
  delay(DELAY);
  
  digitalWrite(dir2, HIGH);
  delay(DELAY);                
  digitalWrite(dir2, LOW);
  delay(DELAY);
  
  digitalWrite(dir3, HIGH);
  delay(DELAY);                
  digitalWrite(dir3, LOW);
  delay(DELAY);
  
  digitalWrite(dir2, HIGH);
  delay(DELAY);                
  digitalWrite(dir2, LOW);
  delay(DELAY);
  
    digitalWrite(dir1, HIGH);
  delay(DELAY);                
  digitalWrite(dir1, LOW);
  delay(DELAY);

  
}
