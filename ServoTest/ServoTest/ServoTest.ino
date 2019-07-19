#include <Servo.h>

Servo TestServo1;
Servo TestServo2;

char RecStart=0;
char Rev;
char Str[10];
char RPos=0;
char RecComplete=0;
int MoveNum=1500;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  TestServo1.attach(4);
  TestServo2.attach(8);
  TestServo1.writeMicroseconds(1500);
  TestServo2.writeMicroseconds(1500);
  Serial.println("Power on.");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    Rev=Serial.read();
    if(Rev=='$')
    {
      RecStart=1;
    }
    if(RecStart==1)
    {
      Str[RPos]=Rev;
      ++RPos;
      if(RPos==8)
      {
        if(Rev=='%')
        {
          RecComplete=1;
        }
        RecStart=0;
        RPos=0;
      }
    }
  }
  if(RecComplete==1)
  {
    RecComplete=0;
    MoveNum=(Str[3]-'0')*1000+(Str[4]-'0')*100+(Str[5]-'0')*10+(Str[6]-'0');
    if(Str[1]=='1')
    {
      TestServo1.writeMicroseconds(MoveNum);
      Serial.print("Servo1,Num=");
      Serial.println(MoveNum);
    }
    if(Str[1]=='2')
    {
      TestServo2.writeMicroseconds(MoveNum);
      Serial.print("Servo2,Num=");
      Serial.println(MoveNum);
    }
    if(Str[1]=='T')
    {
      Serial.print("Test OK,Num=");
      Serial.println(MoveNum);
    }
  }
}
