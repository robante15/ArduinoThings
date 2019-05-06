int a = A0;
int b = A1;
int c = 2;
int d = 3;
int e = 4;
int f = 5;
int g = 6;
int s7 = 7;
int s6 = 8;
int s5 = 9;
int s4 = 10;
int s3 = 11;
int s2 = 12;
int s1 = 13;
int cont = 0;


void setup() {
    pinMode(a, OUTPUT); // Setea el PIN como salida
    pinMode(b, OUTPUT); 
    pinMode(c, OUTPUT); 
    pinMode(d, OUTPUT); 
    pinMode(e, OUTPUT); 
    pinMode(f, OUTPUT); 
    pinMode(g, OUTPUT); 
    pinMode(s1, INPUT);
    pinMode(s2, INPUT);
    pinMode(s3, INPUT);
    pinMode(s4, INPUT);
    pinMode(s5, INPUT);
    pinMode(s6, INPUT);
    pinMode(s7, INPUT);
}

void loop() {

    /*if(digitalRead(s1)){
      NumberDisplay(1);
    }else{
      limpiar();
    }

    if(digitalRead(s2)){
      NumberDisplay(2);
    }else{
      limpiar();
    }

    if(digitalRead(s3)){
      NumberDisplay(3);
    }else{
      limpiar();
    }

    if(digitalRead(s4)){
      NumberDisplay(4);
    }else{
      limpiar();
    }

    if(digitalRead(s5)){
      NumberDisplay(5);
    }else{
      limpiar();
    }

    if(digitalRead(s6)){
      NumberDisplay(6);
    }else{
      limpiar();
    }

    if(digitalRead(s7)){
      NumberDisplay(7);
    }else{
      limpiar();
    }*/
  
    if (cont <= 10){
      NumberDisplay(cont);
      cont++;
    }else{
      cont = 0;
    }

  delay(1000);
  limpiar();

}

void limpiar(){
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
}

void NumberDisplay(int number){
  switch(number){
    case 1:
    digitalWrite(c, HIGH);
    digitalWrite(b, HIGH);
    break;

    case 2:
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(g, HIGH);
    break;

    case 3:
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(g, HIGH);
    break;

    case 4:
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    break;

    case 5:
    digitalWrite(a, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    break;

    case 6:
    digitalWrite(a, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    break;

    case 7:
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    break;

    case 8:
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    break;

    case 9:
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    break;

    case 0:
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    break;
  }
}
