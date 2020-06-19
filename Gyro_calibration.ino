// MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain
//A4-SDA
//A5-SCL
#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
double gyxangle=0;
int32_t GyXoffset=0;
unsigned long current_time=0;
unsigned long previous_time=0;
void setup(){
  Wire.begin();
   TWBR = 12;                                                                //Set the I2C clock speed to 400kHz
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
    Wire.beginTransmission(MPU_addr);                                     //Start communication with the address found during search.
  Wire.write(0x1B);                                                         //We want to write to the GYRO_CONFIG register (1B hex)
  Wire.write(0x00);                                                         //Set the register bits as 00000000 (250dps full scale)
  Wire.endTransmission(true);                                                   //End the transmission with the gyro
  //Set the full scale of the accelerometer to +/- 4g.
  Wire.beginTransmission(MPU_addr);                                     //Start communication with the address found during search.
  Wire.write(0x1C);                                                         //We want to write to the ACCEL_CONFIG register (1A hex)
  Wire.write(0x08);                                                         //Set the register bits as 00001000 (+/- 4g full scale range)
  Wire.endTransmission(true);                                                   //End the transmission with the gyro
 Serial.begin(115200);
 pinMode(13, OUTPUT);  
  //////////////////////////////////////////Calculating Offset//////////////////////////////////////////
  for(int i=0;i<100;i++)
  {if(i%10==0)digitalWrite(13,!digitalRead(13));
   Wire.beginTransmission(MPU_addr);
  Wire.write(0x43);  // starting with register 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,2, true);
  GyXoffset+=Wire.read()<<8|Wire.read();
  delayMicroseconds(5500);
  }
 GyXoffset=GyXoffset/100;
  //Serial.print("Offset = ");Serial.println(GyXoffset);
 
  
}
void loop(){
  
   ////////////////////////////////////////Reads all values///////////////////////////////////////
 /* Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  //Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  delay(333);*/
  ////////////////////////////////////////X axis values//////////////////////////////////////////////////
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x43);  // starting with register 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,2, true);
  GyX=Wire.read()<<8|Wire.read();
  GyX-=GyXoffset;
  //Serial.print(GyX);Serial.print("   ");    //corrected raw value from gyroscope
  //gyxangle+=GyX*0.00000611;    //assuming clock speed is 400kHz
  gyxangle+=GyX*0.000031;
  Serial.println(gyxangle);
  //Serial.print("   ");
  //current_time=micros();
  //Serial.println(current_time-previous_time);
  //previous_time=current_time;
  delayMicroseconds(3300);
  
  
  }
  
