/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:

const int DELAY=1500;


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
}
  
// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(rele1, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(esq1, HIGH);
  digitalWrite(dir1, HIGH);
  delay(DELAY);                // wait for a second
  digitalWrite(rele1, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(esq1, LOW);
  digitalWrite(dir1, LOW);
  delay(DELAY);
  digitalWrite(rele2, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(esq2, HIGH);
  digitalWrite(dir2, HIGH);
  delay(DELAY);               // wait for a second
  digitalWrite(rele2, LOW);   // turn the LED off by making the voltage LOW
  digitalWrite(esq2, LOW);
  digitalWrite(dir2, LOW);
  delay(DELAY);               // wait for a second
  digitalWrite(rele3, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(esq3, HIGH);
  digitalWrite(dir3, HIGH);
  delay(DELAY);               // wait for a second
  digitalWrite(rele3, LOW);   // turn the LED off by making the voltage LOW
  digitalWrite(esq3, LOW);
  digitalWrite(dir3, LOW);
  delay(DELAY);
  digitalWrite(rele4, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(esq4, HIGH);
  digitalWrite(dir4, HIGH);
  delay(DELAY);               // wait for a second
  digitalWrite(rele4, LOW);   // turn the LED off by making the voltage LOW
  digitalWrite(esq4, LOW);
  digitalWrite(dir4, LOW);
  delay(DELAY);
}
