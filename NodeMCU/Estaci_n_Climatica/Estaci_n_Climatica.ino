//Comments for each line is given in the .ino file below

#include <Adafruit_Sensor.h>
#define BLYNK_PRINT Serial
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
#define I2C_SCL D1
#define I2C_SDA D2

float dst,bt,bp,ba;
char dstmp[20],btmp[20],bprs[20],balt[20];
bool bmp085_present=true;

char auth[]="Put your Authication key from the Blynk app here";
char ssid[] = "Your WiFi SSID";
char pass[] = "Your Password";
#define DHTPIN D6
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); //Defining the pin and the dhttype
BlynkTimer timer;
void sendSensor()
{

  if (!bmp.begin()) 
  {
           Serial.println("Could not find a valid BMP085 sensor, check wiring!");
              while (1) {}
        }

float h = dht.readHumidity();
float t = dht.readTemperature();
  

  if (isnan(h) || isnan(t))
  {
  Serial.println("Failed to read from DHT sensor!");
  return;
  }

  double gamma = log(h/100) + ((17.62*t) / (243.5+t));
  double dp = 243.5*gamma / (17.62-gamma);

float bp =  bmp.readPressure()/100;
float ba =  bmp.readAltitude();
float bt =  bmp.readTemperature();
float dst = bmp.readSealevelPressure()/100;

Blynk.virtualWrite(V5 , h);
Blynk.virtualWrite(V6 , t);
Blynk.virtualWrite(V10, bp);
Blynk.virtualWrite(V11, ba);
Blynk.virtualWrite(V12, bt);
Blynk.virtualWrite(V13, dst);
Blynk.virtualWrite(V14, dp);


}


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  Wire.begin(I2C_SDA, I2C_SCL);
  delay(10);
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
