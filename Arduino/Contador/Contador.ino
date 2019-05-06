int CLK = 2; // Pin en el que entra la señal del CLOCK
int Timems = 5;

int OutputPIN1 = 7;  // Salida 1 del Contador
int OutputPIN2 = 8;  // Salida 2 del Contador
int OutputPIN3 = 9;  // Salida 3 del Contador
int OutputPIN4 = 10; // Salida 4 del Contador
int OutputPIN5 = 11; // Salida 5 del Contador
int OutputPIN6 = 12; // Salida 6 del Contador
int OutputPIN7 = 13; // Salida 7 del Contador

int OutputPIN[7] = {7, 8, 9, 10, 11, 12, 13};

int val = 0; // Si el pin CLK esta activo

void setup()
{
    pinMode(CLK, INPUT);         // sets the digital pin 7 as input
    pinMode(OutputPIN1, OUTPUT); // Setea el PIN como salida
    pinMode(OutputPIN2, OUTPUT); // Setea el PIN como salida
    pinMode(OutputPIN3, OUTPUT); // Setea el PIN como salida
    pinMode(OutputPIN4, OUTPUT); // Setea el PIN como salida
    pinMode(OutputPIN5, OUTPUT); // Setea el PIN como salida
    pinMode(OutputPIN6, OUTPUT); // Setea el PIN como salida
    pinMode(OutputPIN7, OUTPUT); // Setea el PIN como salida
}

void loop()
{

    if (digitalRead(CLK) == 1)
    {
        for (int i = 0; i <= 13; i++)
        {
            digitalWrite(OutputPIN[i], 1);
            delay(Timems);
            digitalWrite(OutputPIN[i], 0);
        }
    }
}