/*
  Picobot2.cpp - Library for basic functionality of Picobot2
  Created by Gareth Davies, 4tronix, November 2015
  Released into the public domain
  ---
  Supports the following features:
  Motors: Forward, Reverse, Brake, Coast, Spin, Turn
  Line sensors: Read analog value
  Light sensors: Read analog value
  Ultrasonic: Get distance to nearest object
  Mode switch: Read boolean value (true == pressed)
  RGB Pixels: Set brightness, All off, All set RGB, Individual off, Individual set RGB
  ---
  Bluetooth and ESP8266 not supported within this library
*/

#include "Picobot2.h"

// Constructor
Picobot2::Picobot2()
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
}

// Motor functions
void Picobot2::forward(int speed)
{
	analogWrite(LMB, 255-speed);
	analogWrite(RMB, 255-speed);
	digitalWrite(LMA, HIGH);
	digitalWrite(RMA, HIGH);
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
		digitalWrite(LMB, HIGH);
		digitalWrite(RMB, HIGH);
		digitalWrite(LMA, HIGH);
		digitalWrite(RMA, HIGH);
	}
	else
		{
		digitalWrite(LMB, LOW);
		digitalWrite(RMB, LOW);
		digitalWrite(LMA, LOW);
		digitalWrite(RMA, LOW);
	}
}

void Picobot2::spinLeft(int speed)
{
	analogWrite(LMB, speed);
	analogWrite(RMB, 255-speed);
	digitalWrite(LMA, LOW);
	digitalWrite(RMA, HIGH);
}

void Picobot2::spinRight(int speed)
{
	analogWrite(LMB, 255-speed);
	analogWrite(RMB, speed);
	digitalWrite(LMA, HIGH);
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
byte Picobot2::lineRead(bool left)
{
	if (left)
		return analogRead(leftLine);
	else
		return analogRead(rightLine);
}

byte Picobot2::lightRead(bool left)
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

	rval = duration / 29 / 2;
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

