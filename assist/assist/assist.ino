#include <CommunicationUtils.h>
#include <DebugUtils.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <FreeSixIMU.h>
#include <DFRobot_BMP280.h>
#include <DFRobot_QMC5883.h>
#include <Wire.h>

char SendString[33]="$0:0:0:0:0:0:000:000:000:000:000%";

float postureangles[3]; // yaw pitch roll
int AngleInt[3];
int TemInt;
int DEInt;
char WaterFlag[2]={0};
char HitFlag[4]={0};
DFRobot_QMC5883 compass;
// Set the FreeSixIMU object
FreeSixIMU sixDOF = FreeSixIMU();
DFRobot_BMP280 bmp;


void setup() 
{ 
  delay(6000);
  Serial.begin(9600);
  Wire.begin();
  delay(5);
  sixDOF.init(); //begin the IMU
  delay(5);
  while (!compass.begin())
  {
    delay(500);
  }
    if(compass.isHMC()){
        compass.setRange(HMC5883L_RANGE_1_3GA);
        compass.setMeasurementMode(HMC5883L_CONTINOUS);
        compass.setDataRate(HMC5883L_DATARATE_15HZ);
        compass.setSamples(HMC5883L_SAMPLES_8);
    }
   else if(compass.isQMC()){
        compass.setRange(QMC5883_RANGE_2GA);
        compass.setMeasurementMode(QMC5883_CONTINOUS); 
        compass.setDataRate(QMC5883_DATARATE_50HZ);
        compass.setSamples(QMC5883_SAMPLES_8);
   }
   while (!bmp.begin()) {  
    Serial.println("Error initializing BMP280!");
    delay(1000);
  }
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
}

void loop() { 

  WaterFlag[0]=digitalRead(2);
  int a3=analogRead(A3);
  float water2=(float)a3*(5 / 1024.0);
  HitFlag[0]=digitalRead(4);
  HitFlag[1]=digitalRead(5);
  HitFlag[2]=digitalRead(6);
  HitFlag[3]=digitalRead(7);

  if(water2>=1.5)
  {
    WaterFlag[1]=1;
  }
  else
  {
    WaterFlag[1]=0;
  }

  
   Vector norm = compass.readNormalize();

  // Calculate heading
  float heading = atan2(norm.YAxis, norm.XAxis);

  // Set declination angle on your location and fix heading
  // You can find your declination on: http://magnetic-declination.com/
  // (+) Positive or (-) for negative
  // For Bytom / Poland declination angle is 4'26E (positive)
  // Formula: (deg + (min / 60.0)) / (180 / PI);
  float declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / PI);
  heading += declinationAngle;

  // Correct for heading < 0deg and heading > 360deg
  if (heading < 0){
    heading += 2 * PI;
  }

  if (heading > 2 * PI){
    heading -= 2 * PI;
  }

  // Convert to degrees
  float headingDegrees = heading * 180/PI; 
  float Temperature=bmp.readTemperatureValue();
  DEInt=(int)headingDegrees;
  TemInt=(int)Temperature;
  sixDOF.getEuler(postureangles);
  for(int i=0;i<3;++i)
  {
    if(postureangles[i]<0)
    {
      postureangles[i]+=360;
    }
    AngleInt[i]=postureangles[i];
  }
  SendString[1]=WaterFlag[0]+'0';
  SendString[3]=WaterFlag[1]+'0';
  SendString[5]=HitFlag[0]+'0';
  SendString[7]=HitFlag[1]+'0';
  SendString[9]=HitFlag[2]+'0';
  SendString[11]=HitFlag[3]+'0';
  SendString[13]=(DEInt/100)+'0';
  DEInt%=100;
  SendString[14]=(DEInt/10)+'0';
  SendString[15]=(DEInt%10)+'0';
  SendString[17]=(TemInt/100)+'0';
  TemInt%=100;
  SendString[18]=(TemInt/10)+'0';
  SendString[19]=(TemInt%10)+'0';
  SendString[21]=(AngleInt[0]/100)+'0';
  AngleInt[0]%=100;
  SendString[22]=(AngleInt[0]/10)+'0';
  SendString[23]=(AngleInt[0]%10)+'0';
  SendString[25]=(AngleInt[1]/100)+'0';
  AngleInt[1]%=100;
  SendString[26]=(AngleInt[1]/10)+'0';
  SendString[27]=(AngleInt[1]%10)+'0';
  SendString[29]=(AngleInt[2]/100)+'0';
  AngleInt[2]%=100;
  SendString[30]=(AngleInt[2]/10)+'0';
  SendString[31]=(AngleInt[2]%10)+'0';
  Serial.print(SendString);
  delay(90);   
}
