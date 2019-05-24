#include <Wire.h>                 //Maneja el I2C
#include <LiquidCrystal_I2C.h>    //Maneja el LCD

#define trigPin 11
#define echoPin 9
#define button1 2
#define button2 4

float tiempo;
int state;
String receivedString;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup(){
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);

  //Inicializar la pantalla
  lcd.begin(16, 2);
  lcd.home ();
  lcd.print("Ultrasonic");
  delay(750);
  lcd.clear();
}

void loop(){

  if(Serial.available()>0){
    receivedString = Serial.readStringUntil('\n');
  }
   
  if(receivedString.equals("dist") || receivedString.equals("DIST") || digitalRead(button1) == HIGH){
    float distancia = medirDistancia();
    Serial.print(distancia);
    imprimirDistancia(distancia);
    Serial.print("\n");
    receivedString = "";
    delay(200);
   }

   if(receivedString.equals("prom") || receivedString.equals("PROM") || digitalRead(button2) == HIGH){
   float distancia = 0;
   float distancias = 0;
   float promedio = 0;

    for(int i = 0; i < 10; i++){
      distancia = medirDistancia();
      distancias = distancias + distancia;
      imprimirDistanciaPromedio(i, distancia);
      delay(200);
    }

   promedio = distancias/10;
   Serial.print(promedio);
   imprimirDistancia(promedio);
   Serial.print("\n");
   promedio = 0;
   distancias = 0;
   distancia = 0;
   receivedString = "";
   }
}

void imprimirDistancia(float dist){
  lcd.clear();
  lcd.print("Distancia:");
  lcd.setCursor(0, 1);
  lcd.print(dist);
  lcd.print("cm");
}

void imprimirDistanciaPromedio(int iterador, float dist){
  lcd.clear();
  lcd.print("Promedio: ");
  lcd.print(iterador+1);
  lcd.setCursor(0, 1);
  lcd.print(dist);
  lcd.print("cm");
}

float medirDistancia(){
    float distancia;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    tiempo = pulseIn(echoPin, HIGH);
    distancia = tiempo * 0.034 / 2;
    return distancia;
}
