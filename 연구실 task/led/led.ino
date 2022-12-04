int Red = 9;
int Green = 10;
int Blue = 11;

void setup ()
{
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);
  
}

void loop()
{

digitalWrite(Red,HIGH);
delay(5000);
digitalWrite(Red, LOW);
delay(5000);

digitalWrite(Green, LOW);
delay(5000);
digitalWrite(Green, HIGH);
delay(5000);

digitalWrite(Blue, HIGH);
delay(5000);
digitalWrite(Blue, LOW);
delay(5000);
}
