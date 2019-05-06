/* 
 Ejemplo de control de motor DC usando modulo L298
 http://electronilab.co/tienda/driver-dual-para-motores-full-bridge-l298n/
 
 El programa activa el motor en un sentido por 4 segundos, 
 para el motor por 500 ms, activa el motor en sentido inverso por 4 segundos 
 y se detiene por 5 segundos. Luego repite la acción indefinidamente.
 
 Creado 16/05/14
 por Andres Cruz
 ELECTRONILAB.CO
 */

int IN3 = 5; 
int IN4 = 4;

void setup()
{
  pinMode (IN4, OUTPUT);    // Input4 conectada al pin 4 
  pinMode (IN3, OUTPUT);    // Input3 conectada al pin 5
}
void loop()
{
  // Motor gira en un sentido
  digitalWrite (IN4, HIGH);
  digitalWrite (IN3, LOW); 
  delay(100);
  // Motor no gira
  digitalWrite (IN4, LOW); 
  delay(500);
  // Motor gira en sentido inverso
  digitalWrite (IN3, HIGH);
  delay(100);
  // Motor no gira
  digitalWrite (IN3, LOW); 
  delay(1000);
}
