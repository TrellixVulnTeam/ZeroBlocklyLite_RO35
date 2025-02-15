#include <Wire.h>
#include <BeatleSerial.h>
#include "MPU9250.h"

MPU9250 mpu;

BeatleSerial bSerial;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;



void MPU9250setup() 
{
  Serial.begin(115200);

  Wire.begin();

  delay(2000);
  mpu.setup();
    

  

}

void MPU9250loop()
{
  static uint32_t prev_ms = millis();
    if ((millis() - prev_ms) > 16)
    {
        mpu.update();
        //mpu.print();
        roll = mpu.getRoll();
        pitch = mpu.getPitch();
        yaw = mpu.getYaw();
        Serial.print("roll  (x-forward (north)) : ");
        Serial.println(roll);
        Serial.print("pitch (y-right (east))    : ");
        Serial.println(pitch);
        Serial.print("yaw   (z-down (down))     : ");
        Serial.println(yaw);

        prev_ms = millis();
    }



  if ( yaw <= 1 && yaw >= -1 ) {   // you can increse the range to suit your sensor's accuracy
       bSerial.setSpeeds(0, 0);
  }
  else {
    if ( yaw < -1 ) {
        bSerial.setSpeeds(-100, 100);
  }

  else {
        bSerial.setSpeeds(100, -100);
  }
    
  }
}
