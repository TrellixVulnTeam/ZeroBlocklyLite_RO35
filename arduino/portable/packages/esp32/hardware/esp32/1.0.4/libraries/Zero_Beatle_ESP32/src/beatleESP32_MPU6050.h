#include <Wire.h>
#include <MPU6050.h>
#include <BeatleSerial.h>


BeatleSerial bSerial;
MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;


void MPU6050setup() 
{
  Serial.begin(115200);

  //pinMode(DSL,INPUT);
  //pinMode(DSR,INPUT);
  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(3);

}

void MPU6050loop()
{
  timer = millis();

  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Pitch, Roll and Yaw
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;

  // Output raw
  Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.print(roll);  
  Serial.print(" Yaw = ");
  Serial.println(yaw);

  // Wait to full timeStep period
  delay((timeStep*1000) - (millis() - timer));

  if ( yaw <= 3 && yaw >= -3 ) {   // you can increse the range to suit your sensor's accuracy
       bSerial.setSpeeds(0, 0);
  }
  else {
    if ( yaw < -3 ) {
        bSerial.setSpeeds(-100, 100);
  }

  else {
        bSerial.setSpeeds(100, -100);
  }
    
  }
}
