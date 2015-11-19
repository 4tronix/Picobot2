// Picobot Ultrasonic Test
// This code is designed for the 4tronix Picobot2
// Using an HC-SR04 Ultrasonic Sensor
// Reads the distance in cm and porints it to the serial monitor
//
// Purpose: Demonstrate use of the ultrasonic sensor 
//
// This example code is licensed under CC-BY-SA https://creativecommons.org/licenses/by-sa/3.0/

#include "Picobot2.h"
Picobot2 pb2;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  int cm;
  cm = pb2.distanceRead();
  Serial.println(cm);
  delay(1000);
}





