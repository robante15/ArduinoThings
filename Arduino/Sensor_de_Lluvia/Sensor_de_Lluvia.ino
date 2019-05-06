void setup()

{

  // put your setup code here, to run once:

  Serial.begin (9600);

  pinMode (2 , INPUT);

}

void loop()

{

  // put your main code here, to run repeatedly:

  int value = analogRead(A1);

  int digital = digitalRead(2);

 

  Serial.println (value);
  Serial.println (digital);

if(digital == 0){
  Serial.println("Esta lloviendo hijosdelagranputa");
}else{
  Serial.println("Puta acá en San Miguel nunca llueve culeros");
}

  delay(5000);

}
