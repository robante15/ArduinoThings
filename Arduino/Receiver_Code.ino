#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
int pos = 0;




void setup() {
    Serial.begin(9600);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(8,OUTPUT);
    pinMode(9,OUTPUT); 
    pinMode(6,OUTPUT);
    pinMode(10,OUTPUT); 
    pinMode(11,OUTPUT);
        
     mySwitch.enableReceive(0);
}
void loop() {
    if (mySwitch.available()) {
        int value = mySwitch.getReceivedValue();
        if (value > 0) {
            if (mySwitch.getReceivedValue()==1){digitalWrite(4,HIGH);digitalWrite (6,LOW); digitalWrite (7, HIGH); digitalWrite (10,LOW); digitalWrite (11, HIGH);}
            else if (mySwitch.getReceivedValue()==2){digitalWrite(5,HIGH);digitalWrite (6,HIGH); digitalWrite (7, LOW); digitalWrite (10,HIGH); digitalWrite (11, LOW);}
            else if (mySwitch.getReceivedValue()==3){digitalWrite(8,HIGH);digitalWrite (6,LOW); digitalWrite (7, HIGH);digitalWrite (10,HIGH); digitalWrite (11, LOW);}
            else if (mySwitch.getReceivedValue()==4){digitalWrite(9,HIGH);digitalWrite (6,HIGH); digitalWrite (7, LOW);digitalWrite (10,LOW); digitalWrite (11, HIGH);}
            else if (mySwitch.getReceivedValue()==5){
                digitalWrite(4,LOW);
                digitalWrite(5,LOW);
                digitalWrite(8,LOW);
                digitalWrite(9,LOW);
                digitalWrite(6,LOW);
                digitalWrite(7,LOW);
                digitalWrite(10,LOW);
                digitalWrite(11,LOW);
               
            }
        }
        mySwitch.resetAvailable();
    }
}
