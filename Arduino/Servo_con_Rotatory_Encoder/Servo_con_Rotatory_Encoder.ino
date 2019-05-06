// Incluímos la librería para poder controlar el servo
#include <Servo.h>

int val;
int PinCLK = 3;
int PinDT = 4;
int PinSW = 8;

int Posicion = 0;
int PinCLKanterior = LOW;
int n = LOW;

// Declaramos la variable para controlar el servo
Servo servoMotor;

void setup() {
  // Iniciamos el monitor serie para mostrar el resultado
  Serial.begin(9600);
  pinMode (PinCLK, INPUT);
  pinMode (PinDT, INPUT);
  pinMode (PinSW, INPUT);

  // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(9);
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
    Posicion = 0;
    servoMotor.write(Posicion);
  }

  // Desplazamos a la posición 0º

}
