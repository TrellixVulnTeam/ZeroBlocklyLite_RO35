/**
 * \par Copyright (C), 206, Zeroworkshop
 * \class   StarterProI2C
 * \brief   Driver for Starter Pro module.
 * @file    StarterProI2C.h
 * @author  Zeroworkshop
 * @version V1.0.0
 * @date    2019/05/8
 * @brief   Header for StarterProI2C.cpp module
 *
 * \par Copyright
 * This software is Copyright (C), 2016-2019, Zeroworkshop. Use is subject to license \n
 * conditions. The main licensing options available are GPL V2 or Commercial: \n
 *
 * \par Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your \n
 * application with everyone you distribute it to, and you also want to give them \n
 * the right to share who uses it. If you wish to use this software under Open \n
 * Source Licensing, you must contribute all your source code to the open source \n
 * community in accordance with the GPL Version 2 when your application is \n
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
*/
//#ifndef _ZEROBEATLE_FUNCTIONS_H_
//#define _ZEROBEATLE_FUNCTIONS_H_

#include <Wire.h>
#include <MPU6050.h>
#include "Beatle.h"

Beatle beatle;


MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;


void beatleKeepDirection_setup() {
	  Serial.begin(115200);

  pinMode(DSL,INPUT);
  pinMode(DSR,INPUT);
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

void beatleKeepDirection() {
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
       beatle.motors.setSpeeds(0, 0);
  }
  else {
    if ( yaw < -3 ) {
        beatle.motors.setSpeeds(-100, 100);
  }

  else {
        beatle.motors.setSpeeds(100, -100);
  }
    
  }
}