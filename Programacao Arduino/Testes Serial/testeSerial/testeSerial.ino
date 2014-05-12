char newChar, deletedChar;
String buffer;

void setup()
{
  Serial.begin (9600);
}

void loop()
{
  Serial.println(buffer);
  Serial.println(deletedChar);
  
  if ( Serial.available() )
    {
      newChar = Serial.read();
     if (newChar == 'a') //backspace
      {
        deletedChar = buffer.charAt(0);
        buffer = buffer.substring(1,buffer.length());
        
      }
      else
        buffer += newChar;
     
    }
}
