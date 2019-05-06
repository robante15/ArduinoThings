int lento = 7;
int medio = 6;
int rapido = 5;
int pulso = 13;
int time = 1000;

void setup()
{

    pinMode(pulso, OUTPUT);
    pinMode(lento, INPUT);
    pinMode(medio, INPUT);
    pinMode(rapido, INPUT);
}

void loop()
{
    if(digitalRead(lento) == 1){
        time = 500;
    }

    if(digitalRead(medio) == 1){
        time = 150;
    }

    if(digitalRead(rapido) == 1){
        time = 50;
    }

    digitalWrite(pulso, HIGH);
    delay(time);
    digitalWrite(pulso, LOW);
    delay(time);
}
