const int Espera_Posicionamento=500; //tempo para a garra chegar a posição (duração do movimento)
const int Espera_Garra=200; //tempo para a garra abrir ou fechar (duração do movimento)

int rele1 = 8;
int rele2 = 2;
int rele3 = 6;
int rele4 = 7;
int esq1 = 3;
int esq2 = 10;
int esq3 = 4;
int esq4 = 5;
int dir1 = 12;
int dir2 = 11;
int dir3 = 9;
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
  
  delay(10000);
  //PARA O TESTE 3
  garraEsq_abre();
  
  garraDir_pos_2();
  garraEsq_pos_2();
  
  garraDir_abre();
  delay(5000);
  garraDir_fecha();
  delay(5000);
  
}
  
void loop() {

   //TESTE1
//  garraEsq_abre();
//  garraDir_abre();
//  delay(Espera_Garra);
//  
//  garraEsq_fecha();
//  garraDir_fecha();
//  delay(Espera_Garra);
  //TESTE2
//  garraEsq_pos_2();
//  garraDir_pos_2();
//  delay(Espera_Posicionamento);
//  
//  garraEsq_abre();
//  garraDir_abre();
//  delay(Espera_Garra);
//  
//  garraEsq_pos_3();
//  garraDir_pos_3();
//  delay(Espera_Posicionamento);
//  
//  garraEsq_fecha();
//  garraDir_fecha();
//  delay(Espera_Garra);
//  
//  garraEsq_pos_4();
//  garraDir_pos_4();
//  delay(Espera_Posicionamento);  
//  
//  garraEsq_abre();
//  garraDir_abre();
//  delay(Espera_Garra);
//  
//  garraEsq_pos_3();
//  garraDir_pos_3();
//  delay(Espera_Posicionamento);
//  
//  garraEsq_fecha();
//  garraDir_fecha();
//  delay(Espera_Garra);

  //TESTE3
  garraEsq_pos_2();
  delay(Espera_Posicionamento);
  
  garraEsq_fecha();
  delay(Espera_Garra);
  
  garraEsq_pos_3();
  delay(Espera_Posicionamento);
  
  garraEsq_pos_4();
  delay(Espera_Posicionamento);
  
  garraEsq_abre();
  delay(Espera_Garra);
  
  garraEsq_pos_3();
  delay(Espera_Posicionamento);  
}

  void garraEsq_fecha() //abre a garra esquerda
  {
    digitalWrite(rele1, LOW);
    digitalWrite(rele2, HIGH);
  }
  void garraDir_fecha() //abre a garra direita
  {
    digitalWrite(rele3, LOW);
    digitalWrite(rele4, HIGH);
  }
  void garraEsq_abre() //fecha a garra esquerda
  {
    digitalWrite(rele1, HIGH);
    digitalWrite(rele2, LOW);
  }
  void garraDir_abre() //fecha a garra direita
  {
    digitalWrite(rele3, HIGH);
    digitalWrite(rele4, LOW);
  }
  
  //PARA TODOS OS MOVIMENTOS DOS SERVOS:
  //PRIMEIRO ZERA AS POSIÇÕES INVALIDAS PARA DEPOIS SETAR A POSIÇÃO VALIDA
  void garraEsq_pos_1()
  {
    digitalWrite(esq2, LOW);
    digitalWrite(esq3, LOW);
    digitalWrite(esq4, LOW);
    digitalWrite(esq1, HIGH);
  }
  void garraEsq_pos_2()
  {
    digitalWrite(esq1, LOW);
    digitalWrite(esq3, LOW);
    digitalWrite(esq4, LOW);
    digitalWrite(esq2, HIGH);  
  }
  void garraEsq_pos_3()
  {
    digitalWrite(esq1, LOW);
    digitalWrite(esq2, LOW);
    digitalWrite(esq4, LOW);
    digitalWrite(esq3, HIGH);  
  }
  void garraEsq_pos_4()
  {
    digitalWrite(esq1, LOW);
    digitalWrite(esq2, LOW);
    digitalWrite(esq3, LOW);
    digitalWrite(esq4, HIGH);
  }
  void garraDir_pos_1()
  {
    digitalWrite(dir2, LOW);
    digitalWrite(dir3, LOW);
    digitalWrite(dir4, LOW);
    digitalWrite(dir1, HIGH);
  }
  void garraDir_pos_2()
  {
    digitalWrite(dir1, LOW);
    digitalWrite(dir3, LOW);
    digitalWrite(dir4, LOW);
    digitalWrite(dir2, HIGH);
  }
  void garraDir_pos_3()
  {
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, LOW);
    digitalWrite(dir4, LOW);
    digitalWrite(dir3, HIGH);
  }
  void garraDir_pos_4()
  {
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, LOW);
    digitalWrite(dir3, LOW);
    digitalWrite(dir4, HIGH);
  }
