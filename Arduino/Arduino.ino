#define IN1 D10 //motor A 
#define IN2 D9 //motor A 
#define IN3 D6 //motor B 
#define IN4 D5 //motor B

#define left D2 //leftsensor
#define right D11 //rightsensor
#define back D4 //backsensor

#define RED 1
#define YELLOW 2
#define BLACK 3
#define NOCOLOR 0
#define maxSpd 255    // motor max speed

#include <HCSR04.h>
HCSR04 hc(D8,D7); //initialisation class HCSR04 (trig,echo);

int analogPin = A6; //ประกาศตัวแปร ให้ analogPin แทนขา analog ขาที่6

int led1 = D13;
int buttonPin = D12;
int val=0;
int old_val=0;
int state=0;

int color=0;
int getColor() {
  int NO_color = analogRead(analogPin);           //อ่านค่าสัญญาณ analog ขา6 ที่ต่อกับ TCRT5000 
  if ((NO_color>1900)&&(NO_color<2200))           //สีเหลือง
    return YELLOW;
  else if ((NO_color>2200)&&(NO_color<2500))      //สีแดง
    return RED;
  else if ((NO_color>3600)&&(NO_color<3900))      //สีดำ
    return BLACK;
  else                                            //ไม่พบสี
    return NOCOLOR;
}

void setup() {
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  pinMode(back, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(led1, OUTPUT); 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(115200);
}

void loop() 
{ 
 color = getColor();
 val = digitalRead(buttonPin);
 if( (val==HIGH) && (old_val==LOW)) 
 {
  state=!state;
 }
 old_val=val;
 if (state==1) //เมื่อกดสวิทซ์ 1 ครั้ง ใช้กลยุทธ์รุก
 {
  digitalWrite(led1, HIGH);
  if((hc.dist()>10)&&((digitalRead(left)==HIGH)||(digitalRead(right)==HIGH))&&(color == NOCOLOR))  // เดินหน้าเมื่อ sensor ด้านหน้า  ด้านข้าง และด้านล่างไม่ทำงาน 
  {
  MotorAForward(maxSpd);
  MotorBForward(maxSpd);
  }
  if((hc.dist()<10)&&(digitalRead(back)==LOW)&&((digitalRead(left)==HIGH)||(digitalRead(right)==HIGH))&&(color == NOCOLOR))  // break เมื่อ sensor ด้านหน้า ด้านหลังทำงาน แต่ด้านข้างและด้านล่างไม่ทำงาน
  {
  MotorABreakTime(1000);
  MotorBBreakTime(1000); 
  }
  if((hc.dist()<10)&&(digitalRead(back)==HIGH)&&((digitalRead(left)==LOW)||(digitalRead(right)==LOW))&&(color == NOCOLOR))   // เดินถอยหลัง 3วิ เมื่อ sensor ด้านหน้าและข้างซ้ายหรือขวาทำงาน แต่ด้านหลังไม่ทำงาน
  {
  MotorARewardTime(3000);
  MotorBRewardTime(3000);
  }

  if(color == RED)  // เดินกลับรถ เมื่อ sensor ด้านล่างตรวจจับเส้นสีแดงได้
  {
  MotorAForwardTime(5000);
  MotorBRewardTime(5000);
  }

  if(color == YELLOW)  // รถหยุด เมื่อ sensor ด้านล่างตรวจจับเส้นสีเหลืองได้
  {
  MotorAStop();
  MotorBStop();
  }
 }
 else
 {
  digitalWrite (led1,LOW);
  if((hc.dist()>5)&&((digitalRead(left)==HIGH)||(digitalRead(right)==HIGH))&&(color == NOCOLOR))  // ถอยหลังเมื่อ sensor ด้านหน้า ด้านข้าง และด้านล่าง ไม่ทำงาน
  {
  MotorAReward(maxSpd);
  MotorBReward(maxSpd);
  }

  if((hc.dist()<5)&&((digitalRead(left)==HIGH)||(digitalRead(right)==HIGH))&&(color == NOCOLOR)) // เดินหน้าเมื่อ sensor ด้านหน้าทำงาน แต่ด้านข้างและล่างไม่ทำงาน
  {
  MotorAForwardTime(3000);
  MotorBForwardTime(3000);
  }
  
  if((digitalRead(left)==LOW)||(digitalRead(right)==LOW)&&(color == NOCOLOR))  // เบรค เมื่อ sensor ด้านข้างซ้ายหรือขวาทำงาน แต่ล่างไม่ทำงาน
  {
  MotorABreakTime(1000);
  MotorBBreakTime(1000); 
  } 
    
  if(color == BLACK)  // กลับรถ เมื่อ sensor ด้านล่างตรวจจับเส้นสีดำได้
  {
  MotorAForwardTime(5000);
  MotorBRewardTime(5000);
  }
  
  }
  delay(20);
       
}

void MotorAStop()
{
  digitalWrite(IN1, LOW);   // motor stop
  digitalWrite(IN2, LOW);    
}

void MotorABreak()
{
  digitalWrite(IN1, HIGH);   // motor break
  digitalWrite(IN2, HIGH);    
}

void MotorBStop()
{
  digitalWrite(IN3, LOW);   // motor stop
  digitalWrite(IN4, LOW);    
}

void MotorBBreak()
{
  digitalWrite(IN3, HIGH);   // motor break
  digitalWrite(IN4, HIGH);    
}

void MotorAForward(int speed)
{
  digitalWrite(IN2, LOW);   
  analogWrite(IN1, speed);   
}

void MotorBForward(int speed)
{
  digitalWrite(IN4, LOW);   
  analogWrite(IN3, speed);   
}

void MotorAReward(int speed)
{
  digitalWrite(IN1, LOW);   
  analogWrite(IN2, speed);   
}

void MotorBReward(int speed)
{
  digitalWrite(IN3, LOW);   
  analogWrite(IN4, speed);   
}

void MotorARewardTime(int time)
{
  digitalWrite(IN1, LOW);   
  analogWrite(IN2, maxSpd);
  delay (time);   
}

void MotorBRewardTime(int time)
{
  digitalWrite(IN3, LOW);   
  analogWrite(IN4, maxSpd);
  delay (time);    
}

void MotorAForwardTime(int time)
{
  digitalWrite(IN2, LOW);   
  analogWrite(IN1, maxSpd);
  delay (time);    
}

void MotorBForwardTime(int time)
{
  digitalWrite(IN4, LOW);   
  analogWrite(IN3, maxSpd);
  delay (time);    
}

void MotorABreakTime(int time)
{
  digitalWrite(IN1, HIGH);   
  digitalWrite(IN2, HIGH);
  delay (time);    
}

void MotorBBreakTime(int time)
{
  digitalWrite(IN3, HIGH);   
  digitalWrite(IN4, HIGH);
  delay (time);
      
}
