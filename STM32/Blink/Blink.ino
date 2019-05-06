//const int ledPIN = PB1;  //esto es lo que viene en el ejemplo pero no funciona
const int ledPIN = PC13;  // depende de cada placa
 
void setup()
{
  pinMode(ledPIN, OUTPUT);
}
 
void loop()
{
  digitalWrite(ledPIN, HIGH);
  delay(1000);
  digitalWrite(ledPIN, LOW);
  delay(1000);
}
