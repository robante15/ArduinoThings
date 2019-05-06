/*Author:
     |*******************************************|
     |1.K.Rajesh,B.Tech IT.                      |
     |*******************************************|
   pin 6->Rx
   pin 7->Tx
*/
#include<SoftwareSerial.h>
SoftwareSerial myserial(6,7);//RX,TX
void setup()
{

Serial.begin(9600);
myserial.begin(9600);
}
void loop()
{
   if(myserial.available()){
       Serial.write(myserial.read());
   } 
   if(Serial.available())
       myserial.write(Serial.read());

}
