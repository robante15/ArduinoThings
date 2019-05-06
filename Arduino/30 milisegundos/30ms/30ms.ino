int ledPin = 13;                 // LED connected to digital pin 13
int min = 20;
int max = 90;

void setup()
{
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
}

void loop()
{
  digitalWrite(ledPin, HIGH);   // sets the LED on
  delay(random(min, max));                  // waits for a second
  digitalWrite(ledPin, LOW);    // sets the LED off
  delay(random(min, max));                  // waits for a second
}
