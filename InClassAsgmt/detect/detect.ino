const int Sensor=D2;
int inputVal = 0;
void setup() 
{                
  pinMode(Sensor,INPUT);    
  Serial.begin(9600);
}

void loop() 
{  
   if(digitalRead(Sensor)==HIGH)
{

Serial.println("sensor not detected object"" ");
delay(200);    // wait for a second
}
else 
{
Serial.println("sensor detected object");

}
}
