#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

// Replace with your network credentials
const char* ssid = "robante_guest";
const char* password = "680c777656";

#define DHTPIN D6     //El pin al cual está conectado el Sensor DTH
#define DHTTYPE DHT11 //El tipo de Sensor que estoy utilizando

DHT dht(DHTPIN, DHTTYPE);
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";

//Declaración de las variables usadas para medir la temperatura y humedad
float humedad;
float temperaturaC;
float temperaturaF;
float SenTerF;
float SenTerC;

void setup(void) {

  delay(1000);
  Serial.begin(115200);
  Serial.println("DHTxx test!");
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", []() {
    page = "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n    <meta charset=\"UTF-8\">\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n    <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">\n    <title>Temperatura y Humedad</title>\n    <link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css\">\n</head>\n<body>\n    <h1>Sensor de Temperatura y Humedad con NodeMCU, HTML5 y Bootstrap 4</h1>\n    <p>\n        <h4>Humedad: </h4> "+ String(humedad) + "%\n        <h4>Temperatura: </h4> "+ String(temperaturaC) + "°C\n "+ String(temperaturaF) + "°F\n       <h4>Sensación Termica: </h4> "+ String(SenTerC) + "°C\n "+ SenTerF +"°F\n    </p>\n</body>\n</html>";
    server.send(200, "text/html", page);
  });

  dht.begin();
  server.begin();
  Serial.println("Web server started!");
}

void loop(void) {

  humedad = dht.readHumidity();              //Lee el porcentaje de humedad en el aire
  temperaturaC = dht.readTemperature();      // Lee la temperatura en Centigrados (Por defecto)
  temperaturaF = dht.readTemperature(true);  // Lee la temperatura en Fahrenheit (isFahrenheit = true)

  // Chequea si no ha habido un error y vuelve a comprobar
  if (isnan(humedad) || isnan(temperaturaC) || isnan(temperaturaF)) {
    Serial.println("Error de lectura desde el sensor DHT!");
    return;
  }

  SenTerF = dht.computeHeatIndex(temperaturaF, humedad);          // Calcula la sensación termica en Fahrenheit (Por defecto)
  SenTerC = dht.computeHeatIndex(temperaturaC, humedad, false);   // Calcula la sensación termica en Centigrados (isFahreheit = false)

  delay(1000);
  server.handleClient();
}
