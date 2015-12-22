///////////////////////////////////////////////////////////////////////////////////////////
//
// Testing the LEDs on Picobot2
// Sets Red, Green, Blue, White in turn
//    
///////////////////////////////////////////////////////////////////////////////////////////

#include "Picobot2.h"

Picobot2 pb2;  // create a Picobot2 object to work with

// This function sets up the leds and tells the controller about them
void setup()
{
  pb2.begin();  // initialise the Picobot2
}

int wait = 800; // This is the delay in ms between LED colour changes

// This function runs over and over, and is where you do the magic to light your leds.
void loop()
{
  pb2.pixelAllOff();
  delay(wait);
  pb2.pixelAllSet(CRGB(255,0,0));
  delay(wait);
  pb2.pixelAllSet(CRGB(0,255,0));
  delay(wait);
  pb2.pixelAllSet(CRGB(0,0,255));
  delay(wait);
  pb2.pixelAllSet(CRGB(255,255,255));
  delay(wait);
}


