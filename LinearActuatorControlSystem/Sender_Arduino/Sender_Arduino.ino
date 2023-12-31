#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_MPU6050 mpu;

union Onion
{
    uint8_t     fBytes[sizeof( float )];
    float       fValue;
};
Onion flt;

void setup( void )
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
  while( !Serial );
  if (!mpu.begin()) 
  {
    digitalWrite(LED_BUILTIN,HIGH); //built in led high means the arduino failed to recognize the gyro
    while (1) 
    {
      delay(10);
    }
  }
  else  digitalWrite(LED_BUILTIN,LOW); //led low means gyro is connected properly
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_1000_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
    
}//setup

void loop( void )
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  flt.fValue = g.gyro.y;
  Sender();
  //delay(1000);
    
}//loop
void Sender()
{
  Serial.write( '>' );
  Serial.write( flt.fBytes, sizeof( float ) );
  Serial.write( '<' );
}
