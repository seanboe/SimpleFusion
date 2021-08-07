// ******************************************************
// An example of the SimpleFusion library that combines
// accelerometer and gyroscope data quickly and easily.
//
// This example uses the mpu6050 6-dof IMU and the 
// Adafruit library for it.
//
// Created in 2021 by Sean Boerhout under the MIT License
// ******************************************************


#include <simpleFusion.h>     // If you've used the "include library" tool, you'll need to use '<[library]>'

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

SimpleFusion fuser;               // Initialize the SimpleFusion object
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  while(!Serial)
    ;
  
  fuser.init(100, 0.98, 0.98);    // Initialize the fusion object with the filter update rate (hertz) and 

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
    delay(10);
  }
  
}

void loop() {

  if (fuser.shouldUpdateData()) {

    FusedAngles fusedAngles;        // Variable to store the output
    
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    
    ThreeAxis accelerometer;                  // Please verify that the units are in meters / second ^ 2
    accelerometer.x = a.acceleration.x;
    accelerometer.y = a.acceleration.y;
    accelerometer.z = a.acceleration.z;
  
    ThreeAxis gyroscope;                      // Please verify that the units are in raidans / second
    gyroscope.x = g.gyro.x;
    gyroscope.y = g.gyro.y;
    gyroscope.z = g.gyro.z;
    
    fuser.getFilteredAngles(accelerometer, gyroscope, &fusedAngles, UNIT_DEGREES);    // Fuse the angles

    Serial.print(" Pitch: ");
    Serial.print(fusedAngles.pitch);
    Serial.print(" Roll : ");
    Serial.println(fusedAngles.roll);
  }
  
}
