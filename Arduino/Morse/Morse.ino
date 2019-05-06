#include <Morse.h>

Morse morse(13);

void setup()
{
}

void loop()
{
  morse.dot(); morse.dot(); morse.dot(); // The letter S consists of three dots
  morse.dash(); morse.dash(); morse.dash(); // The letter O consists of three dashes
  morse.dot(); morse.dot(); morse.dot(); // The letter S consists of three dots
  delay(3000);
}
