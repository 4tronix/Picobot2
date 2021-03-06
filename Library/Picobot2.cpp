/*
  Picobot2.cpp - Library for basic functionality of Picobot2
  Created by Gareth Davies, 4tronix, November 2015
  Valid for version Picobot2 0.4 onwards
  Released into the public domain
  ---
  Supports the following features:
  Motors: Forward, Reverse, Brake, Coast, Spin, Turn
  Line sensors: Read analog value
  Light sensors: Read analog value
  Ultrasonic: Get distance to nearest object
  Mode switch: Read boolean value (true == pressed)
  RGB Pixels: Set brightness, All off, All set RGB, Individual off, Individual set RGB
  Accelerometer (TBD): Read X, Y, Z; check Tap and Shake
  ---
  Bluetooth and ESP8266 not supported within this library
*/

#include "Picobot2.h"
#include <Wire.h>

// Constructor
Picobot2::Picobot2()
{
}

void Picobot2::begin()
{
	// set output pins
	pinMode(LMA, OUTPUT);
	pinMode(LMB, OUTPUT);
	pinMode(RMA, OUTPUT);
	pinMode(RMB, OUTPUT);
	pinMode(pixels, OUTPUT);
	pinMode(sonicPing, OUTPUT);
	pinMode(blueLED, OUTPUT);

	// add pullup to mode switch
	pinMode(button, INPUT_PULLUP);

	// Initialise RGB pixels
	FastLED.addLeds<WS2812B, pixels, RGB>(leds, ledCount);
	FastLED.setBrightness(initialBrightness);

	// Setup the accelerometer
	/* --- No accelerometer
	Wire.begin();
	accelWrite(regMODE, 0x00);	// set mode to standby so we can set up the registers
	accelWrite(regINTSU, 0x04);	// Set tap interrupt to enable
	accelWrite(regSR, 0x00);	// 120 samples per second and set Tap detection mode
	accelWrite(regMODE, 0x01);	// set mode to Active
	--- */
}

// Motor functions
void Picobot2::forward(int speed)
{
	analogWrite(LMA, speed);
	analogWrite(RMA, speed);
	digitalWrite(LMB, LOW);
	digitalWrite(RMB, LOW);
}

void Picobot2::reverse(int speed)
{
	analogWrite(LMB, speed);
	analogWrite(RMB, speed);
	digitalWrite(LMA, LOW);
	digitalWrite(RMA, LOW);
}

void Picobot2::stop(bool brake)
{
	if (brake)
	{
		digitalWrite(LMA, HIGH);
		digitalWrite(RMA, HIGH);
		digitalWrite(LMB, HIGH);
		digitalWrite(RMB, HIGH);
	}
	else
		{
		digitalWrite(LMA, LOW);
		digitalWrite(RMA, LOW);
		digitalWrite(LMB, LOW);
		digitalWrite(RMB, LOW);
	}
}

void Picobot2::spinLeft(int speed)
{
	analogWrite(LMB, speed);
	analogWrite(RMA, speed);
	digitalWrite(LMA, LOW);
	digitalWrite(RMB, LOW);
}

void Picobot2::spinRight(int speed)
{
	analogWrite(LMA, speed);
	analogWrite(RMB, speed);
	digitalWrite(LMB, LOW);
	digitalWrite(RMA, LOW);
}

void Picobot2::turnForward(int speedLeft, int speedRight)
{
	analogWrite(LMB, 255-speedLeft);
	analogWrite(RMB, 255-speedRight);
	digitalWrite(LMA, HIGH);
	digitalWrite(RMA, HIGH);
}

void Picobot2::turnReverse(int speedLeft, int speedRight)
{
	analogWrite(LMB, speedLeft);
	analogWrite(RMB, speedRight);
	digitalWrite(LMA, LOW);
	digitalWrite(RMA, LOW);
}
// End of Motor Functions

// Sensor Reading Functions
int Picobot2::lineRead(bool left)
{
	if (left)
		return analogRead(leftLine);
	else
		return analogRead(rightLine);
}

int Picobot2::lightRead(bool left)
{
	if (left)
		return analogRead(leftLight);
	else
		return analogRead(rightLight);
}

bool Picobot2::buttonRead()
{
	return (digitalRead(button) == HIGH);
}

int Picobot2::distanceRead()
{
	unsigned int rval;
	digitalWrite(sonicPing, LOW);
	delayMicroseconds(2);
	digitalWrite(sonicPing, HIGH);
	delayMicroseconds(5);
	digitalWrite(sonicPing, LOW);

	long duration = pulseIn(sonicEcho, HIGH);

	rval = duration / 29L / 2L;
	return rval;
}
// End of Sensor reading

// Pixel Functions
void Picobot2::pixelBrightness(byte brightness)
{
	FastLED.setBrightness(brightness);
	FastLED.show();
}

void Picobot2::pixelOff(byte pixelNo)
{
	if (pixelNo < ledCount)
	{
		leds[pixelNo] = 0;
		FastLED.show();
	}
}

void Picobot2::pixelSet(byte pixelNo, CRGB colour)
{
	if (pixelNo < ledCount)
	{
		leds[pixelNo].r = colour.g;
		leds[pixelNo].g = colour.r;
		leds[pixelNo].b = colour.b;
		FastLED.show();
	}
}

void Picobot2::pixelAllOff()
{
	for(int i = 0; i < ledCount; i++)
		leds[i] = 0;
	FastLED.show();
}

void Picobot2::pixelAllSet(CRGB colour)
{
	for(int i = 0; i < ledCount; i++)
	{
		leds[i].r = colour.g;
		leds[i].g = colour.r;
		leds[i].b = colour.b;
	}
	FastLED.show();
}

void Picobot2::setBlueLED(bool LEDon)
{
	if (LEDon)
		digitalWrite(blueLED, HIGH);
	else
		digitalWrite(blueLED, LOW);
}

/* --- No accelerometer
void Picobot2::accelWrite(byte reg, byte data)
{
	Wire.beginTransmission(accelI2C);
	Wire.write(reg);
	Wire.write(data);
	Wire.endTransmission();
}

void Picobot2::accelRead(int *x, int *y, int *z)
{
	Wire.beginTransmission(accelI2C);
	Wire.write(regXOUT);  // Start reading from x register
	Wire.endTransmission();
	Wire.requestFrom(accelI2C, 3); // read 3 consecutive registers
	if(Wire.available())
	{
		*x = Wire.read();
		*y = Wire.read();
		*z = Wire.read();
	}
	*x=((*x)<<2)/4;
	*y=((*y)<<2)/4;
	*z=((*z)<<2)/4;
}

bool Picobot2::tapRead()
{
	byte tap = 0;
	Wire.beginTransmission(accelI2C);
	Wire.write(regTILT);  // Start reading from x register
	Wire.endTransmission();
	Wire.requestFrom(accelI2C, 1); // read 1 byte
	if(Wire.available())
		tap = Wire.read();
	return ((tap & 0x20) == 0x20);
}

--- */