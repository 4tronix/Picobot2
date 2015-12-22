// Picobot Ultrasonic Test
// This code is designed for the 4tronix Picobot2
// Using an HC-SR04 Ultrasonic Sensor
// Reads the distance in cm and sends the values to the serial port and the software serial port, so can be read via a Bluetooth BLE device (if Bluetooth is fitted on your Picobot2)
//
// Purpose: Demonstrate use of the ultrasonic sensor 
//
// This example code is licensed under CC-BY-SA https://creativecommons.org/licenses/by-sa/3.0/

#include "Picobot2.h"
Picobot2 pb2;

#include <SoftwareSerial.h>
SoftwareSerial BLE (2, 3); // RX, TX

// Initialise the serial libraries and Picobot2 libraries
void setup()
{
  pb2.begin();
  Serial.begin(115200); // You can change this baud rate to match the speed of the serial monitor
  BLE.begin(9600);  // the BLE module should be run at 9600 baud so don't change this
}

void loop()
{
  int cm;
  cm = pb2.distanceRead();
  String s = String(cm) + "cm";
  Serial.println(s);
  BLE.println(s);
  delay(1000);
  pb2.setBlueLED(ON);
  delay(100);
  pb2.setBlueLED(OFF);
}





