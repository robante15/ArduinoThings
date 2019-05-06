ale // Incluímos la librería para poder controlar el servo
#include <Servo.h>
#include <ESP8266WiFi.h>

const char* ssid = "robante_guest";
const char* password = "680c777656";
WiFiServer server(80);

int val;
int PinCLK = D0;
int PinDT = D3;
int PinSW = D2;

int Posicion = 0;
int PinCLKanterior = LOW;
int n = LOW;

// Declaramos la variable para controlar el servo
Servo servoMotor;

void setup() {
  // Iniciamos el monitor serie para mostrar el resultado
  Serial.begin(115200);
  pinMode (PinCLK, INPUT);
  pinMode (PinDT, INPUT);
  pinMode (PinSW, INPUT);

  // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(D4);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Conectado");

  // Start the server
  server.begin();
  Serial.println("Servidor iniciado");

  // Print the IP address
  Serial.print("Usa esta URL para conectarte: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
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
    Serial.println(Posicion);
  }

  PinCLKanterior = n;
  if ((digitalRead(PinSW) == LOW)) {
    Posicion = 0;
    servoMotor.write(Posicion);
  }

  // Desplazamos a la posición 0º

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("Nuevo cliente");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request

  int value = 0;
  if (request.indexOf("/SERVO=0") != -1)  {
    //Serial.println(request.);
    servoMotor.write(0);
    value = 0;
  }
  if (request.indexOf("/SERVO=45") != -1)  {
    servoMotor.write(45);
    value = 45;
  }
  if (request.indexOf("/SERVO=90") != -1)  {
    servoMotor.write(90);
    value = 90;
  }
  if (request.indexOf("/SERVO=135") != -1)  {
    servoMotor.write(135);
    value = 135;
  }
  if (request.indexOf("/SERVO=180") != -1)  {
    servoMotor.write(180);
    value = 180;
  }
  

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("El servo ahorita esta en: ");

  client.print(value);
  client.println("<br><br>");
  client.println("<a href=\"/SERVO=0\"\"><button>0 Grados</button></a>");
  client.println("<a href=\"/SERVO=45\"\"><button>45 Grados </button></a><br />");
  client.println("<a href=\"/SERVO=90\"\"><button>90 Grados </button></a><br />");
  client.println("<a href=\"/SERVO=135\"\"><button>135 Grados </button></a><br />");
  client.println("<a href=\"/SERVO=180\"\"><button>180 Grados </button></a><br />");
  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");



}

void ObtenerIPExterna()
{
  WiFiClient client;
  if (!client.connect("api.ipify.org", 80)) {
    Serial.println("Failed to connect with 'api.ipify.org' !");
  }
  else {
    int timeout = millis() + 5000;
    client.print("GET /?format=json HTTP/1.1\r\nHost: api.ipify.org\r\n\r\n");
    while (client.available() == 0) {
      if (timeout - millis() < 0) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
    int size;
    while ((size = client.available()) > 0) {
      uint8_t* msg = (uint8_t*)malloc(size);
      size = client.read(msg, size);
      Serial.write(msg, size);
      free(msg);
    }
  }
}
