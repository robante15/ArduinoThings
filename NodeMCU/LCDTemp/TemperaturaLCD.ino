#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include  <LiquidCrystal_I2C.h>

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Muestra las características del sensor
void displaySensorDetails(void) {
    sensor_t sensor;
    bmp.getSensor(&sensor);
    Serial.println("------------------------------------");
    Serial.print("Sensor: ");
    Serial.println(sensor.name);
    Serial.print("Driver: ");
    Serial.println(sensor.version);
    Serial.print("ID: ");
    Serial.println(sensor.sensor_id);
    Serial.print("Max Valor: ");
    Serial.print(sensor.max_value);
    Serial.println(" hPa");
    Serial.print("Min Valor: ");
    Serial.print(sensor.min_value);
    Serial.println(" hPa");
    Serial.print("Resolucion: ");
    Serial.print(sensor.resolution);
    Serial.println(" hPa");
    Serial.println("------------------------------------");
    Serial.println("");
    delay(1000);
}

void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.home();
    lcd.print("Test Presion");
    Serial.println("\nPrueba del sensor de presión");
    Serial.println("");
    if (!bmp.begin()) { // Initicializa el sensor
        // Error en la detección del sensor
        lcd.setCursor(0, 1);
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
        // Muestra la presión atmosférica en hPa
        Serial.print("Presion: ");
        Serial.print(event.pressure);
        Serial.println(" hPa");
        // Obtenemos la temperatura
        float temperature;
        bmp.getTemperature(&temperature);
        Serial.print("Temperatura: ");
        Serial.print(temperature);
        Serial.println(" C");
        // Cálculo de la altura
        float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
        Serial.print("Altitud: ");
        Serial.print(bmp.pressureToAltitude(seaLevelPressure, event.pressure));
        Serial.println(" m");
        Serial.println("");
    } else {
        Serial.println("Error en el sensor");
    }
    delay(20000); // Muestras cada 20 seg.

}
