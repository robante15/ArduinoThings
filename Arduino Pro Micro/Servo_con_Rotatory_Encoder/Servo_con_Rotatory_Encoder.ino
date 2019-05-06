// Incluímos la librería para poder controlar el servo
#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
#include <Servo.h>


LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int val;
int PinCLK = 4;
int PinDT = 6;
int PinSW = 9;

int Posicion = 75;
int PinCLKanterior = LOW;
int n = LOW;

// Declaramos la variable para controlar el servo
Servo servoMotor;
  //

void setup() {
  // Iniciamos el monitor serie para mostrar el resultado
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print(" Control de Servo ");
  delay(1000);
  Serial.begin(9600);
  pinMode (PinCLK, INPUT);
  pinMode (PinDT, INPUT);
  pinMode (PinSW, INPUT);

  // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(5);
}

void loop() {

  n = digitalRead(PinCLK);
  if ((PinCLKanterior == LOW) && (n == HIGH)) {
    if (digitalRead(PinDT) == LOW) {
      Posicion -= 5;
    }
    else {
      Posicion += 5;
    }

    servoMotor.write(Posicion);
    Serial.println (Posicion);
  }
  PinCLKanterior = n;
  if ((digitalRead(PinSW) == LOW)) {
    Posicion = 75;
Serial.println (Posicion);
    servoMotor.write(Posicion);
  }

  // Desplazamos a la posición 0º
}
