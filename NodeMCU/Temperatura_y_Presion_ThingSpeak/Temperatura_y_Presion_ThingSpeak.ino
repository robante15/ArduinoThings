#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include "DHT.h"

/* Credenciales para la conexión con la red WiFi */
const char *ssid = "robante_guest";
const char *password = "680c777656";

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

//Parametros para el acceso web a ThingSpeak
const char *host = "api.thingspeak.com";
String apiKey = "DL76KLL2YGL86P8T";  //ENTER YOUR API KEY <<<<<<<<<<<


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

void SendToThingSpeak(WiFiClient client, String TSpresion, String TStemp1, String TSalt, String TSst1, String TShumedad, String TStemp2, String TSst2) {

  String Link = "GET /update?api_key=" + apiKey + "&field1="; //Requeste webpage
  Link = Link + TSpresion + "&field2=";
  Link = Link + TStemp1 + "&field3=";
  Link = Link + TSalt + "&field4=";
  Link = Link + TSst1 + "&field5=";
  Link = Link + TShumedad + "&field6=";
  Link = Link + TStemp2 + "&field7=";
  Link = Link + TSst2;
  Link = Link + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n";

  Serial.println("Link de request: " + Link);

  client.print(Link);

  delay(1000);

  //---------------------------------------------------------------------
  //Wait for server to respond with timeout of 5 Seconds
  int timeout = 0;
  while ((!client.available()) && (timeout < 1000))    //Wait 5 seconds for data
  {
    delay(10);  //Use this with time out
    timeout++;
  }

  //---------------------------------------------------------------------
  //If data is available before time out read it.
  if (timeout < 500)
  {
    while (client.available()) {
      Serial.println(client.readString()); //Response from ThingSpeak
    }
  }
  else
  {
    Serial.println("Request timeout..");
  }

  delay(5000);  //Read Web Page every 5 seconds
}

void setup(void) {
  Serial.begin(115200);

  /*---------------Configuración de la parte WiFi---------------------*/
  Serial.println("\nIniciando NodeMCU como Cliente WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Conectando...");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Conectado a");
  Serial.println(ssid);
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

  /*--------------------------Inicialización de los sensores--------------------------*/

  Serial.println("Testeando DHT11!");
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
    Serial.println(DHT_humedad);
    Serial.println(DHT_temperatura);
    delay(500);
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

  WiFiClient client;
  const int httpPort = 80; //Port 80 is commonly used for www
  //---------------------------------------------------------------------
  //Connect to host, host(web site) is define at top
  if (!client.connect(host, httpPort)) {
    Serial.println("Conexion Fallida");
    delay(300);
    return; //Keep retrying until we get connected
  }

  SendToThingSpeak(client, String(BMP_presion), String(BMP_temperatura), String(BMP_altitud), String(BMP_SenTer), String(DHT_humedad), String(DHT_temperatura), String(DHT_SenTer));

  delay(49000); // Muestras cada 20 seg.
}
