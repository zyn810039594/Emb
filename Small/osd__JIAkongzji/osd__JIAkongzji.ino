
#include <Servo.h>

void splitString(char* date);
void setMOTOR(char* date);

char buffer[75];
Servo myservo2;   //水平推进器A
Servo myservo3;   //水平推进器B
Servo myservo4;   //垂直推进器
Servo myservo5;   //机械手
Servo myservo6;   //云台
  
  
int KL;       //控制仓漏水传感器1
int KL1;      //控制仓漏水传感器2
int DL;       //动力舱漏水传感器1
int DL1;      //动力舱漏水传感器2
int D;        //电压传感器
int Db;
int Ds;
int Dg;
int Hsq;      //电子罗盘舍弃数据缓存位
int Hb;       //罗盘数据百位
int Hs;       //罗盘数据十位
int Hg;       //罗盘数据个位
int S;        //深度传感器
int Sb;       //深度传感器百位
int Ss;       //深度传感器十位
int Sg;       //深度传感器个位
// int W;       //温度传感器
// int Ws;
// int Wg;
 int i;
int val;
 
int ledPin = 5;
int Key1Pin = 30;      //关机
int Key2Pin = 32;      //预留
 
 
void setup() {
	Serial1.begin(9600);      //与电子罗盘通讯
	Serial2.begin(9600);      //与OSD模块通讯
	Serial3.begin(9600);
	delay(50);             
	pinMode(Key1Pin, OUTPUT);  //设置端口30为输出
	pinMode(Key2Pin, OUTPUT);  //设置端口32为输出
	pinMode(ledPin, OUTPUT);
   
	myservo2.attach(2);
	
	myservo3.attach(3);
	myservo4.attach(8);
	myservo5.attach(7);
	myservo6.attach(4);
   
	myservo2.write(90);
	myservo3.write(90);
	myservo4.write(90);
	myservo5.write(90);
	myservo6.write(90);
     
	delay(1000);
   
	unsigned char hexdate1[5] = { 0x55, 0x03, 0x00, 0x00, 0x00 };
	Serial2.write(hexdate1, 5);    //设置OSD模块水平位，垂直位移为0
   
	unsigned char hexdate2[5] = { 0x55, 0x04, 0x1E, 0x00, 0x00 };
	Serial2.write(hexdate2, 5);    //PAL设置扫描起始垂直位移为30
   
	unsigned char hexdate3[5] = { 0x55, 0x06, 0x00, 0x01, 0x00 };
	Serial2.write(hexdate3, 5);    //字符尺寸标准大小 在第1行
   
	unsigned char hexdate4[5] = { 0x55, 0x06, 0x00, 0x02, 0x00 };
	Serial2.write(hexdate4, 5);    //字符尺寸标准大小 在第2行
   
	unsigned char hexdate5[5] = { 0x55, 0x06, 0x00, 0x03, 0x00 };
	Serial2.write(hexdate5, 5);    //字符尺寸标准大小 在第3行
   
	unsigned char hexdate6[5] = { 0x55, 0x06, 0x00, 0x04, 0x00 };
	Serial2.write(hexdate6, 5);    //字符尺寸标准大小 在第4行
   
	unsigned char hexdate7[5] = { 0x55, 0x06, 0x00, 0x05, 0x00 };
	Serial2.write(hexdate7, 5);    //字符尺寸标准大小 在第5行
   
	unsigned char hexdate8[5] = { 0x55, 0x06, 0x00, 0x06, 0x00 };
	Serial2.write(hexdate8, 5);    //字符尺寸标准大小 在第6行
   
	unsigned char hexdate9[5] = { 0x55, 0x06, 0x00, 0x07, 0x00 };
	Serial2.write(hexdate9, 5);    //字符尺寸标准大小 在第7行
   
	unsigned char hexdate10[5] = { 0x55, 0x06, 0x00, 0x08, 0x00 };
	Serial2.write(hexdate10, 5);    //字符尺寸标准大小 在第8行
   
	unsigned char hexdate11[5] = { 0x55, 0x06, 0x00, 0x09, 0x00 };
	Serial2.write(hexdate11, 5);    //字符尺寸标准大小 在第9行
   
	unsigned char hexdate12[5] = { 0x55, 0x06, 0x00, 0x10, 0x00 };
	Serial2.write(hexdate12, 5);    //字符尺寸标准大小 在第10行
   
	unsigned char hexdate13[5] = { 0x55, 0x06, 0x00, 0x11, 0x00 };
	Serial2.write(hexdate13, 5);    //字符尺寸标准大小 在第11行
   
	unsigned char hexdate14[5] = { 0x55, 0x06, 0x00, 0x12, 0x00 };
	Serial2.write(hexdate14, 5);    //字符尺寸标准大小 在第12行
   
	unsigned char hexdate15[5] = { 0x55, 0x09, 0x71, 0x00, 0x00 };
	Serial2.write(hexdate15, 5);    //设置字符颜色白色和背景颜色蓝色
   
	unsigned char hexdate16[5] = { 0x55, 0x02, 0x11, 0x00, 0x00 };
	Serial2.write(hexdate16, 5);    //视频扫描方式
   
	unsigned char hexdate17[17] = {
		 0x55,
		 0x06, 
		0x71, 
		0x00, 
		0x00,
		 0x71, 
		0x71, 
		0x71, 
		0x71,
		 0x71,
		 0x71,
		 0x71, 
		0x71,
		 0x71,
		 0x71,
		 0x71,
		 0x71
	 };
	Serial2.write(hexdate17, 17);    //
   
	unsigned char hexdate19[5] = { 0x55, 0x0A, 0x00, 0x00, 0x00 };
	Serial2.write(hexdate19, 5);    //设置行距为0
   
	unsigned char hexdate20[5] = { 0x55, 0x01, 0x01, 0x01, 0x00 };
	Serial2.write(hexdate20, 5);    //清屏底色为蓝色
   
	delay(100);    //  延时0.1S
   
	unsigned char hexdate21[16] = {
		 0x55, 
		0x07,
		 0x01,
		 0x01,
		 0x00,
		0x55,
		 0x31,
		 0x03,
		 0x01,
		 0x00,
		 0xB5,
		 0xE7, 
		0xD1, 
		0xB9, 
		0xA3,
		 0xBA
	 };
	Serial2.write(hexdate21, 16);    //一行一列显示 电压:
   
	unsigned char hexdate22[12] = {
		 0x55,
		 0x07, 
		0x01, 
		0x06,
		 0x00,
		0x55,
		 0x31, 
		0x01,
		 0x01, 
		0x00, 
		0xA3,
		 0xAE
	 };
	Serial2.write(hexdate22, 12);    //一行六列显示 ·
   
	unsigned char hexdate23[12] = {
		 0x55,
		 0x07,
		 0x01,
		 0x08, 
		0x00,
		0x55,
		 0x31,
		 0x01,
		 0x01,
		 0x00,
		 0xA3,
		 0xF6
	 };
	Serial2.write(hexdate23, 12);    //一行八列显示 V
   
	unsigned char hexdate24[16] = {
		 0x55, 
		0x07, 
		0x02,
		 0x01,
		 0x00,
		0x55,
		 0x31, 
		0x03,
		 0x01,
		 0x00, 
		0xC9,
		 0xEE,
		 0xB6, 
		0xC8,
		 0xA3,
		 0xBA 
	};
	Serial2.write(hexdate24, 16);    //二行一列显示 深度:
   
	unsigned char hexdate25[16] = {
		 0x55,
		 0x07,
		 0x02,
		 0x06,
		 0x00,
		0x55,
		 0x31,
		 0x01, 
		0x01,
		 0x00, 
		0xA3, 
		0xAE 
	};
	Serial2.write(hexdate25, 16);    //二行六列显示 ·
   
	unsigned char hexdate26[12] = {
		 0x55, 
		0x07,
		 0x02,
		 0x08,
		 0x00,
		0x55,
		 0x31, 
		0x01, 
		0x01,
		 0x00,
		 0xA3,
		 0xED
	 };
	Serial2.write(hexdate26, 12);    //二行八列显示 m
   
	unsigned char hexdate27[16] = {
		 0x55, 
		0x07, 
		0x03,
		 0x01,
		 0x00,
		0x55, 
		0x31, 
		0x03,
		 0x01,
		 0x00,
		 0xBA,
		 0xBD,
		 0xCF, 
		0xF2, 
		0xA3,
		 0xBA
	 };
	Serial2.write(hexdate27, 16);    //三行一列显示 航向:
   
	unsigned char hexdate28[12] = { 
		0x55, 
		0x07, 
		0x03,
		 0x07,
		 0x00,
		0x55,
		 0x31, 
		0x01, 
		0x01,
		 0x00, 
		0xA1,
		 0xE3 
	};
	Serial2.write(hexdate28, 12);    //三行七列显示 °
    

	unsigned char hexdate29[12] = {
		 0x55, 
		0x07, 
		0x03,
		 0x07,
		 0x00,
		0x55,
		 0x31,
		 0x01, 
		0x01,
		 0x00, 
		0xA1,
		 0xE3
	 };
	Serial2.write(hexdate29, 12);    //三行七列显示 °
    
}
 
void loop() {
   
	KL = analogRead(A0);
	KL = map(KL, 0, 1023, 0, 10);
	if (KL >= 7) {
		unsigned char hexdate40[14] = { 
			0x55,
			 0x07,
			 0x01, 
			0x0F,
			 0x00,
			0x55,
			 0x31, 
			0x02,
			 0x01,
			 0x00,
			 0xBE, 
			0xAF,
			 0xB8,
			 0xE6
		 };
		Serial2.write(hexdate40, 14);
		delay(1);
		unsigned char hexdate41[26] = {
			 0x55,
			 0x07, 
			0x02,
			 0x0C,
			 0x00,
			0x55,
			 0x31,
			 0x08,
			 0x01, 
			0x00, 
			0xD0,
			 0xB9, 
			0xC2,
			 0xA9,
			 0xD6,
			 0xD0,
			0xC7,
			 0xEB,
			 0xBF,
			 0xEC,
			 0xCB,
			 0xD9, 
			0xC9, 
			0xCF, 
			0xB8,
			 0xA1
		 };
		Serial2.write(hexdate41, 26);
		delay(1);
     
	}
   
	DL = analogRead(A1);
	DL = map(DL, 0, 1023, 0, 5);
	if (DL >= 3) {
		unsigned char hexdate44[14] = {
			 0x55,
			 0x07, 
			0x01, 
			0x0F,
			 0x00,
			0x55,
			 0x31,
			 0x02,
			 0x01, 
			0x00,
			 0xBE,
			 0xAF, 
			0xB8,
			 0xE6
		 };
		Serial2.write(hexdate44, 14);
		delay(1);
		unsigned char hexdate45[26] = {
			 0x55,
			 0x07,
			 0x03,
			 0x0C,
			 0x00,
			0x55, 
			0x31,
			 0x08,
			 0x01, 
			0x00,
			 0xD0,
			 0xB9, 
			0xC2, 
			0xA9,
			 0xD6,
			 0xD0,
			0xC7, 
			0xEB,
			 0xBF,
			 0xEC,
			 0xCB, 
			0xD9, 
			0xC9, 
			0xCF,
			 0xB8,
			 0xA1 
		};
		Serial2.write(hexdate45, 26);
		delay(1);
	}   
 
	DL1 = analogRead(A2);
	DL1 = map(DL1, 0, 1023, 0, 5);
	if (DL1 >= 3) {
		unsigned char hexdate46[14] = { 
			0x55,
			 0x07,
			 0x01,
			 0x0F,
			 0x00,
			0x55,
			 0x31,
			 0x02, 
			0x01,
			 0x00, 
			0xBE,
			 0xAF, 
			0xB8, 
			0xE6 
		};
		Serial2.write(hexdate46, 14);
		delay(1);
		unsigned char hexdate47[26] = { 
			0x55, 
			0x07,
			 0x04,
			 0x0C, 
			0x00,
			0x55,
			 0x31,
			 0x08, 
			0x01, 
			0x00,
			 0xD0,
			 0xB9, 
			0xC2,
			 0xA9, 
			0xD6, 
			0xD0,
			0xC7,
			 0xEB,
			 0xBF,
			 0xEC, 
			0xCB,
			 0xD9,
			 0xC9, 
			0xCF, 
			0xB8, 
			0xA1
		 };
		Serial2.write(hexdate47, 26);
		delay(1);
	}
   
	D = analogRead(A4);
	D = map(D, 0, 1023, 6, 250);
	/* if(D <= 60){
	   unsigned char hexdate48[16] = {0x55,0x07,0x04,0x0A,0x00,
	   0x55,0x31,0x03,0x01,0x00,0xB9,0xD8,0xBB,0xFA,0xD6,0xD0};
	   Serial2.write(hexdate48,16);
	   delay(1);
	   digitalWrite(Key1Pin,HIGH);
	  }
	  else{
	   digitalWrite(Key1Pin,LOW);
	  }
    
	if(D <= 61){
	   unsigned char hexdate50[28] = {0x55,0x07,0x04,0x01,0x00,
	   0x55,0x31,0x09,0x01,0x00,0xCC,0xE1,0xCA,0xBE,0xA3,0xBA,
	   0xB5,0xE7,0xC1,0xBF,0xBC,0xB4,0xBD,0xAB,0xBA,0xC4,0xBE,
	   0xA1};
	   Serial2.write(hexdate50,28);
	   delay(1);
	   }
	  */
	Db = (D + 0);
	if (Db >= 200) {
		unsigned char hexdate53[12] = { 
			0x55, 
			0x07, 
			0x01,
			 0x04, 
			0x00,
			0x55, 
			0x31, 
			0x01,
			 0x01, 
			0x00,
			 0xA3, 
			0xB2 
		};
		Serial2.write(hexdate53, 12);
		delay(1);
	}
    
	if ((Db < 200) && (Db >= 100)) {
		unsigned char hexdate54[12] = { 
			0x55, 
			0x07, 
			0x01,
			 0x04,
			 0x00,
			0x55,
			 0x31, 
			0x01,
			 0x01,
			 0x00,
			 0xA3,
			 0xB1
		 };
		Serial2.write(hexdate54, 12);
		delay(1);
	}
    
	if ((Db < 100) && (Db >= 0)) {
		unsigned char hexdate55[12] = {
			 0x55,
			 0x07,
			 0x01,
			 0x04, 
			0x00,
			0x55, 
			0x31,
			 0x01,
			 0x01, 
			0x00, 
			0xA3, 
			0xB0 
		};
		Serial2.write(hexdate55, 12);
		delay(1);
	}
     
	Ds = ((D / 10) % 10);
	switch (Ds) {
	case 0: {
			unsigned char hexdate60[12] = {
				 0x55, 
				0x07,
				 0x01, 
				0x05,
				 0x00,
				0x55,
				 0x31,
				 0x01,
				 0x01, 
				0x00, 
				0xA3,
				 0xB0 
			};
			Serial2.write(hexdate60, 12);
			delay(1);
		} 
		break; 
     
	case 1: {
			unsigned char hexdate61[12] = {
				 0x55,
				 0x07, 
				0x01,
				 0x05,
				 0x00,
				0x55,
				 0x31,
				 0x01, 
				0x01, 
				0x00,
				 0xA3, 
				0xB1 
			};
			Serial2.write(hexdate61, 12);
			delay(1);
		} 
		break; 
  
	case 2: {
			unsigned char hexdate62[12] = {
				 0x55, 
				0x07, 
				0x01, 
				0x05,
				 0x00,
				0x55, 
				0x31, 
				0x01, 
				0x01,
				 0x00,
				 0xA3,
				 0xB2
			 };
			Serial2.write(hexdate62, 12);
			delay(1);
		} 
		break; 
  
	case 3: {
			unsigned char hexdate63[12] = {
				 0x55,
				 0x07,
				 0x01,
				 0x05, 
				0x00,
				0x55, 
				0x31,
				 0x01,
				 0x01,
				 0x00, 
				0xA3,
				 0xB3
			 };
			Serial2.write(hexdate63, 12);
			delay(1);
		} 
		break; 
  
	case 4: {
			unsigned char hexdate64[12] = {
				 0x55,
				 0x07, 
				0x01, 
				0x05, 
				0x00,
				0x55,
				 0x31,
				 0x01, 
				0x01, 
				0x00,
				 0xA3, 
				0xB4 
			};
			Serial2.write(hexdate64, 12);
			delay(1);
		} 
		break; 
  
	case 5: {
			unsigned char hexdate65[12] = {
				 0x55, 
				0x07,
				 0x01,
				 0x05,
				 0x00,
				0x55,
				 0x31, 
				0x01, 
				0x01,
				 0x00, 
				0xA3,
				 0xB5
			 };
			Serial2.write(hexdate65, 12);
			delay(1);
		} 
		break; 
  
	case 6: {
			unsigned char hexdate66[12] = { 
				0x55,
				 0x07,
				 0x01,
				 0x05, 
				0x00,
				0x55, 
				0x31,
				 0x01, 
				0x01,
				 0x00,
				 0xA3, 
				0xB6
			 };
			Serial2.write(hexdate66, 12);
			delay(1);
		} 
		break; 
  
	case 7: {
			unsigned char hexdate67[12] = { 
				0x55,
				 0x07, 
				0x01,
				 0x05,
				 0x00,
				0x55,
				 0x31,
				 0x01,
				 0x01,
				 0x00,
				 0xA3,
				 0xB7 
			};
			Serial2.write(hexdate67, 12);
			delay(1);
		} 
		break;   
    
	case 8: {
			unsigned char hexdate68[12] = {
				 0x55, 
				0x07,
				 0x01,
				 0x05,
				 0x00,
				0x55, 
				0x31,
				 0x01,
				 0x01,
				 0x00,
				 0xA3,
				 0xB8 
			};
			Serial2.write(hexdate68, 12);
			delay(1);
		} 
		break; 
   
	case 9: {
			unsigned char hexdate69[12] = {
				 0x55,
				 0x07, 
				0x01,
				 0x05,
				 0x00,
				0x55,
				 0x31, 
				0x01,
				 0x01, 
				0x00,
				 0xA3,
				 0xB9 
			};
			Serial2.write(hexdate69, 12);
			delay(1);
		} 
		break;  
	}
    
	Dg = (D % 10);
	switch (Dg) { 
	case 0: {
			unsigned char hexdate70[12] = { 
				0x55, 
				0x07,
				 0x01, 
				0x07, 
				0x00,
				0x55, 
				0x31, 
				0x01,
				 0x01,
				 0x00,
				 0xA3,
				 0xB0 
			};
			Serial2.write(hexdate70, 12);
			delay(1);
		} 
		break; 
     
	case 1: {
			unsigned char hexdate71[12] = {
				 0x55, 
				0x07, 
				0x01, 
				0x07, 
				0x00,
				0x55, 
				0x31,
				 0x01,
				 0x01, 
				0x00,
				 0xA3, 
				0xB1
			 };
			Serial2.write(hexdate71, 12);
			delay(1);
		} 
		break; 
  
	case 2: {
			unsigned char hexdate72[12] = { 
				0x55,
				 0x07,
				 0x01, 
				0x07, 
				0x00,
				0x55,
				 0x31,
				 0x01, 
				0x01, 
				0x00,
				 0xA3, 
				0xB2
			 };
			Serial2.write(hexdate72, 12);
			delay(1);
		} 
		break; 
  
	case 3: {
			unsigned char hexdate73[12] = { 
				0x55,
				 0x07,
				 0x01,
				 0x07,
				 0x00,
				0x55, 
				0x31,
				 0x01,
				 0x01,
				 0x00,
				 0xA3, 
				0xB3 
			};
			Serial2.write(hexdate73, 12);
			delay(1);
		} 
		break; 
  
	case 4: {
			unsigned char hexdate74[12] = { 
				0x55,
				 0x07,
				 0x01, 
				0x07, 
				0x00,
				0x55,
				 0x31,
				 0x01,
				 0x01, 
				0x00, 
				0xA3, 
				0xB4
			 };
			Serial2.write(hexdate74, 12);
			delay(1);
		} 
		break; 
  
	case 5: {
			unsigned char hexdate75[12] = {
				 0x55,
				 0x07, 
				0x01,
				 0x07,
				 0x00,
				0x55, 
				0x31,
				 0x01, 
				0x01,
				 0x00,
				 0xA3, 
				0xB5 
			};
			Serial2.write(hexdate75, 12);
			delay(1);
		} 
		break; 
  
	case 6: {
			unsigned char hexdate76[12] = { 
				0x55, 
				0x07,
				 0x01,
				 0x07,
				 0x00,
				0x55, 
				0x31, 
				0x01,
				 0x01, 
				0x00, 
				0xA3,
				 0xB6 
			};
			Serial2.write(hexdate76, 12);
			delay(1);
		} 
		break; 
  
	case 7: {
			unsigned char hexdate77[12] = {
				 0x55,
				 0x07,
				 0x01,
				 0x07,
				 0x00,
				0x55, 
				0x31,
				 0x01,
				 0x01,
				 0x00,
				 0xA3,
				 0xB7
			 };
			Serial2.write(hexdate77, 12);
			delay(1);
		} 
		break;   
    
	case 8: {
			unsigned char hexdate78[12] = {
				 0x55,
				 0x07,
				 0x01,
				 0x07, 
				0x00,
				0x55, 
				0x31,
				 0x01,
				 0x01, 
				0x00, 
				0xA3, 
				0xB8
			 };
			Serial2.write(hexdate78, 12);
			delay(1);
		} 
		break; 
   
	case 9: {
			unsigned char hexdate79[12] = { 
				0x55,
				 0x07, 
				0x01,
				 0x07, 
				0x00,
				0x55,
				 0x31,
				 0x01,
				 0x01,
				 0x00, 
				0xA3, 
				0xB9
			 };
			Serial2.write(hexdate79, 12);
			delay(1);
		} 
		break;  
	}
     
     
	S = analogRead(A3);
	S = map(S, 15, 1023, 0, 600);
	Sb = (S + 0);
	if (Sb >= 600) {
		unsigned char hexdate90[12] = {
			 0x55, 
			0x07, 
			0x02,
			 0x04,
			 0x00,
			0x55,
			 0x31, 
			0x01, 
			0x01,
			 0x00,
			 0xA3,
			 0xB6
		 };
		Serial2.write(hexdate90, 12);
		delay(1);
	}  
     
	if ((Sb < 600)&&(Sb >= 500)) {
		unsigned char hexdate91[12] = {
			 0x55,
			 0x07, 
			0x02, 
			0x04,
			 0x00,
			0x55,
			 0x31,
			 0x01,
			 0x01,
			 0x00, 
			0xA3,
			 0xB5 
		};  
		Serial2.write(hexdate91, 12);
		delay(1);
	}
     
	if ((Sb < 500)&&(Sb >= 400)) {
		unsigned char hexdate92[12] = { 
			0x55,
			 0x07,
			 0x02, 
			0x04, 
			0x00,
			0x55,
			 0x31,
			 0x01, 
			0x01, 
			0x00,
			 0xA3, 
			0xB4
		 };  
		Serial2.write(hexdate92, 12);
		delay(1);
	}
     
	if ((Sb < 400)&&(Sb >= 300)) {
		unsigned char hexdate93[12] = { 
			0x55,
			 0x07,
			 0x02,
			 0x04,
			 0x00,
			0x55, 
			0x31,
			 0x01, 
			0x01, 
			0x00,
			 0xA3,
			 0xB3
		 };  
		Serial2.write(hexdate93, 12);
		delay(1);
	}  
     
	if ((Sb < 300)&&(Sb >= 200)) {
		unsigned char hexdate94[12] = { 
			0x55,
			 0x07,
			 0x02,
			 0x04, 
			0x00,
			0x55, 
			0x31, 
			0x01, 
			0x01,
			 0x00,
			 0xA3,
			 0xB2
		 };  
		Serial2.write(hexdate94, 12);
		delay(1);
	}
     
	if ((Sb < 200)&&(Sb >= 100)) {
		unsigned char hexdate95[12] = {
			 0x55, 
			0x07,
			 0x02, 
			0x04, 
			0x00,
			0x55, 
			0x31,
			 0x01,
			 0x01,
			 0x00,
			 0xA3,
			 0xB1
		 };  
		Serial2.write(hexdate95, 12);
		delay(1);
	}  
    
	if ((Sb < 100)&&(Sb >= 0)) {
		unsigned char hexdate96[12] = { 
			0x55, 
			0x07,
			 0x02,
			 0x04,
			 0x00,
			0x55, 
			0x31,
			 0x01,
			 0x01, 
			0x00, 
			0xA3, 
			0xB0 
		};  
		Serial2.write(hexdate96, 12);
		delay(1);
	}  
 
	Ss = ((S / 10) % 10);
	switch (Ss) {
	case 0: {
			unsigned char hexdate100[12] = { 
				0x55,
				 0x07,
				 0x02,
				 0x05, 
				0x00,
				0x55, 
				0x31,
				 0x01,
				 0x01,
				 0x00, 
				0xA3, 
				0xB0 
			};
			Serial2.write(hexdate100, 12);
			delay(1);
		}     
		break;
     
	case 1: {
			unsigned char hexdate101[12] = { 
				0x55,
				 0x07,
				 0x02, 
				0x05,
				 0x00,
				0x55,
				 0x31, 
				0x01,
				 0x01, 
				0x00, 
				0xA3, 
				0xB1 
			};
			Serial2.write(hexdate101, 12);
			delay(1);
		}     
		break;     
     
	case 2: {
			unsigned char hexdate102[12] = {
				 0x55, 
				0x07,
				 0x02, 
				0x05,
				 0x00,
				0x55,
				 0x31,
				 0x01, 
				0x01, 
				0x00,
				 0xA3, 
				0xB2
			 };
			Serial2.write(hexdate102, 12);
			delay(1);
		}     
		break;     
     
	case 3: {
			unsigned char hexdate103[12] = {
				 0x55, 
				0x07,
				 0x02,
				 0x05,
				 0x00,
				0x55, 
				0x31,
				 0x01,
				 0x01,
				 0x00, 
				0xA3, 
				0xB3
			 };
			Serial2.write(hexdate103, 12);
			delay(1);
		}     
		break;     
     
	case 4: {
			unsigned char hexdate104[12] = { 
				0x55, 
				0x07,
				 0x02,
				 0x05, 
				0x00,
				0x55,
				 0x31, 
				0x01, 
				0x01,
				 0x00, 
				0xA3,
				 0xB4 
			};
			Serial2.write(hexdate104, 12);
			delay(1);
		}     
		break;     
     
	case 5: {
			unsigned char hexdate105[12] = { 
				0x55,
				 0x07, 
				0x02,
				 0x05,
				 0x00,
				0x55, 
				0x31, 
				0x01, 
				0x01,
				 0x00, 
				0xA3,
				 0xB5 
			};
			Serial2.write(hexdate105, 12);
			delay(1);
		}     
		break;     
     
	case 6: {
			unsigned char hexdate106[12] = {
				 0x55,
				 0x07, 
				0x02,
				 0x05,
				 0x00,
				0x55, 
				0x31,
				 0x01,
				 0x01, 
				0x00, 
				0xA3,
				 0xB6 
			};
			Serial2.write(hexdate106, 12);
			delay(1);
		}     
		break;     
     
	case 7: {
			unsigned char hexdate107[12] = {
				 0x55, 
				0x07,
				 0x02,
				 0x05,
				 0x00,
				0x55, 
				0x31,
				 0x01,
				 0x01,
				 0x00,
				 0xA3, 
				0xB7
			 };
			Serial2.write(hexdate107, 12);
			delay(1);
		}     
		break;     
     
	case 8: {
			unsigned char hexdate108[12] = {
				 0x55, 
				0x07,
				 0x02, 
				0x05,
				 0x00,
				0x55,
				 0x31,
				 0x01,
				 0x01,
				 0x00, 
				0xA3,
				 0xB8 
			};
			Serial2.write(hexdate108, 12);
			delay(1);
		}     
		break;     
     
	case 9: {
			unsigned char hexdate109[12] = {
				 0x55, 
				0x07, 
				0x02,
				 0x05,
				 0x00,
				0x55,
				 0x31, 
				0x01, 
				0x01, 
				0x00,
				 0xA3, 
				0xB9 
			};
			Serial2.write(hexdate109, 12);
			delay(1);
		}     
		break;     
	default:
		break;
	}
     
	Sg = (S % 10);
	switch (Sg) {
	case 0: {
			unsigned char hexdate110[12] = {
				 0x55, 
				0x07,
				 0x02,
				 0x07,
				 0x00,
				0x55, 
				0x31, 
				0x01, 
				0x01,
				 0x00,
				 0xA3,
				 0xB0
			 };
			Serial2.write(hexdate110, 12);
			delay(1);
		}     
		break;
     
	case 1: {
			unsigned char hexdate111[12] = {
				 0x55, 
				0x07,
				 0x02,
				 0x07,
				 0x00,
				0x55, 
				0x31, 
				0x01,
				 0x01,
				 0x00,
				 0xA3,
				 0xB1 
			};
			Serial2.write(hexdate111, 12);
			delay(1);
		}     
		break;     
     
	case 2: {
			unsigned char hexdate112[12] = {
				 0x55,
				 0x07, 
				0x02, 
				0x07,
				 0x00,
				0x55,
				 0x31,
				 0x01,
				 0x01, 
				0x00,
				 0xA3, 
				0xB2
			 };
			Serial2.write(hexdate112, 12);
		}     
		break;     
     
	case 3: {
			unsigned char hexdate113[12] = { 
				0x55,
				 0x07, 
				0x02, 
				0x07,
				 0x00,
				0x55, 
				0x31,
				 0x01, 
				0x01,
				 0x00,
				 0xA3,
				 0xB3
			 };
			Serial2.write(hexdate113, 12);
			delay(1);
		}     
		break;     
     
	case 4: {
			unsigned char hexdate114[12] = {
				 0x55,
				 0x07,
				 0x02,
				 0x07, 
				0x00,
				0x55,
				 0x31,
				 0x01,
				 0x01,
				 0x00,
				 0xA3, 
				0xB4 
			};
			Serial2.write(hexdate114, 12);
			delay(1);
		}     
		break;     
     
	case 5: {
			unsigned char hexdate115[12] = { 
				0x55,
				 0x07, 
				0x02,
				 0x07, 
				0x00,
				0x55,
				 0x31, 
				0x01,
				 0x01,
				 0x00,
				 0xA3, 
				0xB5 
			};
			Serial2.write(hexdate115, 12);
			delay(1);
		}     
		break;     
     
	case 6: {
			unsigned char hexdate116[12] = {
				 0x55,
				 0x07,
				 0x02,
				 0x07, 
				0x00,
				0x55, 
				0x31,
				 0x01,
				 0x01,
				 0x00,
				 0xA3,
				 0xB6
			 };
			Serial2.write(hexdate116, 12);
			delay(1);
		}     
		break;     
     
	case 7: {
			unsigned char hexdate117[12] = {
				 0x55,
				 0x07,
				 0x02,
				 0x07, 
				0x00,
				0x55,
				 0x31,
				 0x01,
				 0x01,
				 0x00,
				 0xA3, 
				0xB7
			 };
			Serial2.write(hexdate117, 12);
			delay(1);
		}     
		break;     
     
	case 8: {
			unsigned char hexdate118[12] = {
				 0x55, 
				0x07,
				 0x02,
				 0x07,
				 0x00,
				0x55, 
				0x31,
				 0x01,
				 0x01,
				 0x00, 
				0xA3,
				 0xB8
			 };
			Serial2.write(hexdate118, 12);
			delay(1);
		}     
		break;     
     
	case 9: {
			unsigned char hexdate119[12] = { 
				0x55,
				 0x07, 
				0x02, 
				0x07,
				 0x00,
				0x55,
				 0x31, 
				0x01,
				 0x01,
				 0x00,
				 0xA3,
				 0xB9 
			};
			Serial2.write(hexdate119, 12);
			delay(1);
		}     
		break;     
	default:
		break;
	}
     
	/*W = analogRead(A5);
	W = map(W,0,1023,0,550);
	 if(W >= 60){
	   unsigned char hexdate120[22] = {0x55,0x07,0x05,0x04,0x00,
	   0x55,0x31,0x06,0x01,0x00,0xB5,0xE7,0xB3,0xD8,0xCE,0xC2,
	   0xB6,0xC8,0xB9,0xFD,0xB8,0xDF};
	   Serial2.write(hexdate120,22);
	   delay(1);
	   }
   
   
	Ws = ((W/10)%10);
	switch(Ws){
	  case 0:{
	  unsigned char hexdate121[12] = {0x55,0x07,0x05,0x01,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB0};
	  Serial2.write(hexdate121,12);
	  delay(1);
	  }     
	  break;
     
	  case 1:{
	  unsigned char hexdate122[12] = {0x55,0x07,0x05,0x01,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB1};
	  Serial2.write(hexdate122,12);
	  delay(1);
	  }     
	  break;     
     
	  case 2:{
	  unsigned char hexdate123[12] = {0x55,0x07,0x05,0x01,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB2};
	  Serial2.write(hexdate123,12);
	  delay(1);
	  }     
	  break;     
     
	  case 3:{
	  unsigned char hexdate124[12] = {0x55,0x07,0x05,0x01,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB3};
	  Serial2.write(hexdate124,12);
	  delay(1);
	  }     
	  break;     
     
	  case 4:{
	  unsigned char hexdate125[12] = {0x55,0x07,0x05,0x01,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB4};
	  Serial2.write(hexdate125,12);
	  delay(1);
	  }     
	  break;     
     
	  case 5:{
	  unsigned char hexdate126[12] = {0x55,0x07,0x05,0x01,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB5};
	  Serial2.write(hexdate126,12);
	  delay(1);
	  }     
	  break;     
     
	  case 6:{
	  unsigned char hexdate127[12] = {0x55,0x07,0x05,0x01,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB6};
	  Serial2.write(hexdate127,12);
	  delay(1);
	  }     
	  break;     
     
	  case 7:{
	  unsigned char hexdate128[12] = {0x55,0x07,0x05,0x01,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB7};
	  Serial2.write(hexdate128,12);
	  delay(1);
	  }     
	  break;     
     
	  case 8:{
	  unsigned char hexdate129[12] = {0x55,0x07,0x05,0x01,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB8};
	  Serial2.write(hexdate129,12);
	  delay(1);
	  }     
	  break;     
     
	  case 9:{
	  unsigned char hexdate1291[12] = {0x55,0x07,0x05,0x01,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB9};
	  Serial2.write(hexdate1291,12);
	  delay(1);
	  }     
	  break;     
	  default:
	  break;
	  }
     
	Wg = (W%10);
	switch(Wg){
	  case 0:{
	  unsigned char hexdate1101[12] = {0x55,0x07,0x05,0x02,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB0};
	  Serial2.write(hexdate1101,12);
	  delay(1);
	  }     
	  break;
     
	  case 1:{
	  unsigned char hexdate1111[12] = {0x55,0x07,0x05,0x02,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB1};
	  Serial2.write(hexdate1111,12);
	  delay(1);
	  }     
	  break;     
     
	  case 2:{
	  unsigned char hexdate1121[12] = {0x55,0x07,0x05,0x02,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB2};
	  Serial2.write(hexdate1121,12);
	  }     
	  break;     
     
	  case 3:{
	  unsigned char hexdate1131[12] = {0x55,0x07,0x05,0x02,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB3};
	  Serial2.write(hexdate1131,12);
	  delay(1);
	  }     
	  break;     
     
	  case 4:{
	  unsigned char hexdate1141[12] = {0x55,0x07,0x05,0x02,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB4};
	  Serial2.write(hexdate1141,12);
	  delay(1);
	  }     
	  break;     
     
	  case 5:{
	  unsigned char hexdate1151[12] = {0x55,0x07,0x05,0x02,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB5};
	  Serial2.write(hexdate1151,12);
	  delay(1);
	  }     
	  break;     
     
	  case 6:{
	  unsigned char hexdate1161[12] = {0x55,0x07,0x05,0x02,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB6};
	  Serial2.write(hexdate1161,12);
	  delay(1);
	  }     
	  break;     
     
	  case 7:{
	  unsigned char hexdate1171[12] = {0x55,0x07,0x05,0x02,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB7};
	  Serial2.write(hexdate1171,12);
	  delay(1);
	  }     
	  break;     
     
	  case 8:{
	  unsigned char hexdate1181[12] = {0x55,0x07,0x05,0x02,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB8};
	  Serial2.write(hexdate1181,12);
	  delay(1);
	  }     
	  break;     
     
	  case 9:{
	  unsigned char hexdate1191[12] = {0x55,0x07,0x05,0x02,0x00,
	  0x55,0x31,0x01,0x01,0x00,0xA3,0xB9};
	  Serial2.write(hexdate1191,12);
	  delay(1);
	  }     
	  break;     
	  default:
	  break;
	  }*/
     
 
	Serial1.print(0x31, HEX);
	delay(3);
	for (int i = 0; i < 2; i++) {
		Hsq = Serial1.read();
	}
	Hsq = (Hsq + Hsq);
	if (Hsq < 0) {
		Hsq = 0;
	}
     
	Hb = Serial1.read();
	Hb = (Hb - 48);
	switch (Hb) {
	case 0: {
			unsigned char hexdate130[12] = {
				 0x55,
				 0x07,
				 0x03,
				0x04,
				 0x00,
				 0x55,
				 0x31,
				 0x01,
				 0x01, 
				0x00,
				 0xA3, 
				0xB0 
			};
			Serial2.write(hexdate130, 12);
			delay(1);
		}
		break;    
     
	case 1: {
			unsigned char hexdate131[12] = {
				 0x55, 
				0x07,
				 0x03,
				0x04, 
				0x00, 
				0x55, 
				0x31,
				 0x01, 
				0x01,
				 0x00, 
				0xA3, 
				0xB1 
			};
			Serial2.write(hexdate131, 12);
			delay(1);
		} 
		break;
             
     
	case 2: {
			unsigned char hexdate132[12] = {
				 0x55, 
				0x07, 
				0x03,
				0x04, 
				0x00,
				 0x55,
				 0x31, 
				0x01, 
				0x01,
				 0x00,
				 0xA3, 
				0xB2
			 };
			Serial2.write(hexdate132, 12);
			delay(1);
		} 
		break;
              
	case 3: {
			unsigned char hexdate129[12] = { 
				0x55, 
				0x07,
				 0x03,
				0x04,
				 0x00, 
				0x55,
				 0x31,
				 0x01,
				 0x01, 
				0x00,
				 0xA3,
				 0xB3 
			};
			Serial2.write(hexdate129, 12);
			delay(1);
		}
		break; 
	}
      
	Hs = Serial1.read();
	Hs = (Hs - 48);
	switch (Hs) {
	case 0: {
			unsigned char hexdate133[12] = { 
				0x55,
				 0x07,
				 0x03,
				0x05, 
				0x00, 
				0x55, 
				0x31,
				 0x01, 
				0x01, 
				0x00, 
				0xA3,
				 0xB0
			 };
			Serial2.write(hexdate133, 12);
			delay(1);
		}
		break;
                  
            
	case 1: {
			unsigned char hexdate134[12] = {
				 0x55,
				 0x07,
				 0x03,
				0x05,
				 0x00, 
				0x55,
				 0x31,
				 0x01,
				 0x01,
				 0x00, 
				0xA3,
				 0xB1 
			};
			Serial2.write(hexdate134, 12);
			delay(1);
		}
		break;
                     
        
	case 2: {
			unsigned char hexdate136[12] = {
				 0x55, 
				0x07,
				 0x03,
				0x05,
				 0x00, 
				0x55, 
				0x31,
				 0x01,
				 0x01, 
				0x00,
				 0xA3,
				 0xB2
			 };
			Serial2.write(hexdate136, 12);
			delay(1);
		}
		break;
               
       
	case 3: {
			unsigned char hexdate137[12] = { 
				0x55, 
				0x07,
				 0x03,
				0x05,
				 0x00, 
				0x55, 
				0x31, 
				0x01, 
				0x01,
				 0x00, 
				0xA3,
				 0xB3
			 };
			Serial2.write(hexdate137, 12);
			delay(1);
		}
		break;
                
        
	case 4: {
			unsigned char hexdate138[12] = { 
				0x55, 
				0x07,
				 0x03,
				0x05,
				 0x00,
				 0x55, 
				0x31,
				 0x01,
				 0x01,
				 0x00, 
				0xA3,
				 0xB4 
			};
			Serial2.write(hexdate138, 12);
			delay(1);
		}
		break;
                
        
	case 5: {
			unsigned char hexdate139[12] = {
				 0x55, 
				0x07,
				 0x03,
				0x05,
				 0x00,
				 0x55, 
				0x31,
				 0x01, 
				0x01, 
				0x00,
				 0xA3, 
				0xB5
			 };
			Serial2.write(hexdate139, 12);
			delay(1);
		}
		break;
                
        
	case 6: {
			unsigned char hexdate140[12] = {
				 0x55,
				 0x07, 
				0x03,
				0x05,
				 0x00, 
				0x55, 
				0x31, 
				0x01, 
				0x01, 
				0x00,
				 0xA3,
				 0xB6 
			};
			Serial2.write(hexdate140, 12);
			delay(1);
		}
		break;
                
        
	case 7: {
			unsigned char hexdate141[12] = {
				 0x55,
				 0x07, 
				0x03,
				0x05,
				 0x00,
				 0x55,
				 0x31,
				 0x01,
				 0x01,
				 0x00,
				 0xA3,
				 0xB7
			 };
			Serial2.write(hexdate141, 12);
			delay(1);
		}
		break;
                
        
	case 8: {
			unsigned char hexdate142[12] = {
				 0x55, 
				0x07, 
				0x03,
				0x05, 
				0x00, 
				0x55,
				 0x31,
				 0x01,
				 0x01, 
				0x00,
				 0xA3, 
				0xB8
			 };
			Serial2.write(hexdate142, 12);
			delay(1);
		}
		break;
                
        
	case 9: {
			unsigned char hexdate143[12] = { 
				0x55,
				 0x07,
				 0x03,
				0x05,
				 0x00, 
				0x55,
				 0x31, 
				0x01,
				 0x01, 
				0x00,
				 0xA3,
				 0xB9 
			};
			Serial2.write(hexdate143, 12);
			delay(1);
		}
		break;        
	}
      
	Hg = Serial1.read();
	Hg = (Hg - 48);
	switch (Hg) {
	case 0: {
			unsigned char hexdate144[12] = {
				 0x55,
				 0x07, 
				0x03,
				0x06,
				 0x00,
				 0x55,
				 0x31,
				 0x01,
				 0x01, 
				0x00,
				 0xA3,
				 0xB0
			 };
			Serial2.write(hexdate144, 12);
			delay(1);
		}
		break;
                  
            
	case 1: {
			unsigned char hexdate145[12] = {
				 0x55, 
				0x07,
				 0x03, 
				0x06,
				 0x00,
				 0x55,
				 0x31, 
				0x01, 
				0x01, 
				0x00,
				 0xA3, 
				0xB1
			 };
			Serial2.write(hexdate145, 12);
			delay(1);
		}
		break;
                     
        
	case 2: {
			unsigned char hexdate146[12] = {
				 0x55,
				 0x07, 
				0x03,
				0x06, 
				0x00,
				 0x55, 
				0x31,
				 0x01,
				 0x01,
				 0x00,
				 0xA3, 
				0xB2 
			};
			Serial2.write(hexdate146, 12);
			delay(1);
		}
		break;
                       
       
	case 3: {
			unsigned char hexdate147[12] = {
				 0x55,
				 0x07, 
				0x03,
				0x06, 
				0x00, 
				0x55,
				 0x31,
				 0x01,
				 0x01, 
				0x00, 
				0xA3, 
				0xB3 
			};
			Serial2.write(hexdate147, 12);
			delay(1);
		}
		break;
                
        
	case 4: {
			unsigned char hexdate148[12] = {
				 0x55, 
				0x07, 
				0x03,
				0x06, 
				0x00,
				 0x55,
				 0x31, 
				0x01,
				 0x01,
				 0x00, 
				0xA3,
				 0xB4 
			};
			Serial2.write(hexdate148, 12);
			delay(1);
		}
		break;
                
        
	case 5: {
			unsigned char hexdate150[12] = { 
				0x55,
				 0x07,
				 0x03,
				0x06,
				 0x00,
				 0x55, 
				0x31, 
				0x01,
				 0x01,
				 0x00,
				 0xA3,
				 0xB5
			 };
			Serial2.write(hexdate150, 12);
			delay(1);
		}
		break;
                
        
	case 6: {
			unsigned char hexdate151[12] = {
				 0x55,
				 0x07,
				 0x03,
				0x06, 
				0x00, 
				0x55,
				 0x31,
				 0x01,
				 0x01,
				 0x00, 
				0xA3, 
				0xB6 
			};
			Serial2.write(hexdate151, 12);
			delay(1);
		}
		break;
                
        
	case 7: {
			unsigned char hexdate152[12] = {
				 0x55, 
				0x07,
				 0x03,
				0x06,
				 0x00,
				 0x55, 
				0x31, 
				0x01,
				 0x01, 
				0x00, 
				0xA3,
				 0xB7 
			};
			Serial2.write(hexdate152, 12);
			delay(1);
		}
		break;
                
        
	case 8: {
			unsigned char hexdate153[12] = {
				 0x55,
				 0x07,
				 0x03,
				0x06,
				 0x00, 
				0x55, 
				0x31,
				 0x01,
				 0x01, 
				0x00,
				 0xA3,
				 0xB8 
			};
			Serial2.write(hexdate153, 12);
			delay(1);
		}
		break;
                
        
	case 9: {
			unsigned char hexdate154[12] = {
				 0x55,
				 0x07,
				 0x03,
				0x06, 
				0x00, 
				0x55, 
				0x31,
				 0x01,
				 0x01,
				 0x00,
				 0xA3, 
				0xB9 
			};
			Serial2.write(hexdate154, 12);
			delay(1);
		}
		break;            
	}
     
	for (int i = 0; i < 3; i++) {
		Hsq = Serial1.read();
	}
	Hsq = (Hsq + Hsq + Hsq);
	if (Hsq < 0) {
		Hsq = 0;
	} 
	delay(1);
	Serial1.flush();
	delay(1);
   
   
   
   
	if (Serial3.available() > 0) {
		int index = 0;
		delay(75);
		int numChar = Serial3.available();
		if (numChar > 72) {
			numChar = 72;
		}
		while (numChar--) {
			buffer[index++] = Serial3.read();
		}
		splitString(buffer);
	}
}
 
void splitString(char* date) {
	char* parameter;
	parameter = strtok(date, ",");
	while (parameter != NULL) {
		setMOTOR(parameter);
		parameter = strtok(NULL, ",");
	}
	for (int x = 0; x < 73; x++) {
		buffer[x] = '\0';
	}
	Serial3.flush();
} 
  
void setMOTOR(char* date) {

 
	if ((date[0] == 'a') || (date[0] == 'A')) {
		int Ans = strtol(date + 1, NULL, 10);
		if ((Ans >= 100) && (Ans <= 280)) {
			Ans = (Ans - 100);
			Ans = map(Ans, 0, 180, 10, 170);
   
			if ((Ans >= 85) &&(Ans <= 95)) {
				myservo2.write(90);
			}
			else {
				myservo2.write(Ans);
			}
		}
	}
    
   
   
	if ((date[0] == 'b') || (date[0] == 'B')) {
		int Ans = strtol(date + 1, NULL, 10);
		if ((Ans >= 100) && (Ans <= 280)) {
			Ans = (Ans - 100);
			Ans = map(Ans, 0, 180, 10, 170);
			if ((Ans >= 85) &&(Ans <= 95)) {
				myservo3.write(90);
			}
			else {
				myservo3.write(Ans);
			}
		}
	}
     
	if ((date[0] == 'c') || (date[0] == 'C')) {
		int Ans = strtol(date + 1, NULL, 10);
		if ((Ans >= 100) && (Ans <= 280)) {
			Ans = (Ans - 100);
			Ans = map(Ans, 0, 180, 20, 160);
			if ((Ans >= 85) &&(Ans <= 95)) {
				myservo4.write(90);
			}
			else {
				myservo4.write(Ans);
			}
		}
	}
    
	if ((date[0] == 'd') || (date[0] == 'D')) {
		int Ans1 = strtol(date + 1, NULL, 10);
		if ((Ans1 >= 100) && (Ans1 <= 280)) {
			Ans1 = (Ans1 - 100);
			Ans1 = map(Ans1, 0, 180, 10, 170);
			myservo5.write(Ans1);
		}
     
	}  
 
	if ((date[0] == 'e') || (date[0] == 'E')) {
		int Ans2 = strtol(date + 1, NULL, 10);
		if ((Ans2 >= 100) && (Ans2 <= 280)) {
			Ans2 = (Ans2 - 100);
			Ans2 = map(Ans2, 0, 180, 45, 118);
			myservo6.write(Ans2);
                                          
		}          
	}  
    
	if ((date[0] == 'h') || (date[0] == 'H')) {
		int Ans = strtol(date + 1, NULL, 10);
		if ((Ans >= 100) && (Ans <= 280)) {
			Ans = (Ans - 100);
			val = map(Ans, 0, 180, 0, 255);
			analogWrite(ledPin, val);
		}
	}  
} 

