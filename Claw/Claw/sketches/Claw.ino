//��ӵĿ�
#include <Servo.h>

//����u8/u16
#define u8 unsigned char
#define u16 unsigned int
//���ڲ����ʶ���
#define UartSpeed 9600
//������ڶ���
#define Servo1Port 2
#define Servo2Port 3
#define Servo3Port 4
#define Servo4Port 5

//�����������
Servo Servo1;
Servo Servo2;
Servo Servo3;
Servo Servo4;

//ȫ�ֱ�������
u8 Rev;//�ݴ���
u8 RevStart;//�洢��ʼ��־λ
u8 Pos = 0;//�洢λ����־λ
u8 RevA[25];//�ַ���������
u16 ServoCache = 0;//�����ݴ�λ

//���MS����
u16 Servo1Num = 1500;
u16 Servo2Num = 1500;
u16 Servo3Num = 1500;
u16 Servo4Num = 1500;

void setup()
{
	//�������������ڰ�
	Servo1.attach(Servo1Port);
	Servo2.attach(Servo2Port);
	Servo3.attach(Servo3Port);
	Servo4.attach(Servo4Port);
	//�����ʼ��
	Servo1.write(Servo1Num);
	Servo2.write(Servo2Num);
	Servo3.write(Servo3Num);
	Servo4.write(Servo4Num);
	//���ڳ�ʼ��
	Serial.begin(UartSpeed);
}

void loop()
{
	if (Serial.available())
	{
		Rev = Serial.read();
		if (Rev == '$')
		{
			RevStart = 1;
		}
		if (RevStart == 1) 
		{
			if (Rev == '%')
			{
				if (Pos == 20)
				{
					ServoCache = (RevA[1] - '0') * 1000 + (RevA[2] - '0') * 100 + (RevA[3] - '0') * 10 + (RevA[4] - '0');
					Servo1Num = map(ServoCache, 0, 1023, 500, 2500);
					ServoCache = (RevA[6] - '0') * 1000 + (RevA[7] - '0') * 100 + (RevA[8] - '0') * 10 + (RevA[9] - '0');
					Servo2Num = map(ServoCache, 0, 1023, 500, 2500);
					ServoCache = (RevA[11] - '0') * 1000 + (RevA[12] - '0') * 100 + (RevA[13] - '0') * 10 + (RevA[14] - '0');
					Servo3Num = map(ServoCache, 0, 1023, 500, 2500);
					ServoCache = (RevA[16] - '0') * 1000 + (RevA[17] - '0') * 100 + (RevA[18] - '0') * 10 + (RevA[19] - '0');
					Servo4Num = map(ServoCache, 0, 1023, 500, 2500);
					Servo1.write(Servo1Num);
					Servo2.write(Servo2Num);
					Servo3.write(Servo3Num);
					Servo4.write(Servo4Num);
					Serial.print("Servo1:");
					Serial.println(Servo1Num);
					Serial.print("Servo2:");
					Serial.println(Servo2Num);
					Serial.print("Servo3:");
					Serial.println(Servo3Num);
					Serial.print("Servo4:");
					Serial.println(Servo4Num);
				}
				RevStart = 0;
				Pos = 0;
			}
			else
			{
				RevA[Pos] = Rev;
				++Pos;
			}
		}
	}
}
