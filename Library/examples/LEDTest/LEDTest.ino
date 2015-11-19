///////////////////////////////////////////////////////////////////////////////////////////
//
// Testing the LEDs on Picobot2
// Sets Red, Green, Blue, White in turn on RGB and also the Blue LED
//    
///////////////////////////////////////////////////////////////////////////////////////////

// Picobot LED Demonstration
// This code is designed for the 4tronix Picobot2
// Sets Red, Green, Blue, White in turn
//
// Purpose: Demonstrate use of the lights in the library 
//
// This example code is licensed under CC-BY-SA https://creativecommons.org/licenses/by-sa/3.0/

#include "Picobot2.h"
Picobot2 pb2;

void setup()
{
  // Nothing needs setting up for this test
}

int wait = 500; // sets the speed of the flashing. The smaller the number, the faster it goes
int bright = 40;  // sets the brightness of the RGB LEDs (NB. This value is between 0 and 255 but max brightness is set by the pb2.setBrightness() method)

void loop()
{
  pb2.pixelAllSet(CRGB(bright, 0, 0));  // The pixelAllSet() function takes a CRGB type as an argument, This is created with three inputs for Red, Green and Blue levels
  delay(wait);
  pb2.pixelAllSet(CRGB(0, bright, 0));
  delay(wait);
  pb2.pixelAllSet(CRGB(0, 0, bright));
  delay(wait);
  pb2.pixelAllSet(CRGB(bright, bright, bright));  // set all colours on for White
  delay(wait);
  pb2.pixelAllOff();
  pb2.setBlueLED(ON);
  delay(wait);
  pb2.setBlueLED(OFF);
}


