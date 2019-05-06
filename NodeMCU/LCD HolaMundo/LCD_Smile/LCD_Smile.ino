 /*  GeekFactory - "Construye tu propia tecnologia"
   Distribucion de materiales para el desarrollo e innovacion tecnologica
   www.geekfactory.mx
 
   EJEMPLO BÁSICO PARA EL USO DEL LCD 16X2 A TRAVÉS DE I2C
 
   ESTE EJEMPLO MUESTRA COMO IMPRIMIR EL VALOR DE UNA VARIABLE HACIA LA
/*   PANTALLA LCD A TRAVÉS DE I2C. ESTO PUEDE SER UTIL PARA VISUALIZAR EL
   VALOR LEIDO POR UN SENSOR, MOSTRAR UN CONTADOR, ETC.
*/
#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
 
// Constructor de la librería de LCD 16x2
// Aqui se configuran los pines asignados a la pantalla del PCF8574
// Este constructor es para usar con el modulo I2C que se muestra en las
// fotografias de nuestro sitio web. Para otros modelos, puede ser necesario
// cambiar los valores de acuerdo al esquemático del adaptador I2C. Los pines
// del arduino SIEMPRE son los correspondientes al I2C (SDA y SCL)
 
// Constructor sin control de backlight (retroiluminacion)
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);
// Constructor con control de backlignt (retroiluminacion)
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
 
//Definicion de caracteres personalizados
byte smile[8] = {
  0b00000000,
  0b00001010,
  0b00001010,
  0b00001010,
  0b00000000,
  0b00010001,
  0b00001110,
  0b00000000,
};
 
byte sad[8] = {
  0b00000000,
  0b00001010,
  0b00001010,
  0b00001010,
  0b00000000,
  0b00001110,
  0b00010001,
  0b00000000,
};
 
byte body[8] = {
  0b00001110,
  0b00001110,
  0b00000100,
  0b00011111,
  0b00000100,
  0b00001010,
  0b00010001,
  0b00000000,
};
 
byte arrowr[8] = {
  0b00001000,
  0b00000100,
  0b00000010,
  0b00011111,
  0b00000010,
  0b00000100,
  0b00001000,
  0b00000000,
};
 
byte arrowu[8] = {
  0b00000100,
  0b00001110,
  0b00010101,
  0b00000100,
  0b00000100,
  0b00000100,
  0b00000100,
  0b00000000,
};
 
byte arrowd[8] = {
  0b00000100,
  0b00000100,
  0b00000100,
  0b00000100,
  0b00010101,
  0b00001110,
  0b00000100,
  0b00000000,
};
 
byte arrowl[8] = {
  0b00000010,
  0b00000100,
  0b00001000,
  0b00011111,
  0b00001000,
  0b00000100,
  0b00000010,
  0b00000000,
};
 
 
void setup()
{
  // Indicar a la libreria que tenemos conectada una pantalla de 16x2
  lcd.begin(16, 2);
  
  // Crear los caracteres personalizados en la pantalla
  lcd.createChar (0, smile);
  lcd.createChar (1, sad);
  lcd.createChar (2, body);
  lcd.createChar (3, arrowr);
  lcd.createChar (4, arrowu);
  lcd.createChar (5, arrowd);
  lcd.createChar (6, arrowl);
  
  // Mover el cursor a la primera posición de la pantalla (0, 0)
  lcd.clear();
  // Imprimir "Hola Mundo" en la primera linea
  lcd.print(" GEEKFACTORY.MX ");
  // Mover cursor
  lcd.setCursor(0, 1);
  // Escribir bytes a la pantalla
  // Los códigos del 0 al 7 corresponden a los caracteres personalizados
  lcd.write((byte)0);
  lcd.write((byte)1);
  lcd.write((byte)2);
  lcd.write((byte)3);
  lcd.write((byte)4);
  lcd.write((byte)5);
  lcd.write((byte)6);
}
 
void loop()
{
 
}
