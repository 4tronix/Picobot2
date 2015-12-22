/*
  Picobot2.h - Library for basic functionality of Picobot2
  Created by Gareth Davies, 4tronix, November 2015
  Released into the public domain
  ---
  Supports the following features:
  Motors: Forward, Reverse, Brake, Coast, Spin, Turn
  Line sensors: Read analog value
  Light sensors: Read analog value
  Ultrasonic: Get distance to nearest object
  Mode switch: Read digital value
  RGB Pixels: Set brightness, All off, All set RGB, Individual off, Individual set RGB
  Blue LED: On, Off
  ---
  Bluetooth and ESP8266 not supported within this library
*/

#ifndef Picobot2_h
#define Picobot2_h

#include "Arduino.h"
#include "FastLED.h"

// Map ON and OFF to true and false
#define ON true
#define OFF false

// Left and Right Motor pins (Digital, PWM). A & B for each
#define LMA 4
#define LMB 5
#define RMA 7
#define RMB 6

// Left and Right Line Sensors (Analog)
#define leftLine A7
#define rightLine A6

// Left and Right Light Sensors (Analog)
#define leftLight A0
#define rightLight A1

// Ultrasonic Ping and Echo pins
#define sonicPing A4
#define sonicEcho A5

// Mode Button
#define button 10

// RGB Pixels
#define pixels 9
#define ledCount 2
#define initialBrightness 40

// Blue LED
#define blueLED 13

class Picobot2
{
  public:
    Picobot2 ();

	void forward(int speed);
	void reverse(int speed);
	void stop(bool brake);
	void spinLeft(int speed);
	void spinRight(int speed);
	void turnForward(int speedLeft, int speedRight);
	void turnReverse(int speedLeft, int speedRight);

	byte lineRead(bool left);
	byte lightRead(bool left);

	bool buttonRead();
	int distanceRead();

	void pixelBrightness(byte brightness);
	void pixelOff(byte pixelNo);
	void pixelSet(byte pixelNo, CRGB colour);
	void pixelAllOff();
	void pixelAllSet(CRGB colour);
	void setBlueLED(bool LEDon);
  private:
	CRGB leds[ledCount];
};

#endif