//https://circuits4you.com/2017/12/09/thingspeak-esp8266/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

/* Set these to your desired credentials. */
const char *ssid = "robante_guest";
const char *password = "680c777656";

/*Parametros de configuración del DHT*/
#define DHTPIN D6     //El pin al cual está conectado el Sensor DTH
#define DHTTYPE DHT11 //El tipo de Sensor que estoy utilizando
DHT dht(DHTPIN, DHTTYPE);

//Declaración de las variables usadas para medir la temperatura y humedad
float humedad;
float temperaturaC;
float temperaturaF;
float SenTerF;
float SenTerC;

//Web address to read from
const char *host = "api.thingspeak.com";
String apiKey = "DL76KLL2YGL86P8T";  //ENTER YOUR API KEY <<<<<<<<<<<
//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  delay(1000);
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  //WiFi.mode(WIFI_AP_STA);   //Both hotspot and client are enabled
  //WiFi.mode(WIFI_AP);       //Only Access point

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
  Serial.println("Testeando DHT11!");
  dht.begin();
}

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {

  /* Codigo que realiza los analisis en el sensor DHT*/
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


  WiFiClient client;
  const int httpPort = 80; //Port 80 is commonly used for www
  //---------------------------------------------------------------------
  //Connect to host, host(web site) is define at top
  if (!client.connect(host, httpPort)) {
    Serial.println("Conexion Fallida");
    delay(300);
    return; //Keep retrying until we get connected
  }

  //---------------------------------------------------------------------
  //Make GET request as pet HTTP GET Protocol format
  String HumedadData;
  HumedadData = String(humedad);   //String to interger conversion

  String TempCData;
  TempCData = String(temperaturaC);   //String to interger conversion

  String TempFData;
  TempFData = String(temperaturaF);   //String to interger conversion

  String SenTerCData;
  SenTerCData = String(SenTerC);   //String to interger conversion

  String SenTerFData;
  SenTerFData = String(SenTerF);   //String to interger conversion

  String Link = "GET /update?api_key=" + apiKey + "&field1="; //Requeste webpage
  Link = Link + HumedadData + "&field2=";
  Link = Link + TempCData + "&field3=";
  Link = Link + TempFData + "&field4=";
  Link = Link + SenTerCData + "&field5=";
  Link = Link + SenTerFData;
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
//=======================================================================
