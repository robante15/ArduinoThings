#include <Encoder.h>
#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
#include <OneButton.h>

 
// Constructor de la librería de LCD 16x2
// Aqui se configuran los pines asignados a la pantalla del PCF8574
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
long newLeft;
int buttonPin = D7;
OneButton button0(buttonPin, true);

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability

Encoder knobLeft(D5, D6);
//   avoid using pins with LEDs attached

void setup() {
  button0.attachClick(singleClick);
  //button0.attachDoubleClick(doubleClick);
  Serial.begin(9600);
  Serial.println("TwoKnobs Encoder Test:");
  lcd.begin(16, 2);
  // Mover el cursor a la primera posición de la pantalla (0, 0)
  lcd.home ();
  lcd.print("Init SYS");
  delay(2000);
}

long positionLeft  = -999;

void imprimirEncoder(long numero){
  lcd.clear();
  lcd.home();
  lcd.print(numero);
}

void singleClick(){
  newLeft = 0;
  lcd.print("Click");
}

void loop() {
  button0.tick();
  newLeft = knobLeft.read();
  if (newLeft != positionLeft) {
    Serial.print("Left = ");
    Serial.print(newLeft);
    imprimirEncoder(newLeft);
    Serial.println();
    positionLeft = newLeft;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    knobLeft.write(0);
  }
}
