#include <CommunicationUtils.h>
#include <DebugUtils.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <FreeSixIMU.h>
#include <DFRobot_BMP280.h>
#include <DFRobot_QMC5883.h>
#include <Wire.h>

char SendString[32]="0:0:0:0:0:0:000:000:000:000:000";

float postureangles[3]; // yaw pitch roll
int angles[3];
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
    Serial.println("Could not find a valid QMC5883 sensor, check wiring!");
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

  char water1=digitalRead(2);
  int a3=analogRead(A3);
  float water2=(float)a3*(5 / 1024.0);
  char hit1=digitalRead(4);
  char hit2=digitalRead(5);
  char hit3=digitalRead(6);
  char hit4=digitalRead(7);

  if(water1==1)
  {
    Serial.print("!8");
    water1=0;
  }
  if(water2>=2)
  {
    Serial.print("!9");
    water2=0;
  }
  if(hit1==1)
  {
    Serial.print("!1");
    hit1=0;
  }
  if(hit2==1)
  {
    Serial.print("!2");
    hit2=0;
  }
  if(hit3==1)
  {
    Serial.print("!3");
    hit3=0;
  }
  if(hit4==1)
  {
    Serial.print("!4");
    hit4=0;
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

  // Output
//  Serial.print("$HE");
//  if(heading<100)
//  {
//    Serial.print("0");
//    if(heading<10)
//    {
//      Serial.print("0");
//    }
//    
//  }
//  Serial.print(heading,0);
  Serial.print("$DE");
  if(headingDegrees<100)
  {
    Serial.print("0");
    if(headingDegrees<10)
    {
      Serial.print("0");
    }
    
  }
  Serial.println(headingDegrees,0);
  Serial.print("$TE");
  float Temperature=bmp.readTemperatureValue();
  if(Temperature<100)
  {
    Serial.print("0");
    if(Temperature<10)
    {
      Serial.print("0");
    }
    
  }
  Serial.print(Temperature,0);
  Serial.println();
  sixDOF.getEuler(postureangles);
  for(int i=0;i<3;++i)
  {
    if(postureangles[i]<0)
    {
      postureangles[i]+=360;
    }
  }
  Serial.print("$YA"); 
  if((postureangles[0])<100)
  {
    Serial.print("0");
    if((postureangles[0])<10)
    {
      Serial.print("0");
    }
    
  }
  Serial.print(postureangles[0],0);
  Serial.println();
  Serial.print("$PI"); 
  if((postureangles[1])<100)
  {
    Serial.print("0");
    if((postureangles[1])<10)
    {
      Serial.print("0");
    }
    
  }
  Serial.print(postureangles[1],0);
  Serial.println();
  Serial.print("$RO");
  if((postureangles[2])<100)
  {
    Serial.print("0");
    if((postureangles[2])<10)
    {
      Serial.print("0");
    }
    
  }
  Serial.print(postureangles[2],0);
  Serial.println();
  delay(90);   
}
