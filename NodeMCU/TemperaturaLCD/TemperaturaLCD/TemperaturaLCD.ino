#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include  <LiquidCrystal_I2C.h>

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int val;
int PinCLK = D5;
int PinDT = D6;
int PinSW = D7;
      
int Posicion = 0; 
int PinCLKanterior = LOW; 
int n = LOW;

// Muestra las características del sensor
void displaySensorDetails(void) {
  sensor_t sensor;
  bmp.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor: ");
  Serial.println(sensor.name);
  Serial.print  ("Driver: ");
  Serial.println(sensor.version);
  Serial.print  ("ID: ");
  Serial.println(sensor.sensor_id);
  Serial.print  ("Max Valor: ");
  Serial.print(sensor.max_value);
  Serial.println(" hPa");
  Serial.print  ("Min Valor: ");
  Serial.print(sensor.min_value);
  Serial.println(" hPa");
  Serial.print  ("Resolucion: ");
  Serial.print(sensor.resolution);
  Serial.println(" hPa");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(1000);
}

void setup() {
  Serial.begin(9600);
  //Inicialización de los pines para el encoder rotatorio
  pinMode (PinCLK,INPUT); 
  pinMode (PinDT, INPUT);
  pinMode (PinSW, INPUT);

  //Inicialización del LCD
  lcd.begin(16, 2);
  lcd.home ();
  
  lcd.print("Test Presion");
  Serial.println("\nPrueba del sensor de presión");
  Serial.println("");
  if (!bmp.begin()) { // Initicializa el sensor
    // Error en la detección del sensor
    lcd.setCursor ( 0, 1 );
    // Imprimir otra cadena en esta posicion
    lcd.print("Error BMP180");
    Serial.print("Ooops, BMP085 no detectado ... Comprueba las conexiones!");
    while (1); // Bucle infinito
  }
  displaySensorDetails();

}

void loop(void) {
  
  sensors_event_t event;
  bmp.getEvent(&event);

  if (event.pressure) {
    // Obtenemos la temperatura
    float temperature;
    bmp.getTemperature(&temperature);
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" C");
    lcd.clear();
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print("C");
  }
  else {
    Serial.println("Error en el sensor");
  }

  n = digitalRead(PinCLK); 
      if ((PinCLKanterior == LOW) && (n == HIGH)) { 
      if (digitalRead(PinDT) == LOW) {Posicion--;} 
      else {Posicion++;} 
      lcd.setCursor ( 0, 1 );
  lcd.print(Posicion);
      Serial.println (Posicion);
    } 
      PinCLKanterior = n;
    if ((digitalRead(PinSW) == LOW)) {Posicion = 0; }
    delay(350);

}
