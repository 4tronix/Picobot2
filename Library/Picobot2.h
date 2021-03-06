/*
  Picobot2.h - Library for basic functionality of Picobot2
  Created by Gareth Davies, 4tronix, December 2015
  Valid for version Picobot2 1.0 onwards
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
  Accelerometer (Not Supported): Read X, Y, Z; check Tap and Shake
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
#define LMA 6
#define LMB 10
#define RMA 9
#define RMB 5

// Left and Right Line Sensors (Analog)
#define leftLine A7
#define rightLine A6

// Left and Right Light Sensors (Analog)
#define leftLight A0
#define rightLight A1

// Ultrasonic Ping and Echo pins
#define sonicPing A2
#define sonicEcho A3

// Mode Button
#define button 7

// RGB Pixels
#define pixels 4
#define ledCount 2
#define initialBrightness 40

// Blue LED
#define blueLED 13

// Accelerometer
/* --- No Accelerometer in v1.0
#define accelI2C 0x4C
#define regXOUT	0x00	// x output data 6-bits
#define regYOUT 0x01 // y output data 6-bits
#define regZOUT 0x02 // z output data 6-bits
#define regTILT	0x03 // Tilt status
#define regSRST 0x04 // Sampling rate status
#define regSPCNT 0x05 // Sleep count
#define regINTSU 0x06 // Interrupt setup
#define regMODE 0x07 // Mode register
#define regSR  0x08 // Autowake, portrait/landscape, filters
#define regPDET 0x09 // Tap detection
#define regPD 0x0A // Tap debounce count
--- */

class Picobot2
{
  public:
    Picobot2 ();
	void begin();
	void forward(int speed);
	void reverse(int speed);
	void stop(bool brake);
	void spinLeft(int speed);
	void spinRight(int speed);
	void turnForward(int speedLeft, int speedRight);
	void turnReverse(int speedLeft, int speedRight);

	int lineRead(bool left);
	int lightRead(bool left);

	bool buttonRead();
	int distanceRead();

	void pixelBrightness(byte brightness);
	void pixelOff(byte pixelNo);
	void pixelSet(byte pixelNo, CRGB colour);
	void pixelAllOff();
	void pixelAllSet(CRGB colour);
	void setBlueLED(bool LEDon);

	//void accelRead(int *x, int *y, int *z);
	//bool tapRead();
  private:
	CRGB leds[ledCount];
	//void accelWrite(byte reg, byte data);
};

#endif