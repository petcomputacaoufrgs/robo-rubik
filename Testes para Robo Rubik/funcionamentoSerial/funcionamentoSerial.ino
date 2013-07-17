/*Conclusão:
Quando são escritos um pacote de bytes na Serial, esta os guarda em algum buffer e lê ordenadamente.
*/

char valor1='a', valor2='b', valor3='c';
int aux1,aux2,aux3;

void setup ()
{
  Serial.begin (9600);
}

void loop ()
{
   Serial.write(valor1);
   Serial.write(valor2);
   Serial.write(valor3);
  if (Serial.available())
    {
      aux1 = Serial.read();
      aux2 = Serial.read();
      aux3 = Serial.read();
      Serial.println(aux1);      
      Serial.println(aux2);     
      Serial.println(aux3);      
  }
}

