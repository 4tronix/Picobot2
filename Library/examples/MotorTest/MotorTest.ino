// Very simple test of the motors with Picobot2
// Demonstrates a few of the available motor commands

#include "Picobot2.h"

Picobot2 pb2;  // create a Picobot2 object to work with

void setup()
{
  pb2.begin();  // initialise the Picobot2
}


void loop()
{
  pb2.setBlueLED(ON); 
  pb2.forward(200); // Go in a straight line forward at speed 120 (max speed is 255)
  delay(1000);
  pb2.setBlueLED(OFF);
  pb2.stop(false); // Stop - Coast to a halt (not Brake)
  delay(1000);
  
  pb2.setBlueLED(ON);
  pb2.reverse(100);
  delay(1000);
  pb2.setBlueLED(OFF);
  pb2.stop(false); // Stop - Coast to a halt (not Brake)
  delay(500);
  
  pb2.setBlueLED(ON);
  pb2.spinLeft(100);
  delay(1000);
  pb2.setBlueLED(OFF);
  pb2.stop(true); // Stop - Brake immediately
  delay(500);
  
  pb2.setBlueLED(ON);
  pb2.spinRight(100);
  delay(1000);
  pb2.setBlueLED(OFF);
  pb2.stop(true); // Stop - Brake immediately
  delay(500);
  
  pb2.setBlueLED(ON);
  pb2.turnForward(100, 200);
  delay(1000);
  pb2.setBlueLED(OFF);
  pb2.stop(true); // Stop - Brake immediately
  delay(500);
  
  pb2.setBlueLED(ON);
  pb2.turnReverse(100, 200);
  delay(1000);
  pb2.setBlueLED(OFF);
  pb2.stop(true); // Stop - Brake immediately
  delay(500);
}
