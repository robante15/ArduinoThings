//https://programarfacil.com/tutoriales/fragmentos/servomotor-con-arduino/

// Incluímos la librería para poder controlar el servo
#include <Servo.h>
#include <Wire.h> 
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x3F,16,2);
Servo servoMotor;

void setup() {

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  servoMotor.attach(5);
}

void loop() {
  
  // Desplazamos a la posición 0º
  servoMotor.write(0);
  // Esperamos 1 segundo
  delay(1000);
  
  // Desplazamos a la posición 90º
  servoMotor.write(90);
  // Esperamos 1 segundo
  delay(1000);
  
  // Desplazamos a la posición 180º
  servoMotor.write(180);
  // Esperamos 1 segundo
  delay(1000);
}
