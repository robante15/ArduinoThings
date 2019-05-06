
// Read Quadrature Encoder 
// Sketch by max wolf / www.meso.net
// Modificado por Juan A. Villalpando
// kio4.com 
      int val;
      int PinCLK = 3; 
      int PinDT = 4; 
      int PinSW = 8;
      
      int Posicion = 0; 
      int PinCLKanterior = LOW; 
      int n = LOW;
       
      void setup() { 
      pinMode (PinCLK,INPUT); 
      pinMode (PinDT, INPUT);
      pinMode (PinSW, INPUT);
      Serial.begin (9600);
      } 
      
void loop() { 
      n = digitalRead(PinCLK); 
      if ((PinCLKanterior == LOW) && (n == HIGH)) { 
      if (digitalRead(PinDT) == LOW) {Posicion--;} 
      else {Posicion++;} 
      
      Serial.println (Posicion);
} 
      PinCLKanterior = n;
if ((digitalRead(PinSW) == LOW)) {Posicion = 0; }
}
