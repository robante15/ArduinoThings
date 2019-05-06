#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include "DHT.h"

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

/*Parametros de configuración del DHT*/
#define DHTPIN D6     //El pin al cual está conectado el Sensor DTH
#define DHTTYPE DHT11 //El tipo de Sensor que estoy utilizando
DHT dht(DHTPIN, DHTTYPE);

//Declaración de las variables usadas para medir la temperatura y humedad
float DHT_humedad;
float DHT_temperatura;
float DHT_SenTer;
float BMP_presion;
float BMP_altitud;
float BMP_temperatura;
float BMP_SenTer;

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

void setup(void) {
  Serial.begin(9600);

  Serial.println("\nPrueba del sensor de presión");
  Serial.println("");
  if (!bmp.begin()) { // Initicializa el sensor
    // Error en la detección del sensor
    Serial.print("Ooops, BMP085 no detectado ... Comprueba las conexiones!");
    while (1); // Bucle infinito
  }
  displaySensorDetails();

  Serial.println("DHT11 test!");
  dht.begin();

}

void loop(void) {

  /* Codigo que realiza los analisis en el sensor DHT*/
  DHT_humedad = dht.readHumidity();              //Lee el porcentaje de humedad en el aire
  DHT_temperatura = dht.readTemperature();      // Lee la temperatura en Centigrados (Por defecto)

  // Chequea si no ha habido un error y vuelve a comprobar
  if (isnan(DHT_humedad) || isnan(DHT_temperatura)) {
    Serial.println("Error de lectura desde el sensor DHT!");
    return;
  }

  DHT_SenTer = dht.computeHeatIndex(DHT_temperatura, DHT_humedad, false);   // Calcula la sensación termica en Centigrados (isFahreheit = false)

  // Obtiene un nuevo evento del sensor de presión BMP180
  sensors_event_t event;
  bmp.getEvent(&event);

  // Muestra los resultados
  if (event.pressure) {
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    BMP_presion = event.pressure;
    BMP_altitud = bmp.pressureToAltitude(seaLevelPressure, BMP_presion);
    bmp.getTemperature(&BMP_temperatura);
    BMP_SenTer = dht.computeHeatIndex(BMP_temperatura, DHT_humedad, false);

    // Muestra la presión atmosférica en hPa (BMP180)
    Serial.print("BMP Presion: ");
    Serial.print(BMP_presion);
    Serial.println(" hPa");
    
    // Obtenemos la temperatura (BMP180)  
    Serial.print("BMP Temperatura: ");
    Serial.print(BMP_temperatura);
    Serial.println("°C");
    
    // Cálculo de la altura (BMP180)
    Serial.print("BMP Altitud: ");
    Serial.print(BMP_altitud);
    Serial.println(" m");
    
    // Calculo de la sensación termica (BMP180)
    Serial.print("BMP Sensacion Termica: ");
    Serial.print(BMP_SenTer);
    Serial.println("°C");

    
    /*------------------DHT11------------------*/
    // Muesta la humedad porcentual (DHT11)
    Serial.print("DHT Humedad: ");
    Serial.print(DHT_humedad);
    Serial.println("%");
    // Obtenemos la temperatura (DHT11)
    Serial.print("DHT Temperatura: ");
    Serial.print(DHT_temperatura);
    Serial.println("°C");
    // Calculo de la sensación termica (DHT11)
    Serial.print("DHT Sensacion Termica: ");
    Serial.print(DHT_SenTer);
    Serial.println("°C");
    Serial.println("");
    Serial.println("");

  }
  else {
    Serial.println("Error en el sensor");
  }

  delay(20000); // Muestras cada 20 seg.
}
