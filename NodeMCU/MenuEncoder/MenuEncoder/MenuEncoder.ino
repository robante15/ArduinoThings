#include <Encoder.h>              //Maneja el encoder
#include <Wire.h>                 //Maneja el I2C
#include <LiquidCrystal_I2C.h>    //Maneja el LCD
#include <OneButton.h>            //Maneja el boton
#include <Adafruit_Sensor.h>      //Maneja el sensor
#include <Adafruit_BMP085_U.h>    //Maneja el sensor BMP

//Creación de variables
long rotacion = 0;
long rotacionAnterior  = -999;
float temperatura;
float temperaturaAnterior = -999;

//Inicializar Dispositivos
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
Adafruit_BMP085_Unified BMP180 = Adafruit_BMP085_Unified(10085);

//Definición de los IO
int BotonRotary = D7;                 //SW del Rotary Encoder al pin D7
Encoder Rotador(D5, D6);              //Inicializando el EncoderRotatorio en los pines D5 y D6

//Inicializar boton
OneButton Boton0(BotonRotary, true);  //Se inicializa el boton de la librería, y se le pasa el valor

void setup() {
  Boton0.attachClick(singleClick);    //Se indica la función que va a ejecutar cuando haya un solo click
  
  //Inicializar la pantalla
  lcd.begin(16, 2);
  lcd.home ();
  lcd.print("AC System");
  delay(750);

  //Comprobando el estado del BMP180
  lcd.clear();
  lcd.print("--Test BMP180--");
  if (!BMP180.begin()) {
        lcd.setCursor(0, 1);
        lcd.print("Error BMP180");
        while (1);
    }else{
      lcd.setCursor(0, 1);
      lcd.print("BMP180 OK");
      delay(750);
    }
    lcd.clear();
}

void singleClick(){
  Rotador.write(0);
  rotacion = 0;
  lcd.clear();
  lcd.home();
  lcd.print(temperatura);
  lcd.setCursor(0, 1);
  lcd.print(rotacion);
}

void medirTemperatura(){
        BMP180.getTemperature(&temperatura);
        if(temperatura != temperaturaAnterior){
          lcd.home();
          lcd.print(temperatura);
          temperaturaAnterior = temperatura;
        }
}

void imprimirEncoder(long numero){
  lcd.clear();
  lcd.print(temperatura);
  lcd.setCursor(0, 1);
  lcd.print(numero);
}

void loop() {
  //Espera a un evento del BMP180
  sensors_event_t event;
  BMP180.getEvent(&event);
  if (event.pressure) {
    medirTemperatura();
  }else{
    lcd.print("Error BMP180");
  }

  
  Boton0.tick();                //Está a la espera de un evento en el boton
  rotacion = Rotador.read();    
  if (rotacion != rotacionAnterior) {
    imprimirEncoder(rotacion);
    rotacionAnterior = rotacion;
  }
  
}
