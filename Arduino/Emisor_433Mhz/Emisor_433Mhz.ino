#include <VirtualWire.h>
 
const int dataPin = 9;
 
void setup()
{
    Serial.begin(9600);     
    vw_setup(2000);
    vw_set_tx_pin(dataPin);
}
 
void loop()
{
    
      char data[1];
      data[0] = 'a';
      vw_send((uint8_t*)data,sizeof(data));
      vw_wait_tx();         
   
    delay(200);
}
