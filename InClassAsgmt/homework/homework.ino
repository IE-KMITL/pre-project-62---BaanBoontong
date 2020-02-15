#include <HCSR04.h>
HCSR04 hc(D11,D10); //trig,echo
int SensorL=D2; //right LED
int SensorR=D3; //left LED
int LEDRight=D4; //Yellow LED
void setup() {
   Serial.begin(38400);
   pinMode(LED_BUILTIN, OUTPUT); //left light
   pinMode(LEDRight, OUTPUT); //right light
   pinMode(SensorL,INPUT);  
   pinMode(SensorR,INPUT); 

}

void loop() {
 

 if(digitalRead(SensorL)==LOW) //detectLeft
 {
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(LEDRight, HIGH);
   delay(100);
 }
  else if(digitalRead(SensorR)==LOW)//detectRight
  {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LEDRight, LOW);
     delay(100);
  }
    else if(hc.dist()<20)//detectFront20cm
    { digitalWrite(LED_BUILTIN,LOW);
    digitalWrite(LEDRight,LOW);
    delay(100);
    }
    else if(hc.dist()>40)//ObjFar40cm
    { digitalWrite(LED_BUILTIN,HIGH);
    digitalWrite(LEDRight,HIGH);
    delay(100);
    }
    else if(hc.dist()>=20 && hc.dist()<=40)//detectFront20to40cm
    { 
    
      digitalWrite(LED_BUILTIN,HIGH);
       digitalWrite(LEDRight,HIGH);
       delay(1000);
    }
   else
   {digitalWrite(LED_BUILTIN,LOW);
       digitalWrite(LEDRight,LOW);
   }
   Serial.println(hc.dist());
  }
